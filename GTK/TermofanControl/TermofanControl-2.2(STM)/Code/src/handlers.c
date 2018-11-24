/**
  ******************************************************************************
  * @file    handlers.c
  * @author  D3D Application Team
  * @version V1.0.0
  * @date    05-June-2018
  * @brief
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
  * <h2><center>&copy; COPYRIGHT 2018 D3D</center></h2>
  ******************************************************************************
  */

#include "handlers.h"



/*******************************************************************************
* Function Name : TIM2_IRQHandler
* Description :
*
*******************************************************************************/

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus (TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit (TIM2, TIM_IT_Update);
		toggle_Pin_13;

        }
	}


void USART1_IRQHandler (void){

	        if (USART1->SR & USART_SR_RXNE){
               	USART1->SR &= ~USART_SR_RXNE;

		if (USART1->DR == 0x01){GPIOC->BSRR |= GPIO_BSRR_BS2;}
		if (USART1->DR == 0x02){GPIOC->BSRR |= GPIO_BSRR_BR2;}

		if (USART1->DR == 0x03){GPIOC->BSRR |= GPIO_BSRR_BS3;}
		if (USART1->DR == 0x04){GPIOC->BSRR |= GPIO_BSRR_BR3;}

	}

}


void USART2_IRQHandler(void)
{
  if (USART2->SR & USART_SR_RXNE)
  {
      USART2->SR &= ~USART_SR_RXNE;

      if (USART2->DR == '0')
      {
	SendStringUSART2("OFF");
	GPIOC->BSRR |= GPIO_BSRR_BR8;
      }
  }
}