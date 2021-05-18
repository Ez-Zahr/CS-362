// Aziz Alzahrani - 675518850
// Lab 9 - Graphing sensor data on a PC
// This code reads in analog values from a potentiometer and a photoresistor and transmits them through the serial port.
// On the other side of the port, the program Processing running on a PC listens for those values and graphs them.
// Assumptions made:
// - Potentiometer is connected to pin A0
// - Photoresistor is connected to pin A1
// References used:
// - https://www.arduino.cc/en/Tutorial/BuiltInExamples/Graph
// - https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing#introduction
// Youtube video link - https://youtu.be/v3vSPfjr2i0

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

void loop() {
  // send the value of analog input 0 and 1 separated by a comma for parsing:
  Serial.println(String(analogRead(A0)) + "," + String(analogRead(A1)));
  
  delay(2);
}
