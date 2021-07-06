#include "TS.h"
#include <Arduino.h>

uint8_t CAL_Temp_Sen1()
{
  uint8_t val1;
  val1 = analogRead(0);//stm32
  uint8_t cel;
  float mv;
  mv = ( val1 *5.0/ 1023.0) * 1000;
  cel = mv / 10;
  return cel;
}

uint8_t CAL_Temp_Sen2()
{
  uint8_t val2;
  val2 = analogRead(1);//stm32
  uint8_t cel;
  float mv;
  mv = ( val2*5.0/ 1023.0) * 1000;
  cel = mv / 10;
  return cel;
}

uint8_t CAL_Temp_Sen3()
{
  uint8_t val3;
  val3 = analogRead(2);//stm32
  uint8_t cel;
  float mv;
  mv = ( val3 *5.0/ 1023.0) * 1000;
  cel = mv / 10;
  return cel;
}
