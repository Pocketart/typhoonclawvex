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

  if (valBass == 1)//This is actually Snare
  {
    Keyboard.press('s');
  }
  else{
    Keyboard.release('s');
  }
  
  if (valhHat == 1)//This is actually Bass
  {
    Keyboard.press('a');
  }
   else{
    Keyboard.release('a');
  }
  
  if (valhTom == 1)//This is actually Crash
  {
    Keyboard.press('u');
  }
   else{
    Keyboard.release('u');
  }
  if (valmTom == 1)//This is actually Low Tom
  {
    Keyboard.press('h');
  }
   else{
    Keyboard.release('h');
  }
  
  if (valRide == 1)//This is actually High Hat
  {
    Keyboard.press('t');
  }
   else{
    Keyboard.release('t');
  }
  
  if (valSnare == 1)//This is actually Ride
  {
    Keyboard.press('p');
  }
   else{
    Keyboard.release('p');
  }
  
  if (vallTom == 1)//This is actually High Tom
  {
    Keyboard.press('k');
  }
   else{
    Keyboard.release('k');
  }
  
  if (valCrash == 1)//This is actually Mid Tom
  {
    Keyboard.press('j');
  }
   else{
    Keyboard.release('j');
  }
  
  delay(10);

}
