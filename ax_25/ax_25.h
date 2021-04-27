#ifndef AX_25_H_INCLUDED
#define AX_25_H_INCLUDED
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include"sm.h"

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

#define I 0x04


#define PID_FIELD 0XF0

#define AX_25_FLAG 0X7E



extern uint8_t tx_buffer[AX_25_FRAME_LEN];       /*array which include the the output frame
                                            of the framing process*/
extern uint8_t tx_buff_flag;
extern uint8_t rx_buff_flag;


extern uint8_t received_ax_25_frame[AX_25_FRAME_LEN];


extern uint8_t window_buff[4][AX_25_FRAME_LEN]; /* array of frames which used to hold the
                                         tx_frames in case retransmission  */
extern uint8_t windwo_buff_flag;

extern uint8_t rej_var;
extern uint8_t gs_busy;
extern uint8_t rej_cond;
extern uint8_t Rx_com_busy;









void ax_25_set_start_flage();

void ax_25_set_address_field(const uint8_t *des_addr,const uint8_t *source_addr,uint8_t SSID);

uint8_t ax_25_create_control_field(uint8_t type);

void ax_25_set_pid_field(uint8_t type);
void ax_25_set_data_field_iframe();
void ax_25_set_data_field_s_uframe();
unsigned short crc_cal(unsigned char *data, int length1);
void ax_25_set_end_flage();
void ax_25_make_I_frame();
void ax_25_make_S_U_frame(uint8_t type);
void test();
uint8_t ax_25_create_control_field(uint8_t type);

// RECIVEING
uint8_t check_crc();
uint8_t Check_distnation();
uint8_t Check_Source();
uint8_t check_control_field();
void clear_256B(uint8_t *arr);
void set_received_ax_25_frame(uint8_t arr[]);
void deframing(uint8_t rx_frame[]); // DEFRAMING THE RECIEVED FRAM
uint8_t GET_NS(); // GET NS FROM CONTROL FIELD BYTE
uint8_t GET_NR(); // GET NR FROM CONTROL FIELD BYTE


/* **************************************************** */
void Rej_Condtion();
void Srej_Condtion(uint8_t nr);
void reset_parameter(void);
void ClearWindow();
void SetRejectVariable();
void Get_SSP_Data(uint8_t arr[],uint8_t len);
uint8_t Get_VR();
void Extract_I_data();
void ack_NR(uint8_t nr);

#endif // AX_25_H_INCLUDED
