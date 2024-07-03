//
// Created by lftne on 03.07.2024.
//

#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

class WiFiManager {
public:
    WiFiManager(const char* ssid, const char* password);
    void connect();
    IPAddress getLocalIP();
    void printMacAddress();

private:
    const char* ssid;
    const char* password;
    byte mac[6];
};

#endif // WIFIMANAGER_H
