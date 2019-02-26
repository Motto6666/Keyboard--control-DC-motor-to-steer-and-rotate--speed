#include "stm32f10x.h"
#include "bsp_motor_control.h"
#include "bsp_exti_key.h"
#include "bsp_basetime.h"
#include "bsp_led.h"

volatile uint16_t Motor_Speed = 8;//PWM波占空比初始值为80%

int main(void)
{
	MOTOR_CONTROL_Config();//初始化电机控制
	KEY_EXTI_Config();//初始化按键
	BASIC_TIM_Init();//初始化基本定时器
	LED_GPIO_Config();//初始化LED
	
	while(1)
	{
		MOTOR_SPEED_CHANGE(Motor_Speed);//电机速度控制
	}
}

