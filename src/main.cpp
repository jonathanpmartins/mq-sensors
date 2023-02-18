#include "../lib/MQADS1115.cpp"
#include "../lib/sensors/Mq3Sensor.cpp"
#include "ADS1X15.h"
#include <Arduino.h>
#include <Wire.h>
#include <esp_task_wdt.h>
#include <iostream>

TaskHandle_t CPU0;
TaskHandle_t CPU1;

// volatile bool MQADS1115::RDY;

MQADS1115 *MQADS1115::instances[3] = {NULL, NULL, NULL};

MQADS1115 ads0(0, 0x48, 4);
Mq3Sensor mq3(&ads0, 1);

void loop0() {

  Serial.println(mq3.getValue());

  // mq3.getValue();

  // //

  // // uint16_t value = ads0.getChannelValue(i);

  // for (int i = 0; i < 4; i++) {

  //   uint16_t value = ads0.getChannelValue(i);

  //   if (i > 0) {
  //     Serial.print("     ");
  //   }
  //   Serial.print("[");
  //   Serial.print(i);
  //   Serial.print("]: ");
  //   Serial.print(value);
  // }

  // Serial.println("");

  delay(500);
}

void loop1() { ads0.loop(); }

void runTask(int cpu) {
  Serial.println(cpu);
  while (true) {
    if (cpu == 0) {
      loop0();
    }
    if (cpu == 1) {
      loop1();
    }

    esp_task_wdt_reset();
  }
}

void taskCPU0(void *parameters) { runTask(0); }
void taskCPU1(void *parameters) { runTask(1); }

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  ads0.setup();

  const int stackSize = 32768;

  xTaskCreatePinnedToCore(taskCPU0, "CPU0", stackSize, NULL, 0, &CPU0, 0);
  xTaskCreatePinnedToCore(taskCPU1, "CPU1", stackSize, NULL, 1, &CPU1, 1);
}

void loop() { vTaskDelete(NULL); }