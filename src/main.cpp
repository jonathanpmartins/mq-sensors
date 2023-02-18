#include "../lib/AnalogMultiplexer.cpp"
#include "../lib/calibration.cpp"
#include "../lib/sensors/Mq2Sensor.cpp"
#include "../lib/sensors/Mq3Sensor.cpp"
#include "../lib/sensors/Mq4Sensor.cpp"
#include "../lib/sensors/Mq5Sensor.cpp"
#include "../lib/sensors/Mq6Sensor.cpp"
#include "../lib/sensors/Mq7Sensor.cpp"
#include "../lib/sensors/Mq8Sensor.cpp"
#include "../lib/sensors/Mq9Sensor.cpp"
#include <Arduino.h>
// Include the library
#include <MQUnifiedsensor.h>
/************************Hardware Related
 * Macros************************************/
#define Board                                                                  \
  ("ESP-32") // Wemos ESP-32 or other board, whatever have ESP32 core.

// https://www.amazon.com/HiLetgo-ESP-WROOM-32-Development-Microcontroller-Integrated/dp/B0718T232Z
// (Although Amazon shows ESP-WROOM-32 ESP32 ESP-32S, the board is the
// ESP-WROOM-32D)
#define Pin (12) // check the esp32-wroom-32d.jpg image on ESP32 folder

/***********************Software Related
 * Macros************************************/
#define Type                                                                   \
  ("MQ-2") // MQ2 or other MQ Sensor, if change this verify your a and b values.
#define Voltage_Resolution                                                     \
  (5) // 3V3 <- IMPORTANT. Source:
      // https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
#define ADC_Bit_Resolution                                                     \
  (12) // ESP-32 bit resolution. Source:
       // https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
#define RatioMQ2CleanAir (9.83) // RS / R0 = 9.83 ppm
/*****************************Globals***********************************************/
MQUnifiedsensor MQ2(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
/*****************************Globals***********************************************/

AnalogMultiplexer mux(12);

void setup() {

  mux.setup();
  mux.setChannel(15);

  Serial.begin(115200);
  while (!Serial)
    ;

  // Set math model to calculate the PPM concentration and the value of
  // constants
  MQ2.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ2.setA(574.25);
  MQ2.setB(-2.222); // Configure the equation to to calculate concentrations

  /*
      Exponential regression:
      Gas    | a      | b
      H2     | 987.99 | -2.162
      LPG    | 574.25 | -2.222
      CO     | 36974  | -3.109
      Alcohol| 3616.1 | -2.675
      Propane| 658.71 | -2.168
    */

  // MQ2.serialDebug(true);
  MQ2.init();

  delay(1000);

  MQ2.serialDebug(true);

  MQ2.setR0(10);

  /*****************************  MQ CAlibration
   * ********************************************/

  delay(500);
}

void loop() {

  MQ2.readSensor();
  MQ2.update();

  // readSensor

  // Serial.println(MQ2.getRS());

  MQ2.serialDebug();

  // Serial.print();
  // Serial.println(" PPM");

  // Mq2Sensor sensor2(mux.read(15));
  // sensor2.toSerial();

  // Mq3Sensor sensor3(mux.read(1));
  // sensor3.toSerial();

  // Mq4Sensor sensor4(mux.read(2));
  // sensor4.toSerial();

  // Mq5Sensor sensor5(mux.read(3));
  // sensor5.toSerial();

  // Mq6Sensor sensor6(mux.read(4));
  // sensor6.toSerial();

  // // Mq7Sensor sensor7(mux.read(5));
  // // sensor7.toSerial();

  // Mq8Sensor sensor8(mux.read(6));
  // sensor8.toSerial();

  // Mq9Sensor sensor9(mux.read(7));
  // sensor9.toSerial();

  // Serial.println("");
  // Serial.println("-------------------------------------------");

  delay(750);
}