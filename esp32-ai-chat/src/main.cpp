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
    }
    else
    {
        serialPrintln("WiFi连接失败，系统无法运行！");
    }
    oledDisplay(0, 16, "WiFi连接成功!");
    delay(2000);
    oledClear();
    askDeepSeek("你好，用10个字介绍一下自己！");
    
}

void loop()
{

}
      

