#include "Sensor.cpp"

class Mq6Sensor : public Sensor {
public:
  Mq6Sensor(float signal) : Sensor(signal) {}

  void toSerial() {
    unsigned int ppm = map(signal, 0, samples - 1, 200, 10000);
    Serial.print(" MQ6: " + String(signal) + " - ");
    Serial.print(" " + String(ppm) + "(LPG)");

    Serial.println("");
  };
};