#include "weather_oled.h"
#include "Serial.h"

//构造对象 需要知道oled分辨率 芯片厂商名字  
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,/*clock*/OLED_SCL,/*data*/OLED_SDA,/*reset*/U8X8_PIN_NONE);
void oledInit()
{
  Serial.println("OLED屏幕初始化……");
    u8g2.begin();//初始化

    u8g2.clearBuffer();//清空屏幕

    u8g2.setFont(u8g2_font_wqy14_t_gb2312);//设置当前使用的字体

    u8g2.enableUTF8Print();//启用UTF-8编码支持，使`print()`函数能够正确显示UTF-8编码的字符
    //刷显示
    u8g2.sendBuffer();
  Serial.println("OLED屏幕初始化完成!");
}

//屏幕显示模块
void oledShow(uint8_t x,uint8_t y,String text)
{
  u8g2.setCursor(x,y);//设置坐标
  u8g2.print(text);//设置输出信息
  u8g2.sendBuffer();//作用到屏幕上
}

//缓冲区管理区
void oledClear()
{
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}