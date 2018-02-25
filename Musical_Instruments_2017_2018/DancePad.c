#include <Math.h>


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
  
  valBass = digitalRead(bass);// read the input pin
  valhHat = digitalRead(hHat);// read the input pin
  valhTom = digitalRead(bass);// read the input pin
  valmTom = digitalRead(hHat);// read the input pin
  valRide = digitalRead(bass);// read the input pin
  valSnare = digitalRead(hHat);// read the input pin
  vallTom = digitalRead(bass);// read the input pin
  valCrash = digitalRead(hHat);// read the input pin
  
}

void loop()
{
  Serial.println("Bass button");
  Serial.println(valBass);
  Serial.println("high hat");
  Serial.println(valhHat);
  Serial.println("high tom");
  Serial.println(valhTom);
  Serial.println("med tom");
  Serial.println(valmTom);
  Serial.println("ride");
  Serial.println(valRide);
  Serial.println("l snare");
  Serial.println(valSnare); 
  Serial.println("l tome");
  Serial.println(vallTom); 
  Serial.println("crash");
  Serial.println(valCrash);
  //delay('40');
  

}
