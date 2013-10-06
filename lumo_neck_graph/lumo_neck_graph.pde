import processing.serial.*;
Serial myPort;        // The serial port
float xPos = 0;             // horizontal position of the graph
 
void setup () {
  size(300, 300);        // window size
 
  // List all the available serial ports
  println(Serial.list());
 
  String portName = Serial.list()[8];
  myPort = new Serial(this, portName, 9600);
 
  background(#1ABC9C);
}
 
void draw () {
  // nothing happens in draw.  It all happens in SerialEvent()
}
 
void serialEvent (Serial myPort) {
  // get the byte:
  int inByte = myPort.read();
  // print it:
  println(inByte);
 
  float yPos = height - inByte;
  // draw the line in a pretty color:
  stroke(#EA2E49);
  line(xPos, height, xPos, height - inByte);
 
  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    // clear the screen by resetting the background:
    background(#F1C40F);
  }
  else {
    // increment the horizontal position for the next reading:
    xPos++;
  }
}
