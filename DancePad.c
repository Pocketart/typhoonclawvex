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
int valbass = 0;
int valhHat = 0;
int valhTom = 0;
int valmTom = 0;
int valride = 0;
int valsnare = 0;
int vallTom = 0;
int valcrash = 0;

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
  //val = analogRead(analogPin);
  valbass = digitalRead(bass);// read the input pin
  Serial.println(valbass);  
  valhHat = digitalRead(hHat);// read the input pin
  Serial.println(valhHat);  
   valhTom = digitalRead(hTom);// read the input pin
  Serial.println(valhTom);  
   valmTom = digitalRead(mTom);// read the input pin
  Serial.println(valmTom);  
   valride = digitalRead(ride);// read the input pin
  Serial.println(valride); 
   valsnare = digitalRead(snare);// read the input pin
  Serial.println(valsnare);  
   vallTom= digitalRead(lTom);// read the input pin
  Serial.println(vallTom);   
   valcrash = digitalRead(crash);// read the input pin
  Serial.println(valcrash);  
  
// debug value

}
