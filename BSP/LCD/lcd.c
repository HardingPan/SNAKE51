#include "reg51.h"
#include "lcd.h"
#include "intrins.h"
#include"delay.h"

sbit LCD_RS = P2^5;
sbit LCD_RW = P2^6;
sbit LCD_E  = P2^7;
sbit LED_V0 = P1^0;

#define LCD_DataPort P0

void Delay1ms()		//@11.0592MHz 1ms
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void LCD_WriteCommand(unsigned char Command)
{
		LCD_RS = 0;
		LCD_RW = 0;
		LCD_DataPort = Command;
		LCD_E  = 1;
		delay_ms(1);
		LCD_E  = 0;
		delay_ms(1);
		
}

void LCD_WriteData(unsigned char Data)
{
		LCD_RS = 1;
		LCD_RW = 0;
		LCD_DataPort = Data;
		LCD_E  = 1;
		delay_ms(1);
		LCD_E  = 0;
		delay_ms(1);
		
}

void LCD_Init()
{
		LCD_WriteCommand(0x38);
		LCD_WriteCommand(0x0c);
		LCD_WriteCommand(0x06);
		LCD_WriteCommand(0x01);
		LED_V0 = 0;
}

void LCD_SetCursor(unsigned char Line,unsigned char Columu)
{
	if(Line == 1)
	{
		LCD_WriteCommand( 0x80 | (Columu-1) );
	}
	else
	{
		LCD_WriteCommand( 0x80 | ( Columu-1 )+0x40 );
	}
}

void LCD_ShowChar(unsigned char Line , unsigned char Columu , unsigned char Char)
{
		LCD_SetCursor(Line,Columu);
	
		LCD_WriteData(Char);
}

void LCD_ShowString(unsigned char Line , unsigned char Columu , unsigned char* String)
{
		unsigned char i = 0;
	
		LCD_SetCursor(Line,Columu);
	
		for(i=0;String[i] != '\0';i++)
		{
				LCD_WriteData(String[i]);
		}
}

int LCD_Pow(unsigned char x,unsigned char y)
{
		int result = 1;
		unsigned char i = 0;
		
		for(i=0;i<y;i++)
		{
				result *= x;
		}
		
		return result;
}

void LCD_ShowNum(unsigned char Line,unsigned char Columu,unsigned int Num,unsigned int Length)
{
		unsigned char i = 0;
		
		LCD_SetCursor(Line,Columu);
		
		for(i=Length;i>0;i--)
		{
				LCD_WriteData('0'+Num/LCD_Pow(10,i-1)%10);
		}
}

