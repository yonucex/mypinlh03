#ifndef MyPinLM_h
#define MyPinLM_h

#include <Arduino.h>
#include <ModbusMaster.h>

// Define the structure for Modbus parameters
struct ModbusParameter {
  uint16_t address; // MODBUS data address in hexadecimal
  uint8_t count;    // Number of words to read or write
};

class MyPinLM {
  public:
    MyPinLM(uint8_t deviceID, Stream &port); // Constructor to initialize the MyPinLM object
    void begin(long baudRate); // Function to initialize the Modbus communication
    uint8_t readModbusParameter(uint8_t deviceID, const ModbusParameter& param, uint16_t* buffer); // Function to read a parameter
    void readAllDevices(); // Function to read all parameters from all devices

  private:
    ModbusMaster node;
    uint8_t _deviceID;
};

// Declare the Modbus parameters you want to read from each device
extern const ModbusParameter modbusTable[];

#endif // MyPinLM_h
