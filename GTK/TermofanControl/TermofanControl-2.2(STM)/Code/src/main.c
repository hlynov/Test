/******************************************************************************
* File Name :   main.c
* Author :      DESK3D machinary
* Version :     2.0.0
* Date :        20180529
* Target :      ARM Cortex-M4 (STM32F103xC)
* Description : Termofan 1.1 Управление термофеном
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

char a=4;


int main (void)
{

//InitRCC();
//GenMCO();
xQueueHandle SendData;

GPIO_Configuration();
TIM2_Init();
InitUART();
Spi_Init();

lcd44780_init_pins();	//	конфигурирование выводов дисплея
lcd44780_init();	//	инициализация дисплея

lcd44780_ShowStr("wh1602 + STM32");	//	вывод надписи на дисплей

SendStringUSART2("t1.txt=\"");


xTaskCreate(vTask1, "test", 32, NULL, tskIDLE_PRIORITY +1, NULL);
xTaskCreate(vTask2, "test2", 32, NULL, tskIDLE_PRIORITY +2, NULL);

SendData = xQueueCreate(5, sizeof(uint8_t));

vTaskStartScheduler();

while(1);
{
}
//
}



