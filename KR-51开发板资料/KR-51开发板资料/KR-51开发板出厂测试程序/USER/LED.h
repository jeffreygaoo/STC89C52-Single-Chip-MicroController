#ifndef __LED_H
#define __LED_H

extern unsigned char Display_Buff[4];			//四位数码管显示缓存 要显示的内容
extern void LED_Init(void);
extern void Stop_Display();

#endif