#include "main.h"
unsigned char tflag;//温度正负标志  0表示正温度，1表示负温度

void ds1820rst()   /*ds1820复位*/
{ 
	unsigned char x=0;
	DQ = 1;          //DQ复位
	Delay_1US(14); //延时
	DQ = 0;          //DQ拉低
	Delay_1US(480); //精确延时大于480us
	DQ = 1;          //拉高
	Delay_1US(140); 
} 

unsigned char ds1820rd()/*读数据*/
{ 
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{   DQ = 0; //给脉冲信号
	    dat>>=1;
	    DQ = 1; //给脉冲信号
	    if(DQ)
	    dat|=0x80;
	    Delay_1US(20);
	}
   return(dat);
}
void ds1820wr(unsigned char wdata)/*写数据*/
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DQ = 0;
		DQ = wdata&0x01;
		Delay_1US(20);
		DQ = 1;
		wdata>>=1;
	}
}
unsigned int read_temp()/*读取温度值并转换*/
{
	unsigned char a,b;
	unsigned int tvalue;
	ds1820rst();    
	ds1820wr(0xcc);//*跳过读序列号*/
	ds1820wr(0x44);//*启动温度转换*/
	ds1820rst();    
	ds1820wr(0xcc);//*跳过读序列号*/ 
	ds1820wr(0xbe);//*读取温度*/ 
	a=ds1820rd();
	b=ds1820rd();
	tvalue=b;
	tvalue<<=8;
	tvalue=tvalue|a;
	if(tvalue<0x0fff)
	{
		tflag=0;
	}
	else
	{
		tvalue=~tvalue+1;
		tflag=1;
	}
	tvalue=tvalue*(0.0625);//如果需要将温度值精确到1位小数。将0.0625扩大10倍，
	return(tvalue);
}


/************DS18B20温度 end ************/