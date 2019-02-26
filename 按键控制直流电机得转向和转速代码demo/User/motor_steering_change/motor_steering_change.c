#include "motor_steering_change.h"
#include "bsp_led.h"
#include "bsp_motor_control.h"

static uint16_t steering_and_speed_change = 1;//���ת��ת����/����ʶ��,��ʼֵΪ1
extern volatile uint16_t time; //����ʱ�䣬��λΪms����ʼֵΪ0
extern volatile uint16_t Motor_Speed;//PWM��ռ�ձȳ�ʼֵΪ80%

void motor_steering_change(void)
{
	if(time>=2000)//�������л�blink_time_change_modeֵ
		{
			steering_and_speed_change = !(steering_and_speed_change);
			
			if(steering_and_speed_change == 0)
			{
				LED_OFF;//�ر�LED����ʾ�����ʱ��ת��
			  
	      Anti_Clockwise_Rotation;//�����ʱ��ת��
			}
			
			else
			{
				LED_ON;//��LED����ʾ���˳ʱ��ת��
			 
	      Clockwise_Rotation; //���˳ʱ��ת��
			}
		}
		else//�̰����ı�PWM��ռ�ձ�
		{
			switch(steering_and_speed_change)//ѡ����ת����/��ģʽ
			{
				case speed_increase_mode:
					if(Motor_Speed >= 8)//��PWM��ռ�ձȡ�80%ʱ
					{
						Motor_Speed = 8;//PWM��ռ�ձȻָ��������ֵ(80%)
					}
					else
					{
						Motor_Speed += 2; //PWM��ռ�ձ�����20%
					}break;
				
				case speed_reduce_mode:
					if(Motor_Speed <= 2)//��PWM��ռ�ձȡ�20%ʱ
					{
						Motor_Speed = 8;//PWM��ռ�ձȻָ��������ֵ(80%)
					}
					else
					{
						Motor_Speed -= 2;//PWM��ռ�ձȼ���20%
					}break;
				
				default:  break;
			}	
		}
}
