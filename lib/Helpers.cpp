#include "calibration.cpp"
#include <Arduino.h>

class Helpers {

  int averageOneTen = 1;
  int averageOneHundred = 1;
  int averageOneThousand = 1;

public:
  Helpers() {}

  float intToFloat(int value) { return static_cast<float>(value); }

  float ajustVoltageDividerSignal(float value, float fromVolts, float toVolts,
                                  int resistor1InOhms, int resistor2InOhms) {

    float voltageRatio = toVolts / fromVolts;

    float resistor1 = intToFloat(resistor1InOhms);
    float resistor2 = intToFloat(resistor2InOhms);

    float resistorRatio = resistor2 / (resistor1 + resistor2);

    return (value * voltageRatio) / resistorRatio;
  }

  float calibrateEspSignal(float signal) {
    int rounded = round(signal);
    return (int)ADC_LUT[rounded];
  }

  float toPercent(float signal, int samples) {
    return (signal * 100.00) / intToFloat(samples);
  }

  float averageLastTen(int value) {
    averageOneTen = (99.0 * averageOneTen + value) / 100;
    return averageOneTen;
  }

  float averageLastHundred(int value) {
    averageOneHundred = (99.0 * averageOneHundred + value) / 100;
    return averageOneHundred;
  }

  float averageLastThousand(int value) {
    averageOneThousand = (99.0 * averageOneThousand + value) / 100;
    return averageOneThousand;
  }
};