//Arduino Bluetooth sketch for the slave device
//http://www.martyncurrey.com/arduino-to-arduino-by-bluetooth/

#include <AltSoftSerial.h>
AltSoftSerial BTSerial;
 
// Change DEBUG to true to output debug information to the serial monitor
boolean DEBUG = true;
 
// Variables used for incoming data
 
const byte maxDataLength = 20;          // maxDataLength is the maximum length allowed for received data.
char receivedChars[maxDataLength+1] ;
boolean newData = false;               // newData is used to determine if there is a new command
 
void setup()  
{
    if (DEBUG)
    {
        // open serial communication for debugging and show the sketch name and the date compiled
        Serial.begin(9600);
        Serial.println(__FILE__);
        Serial.println(__DATE__);
        Serial.println(" ");
    }
 
    //  open software serial connection to the Bluetooth module.
    BTSerial.begin(9600); 
    if (DEBUG)
    {   
      Serial.println(F("SoftwareSerial started at 9600..."));     
    }
    newData = false;
}
 
void loop()  
{
         // check to see if we have received any new commands
         recvWithStartEndMarkers();
         // if we have a new command do something
         if (newData)
         {   
            processCommand();  
         }    
}
 
void processCommand()
{
    newData = false;
    if(DEBUG)
    {   
      Serial.print("recieved data = ");  Serial.println(receivedChars);         
    }
 
    if(strcmp ("BLACK",receivedChars) == 0)
    { 
      // sharp mode
      // <<<<<<<insert code below>>>>>>>




      
    }
    else if(strcmp ("WHITE",receivedChars) == 0) 
    { 
      // flat mode 
      // <<<<<<<insert code below>>>>>>>
      



    }
}
 
// function recvWithStartEndMarkers by Robin2 of the Arduino forums
// See  http://forum.arduino.cc/index.php?topic=288234.0
void recvWithStartEndMarkers() 
{
     static boolean recvInProgress = false;
     static byte ndx = 0;
     char startMarker = '<';
     char endMarker = '>';
 
     if (BTSerial.available() > 0) 
     {
          char rc = BTSerial.read();
          if (recvInProgress == true) 
          {
               if (rc != endMarker) 
               {
                    if (ndx < maxDataLength) { receivedChars[ndx] = rc; ndx++;  }
               }
               else 
               {
                     receivedChars[ndx] = '\0'; // terminate the string
                     recvInProgress = false;
                     ndx = 0;
                     newData = true;
               }
          }
          else if (rc == startMarker) { recvInProgress = true; }
     }
 
}
