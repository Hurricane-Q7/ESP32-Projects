#include "Serial.h"
#include "weather_clock_wifi.h"
#include "weather_oled.h"
#include "ntp.h"
#include "Weather.h"
//主函数

bool syncNetworkServices() {
  //检验网络连接成功与否
  if (WifiConnect(WIFI_SSID, WIFI_PASSWORD)) {
    oledClear();
    oledShow(0, 16, "WiFi连接成功!");
    oledShow(0, 32, "SSID:" + String(WIFI_SSID));
    oledShow(0, 48, "IP:" + WiFi.localIP().toString());
    delay(1000);
  } else {
    oledClear();
    oledShow(0,16,"WiFi连接失败!");
    oledShow(0, 32, "SSID:" + String(WIFI_SSID));
    return false;
  }
  
  oledClear();
  oledShow(0,16,"正在同步网络时间……");
  if(!ntpSync()){
    serialPrint("NTP同步失败,请检查网络连接!");
  }
  delay(1000);

  oledClear();
  oledShow(0,16,"正在获取天气信息……");
  if(!weatherupdate()){
    serialPrint("天气信息获取失败");
  }
  delay(1000);
  return true;
}

void showAllInfo(){
  u8g2.clearBuffer();

  u8g2.setCursor(0,16);
  u8g2.print(ntpGetDate() + " " + ntpGetTime());

  u8g2.setCursor(0,35);
  u8g2.print("温度 "+ weatherGetInfo().temp + "℃");

  u8g2.setCursor(70,35);
  u8g2.print("湿度 " + weatherGetInfo().humidity + "%");

  u8g2.setCursor(0,55);
  u8g2.print(weatherGetInfo().weather);

  u8g2.setCursor(70,55);
  u8g2.print(weatherGetInfo().city);

  u8g2.sendBuffer();
}

void setup() {
  serialInit(115200);
  serialPrint("系统启动！");

  oledInit();
  oledShow(0, 16, "系统启动中……");

  oledShow(0, 32, "正在初始化WiFi……");
  wifiInit();

  ntpInit();
  weatherInit();

  oledShow(0, 48, "正在连接WiFi……");
  oledShow(0, 64, "SSID" + String(WIFI_SSID));

  syncNetworkServices();
}



void loop() {
  if(WiFi.status()!=WL_CONNECTED){
    serialPrint("WiFi连接断开,尝试重连");

    oledClear();
    oledShow(0,16,"WiFi已断开,重连中……");
    oledShow(0,32,"SSID"+String(WIFI_SSID));
    syncNetworkServices();
  }

   if(WiFi.status()==WL_CONNECTED){
    static uint32_t lastWeatherUpdate = 0;
    static uint32_t lastDisplayUpdate = 0;
    uint32_t currentMillis = millis();
    if(currentMillis - lastWeatherUpdate >= 600000)
    {
      if(weatherupdate()){
            showAllInfo();
      }
      lastWeatherUpdate = currentMillis;
    }
    if(currentMillis - lastDisplayUpdate>=1000){
      showAllInfo();
      lastDisplayUpdate = currentMillis;
    }
   }





}
