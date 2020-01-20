#include "main.h"

/*TS12864A-3 端口定义*/
#define LCD_data  P0             //数据口
sbit LCD_RS  =  P2^0;            //寄存器选择输入 
sbit LCD_RW  =  P2^1;            //液晶读/写控制
sbit LCD_EN  =  P2^2;            //液晶使能控制
sbit LCD_PSB =  P2^3;            //串/并方式控制



/*******************************************************************/
/*                                                                 */
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*                                                                 */
/*******************************************************************/
void LCD_wcmd(unsigned char cmd)
{                          
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    Delay_1US(4); 
    P0 = cmd;
    Delay_1US(8);
    LCD_EN = 1;
    Delay_1US(8);
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/
void LCD_wdat(unsigned char dat)
{                          
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    Delay_1US(8);
    LCD_EN = 1;
    Delay_1US(8);
    LCD_EN = 0; 
}
/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void LCD_Init()
{ 

    LCD_PSB = 1;         //并口方式
    
    LCD_wcmd(0x34);      //扩充指令操作
    Delay_1MS(5);
    LCD_wcmd(0x30);      //基本指令操作
    Delay_1MS(5);
    LCD_wcmd(0x0C);      //显示开，关光标
    Delay_1MS(5);
    LCD_wcmd(0x01);      //清除LCD的显示内容
    Delay_1MS(5);
}

void Clear_Dis12864()
{
    LCD_wcmd(0x01);      //清除LCD的显示内容
    Delay_1MS(5);
}

/*********************************************************/
/*                                                       */
/* 设定显示位置                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(unsigned char X,unsigned char Y)
{                          
	unsigned char  pos;
	if (X==0)
	{
		X=0x80;
	}
	else if (X==1)
	{
		X=0x90;
	}
	else if (X==2)
	{
		X=0x88;
	}
	else if (X==3)
	{
		X=0x98;
	}
	pos = X+Y ;  
	LCD_wcmd(pos);     //显示地址
}


void Dis_many(unsigned char *ttc,unsigned char x,unsigned char y)  //显示字库文字
{
	lcd_pos(x,y);             //设置显示位置
	while(*ttc!= '\0')
	{
		LCD_wdat(*ttc);      //显示字符
		*(ttc++);
	}
}


void Dis_char(unsigned char ttc,unsigned char x,unsigned char y)  //显示字库文字
{
	lcd_pos(x,y);             //设置显示位置
    LCD_wdat(ttc);      //显示字符
}