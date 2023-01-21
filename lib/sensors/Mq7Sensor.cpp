#include "Sensor.cpp"

class Mq7Sensor : public Sensor {
public:
  Mq7Sensor(float signal) : Sensor(signal) {}

  void toSerial() {
    unsigned int ppm = map(signal, 0, samples - 1, 20, 2000);
    Serial.print(" MQ7: " + String(signal) + " - ");
    Serial.print(" " + String(ppm) + "(CO)");

    Serial.println("");
  };
};