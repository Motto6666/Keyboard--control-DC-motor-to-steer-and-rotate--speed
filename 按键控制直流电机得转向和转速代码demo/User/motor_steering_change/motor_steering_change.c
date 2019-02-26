#include "motor_steering_change.h"
#include "bsp_led.h"
#include "bsp_motor_control.h"

static uint16_t steering_and_speed_change = 1;//电机转向、转速增/减标识符,初始值为1
extern volatile uint16_t time; //计数时间，单位为ms，初始值为0
extern volatile uint16_t Motor_Speed;//PWM波占空比初始值为80%

void motor_steering_change(void)
{
	if(time>=2000)//长按，切换blink_time_change_mode值
		{
			steering_and_speed_change = !(steering_and_speed_change);
			
			if(steering_and_speed_change == 0)
			{
				LED_OFF;//关闭LED，表示电机逆时针转动
			  
	      Anti_Clockwise_Rotation;//电机逆时针转动
			}
			
			else
			{
				LED_ON;//打开LED，表示电机顺时针转动
			 
	      Clockwise_Rotation; //电机顺时针转动
			}
		}
		else//短按，改变PWM波占空比
		{
			switch(steering_and_speed_change)//选择电机转速增/减模式
			{
				case speed_increase_mode:
					if(Motor_Speed >= 8)//当PWM波占空比≥80%时
					{
						Motor_Speed = 8;//PWM波占空比恢复到最初的值(80%)
					}
					else
					{
						Motor_Speed += 2; //PWM波占空比增加20%
					}break;
				
				case speed_reduce_mode:
					if(Motor_Speed <= 2)//当PWM波占空比≤20%时
					{
						Motor_Speed = 8;//PWM波占空比恢复到最初的值(80%)
					}
					else
					{
						Motor_Speed -= 2;//PWM波占空比减少20%
					}break;
				
				default:  break;
			}	
		}
}
