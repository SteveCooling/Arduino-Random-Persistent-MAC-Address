
#include <EEPROM.h>

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  int sensorValue = analogRead(A5);
  randomSeed(sensorValue);
}

static byte macAddr[] = { 0x06, 0x01, 0x01, 0x00, 0x00, 0x00 };

// the loop routine runs over and over again forever:
void loop() {
  // generate mac address...
  getMacAddress(macAddr);

  // print out the value you read:
  Serial.println(String(macAddr[0], HEX)+":"+String(macAddr[1], HEX)+":"+String(macAddr[2], HEX)+":"+String(macAddr[3], HEX)+":"+String(macAddr[4], HEX)+":"+String(macAddr[5], HEX));
  delay(1000);
  
}

// This function takes a 6 byte array, and will fill every byte that is 0x00 with device unique data.
// The data is retrieved from a preset place in the Atmega EEPROM.
// If the particular EEPROM bytes are 0x00 or 0xFF, the data is ranomly generated and stored in EEPROM.

void getMacAddress(byte* macAddr) {
  int eepromOffset = 128;
  int b = 0; 
  for (int c = 0; c < 6; c++) {
    b = 0;
    if(macAddr[c] == 0) {
      b = EEPROM.read(eepromOffset + c);
      if(b == 0 || b == 255) {
         b = random(0, 255);
         EEPROM.write(eepromOffset + c, b);
      }
    macAddr[c] = b;
    }
  }
}
