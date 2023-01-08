#include <reg51.h>
#include <delay.h>

//引脚配置：
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;

#define LCD_DataPort P0


/*
lcd写入命令函数
输入：需要写入的命令
输出：对lcd进行设置
*/
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_EN=1;
	delay_ms(1);
	LCD_EN=0;
	delay_ms(1);
}

/*
lcd写入数据函数
输入：需要写入的数据
输出：对lcd进行写入
*/
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DataPort=Data;
	LCD_EN=1;
	delay_ms(1);
	LCD_EN=0;
	delay_ms(1);
}

/*
lcd光标设置函数
输入：光标起始位置（第几行，第几个）
输出：设置效果
*/
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD_WriteCommand(0x80|(Column-1+0x40));
	}
}

/*
lcd写初始化函数
*/
void LCD_Init()
{
	LCD_WriteCommand(0x38);//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);//光标复位，清屏
}

/*
lcd写入字符串函数
输入：初始位置的行和第几个，字符串指针
输出：显示效果
*/
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

