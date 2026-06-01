#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

#define WEATHER_API_KEY "SsDcXXAGqSRUInDK2"  //我的心知天气密钥
#define WEATHER_CITY_ID "WT9NG9P4ZDHG"       //信阳市城市ID
#define WEATHER_URL "https://api.seniverse.com/v3/weather/daily.json?key=%s&location=%s&language=zh-Hans&unit=c&start=0&days=1"

struct WeatherInfo {

  String city;
  String weather;
  String temp;
  String humidity;  //湿度
};

void weatherInit();
bool weatherupdate();
WeatherInfo weatherGetInfo();



#endif