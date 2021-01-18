#ifndef SSP_LIBRARY_H_INCLUDED
#define SSP_LIBRARY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
/*******************************************************************************
 *                            Preprocessor Macros                              *
 *******************************************************************************/
#define FEND 0xC0
#define ESC 0xab
/*******************************************************************************
 *                                 Functions                                   *
 *******************************************************************************/
 /*function name: deframing
 *function arguments: uint8_t frame[]
 *function return void
 *function description: deframe ssp frame
 * */
void deframing (uint8_t frame[]);
/*function name: Search
 *function arguments: uint8_t frame[]
 *function return void
 *function description: searching for SSP frame and put the frame in dynamic array
 * */
void Search (uint8_t frame[]);
/*function name: ByteUnsttuffing
 *function arguments: uint8_t *p
 *function return void
 *function description: Byte unstaffing for SSP frame
 * */
void Byte_Unsttuffing (uint8_t *p);
/*function name: Calculate_CRC
 *function arguments: uint8_t *p1, int length1
 *function return unsigned short
 *function description: calculating CRC for SSP frame
 * */
unsigned short Calculate_CRC(uint8_t *p1, int length1);


#endif // SSP_LIBRARY_H_INCLUDED
