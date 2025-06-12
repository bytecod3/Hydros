/*
 * helper_functions.h
 *
 * Created: 6/6/2025 3:00:51 PM
 *  Author: user
 */ 


#ifndef TIMER_HELPERS_H_
#define TIMER_HELPERS_H_

#include <avr/interrupt.h>

void timer1_delay_blocking_1s_init();
void timer1_delay_blocking_1s();
uint8_t timer1_delay_blocking_1s_TCNCT();
uint8_t timer1_delay_1s_CTC();
void timer1_delay_1s_non_blocking();
#endif /*TIMER_HELPERS_H_ */