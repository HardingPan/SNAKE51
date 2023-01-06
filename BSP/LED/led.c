#include<reg51.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit SRCLK = P3^6;
sbit rCLK = P3^5;
sbit SER = P3^4;

/*
延迟10微秒函数
输入：需要延迟几个10微秒
输出：相应的延迟效果
*/
void delay_10us(u16 ten_us)
{
	while (ten_us--);
}

/*
延迟毫秒函数
输入：需要延迟几个毫秒
输出：相应的延迟效果
*/
void delay_ms(u16 ms)
{
	u16 i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 110; j++);
	}
}

/*
hc595写入函数
输入：想要的IO电平对应的十六进制数
输出：对应的IO电平效果
*/
void hc595_write_data(u8 dat)
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		//字节左移七位取最高位
		SER = dat >> 7;
		//字节右移一位，次高位变最高位
		dat <<= 1;
		//移位寄存器时钟置低电位
		SRCLK = 0;
		delay_10us(1);
		//给移位寄存器一个上升沿信号
		SRCLK = 1;
		delay_10us(1);
	}
	//存储寄存器时钟置低电位
	rCLK = 0;
	delay_10us(1);
	//给存储寄存器一个上升沿信号，将数据输出
	rCLK = 1;
}