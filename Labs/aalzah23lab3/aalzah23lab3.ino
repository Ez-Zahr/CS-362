// Aziz Alzahrani - 675518850
// Lab 3 - Scrolling output
// This code displays my name and a quote on a 16x2 LCD screen. The name is displayed on the first line, and the quote is displayed on the second line
// scrolling to the left, where it then wraps around when it gets off screen.
// This program assumes the following:
// - LCD RS pin is connected to pin 6.
// - LCD E pin is connected to pin 7.
// - LCD D4 pin is connected to pin 9.
// - LCD D5 pin is connected to pin 10.
// - LCD D6 pin is connected to pin 11.
// - LCD D7 pin is connected to pin 12.
// No references used.
// Youtube video link - https://youtu.be/4XCnrMR5eUM

#include <LiquidCrystal.h>

const int rs = 6, en = 7, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String quote = "\"why waste time say lot word, when few word do trick.\" - Ashton Kutcher";
String subQuote = quote.substring(0, 16);
int ind = 0, cur = 15;

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.clear();
  lcd.print("Aziz Alzahrani");
  
  if (ind < quote.length()) {
    lcd.setCursor(0, 1);
    lcd.print(quote.substring(ind, ind + 16));
    ind++;
  } else if (cur >= 0) {
    lcd.setCursor(cur, 1);
    lcd.print(subQuote);
    cur--;
  } else {
    ind = 0;
    cur = 15;
  }

  delay(250);
}
