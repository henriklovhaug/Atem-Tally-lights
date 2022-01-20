#include <string>

#pragma once

#ifndef CONFIG_HPP
#define CONFIG_HPP

struct ESPconfig
{
    const char *SSID = "PlaceHolder";
    const char *PASSWORD = "PlaceHolder";
    int CameraNumber = 4;
    std::string serverEndPoint = "http://192.168.1.1:8080/camera";
};

#endif