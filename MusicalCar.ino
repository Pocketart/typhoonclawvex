#include <MIDI.h>
#include <MATH.h>

String notes[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
int stepArr[] = {0,2,4,5,7,9,11,12};
//int keyStep[] = {10, 5, 0, 7, 2, 9, 4};
int update[] = {0,0};
int _note, _key, _range;
int index;
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
const int outputB = 3;

//Pedal Encoder
const int outputC = 4;
const int outputD = 5;

//Gear Shit Encoder
const int outputE = 6;
const int outputF = 7;

//Turing Light Encoder
const int outputG = 8;
const int outputH = 9;

void noteOn(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MIDIUSB.write(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MIDIUSB.write(noteOff);
}

void playNote(int note, int t){
 noteOn(0, note, 64);
 MIDIUSB.flush();
 delay(t);
  
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
      counterP --;
    }
    Serial.print("PositionT: ");
    Serial.println(counterT);
  }
  gLastState = state;
  }
}

void setup(){
  //Setup encoders' pins
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (outputC,INPUT);
  pinMode (outputD,INPUT);
  pinMode (outputE,INPUT);
  pinMode (outputF,INPUT);
  pinMode (outputG,INPUT);
  pinMode (outputH,INPUT);
  
  // Reads the initial state of the outputA~G
  aLastState = digitalRead(outputA); 
  cLastState = digitalRead(outputC); 
  eLastState = digitalRead(outputE);
  gLastState = digitalRead(outputG);
  
  Serial.begin (9600);
}

void loop(){
  // put your main code here, to run repeatedly: 
  eRead(outputE, outputF);
  _key = (int)((double) counterG/20*11);
  eRead(outputA, outputB);
  _note = _key+stepArr[(int)((double) counterS/40*7)];
  //counterP = encoderRead(outputC, outputD, cLastState);
  //counterG = eRead(outputE, outputF, eLastState);
  playNote(_note, 0);
  //delay(100);
}