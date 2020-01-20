#include "main.h"

sbit LED_WA=P2^0;	//数码管 各个位
sbit LED_WB=P2^1;
sbit LED_WC=P2^2;
sbit LED_WD=P2^3;

code unsigned char LED_Code[17]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf}; 	//0-F 最后一位是 负号
unsigned char Display_Buff[4];			//四位数码管显示缓存 要显示的内容
unsigned char Display_Num=0;			//要显示的数码管位数
unsigned char Display_Time=0;			//数码管显示间隔记录

/************数码管显示 begin ************/

/***********************************
*函数名称：void LED_Init(void)
*函数功能：初始化 
*参数说明：无
*返回说明：无
*其它说明：资源使用  定时器1 用于动态扫描数码管
***********************************/
void LED_Init(void)
{
	
	TMOD|=0x10;	//定时器1 16位手动重装
	TH1=(65536-922)/256;	//11.0592M晶振 1ms重装值
	TL1=(65536-922)%256; 	//为测速记录时间
	ET1=1;	//开定时器1中断
	TR1=0;	//启动定时器1
//
//	EA=1;
}


void Stop_Display(void)
{
	LED_WA=1;
	LED_WB=1;
	LED_WC=1;
	LED_WD=1;
	P0=0xff;
}

/***********************************
*函数名称：void LED_Display(unsigned char num)
*函数功能：数码管显示 
*参数说明：num 指定要显示的位
*返回说明：无
*其它说明：每次显示需指定要显示的位 
***********************************/
void LED_Display(unsigned char num,unsigned char dot)
{
	switch (num)
	{
		case 0:
		{
			LED_WA=0;
			LED_WB=1;
			LED_WC=1;
			LED_WD=1;
			if (dot==0)
			{
				P0=LED_Code[Display_Buff[0]]&0x7F;
			}
			else
			{
				P0=LED_Code[Display_Buff[0]];
			}
		}break;
		case 1:
		{
			LED_WA=1;
			LED_WB=0;
			LED_WC=1;
			LED_WD=1;
			if (dot==1)
			{
				P0=LED_Code[Display_Buff[1]]&0x7F;
			}
			else
			{
				P0=LED_Code[Display_Buff[1]];
			}
		}break;
		case 2:
		{
			LED_WA=1;
			LED_WB=1;
			LED_WC=0;
			LED_WD=1;
			if (dot==2)
			{
				P0=LED_Code[Display_Buff[2]]&0x7F;
			}
			else
			{
				P0=LED_Code[Display_Buff[2]];
			}
		}break;
		case 3:
		{
			LED_WA=1;
			LED_WB=1;
			LED_WC=1;
			LED_WD=0;
			if (dot==3)
			{
				P0=LED_Code[Display_Buff[3]]&0x7F;
			}
			else
			{
				P0=LED_Code[Display_Buff[3]];
			}
		}break;
		default:break;
	}
}

/***********************************
*函数名称：void Time1 () interrupt 3
*函数功能：定时器1 中断服务程序 
*参数说明：无
*返回说明：无
*其它说明：负责 数码管显示
***********************************/
void Time1 () interrupt 3
{
	TH1=(65536-922)/256;	//11.0592M晶振 1ms重装值
	TL1=(65536-922)%256; 	//为测速记录时间
	Display_Time++;
	if (Display_Time>=3)	//数码管显示间隔
	{
		Display_Time=0;
		LED_Display(Display_Num,4);
		if (Display_Num<3)
		{
			Display_Num++;
		}	
		else
		{
			Display_Num=0;
		}
	}
}

/************数码管显示 end ************/