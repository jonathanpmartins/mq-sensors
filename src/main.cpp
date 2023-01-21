#include "../lib/AnalogMultiplexer.cpp"
#include "../lib/calibration.cpp"
#include "../lib/sensors/Mq2Sensor.cpp"
#include "../lib/sensors/Mq3Sensor.cpp"
#include "../lib/sensors/Mq4Sensor.cpp"
#include "../lib/sensors/Mq5Sensor.cpp"
#include "../lib/sensors/Mq6Sensor.cpp"
#include "../lib/sensors/Mq7Sensor.cpp"
#include "../lib/sensors/Mq8Sensor.cpp"
#include "../lib/sensors/Mq9Sensor.cpp"
#include <Arduino.h>

AnalogMultiplexer mux(36);

void setup() {

  mux.setup();

  Serial.begin(115200);
  while (!Serial)
    ;

  delay(500);
}

void loop() {

  Mq2Sensor sensor2(mux.read(0));
  sensor2.toSerial();

  Mq3Sensor sensor3(mux.read(1));
  sensor3.toSerial();

  Mq4Sensor sensor4(mux.read(2));
  sensor4.toSerial();

  Mq5Sensor sensor5(mux.read(3));
  sensor5.toSerial();

  Mq6Sensor sensor6(mux.read(4));
  sensor6.toSerial();

  Mq7Sensor sensor7(mux.read(5));
  sensor7.toSerial();

  Mq8Sensor sensor8(mux.read(6));
  sensor8.toSerial();

  Mq9Sensor sensor9(mux.read(7));
  sensor9.toSerial();

  Serial.println("");
  Serial.println("-------------------------------------------");

  delay(2000); // wait 2s for next reading
}