/**
  ******************************************************************************
  * @file    MAIN.h
  * @author  DESK3D machinary
  * @version V1.0.0
  * @date    30-May-2018
  * @brief   This file contains all the functions prototypes for the MAINellaneous
  *          firmware library functions (add-on to CMSIS functions).
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"

#include "ini.h"
#include "usart.h"
#include "spi.h"

#include "lcd-hd44780.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "mytasks.h"

#include "handlers.h"


//#include "mytestfunc.h"

#define toggle_Pin_13     	GPIOC->ODR ^= GPIO_Pin_13;

extern xQueueHandle SendData;

#define temperatureAdr           0x20000015

#endif /* __MAIN_H */


/******************* (C) COPYRIGHT 2018 DESK3D machinary *****END OF FILE****/

