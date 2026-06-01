#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include  "WiFi.h"
#include "Serial.h"

//宏定义一下WiFi的名称和密码
#define WIFI_SSID "ESP32-PC"
#define WIFI_PASSWORD "12345678"

void wifiInit();
bool WifiConnect(const char* ssid,const char* password);

#endif