#include "calibration.cpp"
#include <Arduino.h>

int samples = 4096;

#define ThresholdInPpm 1200

#define MQ2pin 36
#define MQ3pin 39
#define MQ4pin 34
#define MQ5pin 35
#define MQ6pin 32
#define MQ7pin 33
#define MQ8pin 25
#define MQ9pin 26

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  pinMode(MQ2pin, INPUT);
  pinMode(MQ3pin, INPUT);
  pinMode(MQ4pin, INPUT);
  pinMode(MQ5pin, INPUT);
  pinMode(MQ6pin, INPUT);
  pinMode(MQ7pin, INPUT);
  pinMode(MQ8pin, INPUT);
  pinMode(MQ9pin, INPUT);
}

float toFloat(int value) { return static_cast<float>(value); }

float ajustSignal(float value, float fromVolts, float toVolts,
                  int resistor1InOhms, int resistor2InOhms) {

  float voltageRatio = toVolts / fromVolts;

  float resistor1 = toFloat(resistor1InOhms);
  float resistor2 = toFloat(resistor2InOhms);

  float resistorRatio = resistor2 / (resistor1 + resistor2);

  return (value * voltageRatio) / resistorRatio;
}

float getSignal(int pin) {
  float analog = analogRead(pin);

  int rounted = round(analog);
  float calibrated = (int)ADC_LUT[rounted];

  return ajustSignal(calibrated, 5.00, 3.30, 270, 510);
}

int calculatePpm(float signal, int min, int max) {
  float minPpm = toFloat(min);
  float maxPpm = toFloat(max);
  return round((signal * ((maxPpm - minPpm) / toFloat(samples))) +
               (signal > 0 ? minPpm : 0));
}

float toPercent(float signal) { return (signal * 100.00) / toFloat(samples); }

void getInfo(int pin, int minSensorPpm, int maxSensorPpm) {

  float signal = getSignal(pin);

  int ppm = calculatePpm(signal, minSensorPpm, maxSensorPpm);
  if (ppm > ThresholdInPpm) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }

  int milliVolts = analogReadMilliVolts(pin);

  // unsigned long percent = map(signal, 0, 4095, 0, 100);
  Serial.print("- milli-volts: ");
  Serial.print(milliVolts);
  Serial.print(", signal: ");
  Serial.print(signal);
  Serial.print(", ppm: ");
  Serial.print(ppm);
  Serial.print(", percent: ");
  Serial.print(toPercent(signal));
}

void loop() {

  Serial.print(" MQ2 ");
  getInfo(MQ5pin, 300, 10000);

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

  delay(1000); // wait 2s for next reading
}