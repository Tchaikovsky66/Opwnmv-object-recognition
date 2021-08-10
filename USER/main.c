#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "show.h"
#include "openmv.h"
#include "usart2.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	uart2_init(115200);
 	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 
	LED1 = 0;  
	while(1)	
	{
		oled_show();
	}
}