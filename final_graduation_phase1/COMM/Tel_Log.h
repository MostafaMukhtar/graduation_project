#ifndef TEL_LOG_H_INCLUDED
#define TEL_LOG_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include <string.h>
#include"AX_25_LIB.h"
#include"SSP_LIBRARY.h"
// Telemetry packet
#define Telemetry_packet_len 9
#define Version_namber_len 1
#define Type_len 1
#define lenght_len 1
#define Analog_temp_len 3
#define OBC_sate_len 1
#define ground_state_len 1
#define satellite_mode_len 1
#define VN_ground 0x05 //coming from ground
#define VN_OBC 0x04
#define Telemetry_packet_Data_len 6

// packet between communication and OBC
#define Comm_obc_packet_len 23
#define comm_obc_Version_namber_len 1
#define comm_obc_Type_len 1
#define comm_obc_Data_len 20

//Packet between communication and ground
#define Comm_grd_packet_len 23
#define comm_grd_Version_namber_len 1
#define comm_grd_Type_len 1
#define comm_grd_length 1
#define comm_grd_Data_len 20


/*function name: packet_telemty1
 *function arguments: uint8_t des,uint8_t error_count_GND,uint8_t error_count_OBC
 *function return uint8_t value
 *function description: make telemtry packet contain the sensors measurements
 * */
uint8_t *packet_telemty1(uint8_t des,uint8_t error_count_GND,uint8_t error_count_OBC);

/*function name: packet_telemty2
 *function arguments: uint8_t des, uint8_t *Data
 *function return uint8_t value
 *function description:  make telemtry packet contain the data between communication and OBC
 * */
uint8_t *packet_telemty2(uint8_t des, uint8_t *Data);

/*function name: packet_telemty2
 *function arguments: uint8_t des, uint8_t *Data
 *function return uint8_t value
 *function description: make telemtry packet contain the data between communication and ground
 * */
uint8_t *packet_telemty3(uint8_t des, uint8_t *Data);

#endif // TEL_LOG_H_INCLUDED
