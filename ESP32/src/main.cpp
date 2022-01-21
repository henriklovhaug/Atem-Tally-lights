#include <wificonfig.hpp>
#include <config.hpp>
#include <WebServer.h>

extern struct ESPconfig config;

int cameraNumber = config.CameraNumber;

uint8_t LED1pin = 4;
bool LED1status = LOW;

uint8_t LED2pin = 5;
bool LED2status = LOW;

uint8_t LED3pin = 6;
bool LED3status = LOW;

WebServer server(80);

String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

void handle_root()
{
    server.send(200, "text/html", HTML);
    Serial.println("Got request for root");
}

void setup()
{
    Serial.begin(9600);

    ConnectToWiFi();
    server.on("/", handle_root);
    server.begin();
    delay(100);

    // pinMode(LED1pin, OUTPUT);
    // pinMode(LED2pin, OUTPUT);
    // pinMode(LED3pin, OUTPUT);
}

/* Main loop */
void loop()
{
    delay(500);
    server.handleClient();

    // if (!isConnected())
    // {
    //     reconnect();
    // }

    // else
    // {
    //     /* Ping server to check camera int */
    // }

    // if (LED1status)
    // {
    //     digitalWrite(LED1pin, HIGH);
    // }
    // else
    // {
    //     digitalWrite(LED1pin, LOW);
    // }

    // if (LED2status)
    // {
    //     digitalWrite(LED2pin, HIGH);
    // }
    // else
    // {
    //     digitalWrite(LED2pin, LOW);
    // }

    // if (LED3status)
    // {
    //     digitalWrite(LED3pin, HIGH);
    // }
    // else
    // {
    //     digitalWrite(LED3pin, LOW);
    // }
}
