#include "openmv.h"
#include "led.h"
#include "stm32f10x.h"

int openmv[7]; //stm32接收数据数组
int16_t OpenMV_X;  //cx
int16_t OpenMV_Y;  //cy
int8_t Distance; //距离

int i = 0;

void Openmv_Receive_Data(int16_t data)
{
	static u8 state = 0;
	if(state == 0 && data == 0xb3)
	{
		state = 1;
		openmv[0] = data;
	}
	else if(state == 1 && data == 0xb3)
	{
		state = 2;
		openmv[1] = data;
	}
	else if(state == 2)
	{
		state = 3;
		openmv[2] = data;
	}
	else if(state == 3)
	{
		state = 4;
		openmv[3] = data;
	}
	else if(state == 4)
	{
		state = 5;
		openmv[4] = data;
	}
	else if(state == 5)
	{
		state = 6;
		openmv[5] = data;
	}
	else if(state == 6) // 检测是否接收到结束标志
	{
		if(data == 0x0a)
		{
			state = 0;
			LED0 =~ LED0;
			openmv[6] = data;
			Openmv_Data();
			data = 0;
		}
		else if(data != 0x0a)
		{
			state = 0;
			for(i = 0;i < 7;i++)
			{
				openmv[i] = 0x00;
			}
		}
	}
	else
	{
		state = 0;
		data = 0;
		LED0 = 0;
		for(i = 0;i < 7;i++)
		{
			openmv[i] = 0x00;
		}
	}	
}

void Openmv_Data(void)
{
	OpenMV_X = openmv[2];
	OpenMV_Y = openmv[3];
	Distance = openmv[4];
}