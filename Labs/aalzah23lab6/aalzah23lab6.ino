// Aziz Alzahrani - 675518850
// Lab 6 - Communication
// This code reads in a date (mm/dd/yyyy) and a time (hh/mm/ss) from the user via the serial monitor, keeps accurate time starting from the date and time given,
// and display it on a 16x2 LCD screen. It also keeps track of leap years.
// This program assumes the following:
// - LCD RS pin is connected to pin 6
// - LCD E pin is connected to pin 7
// - LCD D4 pin is connected to pin 8
// - LCD D5 pin is connected to pin 9
// - LCD D6 pin is connected to pin 10
// - LCD D7 pin is connected to pin 11
// No references used.
// Youtube video link - https://youtu.be/rB-nWMJKTis

#include <LiquidCrystal.h>
#include <TimeLib.h>

const int rs = 6, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int m, d, y, hr, mn, sc;
bool isLeap = false;
String prevDate, prevTime;

// Returns true if every character in a string is a digit. Otherwise, returns false.
bool isStringDigit(String s) {
  for (int i = 0; i < s.length(); i++) {
    if (!isDigit(s[i])) return false;
  }

  return true;
}

// This is a blocking function that waits until there are bytes to read in the serial monitor and reads one line per call.
// Returns the input if its length matches the length given and has '/' in index 2 and 5 ("xx/xx/x+"). Otherwise, returns an empty string.
String getInput(int len) {
  while (!Serial.available()) {}
  String input = Serial.readStringUntil('\n');
  
  if (input.length() != len || input[2] != '/' || input[5] != '/') return "";

  return input;
}

// Divides the input string into 3 substrings and stores each substring in the array subs.
// Returns true if all the substrings are digit strings. Otherwise, returns false.
bool subInput(String subs[], String input) {
  subs[0] = input.substring(0, 2);
  subs[1] = input.substring(3, 5);
  subs[2] = input.substring(6);

  if (!isStringDigit(subs[0]) || !isStringDigit(subs[1]) || !isStringDigit(subs[2])) return false;

  return true;
}

// Gets input in the form (mm/dd/yyyy), parses it to extract the date and stores the elements in the global variables m, d, y.
// It also check if all the elements are within the proper range (month from 1 to 12, etc).
// Returns true if the input is valid. Otherwise, returns false.
bool getDate() {
  String input = getInput(10);
  if (input == "") return false;
  
  String subs[3];
  if (subInput(subs, input)) {
    m = subs[0].toInt();
    d = subs[1].toInt();
    y = subs[2].toInt();
  }

  if (m < 1 || m > 12 || d < 1 || d > 31) return false;

  isLeap = (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;

  Serial.println(input);
  return true;
}

// Gets input in the form (hh/mm/ss), parses it to extract the time and stores the elements in the global variables hr, mn, sc.
// It also check if all the elements are within the proper range (hr from 0 to 23, etc).
// Returns true if the input is valid. Otherwise, returns false.
bool getTime() {
  String input = getInput(8);
  if (input == "") return false;
  
  String subs[3];
  if (subInput(subs, input)) {
    hr = subs[0].toInt();
    mn = subs[1].toInt();
    sc = subs[2].toInt();
  }

  if (hr < 0 || hr > 23 || mn < 0 || mn > 59 || sc < 0 || sc > 59) return false;

  Serial.println(input);
  return true;
}

void setup() {
  // Initializing the lcd object and the Serial connection
  lcd.begin(16, 2);
  Serial.begin(9600);

  // Prompting the user for the date
  Serial.print("Enter the date (mm/dd/yyyy): ");
  while (!getDate()) {
    Serial.println("Invalid input!");
    Serial.print("Enter the date (mm/dd/yyyy): ");
  }

  // Prompting the user for the time
  Serial.print("Enter the time (hh/mm/ss): ");
  while (!getTime()) {
    Serial.println("Invalid input!");
    Serial.print("Enter the time (hh/mm/ss): ");
  }

  // Setting the time in TimeLib.h
  setTime(hr, mn, sc, d, m, y);
}

void loop() {
  int yr = year();

  // Constructing the strings to print to the LCD display
  String Date = String(month()) + "/" + String(day()) + "/" + String(yr);
  String Time = String(hour()) + ":" + String(minute()) + ":" + String(second());

  // Checking if the current year is a leap year
  isLeap = (yr % 4 == 0 && yr % 100 != 0) || yr % 400 == 0;

  // Only updating the display if the strings to be printed are different from what's already printed
  if (Date != prevDate || Time != prevTime) {
    prevDate = Date;
    prevTime = Time;
    lcd.clear();
  }

  // Printing the date in the first row
  lcd.setCursor(0, 0);
  lcd.print(Date);

  // Printing a text indicating if it's a leap year
  if (isLeap) {
    lcd.setCursor(12, 0);
    lcd.print("Leap");
    lcd.setCursor(12, 1);
    lcd.print("Year");
  }

  // Printing the time in the second row
  lcd.setCursor(0, 1);
  lcd.print(Time);
}
