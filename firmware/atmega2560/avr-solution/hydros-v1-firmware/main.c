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
#include "flow-meter.h"

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

/* Flow rate meter variables */
uint8_t flow_pin = 2;
float flow_rate = 0;
volatile int pulse_count;

ISR (INT4_vect) {
	pulse_count++;
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
	//timer1_delay_1s_non_blocking();
	
	/* Flow rate meter */
	flow_meter_interrupt_init();
	
	
    while (1) 
    {
		
		/* read flow meter */
		pulse_count = 0;
		sei();
		timer1_delay_blocking_1s(); // wait for 1 second
		cli();
		flow_rate = flow_meter_get_flow_rate(pulse_count);
		
		// USART_send_int(pulse_count);
		USART_send_float(flow_rate);
		
	}
}

