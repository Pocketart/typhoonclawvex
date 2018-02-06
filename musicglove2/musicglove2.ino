#include <Wire.h>
#include <Math.h>
#include <MIDI.h>

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

int state = 0;

/*
  Send register address and the byte value you want to write the magnetometer and
  loads the destination register with the value you send
*/
void Writei2cRegisters(byte numberbytes, byte command)
{
  byte i = 0;

  Wire.beginTransmission(SensorAddressWrite);   // Send address with Write bit set
  Wire.write(command);                          // Send command, normally the register address
  for (i = 0; i < numberbytes; i++)                 // Send data
    Wire.write(i2cWriteBuffer[i]);
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle
}

/*
  Send register address to this function and it returns byte value
  for the magnetometer register's contents
*/
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

void get_TCS34725ID(void)
{
  Readi2cRegisters(1, IDAddress);
  if (i2cReadBuffer[0] = 0x44)
    Serial.println("TCS34725 is present");
  else
    Serial.println("TCS34725 not responding");
}

/*
  Reads the register values for clear, red, green, and blue.
*/
void get_Colors(void)
{
  unsigned int clear_color = 0;
  unsigned int red_color = 0;
  unsigned int green_color = 0;
  unsigned int blue_color = 0;

  Readi2cRegisters(8, ColorAddress);
  clear_color = (unsigned int)(i2cReadBuffer[1] << 8) + (unsigned int)i2cReadBuffer[0];
  red_color = (unsigned int)(i2cReadBuffer[3] << 8) + (unsigned int)i2cReadBuffer[2];
  green_color = (unsigned int)(i2cReadBuffer[5] << 8) + (unsigned int)i2cReadBuffer[4];
  blue_color = (unsigned int)(i2cReadBuffer[7] << 8) + (unsigned int)i2cReadBuffer[6];

  // send register values to the serial monitor

  Serial.print("clear color=");
  Serial.print(clear_color, DEC);
  Serial.print(" red color=");
  Serial.print(red_color, DEC);
  Serial.print(" green color=");
  Serial.print(green_color, DEC);
  Serial.print(" blue color=");
  Serial.println(blue_color, DEC);

  // Basic RGB color differentiation can be accomplished by comparing the values and the largest reading will be
  // the prominent color

  if ((red_color > blue_color) && (red_color > green_color))
    Serial.println("detecting red");
  else if ((green_color > blue_color) && (green_color > red_color))
    Serial.println("detecting green");
  else if ((blue_color > red_color) && (blue_color > green_color))
    Serial.println("detecting blue");
  else
    Serial.println("color not detectable");
    
  const int sizeRow = 9; // RGB
  const int sizeCol = 3; // nine colors
  int constanterror = 3500;
  bool redMatch = false;
  bool greenMatch = false;
  bool blueMatch = false;
  long int ary[sizeRow][sizeCol] =
  { {19000, 12200, 5500}, // red
    {12000, 6800, 3750}, // orange
    {35000, 38700, 15150}, // yellow
    {6700, 15700, 7800}, // green
    {6050, 1000, 10200}, // blue
    {11000, 12500, 10900}, // indigo
    {5200, 4900, 5100}, // violet
    {200, 120, 55}, // black
    {44000, 53100, 34200} // white
  }; 
  String colorary [9] = {"red", "orange", "yellow", "green", "blue", "indigo", "violet", "black", "white"};
  for (int y = 0; y < 9; y++)
  {
    if ((red_color < (ary[0][y] + constanterror)) && (red_color > (ary[0][y] - constanterror)))
    {
      redMatch = true;
    }
    if ((blue_color < (ary[1][y] + constanterror)) && (blue_color > (ary[1][y] - constanterror)))
    {
      blueMatch = true;
    }
    if ((green_color < (ary[2][y] + constanterror)) && (green_color > (ary[2][y] - constanterror)))
    {
      greenMatch = true;
    }
    if ((redMatch == true) && (blueMatch == true) && (greenMatch = true))
    {
      Serial.println(colorary[y]);
      break;
    }
    switch(y)
    {
      case 0:
      playNote("C", 4, 500);
      break;
      case 1:
      playNote("D", 4, 500);
      break;
      case 2:
      playNote("E", 4, 500);
      break;
      case 3: 
      playNote("F", 4, 500);
      break;
      case 4:
      playNote("G", 4, 500);
      break;
      case 5:
      playNote("A", 4, 500);
      break;
      case 6:
      playNote("B", 4, 500);   
      break;
    }
  }
}

String notes[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
int index;

void noteOn(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MIDIUSB.write(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MIDIUSB.write(noteOff);
}

void playNote(String _note, int octave, int t){
  for(int i=0; i<12; i++){
    if(_note.equals(notes[i])){
      index = i;
    }
  }
  noteOn(0, index+octave*12, 64);
  MIDIUSB.flush();
  delay(t);
  
  noteOff(0, index+octave*12, 64);
  MIDIUSB.flush();
}

void setup() {
  Wire.begin();
  Serial.begin(9600);  // start serial for output
  init_TCS34725();
  get_TCS34725ID();     // get the device ID, this is just a test to see if we're connected

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400);
  // Default communication rate of the Bluetooth module
}

void loop() {
  get_Colors();
  delay(1000);

  if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
  }
  if (state == '0') {
    digitalWrite(ledPin, LOW); // Turn LED OFF
    Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
    state = 0;
  }
  else if (state == '1') {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED: ON");;
    state = 0;
  } if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
  }
  if (state == '0') {
    digitalWrite(ledPin, LOW); // Turn LED OFF
    Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
    state = 0;
  }
  else if (state == '1') {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED: ON");;
    state = 0;
  }
}
