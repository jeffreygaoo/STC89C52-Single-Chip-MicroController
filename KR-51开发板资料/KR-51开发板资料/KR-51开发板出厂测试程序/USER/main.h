#ifndef __MAIN_H
#define __MAIN_H

#include <reg52.h>

#include "other.h"
#include "led.h"
#include "ds18b20.h"
#include "inf.h"
#include "lcd12864.h"

sbit Key0=P3^2;
sbit Key1=P3^3;
sbit Key2=P3^4;
sbit Key3=P3^5;

sbit DQ=P2^6;	//DS18B20与单片机借口
sbit BEEP=P2^5;

extern bit MCU_TYPE;   //单片机型号 =0为89C   =1为12C  默认为89C
extern bit TES_MODE;		//自动测试 =0   手动测试=1
extern unsigned char step;


#endif