
#include <config.hpp>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

#pragma once

using namespace std;

ESPconfig config;

const char *SSID = config.SSID;
const char *PASSWORD = config.PASSWORD;




void ConnectToWiFi()
{
    WiFi.config(config.local_ip, config.gateway, config.subnet);

    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to ");
    Serial.println(SSID);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
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
