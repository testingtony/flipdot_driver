#include <Arduino.h>
#include <Ticker.h>
#include <WiFiManager.h>

#include "aws.h"
#include "OTA.h"

WiFiManager wifiManager;
unsigned long last_run = 0;

void setup() {
    Serial.begin(115200);

    wifiManager.autoConnect();
    randomSeed(micros());
    OTA_Setup();

}

void loop() {
    unsigned long now = millis();
    if (now - last_run > 30 * 1000 || now < last_run) {
        JsonDocument doc;
        getTime(doc);
        last_run = now;
    }
    OTA_Loop();
}