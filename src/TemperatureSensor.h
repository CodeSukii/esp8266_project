//
// Created by lftne on 03.07.2024.
//

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <DHT.h>

class TemperatureSensor {
public:
    TemperatureSensor(uint8_t pin, uint8_t type);
    void begin();
    float getTemperature();
    float getHumidity();

private:
    DHT dht;
};

#endif // TEMPERATURESENSOR_H
