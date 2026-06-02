#ifndef OLED_H
#define OLED_H

#include<U8g2lib.h>
#include"serial.h"

//定义OLED屏幕的SDA和SCL引脚，根据自己的连接方式进行修改
#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22

//函数声明
void oledInit();
void oledDisplay(uint8_t x,uint8_t y,String message);
void oledClear();

#endif