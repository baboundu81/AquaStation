#include "common.h"
#include "temperature.h"
#include "comm.h"

/*----------------------------------- Global variables  ---------------------------------*/
float   TEMP_Value;
static OneWire OneWire_dev(TEMP_ONE_WIRE_PIN);

/*---------------------------------- External variables  --------------------------------*/
extern QueueHandle_t COMM_CommandQueue;

/*-------------------------------------- Functions  -------------------------------------*/
/*
 * Init the task to measuse temperature
 */
void TEMP_TaskInit (void) {
  DEBUG_Print("TEMP : Init...");

  // Init temperature variable
  TEMP_Value = 0.0;
  
  xTaskCreate(TEMP_TaskMain, (const portCHAR*) "TEMP task", 200, NULL, 3, NULL);
  
  DEBUG_Println("OK");
}

/*
 * Function to get the temperature from the DS18B20
 * 
 * return true if no error occured, false instead;
 */
boolean TEMP_GetTemperature(float * temp) {
  uint8_t data[9], addr[8];
  TickType_t xLastWakeTime;

  // Reset the OneWire device research
  OneWire_dev.reset_search();
  
  // Search an attached OneWire device
  if(!OneWire_dev.search(addr)) {
    /* If device is found reset OneWire communication
     * and return error
     */
    Serial.print("TEMP : No OneWire found on pin ");
    Serial.println(TEMP_ONE_WIRE_PIN);
    OneWire_dev.reset_search();
    return (false);
  }

  // Check the crc
  if (OneWire::crc8 (addr, 7) != addr[7]) {
    // If the crc fails return error
    Serial.println("TEMP : CRC error");
    return (false);
  }

  // Check the OneWire device address
  if (addr[0] != TEMP_DS18B20_ADDR) {
    // If the address does not match the expected device address return error
    Serial.print("TEMP : The address of the device is not ");
    Serial.print(TEMP_DS18B20_ADDR);
    Serial.print("but ");
    Serial.println(addr[0]);
    return (false);
  }

  // Reset the bus
  OneWire_dev.reset(); 
  // Select the device
  OneWire_dev.select(addr);
  
  // Get the current time
  xLastWakeTime = xTaskGetTickCount();
  // Start a temperature measure
  OneWire_dev.write(0x44, 1);
  // Wait the end of the measure
  vTaskDelayUntil(&xLastWakeTime, (800 / portTICK_PERIOD_MS));
   
  // Reset the bus
  OneWire_dev.reset(); 
  // Select the device
  OneWire_dev.select(addr);
  // Get the scratchpad
  OneWire_dev.write(0xBE);    

  // Read the scratchpad and save the data
  for (byte i = 0; i < 9; i++) {
    data[i] = OneWire_dev.read();     
  }

  // Compute the temperature value
  *temp = ((data[1] << 8) | data[0]) * 0.0625; 

  // No error return true
  return(true);
}

/*
 * Main code for the temperature task
 */

void TEMP_TaskMain (void * pvParams) {
  // Declare a tick type to get the last tick
  TickType_t xLastWakeTime = xTaskGetTickCount();

  // Command to be sent to the comm task
  COMM_Command_t cmd;

  // Main loop of the task
  while(true) {
    cmd = COMM_SEND_TEMP;
    if (!TEMP_GetTemperature(&TEMP_Value)) {
      Serial.println("TEMP : Error reading temperature");
    } else {
//      DEBUG_Print("TEMP : Current temperature is ");
//      DEBUG_Print(TEMP_Value);
//      DEBUG_Println("°C");
      // Tell the COMM task to send the value to the DB
      xQueueSend(COMM_CommandQueue, &cmd, 0);
    }
    // Wait for a delay of 2s
    vTaskDelayUntil(&xLastWakeTime, (30000 / portTICK_PERIOD_MS));
  }
}

