#ifndef NTP_H
#define NTP_H
#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>
void ntpInit();
bool ntpSync();
String ntpGetTime();
String ntpGetDate();
#endif




