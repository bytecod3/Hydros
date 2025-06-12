/*
 * hydros-v1-firmware.c
 *
 * Created: 6/2/2025 6:24:35 PM
 * Author : Edwin Mwiti
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "configs.h"
#include "usart.h"
#include "timer-helpers.h"

void send_data_to_esp32(char* data) {
	USART_put_string(data);
}

/************************************************************************/
/* Interrupt service routines                                                                     */
/************************************************************************/
volatile int isr_tim1_counter = 0;
ISR(TIMER1_COMPA_vect) {
	isr_tim1_counter++;
	PORTD ^= (1 << PD0);
}

int main(void)
{ 
	/* initialize hardware*/
	USART_init(MYUBRR);	
	char* f_version = "Version: Hydros v1.0";
	USART_put_string(f_version);

	DDRD |= (1 << PD0); // OUTPUT MODE
	
	/* output buffers */
	char isr_counter_buffer[10];
	
	/* start timer1 interrupts */
	timer1_delay_1s_non_blocking();

    while (1) 
    {
		
		//if(timer1_delay_blocking_1s_TCNCT()) {
			//PORTD ^= (1 << PD0);
		//}
		
		sprintf(isr_counter_buffer, "%d\r\n", isr_tim1_counter);
		USART_put_string(isr_counter_buffer);
		//USART_put_string("Hello\r\n");
			
	}
}

