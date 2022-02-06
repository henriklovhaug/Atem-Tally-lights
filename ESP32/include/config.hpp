#include <string>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

#pragma once

#ifndef CONFIG_HPP
#define CONFIG_HPP

using namespace std;
struct ESPconfig
{
    const char *SSID = "ESP32";
    const char *PASSWORD = "12345678";
    int CameraNumber = 4;
    IPAddress local_ip = IPAddress(192, 168, 2, 4); //Change this to your local IP
    IPAddress gateway = IPAddress(192, 168, 2, 1);
    IPAddress subnet = IPAddress(255, 255, 255, 0);
};

#endif