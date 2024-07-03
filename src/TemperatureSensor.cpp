//
// Created by lftne on 03.07.2024.
//

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

void TemperatureSensor::begin() {
    dht.begin();
}

float TemperatureSensor::getTemperature() {
    float t = dht.readTemperature();
    if (isnan(t)) {
        Serial.println("Failed to read temperature from DHT sensor!");
        return NAN;
    }
    return t;
}

float TemperatureSensor::getHumidity() {
    float h = dht.readHumidity();
    if (isnan(h)) {
        Serial.println("Failed to read humidity from DHT sensor!");
        return NAN;
    }
    return h;
}
