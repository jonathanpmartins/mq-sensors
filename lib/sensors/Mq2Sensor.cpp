#include "Sensor.cpp"

class Mq2Sensor : public Sensor {
public:
  Mq2Sensor(float signal) : Sensor(signal) {}

  void toSerial() {
    int lpgPpm = map(signal, 0, samples - 1, 200, 5000);
    int butPpm = map(signal, 0, samples - 1, 300, 5000);
    int ch4Ppm = map(signal, 0, samples - 1, 5000, 20000);
    int h2Ppm = map(signal, 0, samples - 1, 300, 5000);
    int alPpm = map(signal, 0, samples - 1, 100, 2000);

    Serial.print(" MQ2: " + String(signal) + " - ");
    Serial.print(" " + String(lpgPpm) + "(LPG)");
    Serial.print(" " + String(butPpm) + "(BUT)");
    Serial.print(" " + String(ch4Ppm) + "(CH4)");
    Serial.print(" " + String(h2Ppm) + "(H2)");
    Serial.print(" " + String(alPpm) + "(AL)");

    Serial.println("");
  }
};