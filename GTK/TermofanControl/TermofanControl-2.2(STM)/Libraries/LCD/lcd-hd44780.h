//************************************************************************//
//	LCD HD44780
//	Alex_EXE
//	http://alex-exe.ru/category/radio/stm32/stm32-lcd-hd44780-spl
//************************************************************************//
#include "stm32f10x.h"

//************************************************************************//
//			Конфигурация порта
//	используемый порт
#define lcd44780_port					GPIOB
//	используемые выводы
#define lcd44780_pin_RS				GPIO_Pin_11
#define lcd44780_pin_E				GPIO_Pin_10
#define lcd44780_pins_data		GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15
//	включить тактирование порта
#define lcd44780_RCC					RCC_APB2Periph_GPIOB
//	смещение начала линии данных
#define lcd44780_offset 			12

#define lcd44780_RS_1 GPIO_SetBits(lcd44780_port, lcd44780_pin_RS);
#define lcd44780_E_1  GPIO_SetBits(lcd44780_port, lcd44780_pin_E);
#define lcd44780_RS_0 GPIO_ResetBits(lcd44780_port, lcd44780_pin_RS);
#define lcd44780_E_0  GPIO_ResetBits(lcd44780_port, lcd44780_pin_E);
//************************************************************************//

//	задержка
//	Input : p - величина задержки
void lcd44780_delay(unsigned int p);

//	Очистка дисплея
void lcd44780_ClearLCD(void);

//	Установка курсора дисплея
//	Input : x , y - координаты курсора
void lcd44780_SetLCDPosition(char x, char y);

//	Отправка символа
//	Input : c - символ
void lcd44780_ShowChar(unsigned char c);

//	Отправка строки
//	Input : *s - ссылка на строку (массив символов)
void lcd44780_ShowStr(unsigned char *s);

//	инициализация выводов дисплея
void lcd44780_init_pins(void);

//	Инициализация дисплея
void lcd44780_init(void);

//	Отправка полубайта дисплею
//	Input : data - пол байта данных
void lcd44780_WriteNibble(unsigned char data);

//	Отправка байта дисплею
//	Input : data - отправляемые данные
void lcd44780_WriteByte(unsigned char data);

//	Перейти на строчку
//	Input : LineNum - номер строки
void lcd44780_GoToLine(char LineNum);
