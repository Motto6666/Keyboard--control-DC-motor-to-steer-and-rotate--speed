#include "stm32f10x.h"
#include "./motor-control/bsp_motor_control.h"
#include "./key/bsp_exti_key.h"
#include "./basetime/bsp_basetime.h"
#include "./led/bsp_led.h"

volatile uint16_t CCR1_Val = 8;//PWM波占空比初始值为80%

int main(void)
{
	motor_control_Config();//初始化电机控制
	KEY_EXTI_Config();//初始化按键中断
	BASIC_TIM_Init();//初始化基本定时器
	LED_GPIO_Config();//初始化LED
	
	while(1)
	{
		TIM_SetCompare1(GENERAL_TIM,CCR1_Val);
	}
}

