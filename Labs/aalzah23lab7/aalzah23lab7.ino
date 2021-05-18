// Aziz Alzahrani - 675518850
// Lab 7 - Serial Communication
// This code makes use of the hardware serial communication on the board using pins 0 (RX) and 1 (TX),
// as well as a defined software serial object utilizing two other pins.
// It reads input from two buttons, each associated with a serial object, and writes to each button's object whenever any of them is pressed.
// Each serial object reads in what the other has wrote and toggles an LED associated to it, based on the data read from the other object.
// This program assumes the following:
// - Software serial object's RX and TX are defined to be pins 2 and 3, respectively.
// - LED associated to the hardware serial is connected to pin 6
// - Button associated to the hardware serial is connected to pin 7
// - LED associated to the software serial is connected to pin 11
// - Button associated to the software serial is connected to pin 12
// No references used.
// Youtube video link - https://youtu.be/-B5-Yc6-Chs

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

const int hwLedPin = 6, hwButtonPin = 7, swLedPin = 11, swButtonPin = 12;
bool hwLedState = false, swLedState = false, isHwBPressed = false, isSwBPressed = false;

void setup() {
  // Starting the serial communications
  Serial.begin(9600);
  mySerial.begin(9600);

  // Setting up the LEDs and buttons
  pinMode(hwLedPin, OUTPUT);
  pinMode(hwButtonPin, INPUT);
  pinMode(swLedPin, OUTPUT);
  pinMode(swButtonPin, INPUT);
}

void loop() {
  // Check if the hardware button is pressed once, invert the software LED's state then write it to the hardware serial object
  if (digitalRead(hwButtonPin)) {
    if (!isHwBPressed) {
      swLedState = !swLedState;
      Serial.write(swLedState);
      isHwBPressed = true;
    }
  } else {
    isHwBPressed = false;
  }

  // Check if the software button is pressed once, invert the hardware LED's state then write it to the software serial object
  if (digitalRead(swButtonPin)) {
    if (!isSwBPressed) {
      hwLedState = !hwLedState;
      mySerial.write(hwLedState);
      isSwBPressed = true;
    }
  } else {
    isSwBPressed = false;
  }
  
  // Check if any data is available to the hardware serial, read in the new state of the hardware LED and update it
  if (Serial.available()) {
    digitalWrite(hwLedPin, Serial.read());
  }

  // Check if any data is available to the software serial, read in the new state of the software LED and update it
  if (mySerial.available()) {
    digitalWrite(swLedPin, mySerial.read());
  }
}
