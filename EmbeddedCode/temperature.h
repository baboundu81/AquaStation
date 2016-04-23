#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

/*--------------------------------------- Defines ---------------------------------------*/
#define TEMP_ONE_WIRE_PIN             7
#define TEMP_DS18B20_ADDR             0x28

/*-------------------------------------- Functions  -------------------------------------*/
void TEMP_TaskInit (void);
void TEMP_TaskMain (void * pvParams);

/*---------------------------------- External variables  --------------------------------*/
extern boolean COMM_Send_Temperature;

#endif
