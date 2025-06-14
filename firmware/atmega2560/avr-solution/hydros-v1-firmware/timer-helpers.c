/*
 * util.h
 *
 * Created: 6/6/2025 3:00:32 PM
 *  Author: user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer-helpers.h"

void timer1_delay_blocking_1s_init() {
	
}

void timer1_delay_blocking_1s() {
	TCCR1B |= (1 << CS12);					// prescale to 256, F = 62.5kHz
	TCNT1 = 0;								// clear the timer counter
	TIFR1 |= (1 << TOV1);					// clear the TOV bit	
	while( !(TIFR1 & (1 << TOV1)) );		// wait for overflow
	TIFR1 |= (1 << TOV1);					// clear the TOV bit	
}

uint8_t timer1_delay_blocking_1s_TCNCT() {
	TCCR1B |= (1 << CS12) | (1 << CS10);	// set prescaler to 1024
	
	if(TCNT1 >= 15624) {
		TCNT1 = 0x00;						// reset counter
		return 1;
	} else {
		return 0;
	}
}

uint8_t timer1_delay_1s_CTC(){
	TCCR1B |= (1 << WGM12);					// set timer1 to CTC mode
	OCR1A = 15624;							// set compare value
	TCCR1B |= (1 << CS12) | (1 << CS10);	// prescaler 1024
	
	if(TIFR1 & (1 << OCF1A)) {
		TIFR1 = (1 << OCF1A);				// reset the timer output compare flag
		return 1;
	}
	
	return 0;
}

void timer1_delay_1s_non_blocking() {
	TCCR1B |= (1 << WGM12);					// set timer1 to CTC mode
	TIMSK1 |= (1 << OCIE1A);				// enable CTC interrupt
	sei();									// enable global interrupts
	OCR1A = 15624;							// set compare value - this value is pre-calculated - 1 second
	TCCR1B |= (1 << CS12) | (1 << CS10);	// prescaler 1024
}

