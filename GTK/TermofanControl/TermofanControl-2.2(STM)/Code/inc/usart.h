/*************************************************** Library ******************************************************************/

#include "stm32f10x.h"

/************************************************ Use functions ***************************************************************/

void InitUART (void);

/**************************************************** USART1 ******************************************************************/

#define HEX_CHARS          "0123456789ABCDEF"    // HEX characters

void UART_SendChar(char chr);
void InitUSART2 (void);

void SendStringUSART2 (char* str);
void SendDataUSART2 (uint8_t data);
void UART_SendInt(int32_t num);
void UART_SendHex16(uint16_t num);
void UART_SendInt0(int32_t num);
void UART_SendHex8(uint8_t num);
void UART_SendStr(char *str);
void UART_SendBuf(char *buf, uint16_t bufsize);
void UART_SendBufPrintable(char *buf, uint16_t bufsize, char subst);
void UART_SendBufHex(char *buf, uint16_t bufsize);

