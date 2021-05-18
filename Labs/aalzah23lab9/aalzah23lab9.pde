// Aziz Alzahrani - 675518850
// Lab 9 - Graphing sensor data on a PC
// This code reads in serial data represented as a string sent to the port at index 0, parses the string for two float values separated by a comma, and graphs these values.
// On the other side of the port, the Arduino is reading the two values from a potentiometer and a photoresistor and transmits them through the serial port.
// Assumptions made:
// - Port used to read data from the Arduino is the port at index 0
// References used:
// - https://www.arduino.cc/en/Tutorial/BuiltInExamples/Graph
// - https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing#introduction
// Youtube video link - https://youtu.be/v3vSPfjr2i0

import processing.serial.*;

Serial myPort;        // The serial port
int xPos1 = 0, xPos2 = 400;         // horizontal positions of the graphs
float inByte1 = 0, inByte2 = 0;

void setup () {
  // set the window size:
  size(800, 400);

  // Opening the port the Arduino is using.
  myPort = new Serial(this, Serial.list()[0], 9600);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // set initial background:
  background(0);
}

void draw () {
  // draw the lines:
  stroke(127, 34, 255);
  line(xPos1, height, xPos1, height - inByte1);
  stroke(128, 221, 0);
  line(xPos2, height, xPos2, height - inByte2);
  
  // at the edge of the screen, go back to the beginning:
  if (xPos1 >= width/2) {
    xPos1 = 0;
    xPos2 = 400;
    background(0);
  } else {
    // increment the horizontal positions:
    xPos1++;
    xPos2++;
  }
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // parse the string to get the different readings:
    String[] inBytes = split(inString, ',');
    // convert to an int and map to the screen height:
    inByte1 = float(inBytes[0]);
    inByte2 = float(inBytes[1]);
    println(inByte1 + ", " + inByte2);
    inByte1 = map(inByte1, 0, 1023, 0, height);
    inByte2 = map(inByte2, 0, 1023, 0, height);
  }
}
