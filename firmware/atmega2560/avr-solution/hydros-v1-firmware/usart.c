/***********************************************************************
* @file: usart.c 
* @brief: defines usart functions                                                                       
***********************************************************************
*/


#include <avr/io.h>
#include "usart.h"

void USART_init(unsigned int ubrr) {
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = ubrr;
	
	/*enable receiver & transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	/* set frame format */
	UCSR0C = (1 << USBS0) | (1 << UCSZ00) | (1 <<UCSZ01);
	
}

void USART_transmit(unsigned char data) {
	/* polling -> wait for empty TX buffer */
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char USART_receive() {
	/*check if RXC (receive complete flag) is set */
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void USART_put_string(char* pstr) {
	/* loop until we are the end of the string */
	while(*pstr != 0x00) {
		USART_transmit(*pstr);
		pstr++;
	}
}



