#include <reg52.h>
#include <intrins.h>

unsigned char temp;
void delayMS(unsigned int n);
unsigned char i;


void main()					
{								
while(1)
	{
		temp=0xfe;		 //temp->Binary 1111 1110			 			  
		P1=temp;
		delayMS(1000);
		for(i=1;i<=7;i++)
		{
			temp=_crol_(temp,1);	  					 		 
	 		P1=temp;
	 		delayMS(1000);//temp->Binary 0111 1111					 
		} 

		for(i=1;i<=7;i++)
		{	
			temp=_cror_(temp,1);	  					 			 
	 		P1=temp;
	 		delayMS(1000);//temp->Binary 1111 1110					 
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