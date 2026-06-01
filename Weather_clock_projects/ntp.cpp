#include "ntp.h"
#include "Serial.h"
#include "weather_oled.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"ntp.aliyun.com",8*3600);

//NTPClient是一个用于与网络时间协议（NTP）服务器进行通信的客户端类

//初始化
void ntpInit(){
serialPrint("初始化NTP客服端");

timeClient.begin();

serialPrint("初始化NTP客服端完成");
}

//获取时间的函数（时-分-秒）
String ntpGetTime(){
   timeClient.update();
   int hours = timeClient.getHours();
   int minutes = timeClient.getMinutes();
   int seconds = timeClient.getSeconds();
   char timeStr[9];
   sprintf(timeStr,"%02d:%02d:%02d",hours,minutes,seconds);
   return String(timeStr);
}

//获取日期的函数（年-月-日）
String ntpGetDate(){
  timeClient.update();//获取时间戳更新内部时间

  time_t epochTime = timeClient.getEpochTime();//返回当前时间的epoch时间戳,适用于需要处理时间戳的应用。
  struct tm *ptm = gmtime((time_t *)&epochTime);
  int year = ptm->tm_year + 1900;
  int month = ptm->tm_mon + 1;
  int day = ptm->tm_mday;

  //用一个数组来接受日期数据
  char dateStr[12];
  sprintf(dateStr,"%04d-%02d-%02d",year,month,day);
  return String(dateStr);
} 

bool ntpSync(){
  serialPrint("正在同步网络时间...");
  oledShow(0,16,"正在同步网络时间...");
  if(timeClient.forceUpdate())
  {
    serialPrint("时间同步成功了");
    serialPrint("获取到的时间是：" + ntpGetTime()); // 如果串口输出为空，说明 return 没写对
    oledClear();
    oledShow(0,16,"时间同步成功");
    oledShow(0,32,"日期：" + ntpGetDate());//'+'号在C++里面可以拼接两个字符串
    oledShow(0,48,"时间：" + ntpGetTime());
    return true;
  }else {
    serialPrint("时间同步失败");
    oledClear();
    oledShow(0,16,"时间同步失败");
    return false;
  }
}