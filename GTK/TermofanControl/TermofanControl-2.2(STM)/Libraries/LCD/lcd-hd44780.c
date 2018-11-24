//************************************************************************//
//	LCD HD44780
//	Alex_EXE
//	http://alex-exe.ru/category/radio/stm32/stm32-lcd-hd44780-spl
//************************************************************************//
#include "lcd-hd44780.h"

const unsigned char lcd44780_addLUT[4] = {0x80, 0xC0, 0x94, 0xD4};
unsigned char lcd44780_Address, lcd44780_Line;

//************************************************************************//
GPIO_InitTypeDef lcd44780_GPIO_InitStructure;	//	структура для инициализации выводов используемых дисплеем

//	задержка
//	Input : p - величина задержки
void lcd44780_delay(unsigned int p)
{
	unsigned long i;
	for(i=0;i<(p*10);i++){}
}

//	инициализация выводов дисплея
void lcd44780_init_pins(void)
{
	RCC_APB2PeriphClockCmd(lcd44780_RCC, ENABLE);
	lcd44780_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	lcd44780_GPIO_InitStructure.GPIO_Pin = 	lcd44780_pin_E | lcd44780_pin_RS | lcd44780_pins_data;
	lcd44780_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//	выходы с открытым коллектором, нужна подвязка к +5В
	GPIO_Init(lcd44780_port, &lcd44780_GPIO_InitStructure);
}
//************************************************************************//

//	Отправка полубайта дисплею
//	Input : data - пол байта данных
void lcd44780_WriteNibble(unsigned char data)
{
	GPIO_SetBits(lcd44780_port, ((data & 0x0F))<<lcd44780_offset);
	lcd44780_delay(200);
	lcd44780_E_1;
	lcd44780_delay(100);
	lcd44780_E_0;
	GPIO_ResetBits(lcd44780_port, 0x0F<<lcd44780_offset);
}

//	Отправка байта дисплею
//	Input : data - отправляемые данные
void lcd44780_WriteByte(unsigned char data)
{
	lcd44780_WriteNibble(data >> 4);
	lcd44780_WriteNibble(data & 0x0F);
}

//	Перейти на строчку
//	Input : LineNum - номер строки
void lcd44780_GoToLine(char LineNum)
{
	lcd44780_RS_0;
	lcd44780_Address = lcd44780_addLUT[LineNum-1];
	lcd44780_WriteByte(lcd44780_Address);
	lcd44780_RS_1;
	lcd44780_Address = 0;
	lcd44780_Line = LineNum;
}

//	Очистка дисплея
void lcd44780_ClearLCD(void)
{
	lcd44780_RS_0;
	lcd44780_WriteByte(0x01);
	lcd44780_delay(1000);
	lcd44780_RS_1;
	lcd44780_GoToLine(1);
}

//	Установка курсора дисплея
//	Input : x , y - координаты курсора
void lcd44780_SetLCDPosition(char x, char y)
{
	lcd44780_RS_0;
	lcd44780_Address = lcd44780_addLUT[y] + x;
	lcd44780_WriteByte(lcd44780_Address);
	lcd44780_RS_1;
	lcd44780_Line = y+1;
}

//	Отправка символа
//	Input : c - символ
void lcd44780_ShowChar(unsigned char c)
{
	lcd44780_RS_1;
	lcd44780_WriteByte(c);
	lcd44780_Address++;
	switch (lcd44780_Address)
	{
		case 20: lcd44780_GoToLine(2); break;
		case 40: lcd44780_GoToLine(3); break;
		case 60: lcd44780_GoToLine(4); break;
		case 80: lcd44780_GoToLine(1); break;
	}
}

//	Отправка строки
//	Input : *s - ссылка на строку (массив символов)
void lcd44780_ShowStr(unsigned char *s)
{
	while (*s != 0) lcd44780_ShowChar(*s++);
}

//	Инициализация дисплея
void lcd44780_init(void)
{
	unsigned char i;
	lcd44780_E_0;
	lcd44780_RS_0;
	lcd44780_delay(5000);
	lcd44780_WriteNibble(0x33);
	lcd44780_WriteNibble(0x33);
	lcd44780_WriteNibble(0x33);
	lcd44780_WriteNibble(0x22);
	lcd44780_WriteByte(0x28);
	lcd44780_WriteByte(0x01);
	lcd44780_WriteByte(0x10);
	lcd44780_WriteByte(0x06);
	lcd44780_WriteByte(0x0C);
	for(i=0x40; i<0x5F; i++)
	{
		lcd44780_delay(1000);
		lcd44780_RS_0;
		lcd44780_WriteByte(i);
		lcd44780_delay(1000);
		lcd44780_ShowChar(0);
	}
	lcd44780_RS_1;
	lcd44780_ClearLCD();
}
