/**
  ******************************************************************************
  * @file    GPIOini.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file contains all the functions prototypes for the GPIOiniellaneous
  *          firmware library functions (add-on to CMSIS functions).
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SPI_H
#define SPI_H


#include "main.h"

#define      CS_LOW     GPIOA->BSRR = GPIO_BSRR_BR4;
#define      CS_HIGH    GPIOA->BSRR = GPIO_BSRR_BS4;

void Spi_Init(void);
uint16_t Spi_Write_Data(uint16_t data);
uint16_t Spi_Get_Temp(uint16_t data);

#endif /* SPI_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
