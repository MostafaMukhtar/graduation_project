#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include <Arduino.h>
#include"SSP_LIBRARY.h"
extern char t1;
extern uint8_t done;
void dis_ssp(uint8_t *frame,uint8_t len,uint8_t pp);



#endif 
