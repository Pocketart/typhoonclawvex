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

  if (valBass == 1)
  {
    //Keyboard.write('a');
  }
  else if (valhHat == 1)
  {
    //Keyboard.write('s');
  }
  else if (valhTom == 1)
  {
    //Keyboard.write('d');
  }
  else if (valmTom == 1)
  {
    //Keyboard.write('f');
  }
  else if (valRide == 1)
  {
    //Keyboard.write('g');
  }
  else if (valSnare == 1)
  {
    //Keyboard.write('h');
  }
  else if (vallTom == 1)
  {
    //Keyboard.write('j');
  }
  else if (valCrash == 1)
  {
    //Keyboard.write('k');
  }

  delay(220);
  

}
