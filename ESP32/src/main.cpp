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

void handle_live_on()
{
    server.send(200);
    Serial.println("Got request for live on");
}

void handle_live_off()
{
    server.send(200);
    Serial.println("Got request for live off");
}

void handle_preview_on()
{
    server.send(200);
    Serial.println("Got request for preview on");
}

void handle_preview_off()
{
    server.send(200);
    Serial.println("Got request for preview off");
}

void setup()
{
    Serial.begin(9600);

    ConnectToWiFi();
    server.on("/live/1", handle_live_on);
    server.on("/live/0", handle_live_off);
    server.on("/preview/1", handle_preview_on);
    server.on("/preview/0", handle_preview_off);
    server.onNotFound([]() {
        server.send(200, "text/html", HTML);
    });
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
