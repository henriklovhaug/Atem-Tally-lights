
#include <config.hpp>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

#pragma once

ESPconfig config;

const char *SSID = config.SSID;
const char *PASSWORD = config.PASSWORD;

std::string serverEndPoint = config.serverEndPoint;

void ConnectToWiFi()
{

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to ");
    Serial.println(SSID);

    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(500);

        if ((++i % 16) == 0)
        {
            Serial.println(F(" still trying to connect"));
        }
    }

    Serial.print(F("Connected. My IP address is: "));
    Serial.println(WiFi.localIP());
}

boolean isConnected()
{
    return WiFi.status();
}

void reconnect()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(SSID, PASSWORD);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print("Reconnecting to WiFi...");
        }
    }
}

int getIsCameraActive()
{
    HTTPClient http;

    http.begin(serverEndPoint.c_str());

    int httpCode = http.GET();

    if (httpCode > 0)
    {
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            Serial.println(payload);
            return payload.toInt();
        }
    }
    return 0;
}