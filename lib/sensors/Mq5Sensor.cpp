#include "Sensor.cpp"

class Mq5Sensor : public Sensor {
public:
  Mq5Sensor(float signal) : Sensor(signal) {}

  void toSerial() {
    unsigned int ppm = map(signal, 0, samples - 1, 200, 10000);
    Serial.print(" MQ5: " + String(signal) + " - ");
    Serial.print(" " + String(ppm) + "(CH4/LPG)");

    Serial.println("");
  };
};