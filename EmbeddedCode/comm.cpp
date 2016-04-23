#include "common.h"
#include "comm.h"

/*----------------------------------- Global variables  ---------------------------------*/
QueueHandle_t COMM_CommandQueue = NULL;

/*---------------------------------- External variables  --------------------------------*/
extern float TEMP_Value;

/*-------------------------------------- Functions  -------------------------------------*/
/*
 * Init task to blink the COMM at 2Hz. Used to now the system is alive
 */
void COMM_TaskInit (void) {
  DEBUG_Print("COMM : Init...");

  COMM_CommandQueue = xQueueCreate(10, sizeof(COMM_Command_t));
  xTaskCreate(COMM_TaskMain, (const portCHAR*) "COMM Task", 200, NULL, 3, NULL);
  
  DEBUG_Println("OK");
}

/* 
 * Taks to manage the COMM 
 */
void COMM_TaskMain (void * pvParams) {
  // Main loop of the task
  COMM_Command_t cmd;
  
  while(true) {
    if (xQueueReceive(COMM_CommandQueue, &cmd, 0)) {
      switch(cmd) {
        case COMM_SEND_TEMP:
          // Send the temperature value to the data base
          DEBUG_Print("COMM : Current temperature is ");
          DEBUG_Print(TEMP_Value);
          DEBUG_Println("°C");
        break;
      }

    }
  }
}
