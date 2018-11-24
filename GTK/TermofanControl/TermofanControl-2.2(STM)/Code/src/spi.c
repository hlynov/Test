/**
  ******************************************************************************
  * @file    ini.c
  * @author  D3D Application Team
  * @version V1.0.0
  * @date    05-June-2018
  * @brief
  ******************************************************************************
  */

#include "spi.h"

/*******************************************************************************
* Function Name : GPIO_Configuration
* Description : Configure
*
*******************************************************************************/

void Spi_Init(void)
{
    //включаем тактирование порта B и альтернативных функций
    RCC->APB2ENR  |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

    //13(SCK) и 15(MOSI) вывод - альтернативная функция  push pull, 14(MISO) вывод - Input floating, 10(CS) вывод - выход, push-pull. SPI2
    //5(SCK) и 6(MOSI) вывод - альтернативная функция  push pull, 14(MISO) вывод - Input floating, 4(CS) вывод - выход, push-pull. SPI1
    //GPIOB->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF15_0 | GPIO_CRH_CNF10_0);
    //GPIOB->CRH |= GPIO_CRH_CNF13_1 | GPIO_CRH_CNF15_1;
    //GPIOB->CRH |= GPIO_CRH_MODE10_0 | GPIO_CRH_MODE13_1 |   GPIO_CRH_MODE15_1;

    //5(SCK) и 6(MOSI) вывод - альтернативная функция  push pull, 14(MISO) вывод - Input floating, 4(CS) вывод - выход, push-pull. SPI1
    GPIOA->CRL &= ~(GPIO_CRL_CNF5_0 | GPIO_CRL_CNF6_0 | GPIO_CRL_CNF4_0);
    GPIOA->CRL |= GPIO_CRL_CNF5_1 | GPIO_CRL_CNF6_1;
    GPIOA->CRL |= GPIO_CRL_MODE4_0 | GPIO_CRL_MODE5_1 |   GPIO_CRL_MODE6_1;

    //включаем тактирование SPI1
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    SPI1->CR1 |= SPI_CR1_BR;                //Baud rate = Fpclk/256
    SPI1->CR1 &= ~SPI_CR1_CPOL;             //Polarity cls signal CPOL = 0;
    SPI1->CR1 &= ~SPI_CR1_CPHA;             //Phase cls signal    CPHA = 0;
    SPI1->CR1 |= SPI_CR1_DFF;               //16 bit data
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;         //MSB will be first
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  //Software slave management & Internal slave select

    SPI1->CR1 |= SPI_CR1_MSTR;              //Mode Master
    SPI1->CR1 |= SPI_CR1_SPE;                //Enable SPI2
}


uint16_t Spi_Write_Data(uint16_t data)
{
    //ждём пока опустошится Tx буфер
    while(!(SPI1->SR & SPI_SR_TXE));
    //активируем Chip Select
    CS_LOW
    //отправляем данные
    SPI1->DR = data;

    //ждём пока придёт ответ
    while(!(SPI1->SR & SPI_SR_RXNE));
    //считываем полученные данные
    data = SPI1->DR;
    //деактивируем Chip Select
    CS_HIGH
    //возвращаем то, что прочитали
    return data;
}

uint16_t Spi_Get_Temp(uint16_t data)
{

	while(!(SPI1->SR & SPI_SR_TXE));

	CS_LOW;
 	SPI1->DR = data;

	while(!(SPI1->SR & SPI_SR_RXNE));

	data = SPI1->DR;
	data = (data >> 3) * 0.25;

	CS_HIGH;
        return data;
}
