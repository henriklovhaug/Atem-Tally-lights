#include <wificonfig.hpp>
#include <config.hpp>
#include <WebServer.h>

extern struct ESPconfig config;

int cameraNumber = config.CameraNumber;

uint8_t LED1pin = GPIO_NUM_23;
bool LED1status = LOW;

uint8_t LED2pin = GPIO_NUM_22;
bool LED2status = LOW;

uint8_t LED3pin = GPIO_NUM_21;
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
    digitalWrite(LED1pin, HIGH);
    Serial.println("Got request for live on");
}

void handle_live_off()
{
    server.send(200);
    digitalWrite(LED1pin, LOW);
    Serial.println("Got request for live off");
}

void handle_preview_on()
{
    server.send(200);
    digitalWrite(LED2pin, HIGH);
    Serial.println("Got request for preview on");
}

void handle_preview_off()
{
    server.send(200);
    digitalWrite(LED2pin, LOW);
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

    pinMode(LED1pin, OUTPUT);
    pinMode(LED2pin, OUTPUT);
    pinMode(LED3pin, OUTPUT);
}

/* Main loop */
void loop()
{
    delay(10);
    server.handleClient();
    reconnect();
    if (isConnected())
    {
        digitalWrite(LED3pin, HIGH);
    }
    else
    {
        digitalWrite(LED3pin, LOW);
    }
}
