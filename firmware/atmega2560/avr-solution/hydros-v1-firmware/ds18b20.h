/*
 * ds18b20.h
 *
 * Created: 6/17/2025 2:54:41 PM
 *  Author: Edwin Mwiti
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

#ifndef F_CPU	16000000UL
#define LOOP_CYCLES	8		// number of cycles the loop takes 
#define us(num) (num/(LOOP_CYCLES * (1/(F_CPU/1000000.0))))


/* thermometer connections */
#define 



#endif /* DS18B20_H_ */