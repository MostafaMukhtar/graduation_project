#include"AX_25_LIB.h"
#include"sm.h"
#include"ph.h"

//TX BUFFER PARAMETERS
uint8_t tx_buf[3][AX_25_FRAME_LEN];
uint8_t tx_buf_pointer=0;
uint8_t tx_buf_size=0;
uint8_t tx_buf_busy=0;

//RX_BUFFER PARAMETERS
uint8_t rx_buf[3][AX_25_FRAME_LEN];
uint8_t rx_buf_pointer=0;
uint8_t rx_buf_size=0;
uint8_t rx_buf_busy=0;
uint8_t rej_cond=0;

//FLOW CONTROL PARAMETERS 
uint8_t sf=0,sl=2,rf=0,rl=2,s=2,r=0;
uint8_t VS=0,VR=0;

//BUSY MODE IDENTIFIER
uint8_t gs_busy=0;
uint8_t comm_busy=0;

//TX_RX FRAME
uint8_t tx_frame[AX_25_FRAME_LEN];
uint8_t received_ax_25_frame[AX_25_FRAME_LEN];
uint8_t tx_buffer_flag=0,rx_buffer_flag=0;




uint8_t counter=0;                   /*counter used to insert flags of ax_25 in out array */

const uint8_t gnd_addr[AX_25_CALLSIGN_LEN]={'N','J','7','P',' ',' '};       /*callsign of the destination*/

const uint8_t comm_addr[AX_25_CALLSIGN_LEN]={'N','7','L','E','M',' '};    /*callsign of the source*/

uint8_t SSID_NAME=0x00;                    /*The SSID is a four-bit integer that uniquely identifies multiple stations using the same amateur callsign.*/

uint8_t SSP_Data[AX_25_DATA_FIELD_LEN];     /*here we receive data from ssp_lib*/


/****************************************************************************************************************************************/


void ax_25_set_start_flage(void){        /*set the start flag which is constant byte 01111110 ,7E hex*/
    *(tx_frame+counter)=AX_25_FLAG;
    counter++;
}
void ax_25_set_end_flage(void){          /*set the end flag which is constant byte 01111110 ,7E hex */
    *(tx_frame+counter)=AX_25_FLAG;
    counter++;
}

/*
address encoding process address field is extended beyond
one octet by assigning the least-significant bit of each octet to be
an �extension bit.� The extension bit of each octet is set to �0� to indicate
the next octet contains more address information, or to �1�, to indicate that
this is the last octet of  the HDLC address field. To make room for this
extension bit, the amateur radio call- sign information is shifted one bit left.
*/
void ax_25_set_address_field(const uint8_t *des_addr,const uint8_t *source_addr,uint8_t SSID_NAME){
    uint8_t addr[AX_25_ADDR_FIELD_LEN];
    int i=0;
    for(;i<AX_25_CALLSIGN_LEN;i++){
    addr[i]=des_addr[i]<<1;}
    addr[i]=(SSID_NAME<<1)|0x60;
    i++;
    for(;(i-7)<AX_25_CALLSIGN_LEN;i++){
        addr[i]=source_addr[i-7]<<1;}
    addr[i]=(SSID_NAME<<1)|0x61;
    memcpy(tx_frame+counter,addr,AX_25_ADDR_FIELD_LEN);
    counter+=AX_25_ADDR_FIELD_LEN;
    }
    
/*create the control field with different type I,U,S*/
uint8_t ax_25_create_control_field(uint8_t type){           
    uint8_t NS=VS,NR=VR;
    switch(type){
    case S_RR:
        return(NR<<5)|0X00|(S_RR<<2)|0X01;
    case S_RNR:
        return(NR<<5)|0X00|(S_RNR<<2)|0X01;
    case S_REJ:
        return(NR<<5)|0X00|(S_REJ<<2)|0X01;
    case S_SREJ:
        return(NR<<5)|0X00|(S_SREJ<<2)|0X01;
    case U_SABM:case U_DISC:case U_DM:case U_UA:case U_TEST:
        return type;
    case I:
        return (NR<<5)| 0x00 |(NS<<1)|0x00 ;
    default : return 0;
    }
}

/*pid indicate the protocol used in network layer in our case pid is 0xf0*/
void ax_25_set_pid_field(uint8_t type){
    uint8_t pid=0;
    if(type==I){pid=PID_FIELD;}
    tx_frame[counter]=pid;
    counter++;
}

/*set the data field in i frame from ssp_lib*/
void ax_25_set_data_field_iframe(void){    
    memcpy(tx_frame+counter,SSP_Data,AX_25_DATA_FIELD_LEN);
    counter+=AX_25_DATA_FIELD_LEN;
}

/*set the data field in s,u frame to zeros to get 256*/
void ax_25_set_data_field_s_uframe(void){        
    int i=0;
    for(;i<AX_25_DATA_FIELD_LEN;i++)tx_frame[counter+i]=0;
    counter+=AX_25_DATA_FIELD_LEN;
}

 /*calculate the crc*/
unsigned short crc_cal(unsigned char *data, int length1){
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

/*making I frame with data field equal to arr_data*/
void ax_25_make_I_frame(void){            
    clear_array(tx_frame,AX_25_FRAME_LEN);
    unsigned short crc;
    ax_25_set_start_flage();
    ax_25_set_address_field(gnd_addr,comm_addr,SSID_NAME);
    tx_frame[counter]=ax_25_create_control_field(I);
    counter++;
    ax_25_set_pid_field(I);
    ax_25_set_data_field_iframe();
    crc=crc_cal(tx_frame+1,AX_25_FRAME_LEN-4);
    tx_frame[counter++]=(uint8_t)crc;
    tx_frame[counter++]=(uint8_t)(crc>>8);
    ax_25_set_end_flage();

    VS=VS+1;
    if(VS>7)VS=0;
    s=s+1;
    if(s>2)s=0;
    memcpy(tx_buf[tx_buf_pointer],tx_frame,AX_25_FRAME_LEN);
    tx_buf_pointer++;
    tx_buf_size++;
    if(tx_buf_size==3) tx_buf_busy=1;
    if(tx_buf_pointer>2) tx_buf_pointer=0;
                                     
    tx_buffer_flag=1;
    PhEvent_Triggered=tx_event;
}

/*used to clear 256 of any array*/
void clear_array(uint8_t *arr,int l){      
    int i =0;
    for(;i<l;i++){arr[i]=0;}
}

/*making s_u frames depending on the type value*/
void ax_25_make_S_U_frame(uint8_t type){        
    clear_array(tx_frame,AX_25_FRAME_LEN);
    unsigned short crc;
    ax_25_set_start_flage();
    ax_25_set_address_field(gnd_addr,comm_addr,SSID_NAME);
    tx_frame[counter]=ax_25_create_control_field(type);
    counter++;
    ax_25_set_pid_field(type);
    ax_25_set_data_field_s_uframe();
    crc=crc_cal(tx_frame+1,AX_25_FRAME_LEN-4);
    tx_frame[counter++]=(uint8_t)crc;
    tx_frame[counter++]=(uint8_t)(crc>>8);
    ax_25_set_end_flage();
    
    tx_buffer_flag=1;
    PhEvent_Triggered=tx_event;
}


/***********************************************************************************************************************************************/

uint8_t check_crc(void){
    unsigned short crc;
    uint8_t crc0,crc1;
    crc=crc_cal(received_ax_25_frame+1,AX_25_FRAME_LEN-4);
    crc0=(uint8_t)crc;
    crc1=(uint8_t)(crc>>8);
    if(crc0==received_ax_25_frame[253]&& crc1==received_ax_25_frame[254]){
        return 1;}
    else{
        return 0;
        }
}

uint8_t Check_distnation(void){
    int i=1;
    for(;i<7;i++){
      if(comm_addr[i-1]!=(received_ax_25_frame[i]>>1)){
        return 0 ;}
      }
    if(received_ax_25_frame[7]!=0x60){
        return 0 ;
       }
    return 1 ;
}

uint8_t Check_Source(void){
    int i=8;
    for(;i<14;i++)
    {
    if(gnd_addr[i-8]!=(received_ax_25_frame[i]>>1))
    {
        return 0;
    }
    }
    if(received_ax_25_frame[14]!=0x61){
        return 0;
    }
    return 1;
}

uint8_t check_control_field(void){
    if(!(received_ax_25_frame[15]&0x01)){
    return I; /****** I FRAME ****/
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


void deframing(void){
 // DATA OF RECIVEIED I FRAME
 
    if(check_crc()){/*valid crc*/
        if(Check_distnation()){/*valid destnation */
            if(Check_Source()){/*valid source*/
                switch(check_control_field()){
                    case I: /*I response */              
                    Event_Triggered=Rx_I_frame;
                        break;  
                    case S_RR:/*RR_RESPONSE */
                        Event_Triggered=RR_Frame;
                        break;
                    case S_RNR:/*RNR_RESPONSE */
                        Event_Triggered=RNR_Frame;    
                        break;
                    case S_REJ:/*REJ_RESPONSE */
                        Event_Triggered=REJ_Frame;
                        break;
                    case S_SREJ:/*SREJ_RESPONSE */
                        Event_Triggered=SREJ_Frame;
                        break;
                    case U_SABM:
                        Event_Triggered=SABM_Frame;
                        /* U_SABM_RESPONCE */ break;
                    case U_DISC:
                        Event_Triggered=DISC_Frame;
                        /* U_DISC_RESPONCE */ break;
                    case U_DM:
                        Event_Triggered=DM_Frame;
                        /* U_DM_RESPONCE */ break;
                    case U_UA:
                        Event_Triggered=UA_Frame;
                        /* U_UA_RESPONCE */ break;
                   case U_TEST:
                        Event_Triggered=TEST_Frame;
                        /* U_UA_RESPONCE */ break;   
                   default:break;
    }
    }
    }
    }
    else{error_count_GND++;}
    rx_buf_busy=0;
    rx_buf_size--;
    rx_buf_pointer++;
    if(rx_buf_pointer==3)rx_buf_pointer=0;
    if(rx_buf_size==0) rx_buffer_flag=0;
}

/*GET NS OF THE RECIEVED FRAME*/
uint8_t GET_NS()    
{
   return (received_ax_25_frame[15]&0x0E)>>1 ; //get NS from control field byte
}

/*GET NR OF THE RECIEVED FRAM*/
uint8_t GET_NR()    
{
   return (received_ax_25_frame[15]&0xE0)>>5 ; //get NR from control field byte
}


void ack_NR(uint8_t nr){//edited  
    tx_buf_size-=nr-sf;
    sf=nr;
    sl=sf+2;
    if(sf>7)sf-=8;
    if(sl>7)sl-=8;
    tx_buf_busy=0;
}

void Rej_Condtion(uint8_t nr){
    rej_cond=1;
    s-=tx_buf_size;
    tx_buffer_flag=1;
}

void Srej_Condtion(uint8_t nr){
    memcpy(tx_frame,tx_buf[0],AX_25_FRAME_LEN);
    tx_buffer_flag=1;
}

void reset_parameter(void){
    VS=0;
    VR=0;
    sf=0;
    sl=3;
    rf=0;
    rl=3;
    s=0;
    r=0;
    
    tx_buffer_flag=0;
    tx_buf_pointer=0;
    tx_buf_size=0;
    tx_buf_busy=0;
    rx_buf_pointer=0;
    rx_buf_size=0;
    rx_buf_busy=0;
    rej_cond=0;
    gs_busy=0;
    comm_busy=0;
}


uint8_t Get_VR(void){
    return VR;
}

void Extract_I_data(void){
    uint8_t DATA[AX_25_DATA_FIELD_LEN];
    memcpy(DATA,received_ax_25_frame+17,AX_25_DATA_FIELD_LEN);
    VR=VR+1;
    if(VR>7)VR=0;    
    deframing_ssp(DATA);
}


void get_tx_frame(uint8_t ss){
  memcpy(tx_frame,tx_buf[ss],AX_25_FRAME_LEN);
}

//SSP will call this function to set data
void Get_SSP_Data(uint8_t arr[],uint8_t len){
    int i=0;
    for(;i<AX_25_DATA_FIELD_LEN;i++){SSP_Data[i]=0;}
    memcpy(SSP_Data,arr,len);
}
