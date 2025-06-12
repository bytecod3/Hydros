/*
 * hydros-v1-firmware.c
 *
 * Created: 6/2/2025 6:24:35 PM
 * Author : Edwin Mwiti
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "configs.h"
#include "usart.h"
#include "timer-helpers.h"

void send_data_to_esp32(char* data) {
	USART_put_string(data);
}


int main(void)
{ 
	/* initialize hardware*/
	USART_init(MYUBRR);	
	char* f_version = "Version: Hydros v1.0";
	USART_put_string(f_version);

	DDRD |= (1 << PD0); // OUTPUT MODE
	
	timer1_delay_blocking_1s_init();

    while (1) 
    {
		timer1_delay_blocking_1s();
		PORTD ^= (1 << PD0);
			
	}
}

