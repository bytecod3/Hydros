#ifndef USART_H
#define USART_H

#include "configs.h"

#define MYUBRR ( (F_CPU / (AVR_BAUDRATE * 16UL)) - 1 ) /* to calculate the UBRR value */

void USART_init(unsigned int ubrr);
void USART_transmit(unsigned char data);
unsigned char USART_receive();
void USART_put_string(char*);
void USART_send_int(int);
void USART_send_float(float);

#endif