#include "Sensor.cpp"

class Mq4Sensor : public Sensor {
public:
  Mq4Sensor(float signal) : Sensor(signal) {}

  void toSerial() {
    unsigned int ppm = map(signal, 0, samples - 1, 200, 10000);
    Serial.print(" MQ4: " + String(signal) + " - ");
    Serial.print(" " + String(ppm) + "(CH4)");

    Serial.println("");
  }
};