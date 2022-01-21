#include <string>

#pragma once

#ifndef CONFIG_HPP
#define CONFIG_HPP

struct ESPconfig
{
    const char *SSID = "MYESP";
    const char *PASSWORD = "12345678";
    int CameraNumber = 4;
    std::string serverEndPoint = "http://192.168.1.1:8080/camera";
};

#endif