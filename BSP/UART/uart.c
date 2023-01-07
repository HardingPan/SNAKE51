#include<reg51.h>
#include"delay.h"


/*
串口初始化函数
输入：设置的波特率
输出：串口初始化并打开
*/
void uart_init(unsigned int baud)
{
    //对定时器1进行设置，工作方式2
    TMOD |= 0x20;
    //对串口寄存器进行设置
    SCON = 0x50;
    PCON = 0x80;
    TH1 = baud;
    TL1 = baud;
    ES = 1;
    EA = 1;
    TR1 =1;

}

void uart_interrupt() interrupt 4
{
    u8 rec;

    RI = 0;
    rec = SBUF;
    SBUF = rec;
    while (!TI);
    TI = 0;
}

void uart_send(unsigned char byte)
{
    SBUF = byte;
    while (TI == 0);
    TI = 0;

}