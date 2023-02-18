#include "../MQADS1115.cpp"
#include "ADS1X15.h"

class Mq3Sensor {
  MQADS1115 *ads;
  uint8_t channel;

public:
  Mq3Sensor(MQADS1115 *a, uint8_t c) {
    this->ads = a;
    this->channel = c;
  }

  uint16_t getValue() { return this->ads->getChannelValue(channel); }
};