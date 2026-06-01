#ifndef ESP_WIFI_H
#define ESP_WIFI_H

#include <Arduino.h>
#include <WiFi.h>
#include "serial.h"
#include "config.h"

void WiFiInit();
bool WiFiConnect(const char* SSID, const char* PASSWORD);

#endif
