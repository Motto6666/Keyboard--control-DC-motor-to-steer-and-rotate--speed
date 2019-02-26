#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "stm32f10x.h"

#define LED_GPIO_PORT_Clock    RCC_APB2Periph_GPIOC
#define LED_GPIO_PORT          GPIOC

#define LED_PIN               GPIO_Pin_3 	

#define LED_ON                GPIO_ResetBits(LED_GPIO_PORT, LED_PIN)
#define LED_OFF               GPIO_SetBits(LED_GPIO_PORT, LED_PIN)

void LED_GPIO_Config(void);

#endif /*__BSP_LED_H*/
