#include <wificonfig.hpp>
#include <config.hpp>

extern struct ESPconfig config;

int cameraNumber = config.CameraNumber;

uint8_t LED1pin = 4;
bool LED1status = LOW;

uint8_t LED2pin = 5;
bool LED2status = LOW;

uint8_t LED3pin = 6;
bool LED3status = LOW;

void setup()
{

    ConnectToWiFi();

    Serial.begin(9600);
    pinMode(LED1pin, OUTPUT);
    pinMode(LED2pin, OUTPUT);
    pinMode(LED3pin, OUTPUT);
}

/* Main loop */
void loop()
{

    if (!isConnected())
    {
        reconnect();
    }

    else
    {
        /* Ping server to check camera int */
    }

    if (LED1status)
    {
        digitalWrite(LED1pin, HIGH);
    }
    else
    {
        digitalWrite(LED1pin, LOW);
    }

    if (LED2status)
    {
        digitalWrite(LED2pin, HIGH);
    }
    else
    {
        digitalWrite(LED2pin, LOW);
    }

    if (LED3status)
    {
        digitalWrite(LED3pin, HIGH);
    }
    else
    {
        digitalWrite(LED3pin, LOW);
    }
}
