#include <MIDI.h>
#include <MATH.h>

String notes[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
int stepArr[] = {0,2,4,5,7,9,11,12};
int keyStep[] = {10, 5, 0, 7, 2, 9, 4};//A#, F, C, G, D, A, E
String displayKey[] = {"A#","F","C","G","D","A","E"};
int _note, _key, _octave = 60;
int oldKey = -1,oldNote = -1;
int counterS = 0;
int counterP = 0;
int counterG = 0;
int counterT = 0;
int state;
int aLastState;
int cLastState;
int eLastState;
int gLastState;

//Steering Wheel Encoder
const int outputA = 2;
const int outputB = 10; 

//Pedal Encoder
const int outputC = 4;
const int outputD = 5;

//Gear Shit Encoder
const int outputE = 6;
const int outputF = 7;

// Button for octave
const int octave4 = 18;
const int octave5 = 19;

//Button for sharp/flat
const int sharpPin = 20;
const int flatPin = 21;
int sharp;
int flat;

int count = 0;

const int S0 = 3;
const int S1 = 8;
const int S2 = 9;
const int S3 = 10;
const int sensorOut = 16;
int color = 0;

int colorArr[7][4] =
  { 
    {
      193, 46, 44, 0}
    , // red
    {
      161, 68, 45, 2}
    , // orange
    {
      121, 100, 45, 4}
    , // yellow
    {
      90, 118, 57, 5}
    , // green
    {
      72, 92, 105, 7}
    , // blue
    {
      102, 81, 87, 9}
    , // indigo
    {
      127, 67, 83, 11} // violet
  }; 
int frequency = 0;

void noteOn(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOn = {
    0x09, 0x90 | channel, pitch, velocity  };
  MIDIUSB.write(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOff = {
    0x08, 0x80 | channel, pitch, velocity  };
  MIDIUSB.write(noteOff);
}

void playNote(int note, int t){
  noteOn(0, note, 64);
  MIDIUSB.flush();
  delay(t);
  eRead(outputC, outputD); 
  noteOff(0, note, 64);
  MIDIUSB.flush();
}

void eRead(int out1, int out2) {
  state = digitalRead(out1);
  if (out1 == 2){
    if (state != aLastState){     
      if (digitalRead(out2) != state) { 
        counterS ++;
      }
      else {
        counterS --;
      }
      Serial.print("PositionS: ");
      Serial.println(abs(counterS));
    }
    aLastState = state;
  }
  if (out1 == 4){
    if (state != cLastState){     
      if (digitalRead(out2) != state) { 
        counterP ++;
      }
      else {
        counterP --;
      }
      Serial.print("PositionP: ");
      Serial.println(counterP);
    }
    cLastState = state;
  }
  if (out1 == 6){
    if (state != eLastState){     
      if (digitalRead(out2) != state) { 
        counterG ++;
      }
      else {
        counterG --;
      }
      Serial.print("PositionG: ");
      Serial.println(abs(counterG));
    }
    eLastState = state;
  }
  if (out1 == 8){
    if (state != gLastState){
      if (digitalRead(out2) != state){ 
        counterT ++;
      }
      else {
        counterT --;
      }
      Serial.print("PositionT: ");
      Serial.println(counterT);
    }
    gLastState = state;
  }
}

void changeOctave(){
  if(digitalRead(octave5)== 1){
    count += 1;
    if (count > 1){
      _octave = 48;
      count = 0;
    }
    else{
      _octave = 60;
    }
  }  
}

void getColor(){
  int r,g,b;
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  r = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  g = frequency;
  Serial.print("  ");
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  b = frequency;
  Serial.println("  ");
  delay(100);
  
  for(int x = 0; x < 7; x++){
    if(abs(r - colorArr[x][0])<= 5 && abs(g - colorArr[x][1])<= 5 && abs(b - colorArr[x][2])<= 5){
      color = colorArr[x][3];
    }
  }
}

void setup(){
  Serial.begin (9600);

  //Setup buttons' pin
  pinMode (octave4, INPUT);
  pinMode (octave5, INPUT);
  pinMode (sharpPin, INPUT);
  pinMode (flatPin, INPUT);
  //Setup encoders' pins
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (outputC,INPUT);
  pinMode (outputD,INPUT);
  pinMode (outputE,INPUT);
  pinMode (outputF,INPUT);

  // Reads the initial state of the outputA, C, E
  aLastState = digitalRead(outputA); 
  cLastState = digitalRead(outputC); 
  eLastState = digitalRead(outputE);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void loop(){
  getColor();
  eRead(outputE, outputF);
  if(counterG > 13){
    counterG = 13;
  }
  oldKey = _key;
  _key = keyStep[(int)((double) counterG*-6/13.0+0.5)];
  eRead(outputA, outputB);
  if(counterS > 40){
    counterS = 40;
  }
  changeOctave();
  _note = _key + color + _octave;
  sharp = digitalRead(sharpPin);
  flat = digitalRead(flatPin);
  _note += sharp - flat;
  eRead(outputC, outputD);
  delay(100);
  if(counterP != 0){
    noteOn(0, _note, 64);
    delay(300);
    while (counterP != 0){
      eRead(outputA, outputB);
      eRead(outputC, outputD);
      eRead(outputE, outputF);
    }
    noteOff(0, _note, 64);
  }
}


