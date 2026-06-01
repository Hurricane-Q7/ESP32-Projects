#include "weather_clock_wifi.h"
#include "Serial.h"
//initialize 模块
void wifiInit()
{
  WiFi.mode(WIFI_STA);//设置WIFI工作模式为站点模式
  WiFi.disconnect();
  delay(100);//延时0.1秒，等待WIFI模块稳定
  serialPrint("WIFI模块初始化完成!");
}

//WIFI连接模块
bool WifiConnect(const char* ssid,const char* password)
{
  serialPrint("正在连接WiFi...");
  WiFi.begin(ssid,password);//连接到指定的WIFI，需要ssid 和 密码password
  int attempts = 0;

  //等待连接……
  while(WiFi.status() != WL_CONNECTED && attempts <20)
  {
    delay(1000);
    serialPrint("等待连接..."+String(attempts+1));
    attempts++;
  }
  //检验wifi是否连接成功，
  if(WiFi.status()==WL_CONNECTED){
    serialPrint("WIFI连接成功");
    serialPrint("IP地址:"+WiFi.localIP().toString());
    return true;
  }
  else 
  {
    serialPrint("连接失败!");
    return false;
  }
}