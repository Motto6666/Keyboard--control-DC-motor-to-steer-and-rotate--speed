#include "stm32f10x.h"
#include "./motor-control/bsp_motor_control.h"
#include "./key/bsp_exti_key.h"
#include "./basetime/bsp_basetime.h"
#include "./led/bsp_led.h"

volatile uint16_t CCR1_Val = 8;//PWM��ռ�ձȳ�ʼֵΪ80%

int main(void)
{
	motor_control_Config();//��ʼ���������
	KEY_EXTI_Config();//��ʼ�������ж�
	BASIC_TIM_Init();//��ʼ��������ʱ��
	LED_GPIO_Config();//��ʼ��LED
	
	while(1)
	{
		TIM_SetCompare1(GENERAL_TIM,CCR1_Val);
	}
}

