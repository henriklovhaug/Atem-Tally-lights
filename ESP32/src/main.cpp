#include <Arduino.h>
#include <wificonfig.hpp>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>


uint8_t LEDRed = GPIO_NUM_23;
uint8_t LEDRedChannel = 0;
bool LED1status = LOW;

uint8_t LEDGreen = GPIO_NUM_22;
uint8_t LEDGreenChannel = 1;
bool LED2status = LOW;

uint8_t LEDBlue = GPIO_NUM_21;
uint8_t LEDBlueChannel = 2;
bool LED3status = LOW;

#define LEDSTRIP_PIN GPIO_NUM_18
uint8_t LEDSTRIP_COUNT = 3;
bool LEDSTRIP_STATUS = false;

Adafruit_NeoPixel pixels(LEDSTRIP_COUNT, LEDSTRIP_PIN, NEO_GRB + NEO_KHZ800);

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
    ledcWrite(LEDRedChannel, 155);
    if(LEDSTRIP_STATUS)
    {
       for(int i = 0; i < LEDSTRIP_COUNT; i++)
       {
          pixels.setPixelColor(i, pixels.Color(255, 0, 0));
          pixels.show();
       }
    }
    Serial.println("Got request for live on");
}

void handle_live_off()
{
    server.send(200);
    pixels.clear();
    pixels.show();
    ledcWrite(LEDRedChannel, 0);
    Serial.println("Got request for live off");
}

void handle_preview_on()
{
    server.send(200);
    ledcWrite(LEDGreenChannel, 155);
    Serial.println("Got request for preview on");
}

void handle_preview_off()
{
    server.send(200);
    ledcWrite(LEDGreenChannel, 0);
    Serial.println("Got request for preview off");
}

void handle_led_strip_on(){
    server.send(200);
    LEDSTRIP_STATUS = true;
}

void handle_led_strip_off(){
    server.send(200);
    LEDSTRIP_STATUS = false;
}

void setup()
{
    Serial.begin(9600);

    ledcAttachPin(LEDRed, 0);
    ledcAttachPin(LEDGreen, 1);
    ledcAttachPin(LEDBlue, 2);
    ledcSetup(0, 1000, 8);
    ledcSetup(1, 1000, 8);
    ledcSetup(2, 1000, 8);
    ConnectToWiFi();
    server.on("/live/1", handle_live_on);
    server.on("/live/0", handle_live_off);
    server.on("/preview/1", handle_preview_on);
    server.on("/preview/0", handle_preview_off);
    server.on("/led/1", handle_led_strip_on);
    server.on("/led/0", handle_led_strip_off);
    server.onNotFound([]() {
        server.send(200, "text/html", HTML);
    });
    server.begin();
    delay(100);
    pixels.begin();

}

/* Main loop */
void loop()
{
    delay(10);
    server.handleClient();
    reconnect();
    if (isConnected())
    {
        ledcWrite(LEDBlueChannel, 155);
    }
    else
    {
        ledcWrite(LEDBlueChannel, 0);
    }

}
