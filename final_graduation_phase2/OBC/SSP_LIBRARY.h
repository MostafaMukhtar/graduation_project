#ifndef SSP_LIBRARY_H_INCLUDED
#define SSP_LIBRARY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include <string.h>
//#include"AX_25_LIB.h"
/*******************************************************************************
 *                            Preprocessor Macros                              *
 *******************************************************************************/
#define FEND 0xC0
#define ESC 0xab
#define GND 0x23
#define COMM 0x12
#define OBC 0x22
#define GET_TEL_1 0x34
#define GET_PACKET_2 0x44
#define GET_PACKET_3 0x45
#define INIT 0x00
#define PING_ 0x43
#define TEL_1_RESPONSE 0x56
#define PACKET_2_RESPONSE 0x11
#define PACKET_3_RESPONSE 0x46
#define ACK 0x89

//#define Comm_Ping 0x88
#define NACK 0x59
#define DISREQ 0x33

#define crc_error 0x04
#define des_error 0x05
#define type_error 0x06

extern uint8_t ptr1[236];
extern uint8_t ptr [236];
extern int length1;
extern int length0;
extern uint8_t tx_SSP_buff_flag;
extern uint8_t rx_SSP_buff_flag;
/*******************************************************************************
 *                                 Functions                                   *
 *******************************************************************************/
 /*function name: deframing
 *function arguments: uint8_t frame[]
 *function return void
 *function description: deframe ssp frame
 * */
void deframing_ssp (uint8_t frame[]);
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
/*function name: Packet_Analysis
 *function arguments: uint8_t *p
 *function return void
 *function description: check the corectness of SRC and make response based on DES
 * */
void Packet_Analysis(uint8_t *p);
/*function name: Generate_Response
 *function arguments: uint8_t type,uint8_t DES
 *function return void
 *function description: forming frame and send it to OBC or GND
 * */
void Generate_Response(uint8_t type,uint8_t DES);
/*function name: Find_Type_of_Frame
 *function arguments: uint8_t type
 *function return uint8_t
 *function description: determine the type of frame based on the type of received frame
 * */
void Find_Type_of_Frame(uint8_t type);
/*function name: GET_DATA
 *function arguments: uint8_t type,uint8_t len
 *function return void
 *function description: get data from sensors
 * */
void GET_DATA(uint8_t type);
/*function name: Byte_Sttuffing
 *function arguments: uint8_t *p
 *function return void
 *function description: Byte stuffing for SSP frame
 * */
void Byte_Sttuffing (uint8_t *p);

/*function name: zeros_arr
 *function arguments: uint8_t arr[]
 *function return void
 *function description: zeroing an array of length 236 byte
 * */
void zeros_arr(uint8_t arr[]);

/*function name: Framing
 *function arguments: uint8_t type,uint8_t DES
 *function return void
 *function description: makeing ssp frame of required type and destination
 * */
void Framing(uint8_t type,uint8_t DES);

#endif // SSP_LIBRARY_H_INCLUDED
