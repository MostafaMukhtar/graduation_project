#include "ax_25.h"

uint8_t out[AX_25_FRAME_LEN];       /*array which include the the output frame
                                    of the framing process*/


uint8_t received_ax_25_frame[AX_25_FRAME_LEN];


uint8_t tx_buff[3][AX_25_FRAME_LEN]; /* array of frames which used to hold the
                                         tx_frames in case retransmission  */


uint8_t counter=0;                   /*counter used to insert flags of ax_25
                                        in out array */

uint8_t VS=0,VR=0;                    /*vs contains the next sequential number to be
                                        assigned to the next transmitted I frame
                                        This variable is updated with the transmission of each I frame.
                                        ***************************************************************
                                        vr contains the sequence number of the next expected
                                        received I frame.
                                        */


uint8_t window_pointer=0;             /*point to the next free position in the tx_buff*/


const uint8_t des_addr[AX_25_CALLSIGN_LEN]={'N','J','7','P',' ',' '};       /*callsign of the destination*/

const uint8_t source_addr[AX_25_CALLSIGN_LEN]={'N','7','L','E','M',' '};    /*callsign of the source*/

uint8_t SSID=0x00;                    /*The SSID is a four-bit integer that uniquely identifies
                                        multiple stations using the same amateur callsign.*/


void ax_25_set_start_flage(){        /*set the start flag which is constant byte 01111110 ,7E hex*/
*(out+counter)=AX_25_FLAG;
counter++;
}


void ax_25_set_end_flage(){          /*set the end flag which is constant byte 01111110 ,7E hex */
*(out+counter)=AX_25_FLAG;
counter++;
}


/*
address encoding process address field is extended beyond
one octet by assigning the least-significant bit of each octet to be
an “extension bit.” The extension bit of each octet is set to “0” to indicate
the next octet contains more address information, or to “1”, to indicate that
this is the last octet of  the HDLC address field. To make room for this
 extension bit, the amateur radio call- sign information is shifted one bit left.

*/

void ax_25_set_address_field(const uint8_t *des_addr,const uint8_t *source_addr,uint8_t SSID){
    uint8_t addr[AX_25_ADDR_FIELD_LEN];

        int i=0;
    for(;i<AX_25_CALLSIGN_LEN;i++){
    addr[i]=des_addr[i]<<1;}

    addr[i]=(SSID<<1)|0x60;
    i++;


    for(;(i-7)<AX_25_CALLSIGN_LEN;i++){
        addr[i]=source_addr[i-7]<<1;}
        addr[i]=(SSID<<1)|0x61;

memcpy(out+counter,addr,AX_25_ADDR_FIELD_LEN);
counter+=AX_25_ADDR_FIELD_LEN;
    }



uint8_t ax_25_create_control_field(uint8_t type){           /*create the control field with different type I,U,S*/
uint8_t NS=VS,NR=VR;
switch(type){
case S_RR:
    return(NR<<5)|0X10|(S_RR<<2)|0X01;
case S_RNR:
    return(NR<<5)|0X10|(S_RNR<<2)|0X01;
case S_REJ:
    return(NR<<5)|0X10|(S_REJ<<2)|0X01;
case S_SREJ:
    return(NR<<5)|0X10|(S_SREJ<<2)|0X01;
case U_SABM:case U_DISC:case U_DM:case U_UA:case U_TEST:
    return type;
case I:
    return (NR<<5)| 0x10 |(NS<<1)|0x00 ;
default : return 0;
}
}



void ax_25_set_pid_field(uint8_t type){
uint8_t pid=0;
if(type==I){
    pid=PID_FIELD;
    }
out[counter]=pid;
counter++;
}


void ax_25_set_data_field_iframe(uint8_t *data){    /*set the data field in i frame*/

memcpy(out+counter,data,AX_25_DATA_FIELD_LEN);
counter+=AX_25_DATA_FIELD_LEN;
}


void ax_25_set_data_field_s_uframe(){        /*set the data field in s,u frame to zeros*/
int i=0;
for(;i<AX_25_DATA_FIELD_LEN;i++)out[counter+i]=0;
counter+=AX_25_DATA_FIELD_LEN;
}


unsigned short crc_cal(unsigned char *data, int length1){ /*  calculate the crc */
# define POLY 0x8408 /* bits reversed for LSB-first */
unsigned short crc = 0xffff;
unsigned char *bufp = data;
int len;
int i;
for (len = length1; len > 0; len--) {
unsigned char ch = *bufp++;
for (i = 8; i > 0; i--) {
crc = (crc >> 1) ^(((ch ^crc) & 0x01) ? POLY : 0 );
ch >>= 1;
}
}
return crc;
}





void ax_25_make_I_frame(uint8_t *arr_data){            /*making I frame with data field equal to arr_data*/
unsigned short crc;
ax_25_set_start_flage();
ax_25_set_address_field(des_addr,source_addr,SSID);
out[counter]=ax_25_create_control_field(I);
counter++;
ax_25_set_pid_field(I);
ax_25_set_data_field_iframe(arr_data);
crc=crc_cal(out+1,AX_25_FRAME_LEN-4);
out[counter++]=(uint8_t)crc;
out[counter++]=(uint8_t)(crc>>8);
ax_25_set_end_flage();

//out

//trans
VS=VS+1;
//window_pointer=0
memcpy(tx_buff[window_pointer],out,AX_25_FRAME_LEN);
//tx_buff[window_pointer]=out
//out=0

int i=0;

for(;i<AX_25_FRAME_LEN;i++){
   printf("%x ",out[i]);

}
clear_256B(out);//clear out
//window_pointer++;
window_pointer++;
if(window_pointer>2) window_pointer=0; //if window_pointer>2
                                        //window_pointer=0

i=0;
for(;i<AX_25_FRAME_LEN;i++){
   printf("%x ",tx_buff[0][i]);

}









}

void clear_256B(uint8_t *arr){      /*used to clear 256 of any array*/
int i =0;
for(;i<256;i++){
    arr[i]=0;
}
}





void ax_25_make_S_U_frame(uint8_t type){        /*making s_u frames depending on the type value*/
unsigned short crc;
ax_25_set_start_flage();
ax_25_set_address_field(des_addr,source_addr,SSID);
out[counter]=ax_25_create_control_field(type);
counter++;
ax_25_set_pid_field(type);
ax_25_set_data_field_s_uframe();
crc=crc_cal(out+1,AX_25_FRAME_LEN-4);
out[counter++]=(uint8_t)crc;
out[counter++]=(uint8_t)(crc>>8);
ax_25_set_end_flage();

int i=0;

for(;i<AX_25_FRAME_LEN;i++){
   printf("%x ",out[i]);

}
}











/***********receiving************/

bool check_crc(){
unsigned short crc;
uint8_t crc0,crc1;
crc=crc_cal(received_ax_25_frame+1,AX_25_FRAME_LEN-4);
crc0=(uint8_t)crc;
crc1=(uint8_t)(crc>>8);

if(crc0==received_ax_25_frame[253]&& crc1==received_ax_25_frame[254]){
    return true;

}
else{

    return false;
}

}

bool Check_distnation(){
    int i=1;
    for(;i<7;i++)
    {
    if(des_addr[i-1]!=(received_ax_25_frame[i]>>1))
    {
        return false ;
    }
    }

    if(received_ax_25_frame[7]!=0x60){

        return false ;
    }

    return true ;
}

bool Check_Source(){
    int i=8;
    for(;i<15;i++)
    {
    if(source_addr[i-8]!=(received_ax_25_frame[i]>>1))
    {
        return false;
    }
    }

    if(received_ax_25_frame[14]!=0x61){

        return false;
    }

    return true;
}




uint8_t check_control_field(){

if(!(received_ax_25_frame[15]&0x01)){

return I;
    /****** I FRAME ****/

}
else {
        if(received_ax_25_frame[15]&0x02){
            switch(received_ax_25_frame[15]){
                case U_SABM:// U_SABM ;
                            return U_SABM;
                            break;
                case U_DISC:// U_DISC;
                            return U_DISC;
                            break;
                case U_DM: // U_DM;
                            return U_DM;
                            break;
                case U_UA: // U_UA;
                            return U_UA;
                            break;
                case U_TEST://U_TEST;
                            return U_TEST;
                            break;

            }}
        else {
                switch((received_ax_25_frame[15] & 0x0c)>>2){
                    case S_RR: // S_RR;
                                return S_RR;
                                break;
                    case S_RNR: // S_RNR
                                return S_RNR;
                                break;
                    case S_REJ: // S_REJ
                                return S_REJ;
                                break;
                    case S_SREJ: // S_SREJ
                                return S_SREJ;
                                break;


            }

    }

}
return 0;

}



void set_received_ax_25_frame(uint8_t arr[]){
int i=0;
for(;i<AX_25_FRAME_LEN;i++){
received_ax_25_frame[i]=arr[i];
}

}



void deframing(uint8_t rx_frame[]){
set_received_ax_25_frame(rx_frame);
if(!check_crc()){/*invalid crc*/}
if(!Check_distnation()){/*invalid destnation */}
if(!Check_Source()){/*invalid source*/}
switch(check_control_field()){
case I: /*I response */ break;

case S_RR:/*RR_RESPONSE */break;
case S_RNR:/*RNR_RESPONSE */break;
case S_REJ:/*REJ_RESPONSE */break;
case S_SREJ:/*SREJ_RESPONSE */break;

case U_SABM: /* U_SABM_RESPONCE */ break;
case U_DISC: /* U_DISC_RESPONCE */ break;
case U_DM: /* U_DM_RESPONCE */ break;
case U_UA: /* U_UA_RESPONCE */ break;
case U_TEST: /* U_TEST_RESPONCE */ break;

}



}


uint8_t GET_NS()
{
   return (received_ax_25_frame[15]&0x0E)>>1 ; //get NS from control field byte

}

uint8_t GET_NR()
{
   return (received_ax_25_frame[15]&0xE0)>>5 ; //get NR from control field byte

}









