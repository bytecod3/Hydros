/*
 * hydros-v1-firmware.c
 *
 * Created: 6/2/2025 6:24:35 PM
 * Author : Edwin Mwiti
 */ 

#define F_CPU 16000000UL /*! clock speed is 16 MHz */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "configs.h"
#include "usart.h"
#include "timer-helpers.h"
#include "flow-meter.h"
#include "ds18b20.h"
#include "ds18b20-untested.h"
#include <util/delay.h>

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

/** 
* DS18B20 register declarations 
*/
#define THERM_PORT	PORTE
#define THERM_DDR	DDRE
#define THERM_PIN	PINE
#define THERM_DQ	PE4

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
	//flow_meter_interrupt_init();
	
	// temperature sensor init 
	//DDRE &= (1 << THERM_DQ); // set temperature sensor pin as input
	int temp;
	
	uint8_t status = therm_reset();
	USART_put_string("DS INIT STATUS: ");
	USART_send_int(status);
	
    while (1) 
    {
		
		/* read flow meter */
		//pulse_count = 0;
		//sei();
		//timer1_delay_blocking_1s(); // wait for 1 second
		//cli();
		//flow_rate = flow_meter_get_flow_rate(pulse_count);
		
		// USART_send_int(pulse_count);
		//USART_send_float(flow_rate);
		
		ds18b20convert(&THERM_PORT, &THERM_DDR, &THERM_PIN, (1<< THERM_DQ), NULL);
		_delay_ms(1000);
		ds18b20read(&THERM_PORT, &THERM_DDR, &THERM_PIN, (1<< THERM_DQ), NULL, &temp);
		
		USART_send_int(temp);
		USART_put_string("\r\n");
		
	}
}

