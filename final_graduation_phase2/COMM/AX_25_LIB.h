#ifndef AX_25_LIB_H_INCLUDED
#define AX_25_LIB_H_INCLUDED
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include"ph.h"
#include"sm.h"
#include"SSP_LIBRARY.h"
#include <Arduino.h>
/******************************macros*****************************/
//FRAME DIMENSIONS
#define AX_25_FRAME_LEN 256
#define AX_25_DATA_FIELD_LEN 236
#define AX_25_ADDR_FIELD_LEN 14
#define AX_25_CALLSIGN_LEN 6
#define AX_25_TX_BUFFER_LEN 256*8
#define AX_25_RX_BUFFER_LEN 256*8
//CONTROL FIELD OF S FRAME
#define S_RR 0X00
#define S_RNR 0X01
#define S_REJ 0X02
#define S_SREJ 0X03
//CONTROL FIELD OF U FRAME
#define U_SABM 0X2f
#define U_DISC 0X43
#define U_DM 0X0f
#define U_UA 0X63
#define U_TEST 0Xe3
//CONTROL FIELD FRAME I
#define I 0x04
//FRAME CONSTANT FIELDS
#define PID_FIELD 0XF0
#define AX_25_FLAG 0X7E
/*************************************************************************************/

extern uint8_t gs_busy;
extern uint8_t rx_buf_busy;
extern uint8_t tx_buffer_flag,rx_buffer_flag;
extern uint8_t sf,sl,rf,rl,s,r;
extern uint8_t tx_frame[AX_25_FRAME_LEN];
extern uint8_t received_ax_25_frame[AX_25_FRAME_LEN];
extern uint8_t rej_cond,tx_buf_size;
extern uint8_t tx_buf[3][AX_25_FRAME_LEN];
extern uint8_t backup,sr;
extern uint8_t VS,VR;
extern uint8_t rx_buf_pointer;
extern uint8_t rx_buf_size;
extern uint8_t rx_buf_busy,BACKUP[AX_25_DATA_FIELD_LEN];



/****************FUNCTIONS PROTOTYPES***************/

/*function name: ax_25_set_start_flage
 *function arguments: void
 *function return void
 *function description: set the start flage of ax_25 frame
 * */
void ax_25_set_start_flage(void);

/*function name: ax_25_set_end_flage
 *function arguments: void
 *function return void
 *function description: set the end flage of ax_25 frame
 * */
void ax_25_set_end_flage(void);

/*function name: ax_25_set_address_field
 *function arguments: const uint8_t *des_addr,const uint8_t *source_addr,uint8_t SSID_NAME
 *function return void
 *function description: encoding the address field in ax_25 frame
 * */
void ax_25_set_address_field(const uint8_t *des_addr,const uint8_t *source_addr,uint8_t SSID_NAME);

/*function name: ax_25_create_control_field
 *function arguments: uint8_t type
 *function return uint8_t value
 *function description: encoding the I,S,U control field in ax_25 frame
 * */
uint8_t ax_25_create_control_field(uint8_t type);

/*function name: ax_25_set_pid_field
 *function arguments: uint8_t type
 *function return void
 *function description: set pid field to 0xf0
 * */
void ax_25_set_pid_field(uint8_t type);


/*function name: ax_25_set_data_field_iframe
 *function arguments: void
 *function return void
 *function description: get data from upper layer and set the data filed in i frame
 * */
void ax_25_set_data_field_iframe(void);

/*function name: ax_25_set_data_field_s_uframe
 *function arguments: void
 *function return void
 *function description: set date field to zeros to get 256 byte length frame 
 * */
void ax_25_set_data_field_s_uframe(void);

/*function name: crc_cal
 *function arguments: unsigned char *data, int length1
 *function return unsigned short
 *function description: crc calculator for ax_25 frame 
 * */
unsigned short crc_cal(unsigned char *data, int length1);

void ax_25_make_I_frame();

/*function name: clear_array
 *function arguments: uint8_t *arr,int l
 *function return void
 *function description: reset an array of length l 
 * */
void clear_array(uint8_t *arr,int l);

/*function name: ax_25_make_S_U_frame
 *function arguments: uint8_t typel
 *function return void
 *function description: make s or u frame as required
 * */
void ax_25_make_S_U_frame(uint8_t type);

/******************************************************************************************************************/

/*function name: check_crc
 *function arguments: void
 *function return uint8_t value
 *function description: check the crc for coming ax_25 frame
 * */
uint8_t check_crc(void);

/*function name: Check_distnation
 *function arguments: void
 *function return uint8_t value
 *function description: check the distnation for coming ax_25 frame
 * */
uint8_t Check_distnation(void);

/*function name: Check_Source
 *function arguments: void
 *function return uint8_t value
 *function description: check the Source for coming ax_25 frame
 * */
uint8_t Check_Source(void);

/*function name: check_control_field
 *function arguments: void
 *function return uint8_t value
 *function description: check the control_field for coming ax_25 frame
 * */
uint8_t check_control_field(void);

/*function name: deframing
 *function arguments: void
 *function return void
 *function description: used to deframing the coming ax_frame
 * */
void deframing(void);

/*function name: GET_NR
 *function arguments: void
 *function return uint8_t value
 *function description: used to extract the received sequence number from  the coming ax_frame
 * */
uint8_t GET_NR(void);

/*function name: GET_NS
 *function arguments: void
 *function return uint8_t value
 *function description: used to extract the send sequence number from  the coming ax_frame
 * */
uint8_t GET_NS(void);

/*function name: ack_NR
 *function arguments: uint8_t nr
 *function return void
 *function description: used to acknowledge the sent ax_25 frmae
 * */
void ack_NR(uint8_t nr);

/*function name: reset_parameter
 *function arguments: void 
 *function return void
 *function description: used to reset all parameter to statr connection 
 * */
void reset_parameter(void);


/*function name: Rej_Condtion
 *function arguments: uint8_t nr 
 *function return void
 *function description: used to response the rej frame 
 * */
void Rej_Condtion(uint8_t nr);

/*function name: Srej_Condtion
 *function arguments: uint8_t nr 
 *function return void
 *function description: used to response the srej frame 
 * */
void Srej_Condtion(uint8_t nr);

/*function name: Get_VR
 *function arguments: void 
 *function return uint8_t value
 *function description: used to return VR value 
 * */
uint8_t Get_VR(void);

/*function name: Extract_I_data
 *function arguments: void
 *function return void
 *function description: extract data from i fram and pass it to ssp  
 * */
void Extract_I_data(void);

/*function name: get_tx_frame
 *function arguments: uint8_t ss
 *function return void
 *function description: pass the frames from tx buffer to txframe to transmit  
 * */
void get_tx_frame(uint8_t ss);

/*function name: Get_SSP_Data
 *function arguments: uint8_t arr[],uint8_t len
 *function return void
 *function description: ssp call this function to transfer the ssp frame to data field in ax_25 
 * */
void Get_SSP_Data(uint8_t arr[],uint8_t len);


#endif // AX_25_LIB_H_INCLUDED
