// Aziz Alzahrani - 675518850
// Lab 1 - Get started with Arduino
// This code controls the built-in LED along with two other external LEDs and cycles through them, toggling one LED at a time.
// All of this is done without the use of delay().
// This program assumes that the other two external LEDs are connected to digital pins 12 and 10.
// The delaying algorithm was inspired by the documentation in arduino.cc after reading about the millis() function.
// Youtube link - https://youtu.be/IURG1ipT8xg

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(13, HIGH);
}

enum LED {
  builtin,
  red,
  green
};

int d = 1000;
unsigned long lim = millis() + d;
LED led = builtin;

void loop() {
  if (millis() > lim) {
    switch (led) {
      case builtin:
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
        led = red;
        break;
      case red:
        digitalWrite(12, LOW);
        digitalWrite(10, HIGH);
        led = green;
        break;
      case green:
        digitalWrite(10, LOW);
        digitalWrite(13, HIGH);
        led = builtin;
        break;
    }
    
    lim = millis() + d;
  }
}
