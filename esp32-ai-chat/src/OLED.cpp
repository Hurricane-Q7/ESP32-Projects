#include "OLED.h"

//结合自己的oled参数，利用u8g2库来创建一个OLED对象
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, OLED_SCL_PIN, OLED_SDA_PIN, U8X8_PIN_NONE);
void oledInit()
{
  oled.begin();
  oled.clear();
  oled.setFont(u8g2_font_wqy12_t_gb2312b);//设置字体大小、粗细程度，支持中文显示
  oled.enableUTF8Print();//启用UTF-8编码支持，以便正确显示中文字符，如果不启用，中文字符可能会显示为乱码
  serialPrintln("OLED屏幕初始化完成!!!");  
}
void oledDisplay(uint8_t x,uint8_t y,String message)
{
    oled.setCursor(x,y);//设置光标位置，x和y分别表示列和行
    oled.print(message);//先将要显示的内容写入缓冲区，最后调用sendBuffer()函数将缓冲区的内容发送到OLED屏幕上进行显示
    oled.sendBuffer();
}
void oledClear()
{
    //调用clear()函数清空缓冲区的内容，调用sendBuffer()函数将清空后的缓冲区内容发送到OLED屏幕上，从而实现清屏的效果
    oled.clear();
    oled.sendBuffer();
}