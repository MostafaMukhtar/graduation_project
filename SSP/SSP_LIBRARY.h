#ifndef SSP_LIBRARY_H_INCLUDED
#define SSP_LIBRARY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include <string.h>
/*******************************************************************************
 *                            Preprocessor Macros                              *
 *******************************************************************************/
#define FEND 0xC0
#define ESC 0xab
#define GND 0x23
#define COMM 0x12
#define OBC 0x22
#define GET_TEL_1 0x34
#define GET_TEL_2 0x44
#define INIT 0x00
#define PING 0x43
#define TEL_1_RESPONSE 0x56
#define TEL_2_RESPONSE 0x11
#define ACK 0x89
#define GET 0x99
#define ID1 0x01
#define ID2 0x02
#define ID3 0x03
#define ID4 0x04
//#define Comm_Ping 0x88
#define FAILED 0x66
#define NACK 0x59



extern uint8_t ptr1[236];
extern int length1;
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
/*function name: Read_Sensor1
 *function arguments: void
 *function return void
 *function description: read the first sensor
 * */
void Read_Sensor1();
/*function name: Read_Sensor2
 *function arguments: void
 *function return void
 *function description: read the second sensor
 * */
void Read_Sensor2();
/*function name: Byte_Sttuffing
 *function arguments: uint8_t *p
 *function return void
 *function description: Byte stuffing for SSP frame
 * */
void Byte_Sttuffing (uint8_t *p);

void test_();
void zeros_arr(uint8_t arr[]);
void Framing(uint8_t type,uint8_t DES);

#endif // SSP_LIBRARY_H_INCLUDED
