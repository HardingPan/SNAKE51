#include<reg51.h>
#include<stdio.h>
#include<stdlib.h>
#include"led.h"
#include"delay.h"

//这是head的移动量，值为-1，0，1
char head_add_x, head_add_y;
//定义蛇的长度length
u8 length;
//游戏初始速度为5
u8 speed;
//存储果实的横纵坐标
u8 food_x, food_y;
//分别存储蛇身的横坐标、总坐标
char snake_x[20] = {0};
char snake_y[20] = {0};

//LED点阵横坐标、纵坐标的亮灭控制，从左下角开始为第一个
u8 led_row[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
u8 led_col[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

/*
贪吃蛇移动函数
输入：蛇身数组的指针，蛇长
输出：移动后的蛇身数组
*/
void snake_move()
{
    u8 i;
    for (i = length; i > 0; i--)
    {
        snake_x[i] = snake_x[i - 1];
        snake_y[i] = snake_y[i - 1];
    }
    //根据贪吃蛇的游戏原理，当坐标为-1时，变为7，当坐标为8时，变为0
    snake_x[0] = (snake_x[0] + head_add_x + 8) % 8;
    snake_y[0] = (snake_y[0] + head_add_y + 8) % 8;
}

/*
游戏初始化函数
输入：无
输出：速度、蛇身长度、LED点阵等回到初始状态，给蛇一个随机的初始方向
*/
void snake_init()
{
	unsigned char d;
	length = 1;
	speed = 1;
	hc595_write_data(led_row[0]);
	P0 = led_col[0];
	
	d = rand() % 2;
	switch (d)
	{
	case 0:
		head_add_x = 1;
		head_add_y = 0;
		break;
	case 1:
		head_add_x = 0;
		head_add_y = 1;
		break;
	}
}

/*
随机生成果实函数
输入：无
输出：生成一个随机位置的果实
*/
void food()
{
	u8 flag = 0;
	u8 i;
	while (!flag)
	{
		food_x = rand() % 8;
		food_y = rand() % 8;
		flag = 1;
		
		for (i = 0; i < length; i++)
		{
			if (snake_x[i] == food_x && snake_y[i] == food_y)
			{
				flag = 0;
				break;
			}
		}
	}
}




void main()
{
	snake_init();
	food();
	while (1)
	{
		u8 i;
		for (i = 0; i < length; i++)
		{
			row(led_row[snake_x[i]]);
			col(led_col[snake_y[i]]);
		}
		row(led_row[food_x]);
		col(led_col[food_y]);
		snake_move();
		delay_ms(20 * (10 - speed));
	}
}