//
// Created by lftne on 03.07.2024.
//

#ifndef WEBSERVERMANAGER_H
#define WEBSERVERMANAGER_H

#include <ESPAsyncWebServer.h>
#include <FS.h>
#include "TemperatureSensor.h"

class WebServerManager {
public:
    WebServerManager();
    void begin();
    void setTemperatureSensor(TemperatureSensor* sensor);

private:
    AsyncWebServer server;
    TemperatureSensor* tempSensor;
    void handleRoot(AsyncWebServerRequest *request);
    void handleData(AsyncWebServerRequest *request);
    void handleNotFound(AsyncWebServerRequest *request);
    String getContentType(String filename);
};

#endif // WEBSERVERMANAGER_H
