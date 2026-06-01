#include "Serial.h"
void serialInit(uint32_t baud_rate)
{
  Serial.begin(baud_rate);
}
void serialPrint(String message){
  //输出内容：[时间戳] message
  Serial.print("[");
  Serial.print(millis());
  Serial.print("]"); 
  Serial.println(message);
}