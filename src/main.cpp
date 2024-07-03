//
// Created by lftne on 03.07.2024.
//

#include "WiFiManager.h"
#include "WebServerManager.h"
#include "TemperatureSensor.h"

const char* ssid = "OvM-Raspi";
const char* password = "abcD1234";

WiFiManager wifiManager(ssid, password);
WebServerManager webServerManager;
TemperatureSensor tempSensor(D6, DHT22);

void setup() {
    Serial.begin(115200);
    wifiManager.connect();

    // Initialize SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    // Set up temperature sensor
    tempSensor.begin();

    // Set temperature sensor for web server
    webServerManager.setTemperatureSensor(&tempSensor);

    // Start web server
    webServerManager.begin();
}

void loop() {
    delay(100); // Short delay to yield

//    Serial.printf("%f C \n", tempSensor.getTemperature());
//    Serial.printf("%f \n\n", tempSensor.getHumidity());
//
//    delay(300); // Short delay to yield
}
