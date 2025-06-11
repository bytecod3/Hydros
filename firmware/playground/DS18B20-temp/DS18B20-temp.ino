#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void setup() {
  Serial.begin(9600);
  sensors.begin();

}

void loop() {
  sensors.requestTemperatures();
  Serial.print("deg Celcius: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" ,deg Faren: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(1000);
}
