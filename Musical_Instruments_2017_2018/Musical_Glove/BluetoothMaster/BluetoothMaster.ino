#include <Math.h>
#include <AltSoftSerial.h>

AltSoftSerial BTSerial;



byte i2cWriteBuffer[10];
byte i2cReadBuffer[10];

#define SensorAddressWrite 0x29 //
#define SensorAddressRead 0x29 // 
#define EnableAddress 0xa0 // register address + command bits
#define ATimeAddress 0xa1 // register address + command bits
#define WTimeAddress 0xa3 // register address + command bits
#define ConfigAddress 0xad // register address + command bits
#define ControlAddress 0xaf // register address + command bits
#define IDAddress 0xb2 // register address + command bits
#define ColorAddress 0xb4 // register address + command bits
#define ledPin 7

//Arduino Bluetooth sketch for the master device
//http://www.martyncurrey.com/arduino-to-arduino-by-bluetooth/

// Change DEBUG to true to output debug information to the serial monitor
boolean DEBUG = true;

//int blackOrWhite; // black: 0, white: 1

byte Readi2cRegisters(int numberbytes, byte command)
{
  byte i = 0;

  Wire.beginTransmission(SensorAddressWrite);   // Write address of read to sensor
  Wire.write(command);
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle

  Wire.requestFrom(SensorAddressRead, numberbytes);  // read data
  for (i = 0; i < numberbytes; i++)
    i2cReadBuffer[i] = Wire.read();
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle
}

void init_TCS34725(void)
{
  i2cWriteBuffer[0] = 0x10;
  Writei2cRegisters(1, ATimeAddress);   // RGBC timing is 256 - contents x 2.4mS =
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1, ConfigAddress);  // Can be used to change the wait time
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1, ControlAddress); // RGBC gain control
  i2cWriteBuffer[0] = 0x03;
  Writei2cRegisters(1, EnableAddress);   // enable ADs and oscillator for sensor
}
void get_Colors(void)
{
  unsigned int clear_color = 0;
  unsigned int red_color = 0;
  unsigned int green_color = 0;
  unsigned int blue_color = 0;

  Readi2cRegisters(8, ColorAddress);
  black_color = (unsigned int)(i2cReadBuffer[3] << 8) + (unsigned int)i2cReadBuffer[2];
  white_color = (unsigned int)(i2cReadBuffer[5] << 8) + (unsigned int)i2cReadBuffer[4];

  long int ary[sizeRow][sizeCol] =
  { 
    {
      6612, 1975, 2010            }
    , // red
    {
      14000, 6300, 4300            }
    , // orange

  Serial.print(" Black color=");
  Serial.print(red_color, DEC);
  Serial.print(" White color=");
  Serial.print(white_color, DEC);

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
    get_Colors();
  delay(1000);

}
//  if 
//    BTserial.println("<BLACK>");
//    if (DEBUG) {Serial.println("BLACK command sent");}    
//    delay (1000);
// if 
//    BTserial.println("<WHITE>");
//    if (DEBUG) {Serial.println("WHITE command sent");}      
//    delay (1000);    
//}

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
