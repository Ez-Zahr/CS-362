// Aziz Alzahrani - 675518850
// Lab 5 - Multiple inputs and outputs
// This code reads in input from a photoresistor and toggles 4 LEDs accordingly. The higher the input read from the photoresistor, The less LEDs light up, and vice versa.
// It places the input value in one of the five ranges:
// 0 - 204: 4 LEDs
// 205 - 408: 3 LEDs
// 409 - 612: 2 LEDs
// 613 - 816: 1 LED
// 817 - 1024: 0 LEDS
// This program assumes the following:
// - LED 1 is connected to pin 2
// - LED 2 is connected to pin 3
// - LED 3 is connected to pin 4
// - LED 4 is connected to pin 5
// - Passive Buzzer is connected to 11
// - Potentiometer is connected to A0
// - Photoresistor is connected to pin A5
// No references used.
// Youtube video link - https://youtu.be/av_1pIT-9yM

const int pRes = A5, buzzer = 11, pMeter = A0;
int leds[] = {2, 3, 4, 5};

void setup() {
  pinMode(pRes, INPUT);
  pinMode(pMeter, INPUT);
  pinMode(buzzer, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

/* Turns off all LEDs and turns back on n LEDs */
void lightLEDs(int n) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }

  for (int i = 0; i < n; i++) {
    digitalWrite(leds[i], HIGH);
  }
}

void loop() {
  // Reading input from the photoresistor
  int input = analogRead(pRes);
  
  // Lighting the corresponding LEDs for the input value
  if (input <= 204) {
    lightLEDs(4);
    
  } else if (input <= 408) {
    lightLEDs(3);
    
  } else if (input <= 612) {
    lightLEDs(2);
    
  } else if (input <= 816) {
    lightLEDs(1);
    
  } else {
    lightLEDs(0);
    
  }

  // Mapping the reading from the potentiometer to a value in the range 50 - 500 and writing that value to the buzzer
  tone(buzzer, map(analogRead(pMeter), 0, 1023, 50, 500));
  
}
