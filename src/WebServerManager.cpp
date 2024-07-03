//
// Created by lftne on 03.07.2024.
//

#include "WebServerManager.h"
#include "TemperatureSensor.h"

WebServerManager::WebServerManager() : server(80), tempSensor(nullptr) {}

void WebServerManager::begin() {
    // Serve static files from SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    // Handle HTTP requests
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->handleRoot(request);
    });
    server.on("/data", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->handleData(request);
    });

    // Serve static files
    server.onNotFound([this](AsyncWebServerRequest *request) {
        this->handleNotFound(request);
    });

    server.begin();
    Serial.println("HTTP server started");
}

void WebServerManager::handleRoot(AsyncWebServerRequest *request) {
    File file = SPIFFS.open("/index.html", "r");
    if (!file) {
        request->send(404, "text/plain", "File not found");
        return;
    }

    request->send(SPIFFS, "/index.html", String(), false);
    file.close();
}

void WebServerManager::handleData(AsyncWebServerRequest *request) {
    if (tempSensor) {
        float temperature = tempSensor->getTemperature();
        float humidity = tempSensor->getHumidity();
        String response = "{ \"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + " }";
        request->send(200, "application/json", response);
    } else {
        request->send(500, "application/json", "{ \"error\": \"Temperature sensor not initialized\" }");
    }
}

void WebServerManager::handleNotFound(AsyncWebServerRequest *request) {
    String path = request->url();
    if (path.endsWith("/")) {
        path += "index.html";
    }

    String contentType = getContentType(path);
    if (!SPIFFS.exists(path)) {
        request->send(404, "text/plain", "File not found");
        return;
    }

    File file = SPIFFS.open(path, "r");
    request->send(SPIFFS, path, contentType);
    file.close();
}

String WebServerManager::getContentType(String filename) {
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    else if (filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}

void WebServerManager::setTemperatureSensor(TemperatureSensor* sensor) {
    this->tempSensor = sensor;
}
