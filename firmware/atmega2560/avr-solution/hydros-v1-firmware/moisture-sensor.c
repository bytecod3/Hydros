/*
 * moisture_sensor.c
 *
 * Created: 6/6/2025 2:54:27 PM
 *  Author: user
 */ 

#include "moisture-sensor.h"

struct MoistureSensor {
	uint8_t _pin;
	int _digitalThreshold;
	int _analogThreshold;	
};

void MoistureSensor_init(MoistureSensor_t _sensor, uint8_t pin) {
	_sensor->_pin = pin;
	
	//todo: set pin as input 
	
	
}

uint8_t MoistureSensor_get_digital_data(MoistureSensor_t _sensor) {
	
}