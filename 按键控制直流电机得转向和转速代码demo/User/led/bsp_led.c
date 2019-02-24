#include "./led/bsp_led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*初始化LED端口时钟*/
	RCC_APB2PeriphClockCmd(LED_GPIO_PORT_Clock,ENABLE);
	
	/*初始化LED2引脚*/
	GPIO_InitStruct.GPIO_Pin = LED_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	/*初始化LED2端口*/
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	
}
