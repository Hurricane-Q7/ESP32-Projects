#include "esp32-wifi.h"
//WiFi初始化
void WiFiInit()
{
   WiFi.mode(WIFI_STA);//设置连接模式，WIFI_STA表示连接到现有的WiFi网络
   WiFi.disconnect();
   delay(100);//等待WiFi模块稳定
   serialPrintln("WiFi模块初始化完成!");
}
//连接wifi
bool WiFiConnect(const char* SSID,const char* PASSWORD)
{
  WiFi.begin(SSID,PASSWORD);
  int attempts = 0;
  //等待连接……
  while(WiFi.status()!=WL_CONNECTED&&attempts<20)
  {
        delay(1000);
        serialPrintln("正在连接WiFi..."+String(attempts+1));
        attempts++;
  }
  //检验wifi是否连接成功，
  if(WiFi.status()==WL_CONNECTED)
  {
    serialPrintln("WiFi连接成功!");
    serialPrintln("IP地址:"+WiFi.localIP().toString());
    return true;
  }
  else
  {
    serialPrintln("连接失败!");
    return false;
  }
}