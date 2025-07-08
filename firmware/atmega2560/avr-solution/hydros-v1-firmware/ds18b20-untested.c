/*
 * ds18b20.c
 *
 * Created: 6/17/2025 2:54:56 PM
 *  Author: user
 */ 

#include <avr/io.h>
#include <stdio.h>
//#include <util/delay.h>
#include "ds18b20-untested.h"

inline __attribute__((gnu_inline)) void therm_delay(uint16_t delay) {
	while(delay--) asm volatile("nop");
}

uint8_t therm_reset() {
	uint8_t i;
	
	THERM_LOW();				// pull line low ans wait for 480us5
	THERM_OUTPUT_MODE();
	therm_delay(us(480));
	//_delay_us(480);
	
	THERM_INPUT_MODE(); // release line and wait for 60us
	therm_delay(us(60));
	//_delay_us(60);
	
	i = (THERM_PIN & (1 << THERM_DQ) );
	therm_delay(us(420));
	//_delay_us(420);
	
	return i; // 0 = OK, 1=ERROR
	
}

void therm_write_bit(uint8_t bit) {
	THERM_LOW();		// pull the line LOW for 1us
	THERM_OUTPUT_MODE();
	therm_delay(us(1));
	//_delay_us(1);

	if(bit) THERM_INPUT_MODE(); // if we want to write 1, release the line, if not keep it low 
	
	therm_delay(us(60));	// wait for 60us and release line, writes a 0
	//_delay_us(60);
	THERM_INPUT_MODE();	
}

uint8_t therm_read_bit() {
	uint8_t bit = 0;
	
	THERM_LOW();			// pull line LOW and wait for 1us
	THERM_OUTPUT_MODE();
	therm_delay(us(1));
	//_delay_us(1);
	
	THERM_INPUT_MODE();		// release line and wait 14us
	therm_delay(us(14)); 
	//_delay_us(14);
	
	//bit = (THERM_PIN & (1 << THERM_DQ));	// read line value 
	if(THERM_PIN & (1 << THERM_DQ)) bit = 1;
	
	therm_delay(us(45));		// wait 45us and return read value
	//_delay_us(45);
	return bit;	
	
}

uint8_t therm_read_byte(void) {
	uint8_t i = 8, n = 0;
	
	while (i--)
	{
		n >>= 1;						// shift one position right and store the read value 
		n |= (therm_read_bit() << 7);	// place bit in the MSB position
	}
	
	return n;
}

void therm_write_byte(uint8_t byte) {
	uint8_t i = 8;
	while(i--) {
		therm_write_bit(byte & 1); // write bit and make the next bit ready
		byte >>= 1;
	}
}

void read_temperature(char* buffer) {
	uint8_t temperature[2]; 
	int8_t digit;
	uint16_t decimal;
	
	therm_reset();	// reset, skip ROM and start temperature conversion
	therm_write_byte(THERM_CMD_SKIPROM);
	therm_write_byte(THERM_CMD_CONVERTTEMP);
	
	while(!therm_read_bit()); // wait for conversion to complete
	
	therm_reset(); // reset, skip ROM and send command to read scratchpad
	therm_write_byte(THERM_CMD_SKIPROM);
	therm_write_byte(THERM_CMD_RSCRATCHPAD);
	
	temperature[0] = therm_read_byte();	// read scratchpad(temperature). See datasheet
	temperature[1] = therm_read_byte();	
	therm_reset();
	
	//sprintf(buffer, "%d, %d \r\n", temperature[0], temperature[1]);
	
	digit = temperature[0] >> 4;	// extract temperature digits and decimal
	digit = (temperature[1] & 0x07)	<< 4;
	
	decimal = temperature[0] & 0x0f; // store decimal digits
	decimal *= THERM_DECIMAL_STEPS_12BIT;
	
	sprintf(buffer, "%+d.%04u C \r\n", digit, decimal);	
	
}