#include "../MQADS1115.cpp"
#include "ADS1X15.h"
#include <MQUnifiedsensor.h>
#include <map>

using namespace std;

class Mq3Sensor {
  MQADS1115 *ads;
  uint8_t channel;
  MQUnifiedsensor mq;

  const char *gases[6] = {"LPG", "CH4", "CO", "Alcohol", "Benzene", "Hexane"};
  std::map<std::string, std::map<int, float>> regression;
  std::map<std::string, float> results;

  bool shouldCalibrate = false;

public:
  Mq3Sensor(MQADS1115 *a, uint8_t c, bool s = false)
      : mq("ESP32", 5.0, 15, A0, "MQ-3") {
    shouldCalibrate = s;
    this->ads = a;
    this->channel = c;

    /*
      Exponential regression:
      Gas    | a      | b
      LPG    | 44771  | -3.245
      CH4    | 2*10^31| 19.01
      CO     | 521853 | -3.821
      Alcohol| 0.3934 | -1.504
      Benzene| 4.8387 | -2.68
      Hexane | 7585.3 | -2.849
    */

    regression["LPG"][0] = 44771;
    regression["LPG"][1] = -3.245;

    regression["CH4"][0] = 2 * 10 ^ 31;
    regression["CH4"][1] = 19.01;

    regression["CO"][0] = 521853;
    regression["CO"][1] = -3.821;

    regression["Alcohol"][0] = 0.3934;
    regression["Alcohol"][1] = -1.504;

    regression["Benzene"][0] = 4.8387;
    regression["Benzene"][1] = -2.68;

    regression["Hexane"][0] = 7585.3;
    regression["Hexane"][1] = -2.849;
  }

  void setRegressionForGas(std::string gas) {
    mq.setA(regression[gas][0]);
    mq.setB(regression[gas][1]);
  }

  uint16_t getValue() { return this->ads->getChannelValue(channel); }

  void setup() {

    Serial.println("Connecting to ADS...");
    while (!this->ads->isConnected()) {
      Serial.print(".");
    }
    Serial.println("...connected!");

    mq.setRegressionMethod(1); //_PPM =  a*ratio^b

    // mq.serialDebug(true);
    mq.init();

    mq.setR0(0.5);
  }

  float calibrate() {
    float result = 0;
    if (getValue() > 0) {
      Serial.println("Calibrating, please wait.");
      float calcR0 = 0;
      for (int i = 1; i <= 10; i++) {
        mq.setADC(getValue());
        calcR0 += mq.calibrate(60);
        Serial.print(".");
        delay(100);
      }
      result = calcR0 / 10;
      mq.setR0(result);

      Serial.print("R0 = ");
      Serial.println(result);
    }
    return result;
  }

  void loop() {
    if (shouldCalibrate) {
      calibrate();
    } else {

      uint16_t value = getValue();

      for (int i = 0; i < 6; i++) {

        setRegressionForGas(gases[i]);

        mq.setADC(value);

        float ppm = mq.readSensor();

        mq.update();

        // if ((a < 0.0) == (b < 0.0) &&
        //     std::abs(b) > std::numeric_limits<double>::max() - std::abs(a)) {
        //   //  Addition would overflow...
        // }

        Serial.print("loop(): gas: ");
        Serial.println(gases[i]);

        Serial.print("loop(): ppm: ");
        Serial.println(ppm);

        results[gases[i]] = ppm;

        // mq.update();

        Serial.println("-------------------");
      }

      Serial.println("=================================================");

      // Serial.print("loop(): getValue(): ");
      // Serial.println(value);

      // Serial.print("loop(): mq.readSensor(): ");
      // Serial.println();
      // mq.serialDebug();
    }
  }

  // int getPpmOfGas(char gas) {}
};

// concentrations MQ2
// /*
//     Exponential regression:
//     Gas    | a      | b
//     H2     | 987.99 | -2.162
//     LPG    | 574.25 | -2.222
//     CO     | 36974  | -3.109
//     Alcohol| 3616.1 | -2.675
//     Propane| 658.71 | -2.168
//   */