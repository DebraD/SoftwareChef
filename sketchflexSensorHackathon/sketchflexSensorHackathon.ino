/*
SparkFun Inventor's Kit
Example sketch 09

FLEX SENSOR

  Use the "flex sensor" to change the position of a servo
  
  In the previous sketch, we learned how to command a servo to
  mode to different positions. In this sketch, we'll introduce
  a new sensor, and use it to control the servo.
  
  A flex sensor is a plastic strip with a conductive coating.
  When the strip is straight, the coating will be a certain
  resistance. When the strip is bent, the particles in the coating
  get further apart, increasing the resistance. You can use this
  sensor to sense finger movement in gloves, door hinges, stuffed
  animals, etc. See http://www.sparkfun.com/tutorials/270 for
  more information.
  
Hardware connections:

  Flex sensor:

    The flex sensor is the plastic strip with black stripes.
    It senses bending away from the striped side.
    
    The flex sensor has two pins, and since it's a resistor,
    the pins are interchangable.
    
    Connect one of the pins to ANALOG IN pin 0 on the Arduino.
    Connect the same pin, through a 10K Ohm resistor (brown
    black orange) to GND.
    Connect the other pin to 5V.

*/


// Include the Liquid library to add LED-control functions:
#include <LiquidCrystal.h>

// Define the analog input pin to measure flex sensor position:

const int flexpin = 0; 
const int buzzerPin = 9;
const int normalRange = 233;
const int forwardRange = 10;
const int backwardRange = 10;
const int outOfRangeTime = 5; // in seconds 
int counter = 0;

LiquidCrystal lcd(12,11,5,4,3,2);

// Length must equal the total number of notes and spaces 

const int songLength = 18;

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)

char notes[] = "cdfda ag cdfdg gf "; // a space represents a rest

// Beats is an array of values for each note and rest.
// A "1" represents a quarter-note, 2 a half-note, etc.
// Don't forget that the rests (spaces) need a length as well.

int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.

int tempo = 150;

void setup() 
{ 
  // Use the serial monitor window to help debug our sketch:
   
  Serial.begin(9600);
  
  pinMode(13, OUTPUT); // led
  pinMode(buzzerPin, OUTPUT); // buzzer
  
  lcd.begin(16, 2);
  lcd.clear();
 // lcd.print("hello, world");
 
} 


void loop() 
{ 
  int flexposition;    // Input value from the analog pin.
//  int servoposition;   // Output value to the servo.
  flexposition = analogRead(flexpin);
  
  // Serial.print("sensor: ");
  Serial.write(flexposition/4);
  
  if (flexposition > normalRange + forwardRange || flexposition < normalRange - backwardRange)
  {
    counter = counter + 1;
    //Serial.println(counter);
    
    if (counter > 5)
    {
    //  Serial.println("Red light on");
      digitalWrite(13, HIGH);
      
      if (counter > 10)
      {
        lcd.print("Straighten up!");
        playSong();
        counter = 0;
      }
    }
  }
  else
  {
    counter = 0;
  //  Serial.println("Red light off");
    digitalWrite(13, LOW);
  }
  
  delay(1000);  // wait 1 second between servo updates
} 

void playSong()
{
  int i, duration;
  
  for (i = 0; i < songLength; i++) // step through the song arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms
    
    if (notes[i] == ' ')          // is this a rest? 
    {
      delay(duration);            // then pause for a moment
    }
    else                          // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }
}

int frequency(char note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.
  
  int i;
  const int numNotes = 8;  // number of notes we're storing
  
  // The following arrays hold the note characters and their
  // corresponding frequencies. The last "C" note is uppercase
  // to separate it from the first lowercase "c". If you want to
  // add more notes, you'll need to use unique characters.

  // For the "char" (character) type, we put single characters
  // in single quotes.

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
  
  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.
  
  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}
