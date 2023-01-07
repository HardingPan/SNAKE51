#include<reg51.h>
#include"delay.h"

sbit SRCLK = P3^6;
sbit rCLK = P3^5;
sbit SER = P3^4;

/*
hc595写入函数
输入：想要的IO电平对应的十六进制数
输出：对应的IO电平效果
*/
void row(u8 dat)
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

/*
P0写入函数
输入：想要的IO电平对应的十六进制数
输出：对应的IO电平效果
*/
void col(u8 dat)
{
	P0 = dat;
}