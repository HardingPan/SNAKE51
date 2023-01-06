#ifndef __LED_H__
#define __LED_H__

typedef unsigned char u8;
typedef unsigned int u16;

void delay_10us(u16 ten_us);
void delay_ms(u16 ms);
void hc595_write_data(u8 dat);

#endif