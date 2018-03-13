/*
TYPHOON CLAW 2018
THIS PROGRAM ONLY WORKS ON THE DANCE PAD LABELLED "DANCE PAD A"
IDEALLY, GARAGEBAND SHOULD BE SET TO THE SAME CONFIGURATION AS SEEN IN THIS IMAGE: https://i.imgur.com/agKXiqV.png
PINS 2 THROUGH 9 ARE ALL BUTTONS THAT RETURN 0 ON IDLE AND 1 ON ACTIVATION.
*/

#include <Math.h>
#include <Keyboard.h>

// Set up variables for each dance pad button pin
int bass= 2; 
int hHat = 3;
int hTom = 4;
int mTom = 5;
int ride = 6;
int snare = 7;
int lTom = 8;
int crash = 9;

// Initiate variables for recording input states
int valBass = 0;
int valhHat = 0;
int valhTom = 0;
int valmTom = 0;
int valRide = 0;
int valSnare = 0;
int vallTom = 0;
int valCrash = 0;


void setup() // Will be run only once
{
  //Serial.begin(9600); // for debugging console
 
  // Set all digital pins as type INPUT
  pinMode(bass, INPUT); 
  pinMode(hHat, INPUT);
  pinMode(hTom, INPUT);
  pinMode(mTom, INPUT);
  pinMode(ride, INPUT);
  pinMode(snare, INPUT);
  pinMode(lTom, INPUT);
  pinMode(crash, INPUT);
 
}

void loop()
{
  valSnare = digitalRead(lTom);// read button 1 state
  valCrash = digitalRead(hTom);// read button 2 state
  valRide = digitalRead(hHat);// read button 3 state
  valhHat = digitalRead(snare);// read button 4 state
  valBass = digitalRead(bass);// read button 5 state
  vallTom = digitalRead(ride);// read button 6 state
  valmTom = digitalRead(mTom);// read button 7 state
  valhTom = digitalRead(crash);// read button 8 state

  // Keyboard state for button 1
  if (valSnare == 1)
  {
    Keyboard.press('a');        // do
  }
   else{
    Keyboard.release('a');      // Since Arduino doesn't support anti-ghosting, each key must have a release condition
  }
 
  // Keyboard state for button 2
  if (valCrash == 1)
  {
    Keyboard.press('s');        // re
  }
   else{
    Keyboard.release('s');
  }
 
  // Keyboard state for button 3
  if (valRide == 1)
  {
    Keyboard.press('d');        // mi
  }
   else{
    Keyboard.release('d');
  }
  
  // Keyboard state for button 4
  if (valhHat == 1)
  {
    Keyboard.press('f');        // fa
  }
   else{
    Keyboard.release('f');
  }
 
  // Keyboard state for button 5
  if (valBass == 1)
  {
    Keyboard.press('g');        // sol
  }
  else{
    Keyboard.release('g');
  }
 
  // Keyboard state for button 6
  if (vallTom == 1)
  {
    Keyboard.press('h');        // la
  }
   else{
    Keyboard.release('h');
  }
  
  // Keyboard state for button 7
  if (valmTom == 1)
  {
    Keyboard.press('j');        // ti
  }
   else{
    Keyboard.release('j');
  }
 
  // Keyboard state for button 8
  if (valhTom == 1)
  {
    Keyboard.press('k');        // do
  }
   else{
    Keyboard.release('k');
  }
  
  delay(10); // Small delay needed to prevent Arduino from potentially freezing

}
