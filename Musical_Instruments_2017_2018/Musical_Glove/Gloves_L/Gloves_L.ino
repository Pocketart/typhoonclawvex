#include <pitchToFrequency.h>
#include <pitchToNote.h>
#include <frequencyToNote.h>
#include <MIDIUSB.h>

// Iron Man Gloves right hand

//#include <AltSoftSerial.h>
//AltSoftSerial BTSerial;
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <MIDI.h>

// our RGB -> eye-recognized gamma color
byte gammatable[256];
const int buttonPinSharp = 2;
const int buttonPinFlat = 3;// the number of the pushbutton pin
int buttonStateSharp = 0; 
int buttonStateFlat = 0; // variable for reading the pushbutton status

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Serial.println("Color Sensor Test!");
  pinMode(buttonPinSharp, INPUT);
  pinMode(buttonPinFlat, INPUT);



  if (tcs.begin()) {
    Serial.println("Found sensor");
  } 
  else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // this helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;  
    gammatable[i] = 255 - x;
  }
}

int color;

void loop() {
  color = get_colors();
  
  buttonStateSharp = digitalRead(buttonPinSharp);
  buttonStateFlat = digitalRead(buttonPinFlat);
  if (buttonStateSharp == HIGH) {
    // turn LED on:
    Serial.println("sharp");
    color_to_note_normal(color);
  } 
  else if(buttonStateFlat == HIGH) {
    Serial.println("flat");
    color_to_note_flat(color);
  }
  else{
    // turn LED off:
    Serial.println("normal");
    color_to_note_normal(color);
  }
    delay(500);


}

int get_colors(){
  uint16_t clear, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clear);

  // Figure out some basic RGB for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\tR:\t"); Serial.print((int)r);
  Serial.print("\tG:\t"); Serial.print((int)g); 
  Serial.print("\tB:\t"); Serial.print((int)b);

  const int sizeRow = 7; // seven colors
  const int sizeCol = 3; // RGB
  int constanterror = 9;
  bool redMatch = false;
  bool greenMatch = false;
  bool blueMatch = false;
  long int ary[sizeRow][sizeCol] =
  { 
    {193, 46, 44}, // red
    {161, 62, 36}, // orange
    {119, 93, 35}, // yellow
    {90, 118, 57}, // green
    {65, 83, 105}, // blue
    {102, 69, 86}, // indigo
    {127, 67, 83} // violet
  }; 
  String colorary [7] = {"red", "orange", "yellow", "green", "blue", "indigo", "violet"};
  for (int y = 0; y < 7; y++)
  {
    redMatch = false;
    greenMatch = false;
    blueMatch = false;
    if (((int)r < (ary[y][0] + constanterror)) && ((int)r > (ary[y][0] - constanterror)))
    {
      redMatch = true;
    }
    if (((int)g < (ary[y][1] + constanterror)) && ((int)g > (ary[y][1] - constanterror)))
    {
      greenMatch = true;
    }
    if (((int)b < (ary[y][2] + constanterror)) && ((int)b > (ary[y][2] - constanterror)))
    {
      blueMatch = true;
    }
    if ((redMatch == true) && (greenMatch == true) && (blueMatch == true))
    {
      Serial.print("\t");
      Serial.println(colorary[y]);
      return y; // return color 
      break;
    }
  }
  Serial.println();
  return -1; // no color detected
}

String notes[] = {
  "C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
int index;

void noteOn(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOn = {
    0x09, 0x90 | channel, pitch, velocity      };
  MIDIUSB.write(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MIDIUSB.write(noteOff);
}

void playNote(String _note, int octave, int t){
  for(int i=0; i<12; i++){
    if(_note.equals(notes[i])){
      index = i;
    }
  }
  noteOn(0, index+octave*12, 64);
  MIDIUSB.flush();
  delay(t);

  noteOff(0, index+octave*12, 64);
  MIDIUSB.flush();
}
 
int octave = 3;
void color_to_note_normal(int c) {
  Serial.print("normal note");
  switch(c){
    case 0:
      playNote("C", octave, 400);
      break;
    case 1:
      playNote("D", octave, 400);
      break;
    case 2:
      playNote("E", octave, 400);
      break;
    case 3: 
      playNote("F", octave, 400);
      break;
    case 4:
      playNote("G", octave, 400);
      break;
    case 5:
      playNote("A", octave, 400);
      break;
    case 6:
      playNote("B", octave, 400);   
      break;
  }
}


void color_to_note_sharp(int c){
    switch(c){
        case 0:
          playNote("C#", octave, 400);
          break;
        case 1:
          playNote("D#", octave, 400);
          break;
        case 2:
          playNote("E", octave, 400);
          break;
        case 3: 
          playNote("F#", octave, 400);
          break;
        case 4:
          playNote("G#", octave, 400);
          break;
        case 5:
          playNote("A#", octave, 400);
          break;
        case 6:
          playNote("B", octave, 400);   
          break;
        }
      }

void color_to_note_flat(int c){ // flat
        switch(c)
        {
        case 0:
          playNote("C", octave, 300);
          break;
        case 1:
          playNote("C#", octave, 300);
          break;
        case 2:
          playNote("D#", octave, 300);
          break;
        case 3: 
          playNote("F", octave, 300);
          break;
        case 4:
          playNote("F#", octave, 300);
          break;
        case 5:
          playNote("G#", octave, 300);
          break;
        case 6:
          playNote("A#", octave, 300);   
          break;
        }
      }
