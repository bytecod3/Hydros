/*
 * util.h
 *
 * Created: 6/6/2025 3:00:32 PM
 *  Author: user
 */ 

#include <avr/io.h>
#include "timer-helpers.h"

void timer1_delay_blocking_1s_init() {
	TCCR1B |= (1 << CS12);					// prescale to 256, F = 62.5kHz
	TCNT1 = 0;								// clear the timer counter
}

void timer1_delay_blocking_1s() {
		 
	TIFR1 |= (1 << TOV1);					// clear the TOV bit	
	while( !(TIFR1 & (1 << TOV1)) );		// wait for overflow
	TIFR1 |= (1 << TOV1);					// clear the TOV bit	
}
