#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <U8g2lib.h>

#define OLED_SDA 21
#define OLED_SCL 22
 
void oledInit();
void oledShow(uint8_t x,uint8_t y,String text);
void oledClear();
extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;
#endif