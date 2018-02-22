// Iron Man Gloves right hand

#include <AltSoftSerial.h>
AltSoftSerial BTSerial;
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Math.h>
#include <MIDI.h>

// our RGB -> eye-recognized gamma color
byte gammatable[256];
int RawValueButton = 0;
int sharp = 0;
int flat = 0;


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Serial.println("Color Sensor Test!");

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
//      gammatable[i] = x;      
//    Serial.println(gammatable[i]);
  }
}

int color;

void loop() {
  color = get_colors();
  color_to_note(color);
  delay(1500);
  RawValueButton = digitalRead(digIn1);
  sharp = digitalRead(digIn3);
  flat = digitalRead(digIn4);
  _note += sharp + flat*-1;
  if(RawValueButton == LOW){
    noteOn(0, _note, 100);
    MIDIUSB.flush();
    while(RawValueButton==LOW){
      delay(1);
      RawValueButton = digitalRead(digIn1);
    }
  }  

}

int get_colors(){t
  uint16_t clear, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clear);
  
//  Serial.print("C:\t"); Serial.print(clear);
//  Serial.print("\tR:\t"); Serial.print(red);
//  Serial.print("\tG:\t"); Serial.print(green);
//  Serial.print("\tB:\t"); Serial.print(blue);

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

  const int sizeRow = 9; // nine colors
  const int sizeCol = 3; // RGB
  int constanterror = 9;
  bool redMatch = false;
  bool greenMatch = false;
  bool blueMatch = false;
  long int ary[sizeRow][sizeCol] =
  { 
    {193, 46, 44}, // red
    {161, 70, 45}, // orange
    {121, 101, 45}, // yellow
    {90, 118, 57}, // green
    {73, 92, 110}, // blue
    {105, 80, 89}, // indigo
    {127, 67, 83}, // violet
    {117, 97, 66}, // black (very close to white????)
    {105, 95, 70} // white
  }; 
  String colorary [9] = {"red", "orange", "yellow", "green", "blue", "indigo", "violet", "black", "white"};
  for (int y = 0; y < 9; y++)
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
      Serial.print(colorary[y]);
      return y; // return color 
      break;
    }
  }
  Serial.println();
  return -1; // no color detected
}

void color_to_note(int c) {
  switch(c){
    case 0:
      playNote("C", 4, 300);
      break;
    case 1:
      playNote("D", 4, 300);
      break;
    case 2:
      playNote("E", 4, 300);
      break;
    case 3: 
      playNote("F", 4, 300);
      break;
    case 4:
      playNote("G", 4, 300);
      break;
    case 5:
      playNote("A", 4, 300);
      break;
    case 6:
      playNote("B", 4, 300);   
      break;
      if(isblack == null){
        switch(y)
        {
        case 0:
          playNote("C", 4, 300);
          break;
        case 1:
          playNote("D", 4, 300);
          break;
        case 2:
          playNote("E", 4, 300);
          break;
        case 3: 
          playNote("F", 4, 300);
          break;
        case 4:
          playNote("G", 4, 300);
          break;
        case 5:
          playNote("A", 4, 300);
          break;
        case 6:
          playNote("B", 4, 300);   
          break;
        }
      }

      else if(isblack == true){ // sharp
        switch(y)
        {
        case 0:
          playNote("C#", 4, 300);
          break;
        case 1:
          playNote("D#", 4, 300);
          break;
        case 2:
          playNote("E", 4, 300);
          break;
        case 3: 
          playNote("F#", 4, 300);
          break;
        case 4:
          playNote("G#", 4, 300);
          break;
        case 5:
          playNote("A#", 4, 300);
          break;
        case 6:
          playNote("B", 4, 300);   
          break;
        }
      }

      else if(isblack == false){ // flat
        switch(y)
        {
        case 0:
          playNote("C", 4, 300);
          break;
        case 1:
          playNote("C#", 4, 300);
          break;
        case 2:
          playNote("D#", 4, 300);
          break;
        case 3: 
          playNote("F", 4, 300);
          break;
        case 4:
          playNote("F#", 4, 300);
          break;
        case 5:
          playNote("G#", 4, 300);
          break;
        case 6:
          playNote("A#", 4, 300);   
          break;
        }
      }
  }
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

