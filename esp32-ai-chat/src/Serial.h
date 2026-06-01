#ifndef SERIAL_H
#define SERIAL_H

#include<Arduino.h>
void serialInit(uint32_t baud_rate);
void serialPrintln(String message);

#endif
