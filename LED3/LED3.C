/*
function:LED��˸�����Ϊ15ms)
STC89C52��LED��com��Ϊ�������͵�ƽ������
algorithm:LED1�ĳ�ʼ״̬�ǵ����ģ����°���1��ʼ��˸����������������
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
				delayMS(10);	 //���������������ٴ��ж��Ƿ��ڵ͵�ƽ
				if(key1==0)
				{
					ledFlash();
				}
	        }
				while(!key1);//��ⰴ���Ƿ��ɿ�
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