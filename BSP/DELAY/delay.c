#include"delay.h"

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