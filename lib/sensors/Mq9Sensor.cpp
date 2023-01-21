#include "Sensor.cpp"

class Mq9Sensor : public Sensor {
public:
  Mq9Sensor(float signal) : Sensor(signal) {}

  void toSerial() {
    unsigned int coPpm = map(signal, 0, 4095, 20, 2000);
    unsigned int ch4Ppm = map(signal, 0, 4095, 500, 10000);
    unsigned int lpgPpm = map(signal, 0, 4095, 500, 10000);
    Serial.print(" MQ9: " + String(signal) + " - ");
    Serial.print(" " + String(coPpm) + "(CO)");
    Serial.print(" " + String(ch4Ppm) + "(CH4)");
    Serial.print(" " + String(lpgPpm) + "(LPG)");

    Serial.println("");
  };
};