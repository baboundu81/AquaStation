#ifndef __COMM_H__
#define __COMM_H__

/*--------------------------------------- Defines ---------------------------------------*/
// TODO : pin to communicate with Wifi module

/*--------------------------------------- Typedef  --------------------------------------*/
enum COMM_Command_t {
  COMM_SEND_TEMP = 1,
  COMM_SEND_PH
};

/*--------------------------------------- Functions  ------------------------------------*/
void COMM_TaskInit (void);
void COMM_TaskMain (void * pvParams);

#endif
