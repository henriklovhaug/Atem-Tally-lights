#include <wificonfig.hpp>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>


uint8_t LEDRed = GPIO_NUM_23;
bool LED1status = LOW;

uint8_t LEDGreen = GPIO_NUM_22;
bool LED2status = LOW;

uint8_t LEDBlue = GPIO_NUM_21;
bool LED3status = LOW;

#define LEDSTRIP_PIN GPIO_NUM_18
uint8_t LEDSTRIP_COUNT = 3;
bool LEDSTRIP_STATUS = true;

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
    digitalWrite(LEDRed, HIGH);
    if(LEDSTRIP_STATUS)
    {
        for(int i=0; i<LEDSTRIP_COUNT; i++)
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

    pinMode(LEDRed, OUTPUT);
    pinMode(LEDGreen, OUTPUT);
    pinMode(LEDBlue, OUTPUT);
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
        digitalWrite(LEDBlue, HIGH);
    }
    else
    {
        digitalWrite(LEDBlue, LOW);
    }

}
