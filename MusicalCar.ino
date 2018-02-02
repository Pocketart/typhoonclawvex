#include <MIDI.h>

String notes[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
int stepArr[] = {0,2,4,5,7,9,11,12};
int keyStep[] = {10, 5, 0, 7, 2, 9, 4};
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
const int outputC = 3;
const int outputD = 4;

//Gear Shit Encoder
const int outputE = 5;
const int outputF = 6;

//Turing Light Encoder
const int outputG = 7;
const int outputH = 8;

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

int eRead(int out1, int out2, int lastState) {
  int counter = 0;
  state = digitalRead(out1);
  if (state != lastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(out2) != state) { 
       counter ++;
     }
  }
  else {
       counter --;
  }
  Serial.print("Position: ");
  Serial.println(counter);
  return counter;
}

void setup(){
  // put your setup code here, to run once:
  Serial.begin (9600);
  
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
}

void loop(){
  // put your main code here, to run repeatedly: 
  counterS = eRead(outputA, outputB, aLastState);
  //counterP = encoderRead(outputC, outputD, cLastState);
  counterG = eRead(outputE, outputF, eLastState);
  //counterT = encoderRead(outputG, outputG, gLastState);
  _key = keyStep[(int)((double) counterG/20*7)];
  _note = _key+stepArr[(int)((double)counterS/40*7)];
  if(true){
    playNote(_note, 500);
  }
  delay(500);
}
