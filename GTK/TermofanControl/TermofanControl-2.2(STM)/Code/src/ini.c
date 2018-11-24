/**
  ******************************************************************************
  * @file    ini.c
  * @author  D3D Application Team
  * @version V1.0.0
  * @date    05-June-2018
  * @brief
  ******************************************************************************
  */

#include "ini.h"

/*******************************************************************************
* Function Name : GPIO_Configuration
* Description : Configure
*
*******************************************************************************/

void GPIO_Configuration(void)
{
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
//RCC->APB2ENR |= RCC_APB2Periph_GPIOB;
//RCC->APB2ENR |= RCC_APB2Periph_GPIOC;
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                // enable clock for port A
RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;                // enable clock for port B
RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

GPIOC->CRH &=~ (GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1);
GPIOC->CRH |= GPIO_CRH_MODE13_1;
GPIOC->CRH &=~ (GPIO_CRH_CNF13_0 | GPIO_CRH_CNF13_1);

GPIOB->CRL &=~ GPIO_CRL_MODE0;
GPIOB->CRL |= GPIO_CRL_MODE0_1;

GPIOB->CRL &=~ GPIO_CRL_CNF0;
GPIOB->CRL |= GPIO_CRL_CNF0_1;
};


void InitRCC (void)
{
RCC->CR |= ((uint32_t)RCC_CR_HSEON); // Enable HSE
	while (!(RCC->CR & RCC_CR_HSERDY));// Ready start HSE

	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY; // Cloclk Flash memory

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // AHB = SYSCLK/1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1; // APB1 = HCLK/1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // APB2 = HCLK/1

	RCC->CFGR &= ~RCC_CFGR_PLLMULL;// clear PLLMULL bits
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;// clearn PLLSRC bits
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;// clearn PLLXTPRE bits

	//RCC->CFGR |= RCC_CFGR_PLLSRC_PREDIV1;// source HSE
	//RCC->CFGR |= RCC_CFGR_PLLXTPRE_PREDIV1;// source HSE/2 = 4 MHz
	RCC->CFGR |= RCC_CFGR_PLLMULL10; // PLL x6: clock = 4 MHz * 6 = 24 MHz

	RCC->CR |= RCC_CR_PLLON;// enable PLL
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}// wait till PLL is ready

	RCC->CFGR &= ~RCC_CFGR_SW;// clear SW bits
        RCC->CFGR |= RCC_CFGR_SW_PLL;// select source SYSCLK = PLL
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}// wait till PLL is used

}



void GenMCO (void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;// enable clock for port A
        GPIOA->CRH &= ~GPIO_CRH_CNF8_0;// setting out alternative push-pull for PA8
	GPIOA->CRH |= GPIO_CRH_CNF8_1;
	GPIOA->CRH |= (GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1);// gpio speed 50 MHz

	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;// select source clokc SYSCLK

}



void TIM2_Init(void)
{
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
TIM2->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;

TIM2->PSC =12000-1;
	TIM2->ARR = 1000;
	TIM2->DIER |= TIM_DIER_UIE;
NVIC_EnableIRQ(TIM2_IRQn);
};


