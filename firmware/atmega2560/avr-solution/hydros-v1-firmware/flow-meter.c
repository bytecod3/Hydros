/*
 * flow_meter.c
 *
 * Created: 6/6/2025 2:57:27 PM
 *  Author: Edwin Mwiti
 */ 

#include <avr/io.h>
#include "flow-meter.h"

void flow_meter_interrupt_init() {
	DDRE &= !(1 << PE4);					// set pin 2(PE4) as input 
	EIMSK |= (1 << INT4);					// activate INT4 interrupt
	EICRB |= (1 << ISC40) | (1 << ISC41);	// set to activate on RISING edge
}

float flow_meter_get_flow_rate(int pulses) {
	float flow_rate = ((float) pulses * 2.25);  // todo: calibrate 
	flow_rate *= 60;					// ml/min
	flow_rate /= 1000;					// ltrs/min
	
	return flow_rate;
}