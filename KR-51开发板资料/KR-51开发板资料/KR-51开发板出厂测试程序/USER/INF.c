#include "main.h"

unsigned char Infrared_Step=0;
unsigned int  Infrared_Time=0;
unsigned char Infrared_Num=0;
unsigned char Infrared_Code[4];
bit Infrared_Flag=0;

/****** 红外解码代码 begin ******/
void INF_Init(void)
{
	TMOD|=0x01;	//定时器1 16位手动重装
	TH0=0;	//重装值
	TL0=0; 	//为红外解码记录时间
	ET0=1;	//开定时器1中断
	TR0=1;	//启动定时器1

	IT0=1; 	//外部中断0低电平触发

	EX0=1;	//外部中断0使能	
	EA=1;	
}

void Time0_isr (void) interrupt 1
{
	TH0=0;
	TL0=1;	
}

/***********************************
*函数名称：void Int0_isr (void) interrupt 0
*函数功能：外部中断0中断服务程序
*参数说明：无
*返回说明：无
*其它说明：无
***********************************/
void Int0_isr (void) interrupt 0
{
    Infrared_Time=TH0*256+TL0;   //中断间隔时长
    TH0=0; 
    TL0=0;            		//定时计数器重新清零
	if (Infrared_Step==0)
	{
		if ((Infrared_Time>12000)&&(Infrared_Time<17000))  //起始码 先确定一个大范围 然后逐次逼近	12000 17000
		{
			Infrared_Step=1;
		}
		else
		{
			Infrared_Step=0;
		}
	}
	else if (Infrared_Step==1)
	{
		if ((Infrared_Time>1450)&&(Infrared_Time<3000))	 //红外编码为比特1 的时间
		{
			Infrared_Code[Infrared_Num/8]<<=1;
			Infrared_Code[Infrared_Num/8]|=0x01;
			Infrared_Num++;
		}
		else if((Infrared_Time>700)&&(Infrared_Time<1450))//红外编码为比特0的时间
		{
			Infrared_Code[Infrared_Num/8]<<=1;
			Infrared_Code[Infrared_Num/8]&=0xfe;
			Infrared_Num++;
		}
		
		if (Infrared_Num>=32)
		{
			Infrared_Num=0;
			Infrared_Step=0;
			if (Infrared_Code[2]==~Infrared_Code[3])
			{
				Infrared_Flag=1;
			}					
		}		
	}
	else
	{				  
		Infrared_Step=0;
	}
}


/****** 红外解码代码  end ******/