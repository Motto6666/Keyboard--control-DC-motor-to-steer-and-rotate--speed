#include "stm32f10x.h"
#include "bsp_motor_control.h"
#include "bsp_exti_key.h"
#include "bsp_basetime.h"
#include "bsp_led.h"

volatile uint16_t Motor_Speed = 8;//PWM��ռ�ձȳ�ʼֵΪ80%

int main(void)
{
	MOTOR_CONTROL_Config();//��ʼ���������
	KEY_EXTI_Config();//��ʼ������
	BASIC_TIM_Init();//��ʼ��������ʱ��
	LED_GPIO_Config();//��ʼ��LED
	
	while(1)
	{
		MOTOR_SPEED_CHANGE(Motor_Speed);//����ٶȿ���
	}
}

