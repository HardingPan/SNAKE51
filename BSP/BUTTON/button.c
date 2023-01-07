#include<reg51.h>
#include"delay.h"

//按钮分别用于游戏开始，游戏结束
sbit key_game_begin = P3^2;
sbit key_game_end = P3^3;

sbit led_1 = P2^2;
sbit led_2 = P2^3;

/*
按钮函数
输入：按下按钮
输出：返回按键值
*/
void key(u8 k)
{
    if (key_game_begin == 0)
	{	
		delay_ms(10);
		if(key_game_begin == 0)
		{
            k = 1;
			led_1 = 0;
			led_2 = 1;
		}
		// while(!key_game_begin);
    }
    else if (key_game_end == 0)
	{	
		delay_ms(10);
		if(key_game_end == 0)
		{
            k = 0;
			led_1 = 1;
			led_2 = 0;
		}
		// while(!key_game_end);
    }
}