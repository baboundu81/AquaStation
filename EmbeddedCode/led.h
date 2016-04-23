#ifndef __LED_H__
#define __LED_H__

/*--------------------------------------- Defines ---------------------------------------*/
#define LED_PIN                       13

/*--------------------------------------- Functions  ------------------------------------*/
void LED_TaskInit (void);
void LED_TaskMain (void * pvParams);

#endif
