#ifndef AX_25_H_INCLUDED
#define AX_25_H_INCLUDED
#include <stdint.h>
#include <stdbool.h>

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
#define U_SABM 0X3f
#define U_DISC 0X53
#define U_DM 0X1f
#define U_UA 0X73
#define U_TEST 0Xf3

#define I 0x04


#define PID_FIELD 0XF0

#define AX_25_FLAG 0X7E



void ax_25_set_start_flage();

void ax_25_set_address_field(const uint8_t *des_addr,const uint8_t *source_addr,uint8_t SSID);

uint8_t ax_25_create_control_field(uint8_t type);

void ax_25_set_pid_field(uint8_t type);
void ax_25_set_data_field_iframe(uint8_t *data);
void ax_25_set_data_field_s_uframe();
unsigned short crc_cal(unsigned char *data, int length1);
void ax_25_set_end_flage();
void ax_25_make_I_frame(uint8_t *arr_data);
void ax_25_make_S_U_frame(uint8_t type);
void test();
uint8_t ax_25_create_control_field(uint8_t type);
bool check_crc();
bool Check_distnation();
bool Check_Source();
uint8_t check_control_field();
void clear_256B(uint8_t *arr);



#endif // AX_25_H_INCLUDED
