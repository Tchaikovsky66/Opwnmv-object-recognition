#include "show.h"
#include "oled.h"

extern int16_t OpenMV_X;
extern int16_t OpenMV_Y;
extern int8_t Distance; 

void oled_show(void)
{
	OLED_ShowString(0,0,"OpenMV-X:"); 
	OLED_ShowNum(70,00,OpenMV_X,3,12);
	OLED_ShowString(0,2,"OpenMV-Y:"); 	
	OLED_ShowNum(70,2,OpenMV_Y,3,12);		 
	OLED_ShowString(0,4,"Distance:");  
	OLED_ShowNum(68,4,Distance,3,12);
	OLED_ShowString(90,4,"cm");
}