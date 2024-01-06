#include <ModbusMaster.h>
ModbusMaster node;

// Define the structure for Modbus parameters
struct ModbusParameter {
  uint16_t address; // MODBUS data address in hexadecimal
  uint8_t count;    // Number of words to read or write
};

// Declare the Modbus parameters you want to read from each device
const ModbusParameter modbusTable[] = {
  {0x0062, 2}, // PV
  {0x0000, 2}, // AL1
  {0x0003, 1}, // AM1
  {0x0004, 2}, // AL2
  {0x0007, 1}, // AM2
  {0x0008, 2}, // AL3
  {0x000B, 1}, // AM3
  {0x000C, 2}, // HY1
  {0x000F, 1}, // Add
  {0x0014, 2}, // USP
  {0x0017, 1}, // dp
  {0x0018, 1}, // Sft
  {0x001C, 2}, // TRL
  {0x0020, 2}, // TRH
  {0x0023, 1}, // Unt
  {0x0024, 1}, // LCK
  // Add additional parameters here as needed
};

// Function to read a parameter from a specific device
uint8_t readModbusParameter(uint8_t deviceID, const ModbusParameter& param, uint16_t* buffer) {
  node.setSlave(deviceID);
  uint8_t result = node.readHoldingRegisters(param.address, param.count);
  if (result == node.ku8MBSuccess) {
    for (uint8_t i = 0; i < param.count; i++) {
      buffer[i] = node.getResponseBuffer(i);
    }
  }
  return result;
}

// Setup and loop functions would go here...

// Example function to read all parameters from all devices
void readAllDevices() {
  uint16_t dataBuffer[2]; // Assuming we won't read more than 2 words at once
  uint8_t deviceAddresses[] = {11, 12, 13, 14, 15}; // Device addresses

  for (uint8_t device : deviceAddresses) {
    Serial.print("Reading from device ");
    Serial.println(device);
    
    for (const ModbusParameter& param : modbusTable) {
      if (readModbusParameter(device, param, dataBuffer) == node.ku8MBSuccess) {
        // Handle the successful read, for example, print the data
        Serial.print("Parameter at address 0x");
        Serial.print(param.address, HEX);
        Serial.print(": ");
        for (uint8_t i = 0; i < param.count; i++) {
          Serial.print(dataBuffer[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
      } else {
        // Handle read error
        Serial.println("Failed to read parameter");
      }
    }
  }
}
