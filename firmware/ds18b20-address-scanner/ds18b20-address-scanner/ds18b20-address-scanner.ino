/**
* Use this code to scan for the addresses of connected DS18B20 temeperature sensors 
* Reference: Last minute engineers
*/
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// variable to hold device addresses
DeviceAddress Thermometer;

int deviceCount = 0;

void setup(void) {
  // start serial port
  Serial.begin(9600);

  // Start up the library
  sensors.begin();

  // locate devices on the bus
  Serial.println("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");

  Serial.println("Printing addresses...");
  for (int i = 0; i < deviceCount; i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" : ");
    sensors.getAddress(Thermometer, i);
    printAddress(Thermometer);
  }
}

void loop(void) {
}

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
}