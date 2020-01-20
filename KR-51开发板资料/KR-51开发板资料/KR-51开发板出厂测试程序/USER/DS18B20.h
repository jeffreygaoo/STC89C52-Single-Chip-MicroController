#ifndef __DS18B20_H
#define __DS18B20_H
extern unsigned char tflag;//温度正负标志  0表示正温度，1表示负温度
extern unsigned int read_temp();
#endif