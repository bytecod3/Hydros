/*
 * moisture_sensor.h
 *
 * Created: 6/6/2025 2:56:24 PM
 *  Author: user
 */ 


#ifndef MOISTURE_SENSOR_H_
#define MOISTURE_SENSOR_H_

typedef struct MoistureSensor* MoistureSensor_t;

void MoistureSensor_init(MoistureSensor_t, uint8_t);
uint16_t MoistureSensor_get_analog_data(MoistureSensor_t);
uint8_t MoistureSensor_get_digital_data(MoistureSensor_t);


#endif /* MOISTURE-SENSOR_H_ */