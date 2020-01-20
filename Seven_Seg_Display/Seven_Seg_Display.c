#include <reg52.h>
#define bitSelect P2
#define segSelect P0
/*
function:数码管循环显示4321（间隔为1000ms)
*/
void delayMS(unsigned int n);

void main(void)
{
	while(1)
	{	
		/*初始状态数码管全部点亮*/
		bitSelect=0x00;
		segSelect=0x00;
		delayMS(1000);

		bitSelect=0xfe; //bitSelect->Binary 1111 1110 
		segSelect=0x99;	//segSelect->Binary dp g f e d c b a  10011001
		delayMS(1000);


		bitSelect=0xfd;
		segSelect=0xb0;
		delayMS(1000);

		bitSelect=0xfb;
		segSelect=0xa4;
		delayMS(1000);
		
		bitSelect=0xf7;
		segSelect=0xf9;
		delayMS(1000);		
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



