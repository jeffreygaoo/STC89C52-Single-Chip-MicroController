/*
function:LED闪烁（间隔为15ms)
STC89C52：LED的com端为阳极，低电平点亮。
algorithm:LED1的初始状态是点亮的，按下按键1后开始闪烁（带有消抖处理）
*/
#include <reg52.h>
sbit led1=P1^0;
unsigned int count;

void main(void)
{
	TMOD&=0xfc;
	TMOD|=0x01;
	
	TH0=0xb1;
	TL0=0xe0;
	
	TR0=1;

	while(1)
	{
		if(TF0==1)
		{
			TF0=0;
			TH0=0xb1;
			TL0=0xe0;
			count++;
			if(count>=50)
			{
				count=0;
				led1=~led1;
			}
		}
	}
}
