#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

const int J_sw = 12, J_x = A0, J_y = A1, MAX_ENEMIES = 1, MAX_BULLETS = 10;

const char level[] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
'P',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','E',' ',' ',' ',' ',' ',' ',' ','F'};
//" ,P, , , , ,E, , , ,W, , , , , , , , , , ,|, , , , , , , , ,E, , , , , , , , , , , , ",
//" , , , , , , , , , ,E, , , , , ,W, , , , ,|,P, , , , ,E, , , , , , , , , , , , , , , ",
//" , , , , ,W, , , , , , , , , , , , ,E, , ,|,P, ,W, , , , , , , , ,E, , , , , , , , , ",
//" ,P, , , ,E, , , , , , , , ,W, , ,E, , , ,|, , , , , , , , ,W, , , , , , , ,E, , , , "};

byte playerSprite[8] = {
  B00000,
  B00110,
  B01100,
  B01110,
  B01110,
  B01100,
  B00110,
  B00000
};

byte playerSprite2[8] = {
  B00000,
  B01100,
  B00110,
  B01110,
  B01110,
  B00110,
  B01100,
  B00000
};

byte enemySprite[8] = {
  B10001,
  B01010,
  B00100,
  B01110,
  B01110,
  B00100,
  B01010,
  B10001
};

byte wall[8] = {
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110
};

void initMap();
void drawMap();
int getInput(int pin);
bool doRandChance(int chance);

int curLevel = 0;
int mapWidth, mapHeight = 2;
char gameMap[2][40];
int gameState = 0;
int viewL = 0, viewR = 16;

struct Entity {
  int x, y, health, damage, sprite, dir, del;
  bool created, destroy;
  unsigned long lim = millis() + del * 1000;

  bool updatePos(int destX, int destY) {
    int newX = constrain(destX, 0, mapWidth - 1);
    int newY = constrain(destY, 0, mapHeight - 1);
    if (gameMap[newY][newX] == byte(1)) return false;
    gameMap[y][x] = ' ';
    x = newX;
    y = newY;
    gameMap[y][x] = byte(sprite);
    return true;
  }
};

struct Projectile : Entity {
  Projectile() {
    sprite = '-';
    del = 100;
    created = false;
    destroy = false;
  }
  
  void doLoop() {
    if (millis() >= lim) {
      updatePos(x + dir, y);
      if (x <= 0 || x >= mapWidth-1 || gameMap[y][x+dir] == byte(1)) {
        destroy = true;
      }
      lim = millis() + del;
    }
  }
};

Projectile bullets[MAX_BULLETS];

struct Player : Entity {
  Player() {
    x = 0;
    y = 1;
    health = 3;
    sprite = 0;
    dir = 1;
    del = 100;
    created = true;
    destroy = false;
  }
  
  void createBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
      if (!bullets[i].created) {
        bullets[i].created = true;
        bullets[i].x = x + dir;
        bullets[i].y = y;
        bullets[i].dir = dir;
        return;
      }
    }
  }
  
  void doLoop() {
    if (millis() >= lim) {
      int xInput = getInput(J_x);
      int yInput = getInput(J_y);
      if (xInput) {
        dir = xInput;
        if (xInput > 0) {
          sprite = 0;
        } else if (xInput < 0) {
          sprite = 3;
        }
      }
      updatePos(x + xInput, y + yInput);

      if (!digitalRead(J_sw)) {
        createBullet();
      }
      
      lim = millis() + del;
    }
  }
};

Player player;

struct Enemy : Entity {
  int originX, originY, state;

  Enemy() {
    originX = 14;
    originY = 1;
    x = originX;
    y = originY;
    sprite = 2;
    state = 0;
    del = 200;
    created = true;
    destroy = false;
  }
  
  bool detectPlayer() {
    int distToP = player.x - x;
    if (abs(distToP) < 5) {
      int dir = constrain(distToP, -1, 1);
      distToP = abs(distToP);
      int myX = x;
      for (int i = 0; i < distToP; i++) {
        if (gameMap[player.y][myX] == byte(1)) {
          return false;
        }
        myX += dir;
      }
      return true;
    }
    return false;
  }

  void doLoop() {
    if (millis() >= lim) {
      if (gameMap[y][x] == '-') {
        destroy = true;
        return;
      } else if (gameMap[y][x] == byte(0) || gameMap[y][x] == byte(3)) {
        player.destroy = true;
      }
      
      if (detectPlayer()) {
        state = 2;
      } else {
        state = (doRandChance(25))? 1 : 0;
      }
      
      switch (state) {
        case 0:
          state = (random(2))? 1 : 0;
          break;
        case 1:
          updatePos(originX + random(-1, 2), originY + random(-1, 2));
          state = 0;
          break;
        case 2:
          if (!updatePos(x + constrain(player.x - x, -1, 1), y + constrain(player.y - y, -1, 1))) {
            if (!updatePos(x, y + constrain(player.y - y, -1, 1))) {
              updatePos(x + constrain(player.x - x, -1, 1), y);
            }
          }
          break;
      }
      
      lim = millis() + del;
    }
  }
};

Enemy enemies[MAX_ENEMIES];

void initMap() {
  mapWidth = 26;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < mapWidth; j++) {
      gameMap[i][j] = ' ';
    }
  }
  gameMap[1][10] = byte(1);
}

void drawMap() {
  if (player.x > viewR - 5) {
    viewR = constrain(viewR + 1, 0, mapWidth);
    viewL = viewR - 16;
  } else if (player.x < viewL + 4) {
    viewL = constrain(viewL - 1, 0, mapWidth);
    viewR = viewL + 16;
  }
  
  for (int i = 0; i < mapHeight; i++) {
    lcd.setCursor(0, i);
    for (int j = viewL; j < viewR; j++) {
      lcd.write(gameMap[i][j]);
    }
  }
}

int getInput(int pin) {
  int val = analogRead(pin);
  if (val > 768) {
    return 1;
  } else if ( val < 256) {
    return -1;
  } else {
    return 0;
  }
}

bool doRandChance(int chance) {
  return random(100) < chance;
}

void setup() {
  lcd.createChar(0, playerSprite);
  lcd.createChar(3, playerSprite2);
  lcd.createChar(2, enemySprite);
  lcd.createChar(1, wall);
  lcd.begin(16, 2);
  
  pinMode(J_sw, INPUT);
  digitalWrite(J_sw, HIGH);

  initMap();

  randomSeed(analogRead(A5));
  Serial.begin(9600);
}

void displayMenu(String msg, String opt) {
  lcd.setCursor(8-msg.length()/2, 0);
  lcd.print(msg);
  lcd.setCursor(8-opt.length()/2, 1);
  lcd.print(opt);
  if (!digitalRead(J_sw)) {
    player.created = true;
    player.x = 0;
    player.y = 1;
    for (int i = 0; i < MAX_ENEMIES; i++) {
      enemies[i].created = true;
      enemies[i].x = enemies[i].originX;
      enemies[i].y = enemies[i].originY;
    }
    for (int i = 0; i < MAX_BULLETS; i++) {
      bullets[i].created = true;
    }
    gameState = 1;
  }
}

void play() {
  if (player.created) {
    player.doLoop();
    if (player.destroy) {
      gameMap[player.y][player.x] = ' ';
      player.created = false;
      player.destroy = false;
      gameState = 2;
    }
  }

  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].created) {
      enemies[i].doLoop();
      if (enemies[i].destroy) {
        gameMap[enemies[i].y][enemies[i].x] = ' ';
        enemies[i].created = false;
        enemies[i].destroy = false;
      }
    }
  }
  
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].created) {
      bullets[i].doLoop();
      if (bullets[i].destroy) {
        gameMap[bullets[i].y][bullets[i].x] = ' ';
        bullets[i].created = false;
        bullets[i].destroy = false;
      }
    }
  }
  
  drawMap();
  Serial.println(player.health);
  delay(100);
}

void loop() {
  switch (gameState) {
    case 0:
      displayMenu("Char Battle", "start");
      break;
    case 1:
      play();
      break;
    case 2:
      displayMenu("You Lost", "restart");
    default:
      break;
  }
}
