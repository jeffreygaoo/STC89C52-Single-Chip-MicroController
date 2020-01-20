#include "main.h"

void Delay_1MS(unsigned int dtime)
{
	unsigned char i, j;
	if (MCU_TYPE==1)
	{
		while(dtime--)
		{
			i = 11;
			j = 190;
			do
			{
				while (--j);
			} while (--i);	
		}	
	}
	else
	{
		while(dtime--)
		{
			i = 2;
			j = 199;
			do
			{
				while (--j);
			} while (--i);	
		}	
	}
}


void Delay_1US(unsigned int dtime)
{
	if (MCU_TYPE==1)
	{
		while(dtime--);	
	}
	else
	{
		dtime/=2;
		while(dtime--);	
	}
}


void Beebee_100 (unsigned char num)
{
	while(num--)
	{
		BEEP=0;
		Delay_1MS(100);
		BEEP=1;
		Delay_1MS(100);
	}
}


void Beebee_200 (unsigned char num)
{
	while(num--)
	{
		BEEP=0;
		Delay_1MS(200);
		BEEP=1;
		Delay_1MS(200);
	}
}