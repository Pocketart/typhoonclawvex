//Arduino Bluetooth sketch for the master device
//http://www.martyncurrey.com/arduino-to-arduino-by-bluetooth/

#include <AltSoftSerial.h>
AltSoftSerial BTSerial;

// Change DEBUG to true to output debug information to the serial monitor
boolean DEBUG = true;

//int blackOrWhite; // black: 0, white: 1

void setup()
{
  if (DEBUG)
    {
        // open serial communication for debugging and show 
        // the sketch filename and the date compiled
        Serial.begin(9600);
        Serial.println(__FILE__);
        Serial.println(__DATE__);
        Serial.println(" ");
    }

  //  open software serial connection to the Bluetooth module.
  BTserial.begin(9600); 
  if (DEBUG)
    {
        Serial.println("BTserial started at 9600...");
    }
}

void loop()  
{
    BTserial.println("<BLACK>");
    if (DEBUG) {Serial.println("BLACK command sent");}    
    delay (1000);
 
    BTserial.println("<WHITE>");
    if (DEBUG) {Serial.println("WHITE command sent");}      
    delay (1000);    
}

//void loop()
//{
//// Read from the slave device and decide if the current mode is sharp or flat
//  while (BTSerial.available())
//  {
//    blackOrWhite = BTSerial.read();
//    Serial.println(blackOrWhite);
//
//    //if black
//    if(blackOrWhite == 0){
//      
//    }
//
//    //if white
//    else if(blackOrWhite == 1){
//      
//    }
//  }    
//}
