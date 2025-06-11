/*
 * hydros-v1-firmware.c
 *
 * Created: 6/2/2025 6:24:35 PM
 * Author : Edwin Mwiti
 */ 

#include <avr/io.h>
#include "configs.h"
#include "usart.h"
#include <OneWire.h>
#include <DallasTemperature.h>

/************************************************************************/
/* DS18B20 temperature sensors                                          */
/************************************************************************/
// addresses of 4 DS18B20 sensors 
uint8_t DS18B20_1_addr[8] = {}; // todo: add addresses here
uint8_t DS18B20_2_addr[8] = {};
uint8_t DS18B20_3_addr[8] = {};
uint8_t DS18B20_4_addr[8] = {};
	
float temp1, temp2, temp3, temp4;

OneWire DS18B20(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&DS18B20);

/************************************************************************/
/* Private function prototypes                                          */
/************************************************************************/
void DS18B20_init();
void DS18B20_request_data();
float DS18B20_read_deg_c(DeviceAddress addr);
void send_data_to_esp32(char* data);


/************************************************************************/
/* Function implementations                                             */
/************************************************************************/
void DS18B20_request_data() {
	sensors.requestTemperatures();
}

void DS18B20_init() {
	sensors.begin();
}

float DS18B20_read_deg_c(DeviceAddress addr){
	return sensors.getTempC(addr);
}

void send_data_to_esp32(char* data) {
	USART_put_string(data);
}


int main(void)
{ 
	/* initialize hardware*/
	USART_init(MYUBRR);
	
	char* f_version = "Version: Hydros v1.0";
	USART_put_string(f_version);
	
    /* Replace with your application code */
    while (1) 
    {
		
		DS18B20_request_data();
		
		// temperatures
		temp1 = DS18B20_read_deg_c(DS18B20_1_addr);
		//temp2 = DS18B20_read_deg_c(DS18B20_2_addr);
		//temp3 = DS18B20_read_deg_c(DS18B20_3_addr);
		//temp4 = DS18B20_read_deg_c(DS18B20_4_addr);
		
		
    }
}

