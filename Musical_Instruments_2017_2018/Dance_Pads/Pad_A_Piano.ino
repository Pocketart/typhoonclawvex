#include <Math.h>
#include <Keyboard.h>
#include <MIDI.h>

// Set up variables for dance pad input
int bass= 2; 
int hHat = 3;
int hTom = 4;
int mTom = 5;
int ride = 6;
int snare = 7;
int lTom = 8;
int crash = 9;

// Set up default variables for input status
int valBass = 0;
int valhHat = 0;
int valhTom = 0;
int valmTom = 0;
int valRide = 0;
int valSnare = 0;
int vallTom = 0;
int valCrash = 0;

// variable to store the value read
 
void setup()
{
  Serial.begin(9600);
  pinMode(bass, INPUT); 
  pinMode(hHat, INPUT);
  pinMode(hTom, INPUT);
  pinMode(mTom, INPUT);
  pinMode(ride, INPUT);
  pinMode(snare, INPUT);
  pinMode(lTom, INPUT);
  pinMode(crash, INPUT);
 
  //  setup serial
}

void loop()
{
  valBass = digitalRead(bass);// read the input pin
  valRide = digitalRead(hHat);// read the input pin
  valCrash = digitalRead(hTom);// read the input pin
  valmTom = digitalRead(mTom);// read the input pin
  vallTom = digitalRead(ride);// read the input pin
  valhHat = digitalRead(snare);// read the input pin
  valSnare = digitalRead(lTom);// read the input pin
  valhTom = digitalRead(crash);// read the input pin

  if (valBass == 1)//bt5
  {
    Keyboard.press('g');
  }
  else{
    Keyboard.release('g');
  }
  
  if (valhHat == 1)//bt4
  {
    Keyboard.press('f');
  }
   else{
    Keyboard.release('f');
  }
  
  if (valhTom == 1)//bt8
  {
    Keyboard.press('k');
  }
   else{
    Keyboard.release('k');
  }
  if (valmTom == 1)//bt7
  {
    Keyboard.press('j');
  }
   else{
    Keyboard.release('j');
  }
  
  if (valRide == 1)//bt3
  {
    Keyboard.press('d');
  }
   else{
    Keyboard.release('d');
  }
  
  if (valSnare == 1)//bt1
  {
    Keyboard.press('a');
  }
   else{
    Keyboard.release('a');
  }
  
  if (vallTom == 1)//bt6
  {
    Keyboard.press('h');
  }
   else{
    Keyboard.release('h');
  }
  
  if (valCrash == 1)//bt2
  {
    Keyboard.press('s');
  }
   else{
    Keyboard.release('s');
  }
  
  delay(10);

}
