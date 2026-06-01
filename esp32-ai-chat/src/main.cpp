#include "esp32-wifi.h"
#include "serial.h"
#include "OLED.h"
#include "http_deepseek.h"

void setup()
{
    serialInit(115200);
    WiFiInit();
    if (WiFiConnect(WIFI_SSID, WIFI_PASSWORD))
    {
        oledInit();
        serialPrintln("系统初始化完成，请在串口输入问题...");
    }
    else
    {
        serialPrintln("WiFi连接失败，系统无法运行！");
    }
    
}

void loop()
{
   int attempts = 0;
   if(attempts<20)
   {
     askDeepSeek("你好，DeepSeek！请问你能介绍一下自己吗？");
     delay(10000);
     attempts++;
   }
}
      

