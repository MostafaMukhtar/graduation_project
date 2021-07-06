#ifndef TS_H_INCLUDED
#define TS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include <string.h>



 /*function name: CAL_Temp_Sen1
 *function arguments: void
 *function return uint8_t value
 *function description: return temp of sensor1
 * */
uint8_t CAL_Temp_Sen1(void);

 /*function name: CAL_Temp_Sen2
 *function arguments: void
 *function return uint8_t value
 *function description: return temp of sensor2
 * */
uint8_t CAL_Temp_Sen2();

 /*function name: CAL_Temp_Sen3
 *function arguments: void
 *function return uint8_t value
 *function description: return temp of sensor3
 * */
uint8_t CAL_Temp_Sen3();


#endif // TS_H_INCLUDED
