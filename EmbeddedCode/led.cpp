#include "common.h"
#include "led.h"

/*----------------------------------- Global variables  ---------------------------------*/
static uint8_t LED_pinValue;

/*-------------------------------------- Functions  -------------------------------------*/
/*
 * Init task to blink the led at 2Hz. Used to now the system is alive
 */
void LED_TaskInit (void) {
  DEBUG_Print("LED : Init...");

  LED_pinValue = LOW;
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_pinValue);
  xTaskCreate(LED_TaskMain, (const portCHAR*) "LED Task", 50, NULL, 3, NULL);
  
  DEBUG_Println("OK");
}

/* 
 * Taks to manage the LED 
 */
void LED_TaskMain (void * pvParams) {
  // Declare a tick type to get the last tick
  TickType_t xLastWakeTime = xTaskGetTickCount();

  // Main loop of the task
  while(true) {
    // Toggle the pin value
    LED_pinValue = LED_pinValue == LOW ? HIGH : LOW;
    
    // Set the new state of the pin
    digitalWrite(LED_PIN, LED_pinValue);

    // Wait for a delay of 500ms
    vTaskDelayUntil(&xLastWakeTime, (500 / portTICK_PERIOD_MS));
  }
}
