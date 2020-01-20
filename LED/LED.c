#include <reg52.h>

sbit LED0=P1^0;
sbit LED1=P1^1;
sbit LED2=P1^2;
sbit LED3=P1^3;
sbit LED4=P1^4;
sbit LED5=P1^5;
sbit LED6=P1^6;
sbit LED7=P1^7;
void delayMS(unsigned int n);

void main()
{
	LED0=0;
	delayMS(1000);
	LED0=1;
	LED1=0;
	delayMS(1000);
	LED1=1;
	LED2=0;
	delayMS(1000);
	LED2=1;
	LED3=0;
	delayMS(1000);	
	LED3=1;
	LED4=0;
	delayMS(1000);
	LED4=1;
	LED5=0;
	delayMS(1000);
	LED5=1;
	LED6=0;
	delayMS(1000);
	LED6=1;
	LED7=0;
	delayMS(1000);
	LED7=1;			
}

void delayMS(unsigned int n)
{
	unsigned char j;
	while(n--)
	{
  		for(j=0;j<113;j++);
	}
}
