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
  delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	uart2_init(115200);
 	OLED_Init();			//初始化OLED  
	OLED_Clear(); 
	LED1 = 0;  
	while(1)	
	{
		oled_show();
	}
}