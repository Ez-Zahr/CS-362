// Aziz Alzahrani - 675518850
// Lab 2 - Input and Output
// This code receives input from two buttons to increment or decrement a 3-bit counter, that's then displayed on 3 LEDs in binary (LED on = 1).
// This program assumes that the two buttons are connected to pin 3 and 2 for incrementing and decrementing, respectivly. It also assumes the LEDs are
// connected to pins 5, 6 and 7 for bits 0, 1 and 2 LEDs, respectivly.
// Reference to using the algorithm to convert from decimal to binary - https://www.geeksforgeeks.org/program-decimal-binary-conversion/
// Youtube video link - https://youtu.be/G8BrBr_U5Lw

const int inc = 3;
const int dec = 2;
const int bit0 = 5;
const int bit1 = 6;
const int bit2 = 7;

int count = 0;
int bits[] = {0, 0, 0};
bool canPress = true;

void updateLEDs() {
  digitalWrite(bit0, bits[0]);
  digitalWrite(bit1, bits[1]);
  digitalWrite(bit2, bits[2]);
}

void setup() {
  pinMode(inc, INPUT);
  pinMode(dec, INPUT);
  pinMode(bit0, OUTPUT);
  pinMode(bit1, OUTPUT);
  pinMode(bit2, OUTPUT);

  updateLEDs();
}

void updateBits() {
  for (int i = 0; i < 3; i++) {
    bits[i] = 0;
  }
  
  int n = count;
  for (int i = 0; n > 0; i++) {
    bits[i] = n % 2;
    n /= 2;
  }
  
  updateLEDs();
}

void loop() {
  if (digitalRead(inc) && canPress) {
    if (count < 7) {
      count++;
      updateBits();
    }
    canPress = false;
  } else if (digitalRead(dec) && canPress) {
    if (count > 0) {
      count--;
      updateBits();
    }
    canPress = false;
  } else if (!digitalRead(inc) && !digitalRead(dec)) {
    canPress = true;
  }
}
