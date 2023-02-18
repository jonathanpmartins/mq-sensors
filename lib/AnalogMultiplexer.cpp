#include <Arduino.h>
#include <iostream>

using namespace std;

#define S0 25
#define S1 26
#define S2 27
#define S3 14

class AnalogMultiplexer {
public:
  int pin;

  const int PINS[4] = {S0, S1, S2, S3};

  const int CHANNELS[16][4] = {
      {LOW, LOW, LOW, LOW},    {HIGH, LOW, LOW, LOW},
      {LOW, HIGH, LOW, LOW},   {HIGH, HIGH, LOW, LOW},
      {LOW, LOW, HIGH, LOW},   {HIGH, LOW, HIGH, LOW},
      {LOW, HIGH, HIGH, LOW},  {HIGH, HIGH, HIGH, LOW},
      {LOW, LOW, LOW, HIGH},   {HIGH, LOW, LOW, HIGH},
      {LOW, HIGH, LOW, HIGH},  {HIGH, HIGH, LOW, HIGH},
      {LOW, LOW, HIGH, HIGH},  {HIGH, LOW, HIGH, HIGH},
      {LOW, HIGH, HIGH, HIGH}, {HIGH, HIGH, HIGH, HIGH},
  };

  AnalogMultiplexer(int p) { pin = p; }

  void setup() {
    pinMode(pin, INPUT);

    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    setChannel(0);
  }

  void setChannel(int channel) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(PINS[i], CHANNELS[channel][i]);
    }
  }

  float read(int channel) {
    setChannel(channel);
    return analogRead(pin);
  }

  float readMilliVolts(int channel) {
    setChannel(channel);

    return analogReadMilliVolts(pin);
  }
};