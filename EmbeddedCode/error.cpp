#include "common.h"
#include "error.h"

/*----------------------------------- Global variables  ---------------------------------*/
static uint8_t ERROR_LedPinValue;

/*-------------------------------------- Functions  -------------------------------------*/
void vApplicationStackOverflowHook (portCHAR * ApplicationName) {
  // Error led init
  pinMode(ERROR_LED_PIN, OUTPUT);
  
  // Error led off
  digitalWrite(ERROR_LED_PIN, LOW);

  // die
  while (true)
  {
    ERROR_LedPinValue = ERROR_LedPinValue == LOW ? HIGH : LOW;
    digitalWrite(ERROR_LED_PIN, ERROR_LedPinValue);
    _delay_ms(250);
  }  
}
