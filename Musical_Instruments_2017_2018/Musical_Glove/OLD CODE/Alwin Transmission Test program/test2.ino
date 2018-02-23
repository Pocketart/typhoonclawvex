#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  delay(300);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while(Wire.available()){
    relay_num = Wire.read();
    delay_sec = Wire.read();
    Serial.println(relay_num);
    Serial.println(delay_sec);
  }
  digitalWrite(0, HIGH);
  delay(delay_sec);
  Serial.println("here");           
  digitalWrite(0, LOW);
  delay(delay_sec); 
}
