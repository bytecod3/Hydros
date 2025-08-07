/**
* @file main.cpp
* @brief This file implements the wireless solenoid valve switch
* @author Edwin Mwiti
*/

#include <Arduino.h>
#include <LoRa.h>

#define LORA_FREQUENCY 433E6

/**
 * Pin definitions
 */
#define RELAY_PIN    27
#define LORA_CS      26
#define LORA_DIO     27
#define LORA_RST     14
#define USER_LED_PIN 13

uint8_t solenoid_state = 0;
uint16_t solenoid_on_time = 0;
char lora_msg[128];

/**
 * Debug tag
 */
static const char* TAG = "Master";

/**
 * Function prototypes
 */
void LORA_init(void);
void LORA_msg_parser(char*);

/**
 * Function implementation
 */

/**
 * @brief This function initialises LORA module
 */
void LORA_init(void) {
    LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO);

    if(LoRa.begin(LORA_FREQUENCY)) {
        ESP_LOGI(TAG, "Could not find LORA module");
    } else {
        ESP_LOGI(TAG, "LORA module init OK");
    }
}

/**
 * @brief This function parses command from LORA
 */
void LORA_msg_parser() {
    char h = '3';

    // todo: Implement
}

void setup() {
    Serial.begin(11500);
    delay(50);

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(USER_LED_PIN, OUTPUT);

    LORA_init();

    esp_log_level_set(TAG, ESP_LOG_INFO);
}

void loop() {
    digitalWrite(RELAY_PIN, HIGH);
    delay(2000);
    digitalWrite(RELAY_PIN, LOW);
    delay(2000);
}