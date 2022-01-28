#include <wificonfig.hpp>
#include <WebServer.h>


uint8_t LEDRed = GPIO_NUM_34;
bool LED1status = LOW;

uint8_t LEDGreen = GPIO_NUM_35;
bool LED2status = LOW;

uint8_t LEDBlue = GPIO_NUM_26;
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
    digitalWrite(LEDRed, HIGH);
    Serial.println("Got request for live on");
}

void handle_live_off()
{
    server.send(200);
    digitalWrite(LEDRed, LOW);
    Serial.println("Got request for live off");
}

void handle_preview_on()
{
    server.send(200);
    digitalWrite(LEDGreen, HIGH);
    Serial.println("Got request for preview on");
}

void handle_preview_off()
{
    server.send(200);
    digitalWrite(LEDGreen, LOW);
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

    pinMode(LEDRed, OUTPUT);
    pinMode(LEDGreen, OUTPUT);
    pinMode(LEDBlue, OUTPUT);
}

/* Main loop */
void loop()
{
    delay(10);
    server.handleClient();
    reconnect();
    if (isConnected())
    {
        digitalWrite(LEDBlue, HIGH);
    }
    else
    {
        digitalWrite(LEDBlue, LOW);
    }
}
