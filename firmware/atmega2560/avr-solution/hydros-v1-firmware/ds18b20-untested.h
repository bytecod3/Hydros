/*
 * ds18b20.h
 *
 * Created: 6/17/2025 2:54:41 PM
 *  Author: Edwin Mwiti
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

//#ifndef F_CPU	
	//#define F_CPU 16000000UL
//#endif

#define F_CPU 16000000UL

#define LOOP_CYCLES	8		// number of cycles the loop takes 
#define us(num) (num/(LOOP_CYCLES * (1/(F_CPU/1000000.0))))


/* useful commands */
#define THERM_CMD_CONVERTTEMP	0x44
#define THERM_CMD_RSCRATCHPAD	0xbe
#define THERM_CMD_WSCRATCHPAD	0x4e
#define THERM_CMD_CPYSCRATCHPAD	0x48
#define THERM_CMD_RECEEPROM		0xb8
#define THERM_CMD_RPWRSUPPLY	0xb4
#define THERM_CMD_SEARCHROM		0xf0
#define THERM_CMD_READROM		0x33
#define THERM_CMD_MATCHROM		0x55
#define THERM_CMD_SKIPROM		0xcc
#define THERM_CMD_ALARMSEARCH	0xec

/* thermometer connections */
#define THERM_PORT	PORTE
#define THERM_DDR	DDRE
#define THERM_PIN	PINE
#define THERM_DQ	PE4

#define THERM_DECIMAL_STEPS_12BIT	625 // .0625

#define THERM_INPUT_MODE()	THERM_DDR &= ~(1 << THERM_DQ)
#define THERM_OUTPUT_MODE()	THERM_DDR |= (1 << THERM_DQ)
#define THERM_LOW()			THERM_PORT &= ~(1 << THERM_DQ)
#define THERM_HIGH()		THERM_HIGH |= (1 << THERM_DQ)

uint8_t therm_reset();
void therm_write_bit(uint8_t bit);
uint8_t therm_read_bit();
uint8_t therm_read_byte(void);
void therm_write_byte(uint8_t byte);
void read_temperature(char* buffer);



#endif /* DS18B20_H_ */