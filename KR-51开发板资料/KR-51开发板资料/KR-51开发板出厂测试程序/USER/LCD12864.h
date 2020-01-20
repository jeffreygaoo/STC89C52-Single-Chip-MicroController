#ifndef __LCD12864_H
#define __LCD12864_H

extern void LCD_Init();
extern void Clear_Dis12864();
extern void Dis_many(unsigned char *ttc,unsigned char x,unsigned char y);
extern void Dis_char(unsigned char ttc,unsigned char x,unsigned char y);

#endif