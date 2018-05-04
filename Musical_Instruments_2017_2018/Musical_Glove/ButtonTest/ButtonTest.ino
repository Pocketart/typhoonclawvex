const int buttonPinSharp = 7;
const int buttonPinFlat = 8;
int buttonStateSharp = 0; 
int buttonStateFlat = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPinSharp, INPUT);
  pinMode(buttonPinFlat, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  buttonStateSharp = digitalRead(buttonPinSharp);
  buttonStateFlat = digitalRead(buttonPinFlat);
  
  //Serial.print("sharp ");
  Serial.println(buttonStateSharp);
  
  //Serial.print("flat ");
  Serial.println(buttonStateFlat);
  delay(200);
}                              
