// Aziz Alzahrani - 675518850
// Lab 4 - More complicated input
// This code reads in some input from a photoresistor and displays the corresponding text on a 16x2 LCD screen. It places the input value in one of the five ranges:
// 0 - 204: "dark"
// 205 - 408: "partially dark"
// 409 - 612: "medium"
// 613 - 816: "partially light"
// > 816 : "fully lit"
// This program assumes the following:
// - LCD RS pin is connected to pin 6.
// - LCD E pin is connected to pin 7.
// - LCD D4 pin is connected to pin 9.
// - LCD D5 pin is connected to pin 10.
// - LCD D6 pin is connected to pin 11.
// - LCD D7 pin is connected to pin 12.
// - Photoresistor is connected to pin A0
// No references used.
// Youtube video link - https://youtu.be/8GLTyuKt6hY

#include <LiquidCrystal.h>

// Defining constant variables for the pins
const int pRes = A0;
const int rs = 6, en = 7, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(pRes, INPUT);
  lcd.begin(16, 2);
}

// This loop() gets the photoresistor reading, clears the LCD screen and prints the corresponding text on it.
void loop() {
  // Reading input from the photoresistor
  int input = analogRead(pRes);
  
  lcd.clear();
  
  // Printing the corresponding text for the input value
  if (input <= 204) {
    lcd.print("dark");
    
  } else if (input <= 408) {
    lcd.print("partially dark");
    
  } else if (input <= 612) {
    lcd.print("medium");
    
  } else if (input <= 816) {
    lcd.print("partially light");
    
  } else {
    lcd.print("fully lit");
    
  }
}
