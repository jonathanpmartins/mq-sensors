#include "Sensor.cpp"

class Mq8Sensor : public Sensor {
public:
  Mq8Sensor(float signal) : Sensor(signal) {}

  void toSerial() {
    unsigned int ppm = map(signal, 0, samples - 1, 100, 10000);
    Serial.print(" MQ8: " + String(signal) + " - ");
    Serial.print(" " + String(ppm) + "(H2)");

    Serial.println("");
  };
};