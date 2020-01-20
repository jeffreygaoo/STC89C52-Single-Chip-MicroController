/**************************************************************************************
*功能：Wifi模块测试 											                      *
*说明：手机安装测试APP，手机连接WiFi模块，控制开发板上的LED、蜂鸣器					  *
*硬件连接：在J10处插上跳线帽  1,3用跳线短路 2,4用跳线短路							  *
*作者：研发中心																		  *
*公司：科睿电子产品有限公司 														  *
*电话：0530-2897239   15192459227			  										  *
*地址：菏泽市开发区广州路与淮河路交叉口科睿电子产品有限公司 						  *
***************************************************************************************/
#include <REGX52.H>
#include<intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;
/**串口数据使用**/
#define	RX1_Lenth		32			//串口接收缓冲长度

uchar	idata RX1_Buffer[RX1_Lenth];	//接收缓冲
uchar	TX1_Cnt;	//发送计数
uchar	RX1_Cnt;	//接收计数
bit		B_TX1_Busy;	//发送忙标志

/*************	端口引脚定义	**************/
sbit LED1=P1^0;//LED1
sbit LED2=P1^1;//LED2
sbit LED3=P1^2;//LED3
sbit DK1=P1^3;//继电器
sbit BEEP=P2^5;//蜂鸣器	

/**wifi模块命令**/
unsigned char LYMS[13]="AT+CWMODE=2\r\n";
unsigned char SZLY[38]="AT+CWSAP='ESP8266','0123456789',11,0\r\n";
unsigned char RST[8]="AT+RST\r\n";
unsigned char SZDLJ[13]="AT+CIPMUX=1\r\n";
unsigned char KQFU[21]="AT+CIPSERVER=1,5000\r\n";
unsigned char FSSJ[13]="AT+CIPSEND=\r\n";//AT+CIPSEND= 发送数据	 


void Delay2(unsigned long cnt)
{
	long i;
 	for(i=0;i<cnt*100;i++);
}
void Delay3(unsigned int N) 
{
	int i;
	for(i=0;i<N*10;i++);
}



/********************************************************************
* 名称 : Uart_Init()
* 功能 : 串口初始化，晶振11.0592,波特率9600，使能了串口中断
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Uart_Init(void)
{
     TMOD = 0x20;   //定时器工作在定时器1的方式2
     PCON = 0x00;   //不倍频
     SCON = 0x50;	//串口工作在方式1，并且启动串行接收	
     TH1 = 0xFd;    //设置波特率 9600
     TL1 = 0xFd;
     TR1 = 1;		//启动定时器1
	 ES = 1;		//开串口中断
	 EA = 1;		//开总中断
	 RX1_Cnt=0;		//接受计数清零
	 TX1_Cnt = 0;	//发送计数清零
	 B_TX1_Busy = 0;//初始化判忙标志位		
}
/********************************************************************
* 名称 : Main()
* 功能 : 主函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void main(void)
{
	char i=0;

	Uart_Init();

	Delay3(2000);
  /******************设置WiFi模块**********************************************/
	for(i=0;i<13;i++)//AT+CWMODE=2 设置成路由模式
	{
		SBUF=LYMS[i];Delay3(5);
	}
	Delay3(1000);
	for(i=0;i<38;i++)//AT+CWSAP="ESP8266","0123456789",11,0 设置路由
	{
		SBUF=SZLY[i];Delay3(5);
	}
	Delay3(3000);
	for(i=0;i<8;i++)//AT+RST 重启
	{
		SBUF=RST[i];Delay3(5);
	}
	Delay3(5000);
	for(i=0;i<13;i++)//AT+CIPMUX=1 设置成多连接
	{
		SBUF=SZDLJ[i];Delay3(5);
	}
	Delay3(2000);
	for(i=0;i<21;i++)//AT+CIPSERVER=1,5000 开启TCP服务端口
	{
		SBUF=KQFU[i];Delay3(5);
	}
	Delay3(2000);
	while (1)
	{
	
	}
}

/********************************************************************
* 名称 : Uart_Int()
* 功能 : 串口中断子函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void UART1_int (void) interrupt 4
{
//	char i,a,b,c;
	if(RI)
	{
		RI = 0;
		RX1_Buffer[RX1_Cnt] = SBUF;		//保存一个字节
		if(RX1_Buffer[0]==0x45)
		{
			RX1_Cnt++;
		}
		else
		{
			RX1_Cnt=0;
		}
		if(RX1_Cnt>=10)
		{
			if(RX1_Buffer[0]==0x45&&RX1_Buffer[1]==0x53&&RX1_Buffer[2]==0x50)
			{
				if(RX1_Buffer[4]==0x4C&&RX1_Buffer[5]==0x45&&RX1_Buffer[6]==0x44)//判断LED
				{
					if(RX1_Buffer[7]==0x31)//判断LED1
					{
						if(RX1_Buffer[3]==0x4B)//判断开
						{
							LED1=0;
						}
						if(RX1_Buffer[3]==0x47)//判断关
						{
							LED1=1;
						}
					}
					if(RX1_Buffer[7]==0x32)//判断LED2
					{
						if(RX1_Buffer[3]==0x4B)//判断开
						{
							LED2=0;
						}
						if(RX1_Buffer[3]==0x47)//判断关
						{
							LED2=1;
						}
					}
					if(RX1_Buffer[7]==0x33)//判断LED3
					{
						if(RX1_Buffer[3]==0x4B)//判断开
						{
							LED3=0;
						}
						if(RX1_Buffer[3]==0x47)//判断关
						{
							LED3=1;
						}
					}
				}
				if(RX1_Buffer[4]==0x4A&&RX1_Buffer[5]==0x44&&RX1_Buffer[6]==0x51)//判断继电器
				{
					if(RX1_Buffer[7]==0x31)//判断LED1
					{
						if(RX1_Buffer[3]==0x4B)//判断开
						{
							DK1=1;
						}
						if(RX1_Buffer[3]==0x47)//判断关
						{
							DK1=0;
						}
					}
				}
				if(RX1_Buffer[3]==0x46&&RX1_Buffer[4]==0x4D&&RX1_Buffer[5]==0x51&&RX1_Buffer[6]==0x43&&RX1_Buffer[7]==0x53)//判断蜂鸣器
				{
					BEEP=1;Delay2(100);BEEP=0;Delay2(100);BEEP=1;Delay2(100);BEEP=0;Delay2(100);
				}
				RX1_Cnt=0;
			}
			else
			{
				RX1_Cnt=0;
			}
			RX1_Cnt=0;
		}
	}
	if(TI)
	{
		TI = 0;
		B_TX1_Busy = 0;		//清除发送忙标志
	}
}

