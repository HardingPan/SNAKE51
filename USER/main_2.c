#include<reg51.h>
#include<stdio.h>
#include<stdlib.h>
#include"led.h"
#include"delay.h"
#include"uart.h"

void main()
{
	uart_init(0xFA);
	while (1);
}