#include "MyPinLM.h"

// Initialize the MyPinLM object. 
// Replace 'Serial1' with the appropriate Serial interface on your Arduino hardware.
MyPinLM myPinLM(1, Serial1);

void setup() {
  // Begin Serial communication for debugging.
  Serial.begin(9600);

  // Begin Modbus communication at the specified baud rate.
  myPinLM.begin(9600);

  // Give some time for Modbus communication to settle.
  delay(1000);
}

void loop() {
  // Example of reading all devices.
  myPinLM.readAllDevices();

  // Wait for some time before the next read.
  delay(5000);
}
