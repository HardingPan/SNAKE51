#include<reg51.h>
#include<stdio.h>
#include<stdlib.h>
#include"led.h"
#include"delay.h"
#include"uart.h"
#include"button.h"

//这是head的移动量，值为-1，0，1
char head_add_x, head_add_y;
//定义蛇的长度length,length-1也就是分数score
u8 length;
//游戏初始速度为1，速度为1-8档
u8 speed;
//存储果实的横纵坐标
u8 food_x, food_y;
//分别存储蛇身的横坐标、总坐标
char snake_x[20] = {0};
char snake_y[20] = {0};

//储存按钮值
u8 key_num;

//记录游戏是否结束
u8 game_flag;
u8 begin_flag;


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
	game_flag = 1;
	begin_flag = 0;
	key_num = 0;
	row(led_row[0]);
	col(led_col[0]);
	
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

/*
显示蛇身函数
*/
void led_snake()
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





void main()
{
	//初始化
	//对游戏进行初始化
	snake_init();
	//对串口进行初始化，通信的波特率设置为9600
	uart_init(0xFA);
	//生成第一个果实
	food();
	//初始化完毕

	//游戏还没输,此时game_flag为1（初始化里设置的）
	while (game_flag)
	{
		key(key_num);
		if (key_num == 1)
		{
			begin_flag = 1;
		}
		//玩家确认开始按钮
		while (begin_flag)
		{
			key(key_num);
			if (key_num == 2)
				//增加速度
				speed = (speed + 1) % 8;
			//按了game over按钮，游戏直接结束
			else if (key_num == 4)
			{
				game_flag = 0;
			}
			//正式开始游戏
			else if (key_num == 3)
			{
				begin_flag = 2;
			}
			while (begin_flag == 2)
			{
				led_snake();
			}
			

		}
		
	}
}