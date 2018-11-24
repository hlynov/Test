/*************************************************** Library ******************************************************************/

#include "mytasks.h"


int16_t testuart=5000 ;
char text_buf[8];






/************************************************ vTask1***************************************************************/

void vTask1 (void *argument)
{

  while(1)
   {
     lcd44780_ClearLCD();
     lcd44780_SetLCDPosition(0, 1);
     lcd44780_ShowStr("love");
     vTaskDelay(100);
     lcd44780_ShowStr("love+");
     vTaskDelay(100);
   }
}


/************************************************ vTask2***************************************************************/

void vTask2 (void *argument)
{

  uint16_t dataGet;



  while(1)
   {
     vTaskDelay(500);
     dataGet = Spi_Get_Temp(1);
     vTaskDelay(500);
     UART_SendInt(dataGet);

     //SendStringUSART2("LOVE");
     //SendStringUSART2(testuart);

   }
}


