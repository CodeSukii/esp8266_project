//
// Created by lftne on 03.07.2024.
//
#include "WiFiManager.h"
#include <WiFiClient.h>

WiFiManager::WiFiManager(const char* ssid, const char* password)
        : ssid(ssid), password(password) {}

void WiFiManager::connect() {
    Serial.begin(115200);
    delay(10);

    Serial.print("WLAN - verbunden");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WLAN - verbunden");
    Serial.println("IP-Adresse: ");
    Serial.println(WiFi.localIP());

    Serial.print("..........................\n");
    WiFi.macAddress(mac);
    printMacAddress();
}

IPAddress WiFiManager::getLocalIP() {
    return WiFi.localIP();
}

void WiFiManager::printMacAddress() {
    Serial.print("MAC-Adresse: \n");
    for (int i = 0; i < 6; ++i) {
        if (i > 0) Serial.print(":");
        Serial.print(mac[i], HEX);
    }
    Serial.println();
}
