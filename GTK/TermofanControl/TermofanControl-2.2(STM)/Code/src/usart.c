/*************************************************** Library ******************************************************************/

#include "usart.h"

/************************************************ Use functions ***************************************************************/

void InitUART (void){

	InitUSART2();
}

/**************************************************** USART2 ******************************************************************/

void InitUSART2 (void){

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	GPIOA->CRL |= GPIO_CRL_CNF2_1;
	GPIOA->CRL |= GPIO_CRL_MODE2;

	GPIOA->CRL |= GPIO_CRL_CNF3_0;
	GPIOA->CRL &= ~GPIO_CRL_MODE3;

	USART2->BRR = 0x9C4;

	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;
	USART2->CR1 |= USART_CR1_UE;

	USART2->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART2_IRQn);

}

void UART_SendChar(char chr) {
	USART2->DR = chr;
	while (!(USART2->SR & USART_SR_TC)); // wait for "Transmission Complete" flag cleared
}


void SendStringUSART2 (char* str){

	uint8_t i = 0;
       	while(str[i])
	UART_SendChar (str[i++]);
}

void SendDataUSART2 (uint8_t data){

	while (!(USART2->SR & USART_SR_TC));
	USART2->DR = data;

}

// Send signed integer value as text to UART
// input
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   num - integer value to send
void UART_SendInt(int32_t num) {
	char str[10]; // 10 chars max for INT32_MAX
	int i = 0;
	if (num < 0) {
		UART_SendChar('-');
		num *= -1;
	}
	do str[i++] = num % 10 + '0'; while ((num /= 10) > 0);
	while (i) UART_SendChar(str[--i]);
}


// Send signed integer value with leading zero as text to UART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   num - integer value to send
void UART_SendInt0(int32_t num) {
	char str[10]; // 10 chars max for INT32_MAX
	int i = 0;
	if (num < 0) {
		UART_SendChar('-');
		num *= -1;
	}
	if ((num < 10) && (num >= 0)) UART_SendChar('0');
	do str[i++] = num % 10 + '0'; while ((num /= 10) > 0);
	while (i) UART_SendChar(str[--i]);
}

// Send byte in HEX format to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   num - 8-bit value to send
void UART_SendHex8(uint8_t num) {
	UART_SendChar(HEX_CHARS[(num >> 4)   % 0x10]);
	UART_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);
}


// Send 16-bit value in HEX format to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   num - 16-bit value to send
void UART_SendHex16(uint16_t num) {
	uint8_t i;
	for (i = 12; i > 0; i -= 4) UART_SendChar(HEX_CHARS[(num >> i) % 0x10]);
	UART_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);
}

// Send zero terminated string to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   str - pointer to zero terminated string
void UART_SendStr(char *str) {
	while (*str) UART_SendChar(*str++);
}

// Send buffer to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   buf - pointer to the buffer
//   bufsize - size of buffer in bytes
void UART_SendBuf(char *buf, uint16_t bufsize) {
	while (bufsize--) UART_SendChar(*buf++);
}

// Send buffer to USART with substitute for unprintable characters
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   buf - pointer to the buffer
//   bufsize - size of buffer in bytes
//   subst - character for substitute
void UART_SendBufPrintable(char *buf, uint16_t bufsize, char subst) {
	char ch;

	while (bufsize--) {
		ch = *buf++;
		UART_SendChar(ch > 32 ? ch : subst);
	}
}

// Send buffer in HEX format to USART
// input:
//   USARTx - pointer to the USART port (USART1, USART2, etc.)
//   buf - pointer to the buffer
//   bufsize - size of buffer in bytes
void UART_SendBufHex(char *buf, uint16_t bufsize) {
	char ch;

	while (bufsize--) {
		ch = *buf++;
		UART_SendChar(HEX_CHARS[(ch >> 4)   % 0x10]);
		UART_SendChar(HEX_CHARS[(ch & 0x0f) % 0x10]);
	}
}
