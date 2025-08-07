/**
* @file main.cpp
* @brief This file implements the wireless solenoid valve switch
* @author Edwin Mwiti
*/

#include <Arduino.h>

#define RELAY_PIN 27

void setup() {
    Serial.begin(11500);
    pinMode(RELAY_PIN, OUTPUT);
}

void loop() {

    digitalWrite(RELAY_PIN, HIGH);
    delay(2000);
    digitalWrite(RELAY_PIN, LOW);
    delay(2000);
    
}