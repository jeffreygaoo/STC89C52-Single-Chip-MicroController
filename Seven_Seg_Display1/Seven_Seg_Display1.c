#include <reg52.h>
#define bitSelect P2
#define segSelect P0
/*
function:数码管循环显示4321（间隔为1000ms)
STC89C52：数码管驱动电路的三极管为PNP型，低电平导通，数码管为共阳极接法，低电平
导通
algorithm:循环导通位选端和段选端
*/
unsigned int i;
unsigned int j;

void delayMS(unsigned int n);


unsigned char bitcode[]={0xfe,0xfd,0xfb,0xf7};	  
unsigned char segcode[]={0x99,0xb0,0xa4,0xf9};

void main(void)
{	
	while(1)
		{
			 
			for(i=0;i<=3;i++)
			{
				segSelect=segcode[i];
				bitSelect=bitcode[i];
				delayMS(1000);
			} 
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
