#include "Sensor.cpp"

class Mq3Sensor : public Sensor {
public:
  Mq3Sensor(float signal) : Sensor(signal) {}

  void toSerial() {
    float mapped = map(signal, 0, samples - 1, 5, 1000);
    Serial.print(" MQ3: " + String(signal) + " - ");
    Serial.print(" " + String(mapped / 100) + "(Alcohol gas)");

    Serial.println("");
  }
};