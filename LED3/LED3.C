/*
function:LED闪烁（间隔为15ms)
STC89C52：LED的com端为阳极，低电平点亮。
algorithm:LED1的初始状态是点亮的，按下按键1后开始闪烁（带有消抖处理）
*/
#include <reg52.h>
sbit led1=P1^0;
sbit key1=P3^2;
void delayMS(unsigned int n);
void ledFlash();

void main(void)
{
	while(1)
	{	led1=0;
	 		if(key1==0)
			{
				delayMS(10);	 //软件消抖处理，再次判断是否处于低电平
				if(key1==0)
				{
					ledFlash();
				}
	        }
				while(!key1);//检测按键是否松开
	}	
}

void ledFlash()
{
	while(1)
	{
		led1=0;
		delayMS(15);
		led1=1;
		delayMS(15);
	}
}

void delayMS(unsigned int n)
{
	unsigned char j;
	while(n--)
	{
  		for(j=0;j<113;j++);
	}
}
