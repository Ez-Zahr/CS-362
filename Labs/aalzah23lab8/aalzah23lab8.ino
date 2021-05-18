// Aziz Alzahrani - 675518850
// Lab 8 - Interrupts
// This code displays a counter starting from 0 on a 16x2 LCD display. It also assigns two interrupts to two buttons.
// If button 1 is pressed and the counter is running, it stops the counter, displays a message, and waits for button 2 to be pressed.
// If button 2 is pressed after button 1 has been pressed, it restarts the counter back to 0 and starts running again.
// Assumptions made:
// - LCD RS pin is connected to pin 6
// - LCD E pin is connected to pin 7
// - LCD D4 pin is connected to pin 8
// - LCD D5 pin is connected to pin 9
// - LCD D6 pin is connected to pin 10
// - LCD D7 pin is connected to pin 11
// - Button 1 is connected to pin 2
// - Button 2 is connected to pin 3
// No references used.
// Youtube video link - https://youtu.be/FWpX-W03JYQ

#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
const int button1 = 2, button2 = 3;

bool count = true;
int counter = 0;

// Clears the display and prints the counter along with a message
void printCounter() {
  lcd.clear();
  lcd.print("We have been");
  lcd.setCursor(0, 1);
  lcd.print("waiting for "+String(counter)+"s");
}

// Interrupt handler for button 1
// Sets count to false (stopping the counting) if it isn't already set to false, and prints a message on the display
void stopCount() {
  if (!count) return;
  
  count = false;
  lcd.clear();
  lcd.print("Interrupt received!");
  lcd.setCursor(0, 1);
  lcd.print("Press button 2 to continue");
}

// Interrupt handler for button 2
// Sets count to true (resuming the counting) if it isn't already set to true, resets the counter to 0, and prints it on the display
void startCount() {
  if (count) return;
  
  count = true;
  counter = 0;
  printCounter();
}

void setup() {
  lcd.begin(16, 2);
  
  printCounter();
  
  attachInterrupt(0, stopCount, RISING); // Attaching stopCount to interrupt at pin 2
  attachInterrupt(1, startCount, RISING); // Attaching startCount to interrupt at pin 3
}

void loop() {
  // Checking if count is true and that a second has passed using millis(), to increment the counter and print it
  if (count && millis()%1000 == 0) {
    counter++;
    printCounter();
  }
}
