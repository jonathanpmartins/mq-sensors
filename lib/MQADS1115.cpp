#include "ADS1X15.h"
#include <Arduino.h>
#include <iostream>

#pragma once

class MQADS1115 {
  volatile bool RDY;

  static MQADS1115 *instances[3];

  static void ads0Ready() {
    if (MQADS1115::instances[0] != NULL) {
      MQADS1115::instances[0]->adsReady();
    }
  }

  static void ads1Ready() {
    if (MQADS1115::instances[1] != NULL) {
      MQADS1115::instances[1]->adsReady();
    }
  }

  static void ads2Ready() {
    if (MQADS1115::instances[2] != NULL) {
      MQADS1115::instances[2]->adsReady();
    }
  }

public:
  ADS1115 ads;

  uint8_t channel = 0;
  uint16_t values[4] = {0, 0, 0, 0};

  int attachPin;
  float tagetVolts = 5.0;
  uint8_t referenceChannel = 0;

  uint8_t instanceIndex;

  MQADS1115(uint8_t index, int address, int pin, float volts = 5.0) {
    RDY = false;

    instanceIndex = index;

    attachPin = pin;
    tagetVolts = volts;

    ADS1115 ads(address);
  }

  void adsReady() { RDY = true; }

  bool isConnected() { return ads.isConnected(); }

  void setup() {
    ads.begin();
    ads.setGain(0);     // 6.144 volt
    ads.setDataRate(4); // default

    // SET ALERT RDY PIN
    ads.setComparatorThresholdHigh(0x8000);
    ads.setComparatorThresholdLow(0x0000);
    ads.setComparatorQueConvert(0);

    // SET INTERRUPT HANDLER TO CATCH CONVERSION READY
    pinMode(attachPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(attachPin), ads0Ready, RISING);
    instances[instanceIndex] = this;

    ads.setMode(0);       // continuous mode
    ads.readADC(channel); // trigger first read
  }

  void handleAndCallNextChannel() {
    if (RDY) {

      int16_t value = ads.getValue();

      if (value > 0) {
        values[channel] = (value / tagetVolts) * ads.getMaxVoltage();
      } else {
        values[channel] = 0;
      }

      channel++;

      if (channel >= 4) {
        channel = 0;
      }

      ads.readADC(channel);

      RDY = false;
    }
  }

  uint16_t getChannelValue(uint8_t channel) {
    return values[channel];
    if (channel == referenceChannel) {
      return values[channel];
    } else {
      uint16_t value = values[channel];
      uint16_t reference = values[referenceChannel];
      return map(value, 0, reference, 0, 32767);
    }
  }

  void setReferenceChannel(uint8_t channel) { referenceChannel = channel; }

  void loop() { handleAndCallNextChannel(); }
};