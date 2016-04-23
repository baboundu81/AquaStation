#include "common.h"
#include "temperature.h"
#include "led.h"
#include "error.h"
#include "comm.h"

#define DEBUG

void setup() {
  // Init Serial debug
  Serial.begin(115200);
  
  // Init for each task
  COMM_TaskInit();
  //LED_TaskInit();
  TEMP_TaskInit();
  

  // Start the scheduler
  vTaskStartScheduler();
}

void loop() {
  // Nothing to do
}
