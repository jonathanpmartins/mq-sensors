#include "../lib/AnalogMultiplexer.cpp"
#include "calibration.cpp"
#include <Arduino.h>

int samples = 4096;

#define SignalPin 36

AnalogMultiplexer mux(SignalPin);

void setup() {

  mux.setup();

  Serial.begin(115200);
  while (!Serial)
    ;

  delay(500);
}

// float toFloat(int value) { return static_cast<float>(value); }

// float ajustSignal(float value, float fromVolts, float toVolts,
//                   int resistor1InOhms, int resistor2InOhms) {

//   float voltageRatio = toVolts / fromVolts;

//   float resistor1 = toFloat(resistor1InOhms);
//   float resistor2 = toFloat(resistor2InOhms);

//   float resistorRatio = resistor2 / (resistor1 + resistor2);

//   return (value * voltageRatio) / resistorRatio;
// }

// float analogReadChannel(int pin, int channel) {

//   // todo, set channel

//   return analogRead(pin);
// }

// float getSignal(int pin, int channel) {
//   float analog = analogReadChannel(pin, channel);

//   Serial.print("- analog: ");
//   Serial.print(analog);

//   int rounded = round(analog);
//   float calibrated = (int)ADC_LUT[rounded];
//   float ajusted = ajustSignal(calibrated, 5.00, 3.30, 270, 510);

//   return ajusted;
// }

// int calculatePpm(float signal, int min, int max) {
//   float minPpm = toFloat(min);
//   float maxPpm = toFloat(max);
//   return round((signal * ((maxPpm - minPpm) / toFloat(samples))) +
//                (signal > 0 ? minPpm : 0));
// }

// float toPercent(float signal) { return (signal * 100.00) / toFloat(samples);
// }

// int globalPpm = 1;

// void getInfo(int pin, int minSensorPpm, int maxSensorPpm) {

//   float signal = getSignal(pin, 0);

//   int ppm = calculatePpm(signal, minSensorPpm, maxSensorPpm);

//   globalPpm = (9.0 * globalPpm + ppm) / 10;

//   int milliVolts = analogReadMilliVolts(pin);

//   // unsigned long percent = map(signal, 0, 4095, 0, 100);
//   Serial.print(", milli-volts: ");
//   Serial.print(milliVolts);
//   Serial.print(", signal: ");
//   Serial.print(signal);
//   Serial.print(", ppm: ");
//   Serial.print(ppm);
//   Serial.print(", globalPpm: ");
//   Serial.print(globalPpm);
//   Serial.print(", percent: ");
//   Serial.print(toPercent(signal));
// }

void loop() {

  float signal;
  unsigned long ppm;
  int coPpm;
  int ch4Ppm;
  int lpgPpm;
  int h2Ppm;

  signal = mux.read(0);

  lpgPpm = map(signal, 0, 4095, 200, 5000);
  int butPpm = map(signal, 0, 4095, 300, 5000);
  ch4Ppm = map(signal, 0, 4095, 5000, 20000);
  h2Ppm = map(signal, 0, 4095, 300, 5000);
  int alPpm = map(signal, 0, 4095, 100, 2000);
  Serial.print(" MQ2: " + String(signal) + " - ");
  Serial.print(" " + String(lpgPpm) + "(LPG)");
  Serial.print(" " + String(butPpm) + "(BUT)");
  Serial.print(" " + String(ch4Ppm) + "(CH4)");
  Serial.print(" " + String(h2Ppm) + "(H2)");
  Serial.print(" " + String(alPpm) + "(AL)");

  Serial.println("");

  signal = mux.read(1);
  float mapped = map(signal, 0, 4095, 5, 1000);
  Serial.print(" MQ3: " + String(signal) + " - ");
  Serial.print(" " + String(mapped / 100) + "(Alcohol gas)");

  Serial.println("");

  signal = mux.read(2);
  ppm = map(signal, 0, 4095, 200, 10000);
  Serial.print(" MQ4: " + String(signal) + " - ");
  Serial.print(" " + String(ppm) + "(CH4)");

  Serial.println("");

  signal = mux.read(3);
  ppm = map(signal, 0, 4095, 200, 10000);
  Serial.print(" MQ5: " + String(signal) + " - ");
  Serial.print(" " + String(ppm) + "(CH4/LPG)");

  Serial.println("");

  signal = mux.read(4);
  ppm = map(signal, 0, 4095, 200, 10000);
  Serial.print(" MQ6: " + String(signal) + " - ");
  Serial.print(" " + String(ppm) + "(LPG)");

  Serial.println("");

  signal = mux.read(5);
  ppm = map(signal, 0, 4095, 20, 2000);
  Serial.print(" MQ7: " + String(signal) + " - ");
  Serial.print(" " + String(ppm) + "(CO)");

  Serial.println("");

  signal = mux.read(6);
  ppm = map(signal, 0, 4095, 100, 10000);
  Serial.print(" MQ8: " + String(signal) + " - ");
  Serial.print(" " + String(ppm) + "(H2)");

  Serial.println("");

  signal = mux.read(7);
  coPpm = map(signal, 0, 4095, 20, 2000);
  ch4Ppm = map(signal, 0, 4095, 500, 10000);
  lpgPpm = map(signal, 0, 4095, 500, 10000);
  Serial.print(" MQ9: " + String(signal) + " - ");
  Serial.print(" " + String(coPpm) + "(CO)");
  Serial.print(" " + String(ch4Ppm) + "(CH4)");
  Serial.print(" " + String(lpgPpm) + "(LPG)");

  Serial.println("");

  // delay(100);

  // 300-10000

  // getInfo(SignalPin, 300, 10000);

  // Serial.print(" MQ3: ");
  // getInfo(MQ3pin);

  // Serial.print(" MQ4: ");
  // getInfo(MQ4pin, 300, 10000);

  // Serial.print(" MQ5: ");
  // getInfo(MQ5pin, 200, 10000);

  // Serial.print(" MQ6: ");
  // getInfo(MQ6pin, 300, 10000);

  // Serial.print(" MQ7: ");
  // getInfo(MQ7pin, 20, 2000);

  // Serial.print(" MQ8: ");
  // getInfo(MQ8pin, 100, 1000);

  // Serial.print(" MQ9: ");
  // getInfo(MQ9pin, 10, 10000);

  Serial.println("");
  Serial.println("-------------------------------------------");

  delay(2000); // wait 2s for next reading
}