#include <string>

#pragma once

#ifndef CONFIG_HPP
#define CONFIG_HPP

using namespace std;
struct ESPconfig
{
    const char *SSID = "ESP32";
    const char *PASSWORD = "12345678";
    int CameraNumber = 4;
    string serverEndPoint = "http://192.168.1.2:8080/camera";
};

#endif