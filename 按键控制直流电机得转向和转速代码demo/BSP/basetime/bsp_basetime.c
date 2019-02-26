#include "bsp_basetime.h"

// �ж����ȼ�����
static void BASIC_TIM_NVIC_Config(void)//��ֲʱ���Ը���ʵ������������޸�
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//��ֲʱ���Ը���ʵ������������޸�	
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;	//��ֲʱ���Ը���ʵ������������޸�
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //��ֲʱ���Ը���ʵ������������޸�
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	//��ֲʱ���Ը���ʵ������������޸�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
 * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            ����
 *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
 *  TIM_Period               ����
 *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
 *}TIM_TimeBaseInitTypeDef; 
 *-----------------------------------------------------------------------------
 */


static void BASIC_TIM_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M,�ڲ�ʱ�ӿɹ̶�
    BASIC_TIM_APBxClock_FUN(BASIC_TIM_CLK, ENABLE);//��ֲʱ���Ը���ʵ��������޸�
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period;//��ֲʱ���Ը���ʵ��������޸�(BASIC_TIM_Period = 1000-1)�ص���⣡��

	  // ʱ��Ԥ��Ƶ��= CK_INT /��BASIC_TIM_Prescaler+1�� = 72M / 71+1 = 1M�����ж����� T = BASIC_TIM_Period * (1/1000000) = 1000 * (1/1000000) = 1ms �ص���⣡��
    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM_Prescaler;//��ֲʱ���Ը���ʵ��������޸�(BASIC_TIM_Prescaler= 71)
	
		// ʱ�ӷ�Ƶ���� ��������ʱ��û�У����ù�
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		// ����������ģʽ��������ʱ��ֻ�����ϼ�����û�м���ģʽ������
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		
		// �ظ���������ֵ��������ʱ��û�У����ù�
		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);//��ֲʱ���Ը���ʵ��������޸�
		
		// ����������жϱ�־λ
    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);//��ֲʱ���Ը���ʵ��������޸�
	  
		// �����������ж�
    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);//��ֲʱ���Ը���ʵ��������޸�
		
		// �رն�ʱ��
    TIM_Cmd(BASIC_TIM, DISABLE);	//��ֲʱ���Ը���ʵ��������޸�
}

void BASIC_TIM_Init(void)
{
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Mode_Config();
}


extern volatile uint16_t time; //����ʱ�䣬��λΪms����ʼֵΪ0
/*������ʱ���жϷ�����*/
void  BASIC_TIM_IRQHandler (void) //�жϷ�������1ms�ж�һ��
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
		time++;
		TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update);  		 
	}		 	
}
