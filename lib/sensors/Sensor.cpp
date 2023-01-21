#include <Arduino.h>
#include <iostream>

#pragma once

using namespace std;

class Sensor {
public:
  int samples = 4096;
  float signal;

  Sensor(float s) { signal = s; }

  // void toSerial(string value) { Serial.print(value); }
};