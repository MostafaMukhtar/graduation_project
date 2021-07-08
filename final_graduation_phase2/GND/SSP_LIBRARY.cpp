#include "SSP_LIBRARY.h"
#include "ssp_state_machine.h"
#include <Arduino.h>
uint8_t ptr[236],ptr1[236];
uint8_t tx_SSP_buff_flag=0;
uint8_t rx_SSP_buff_flag=0;
int length0,length1;
uint8_t error_count_GND=0,error_count_OBC=0; 
uint8_t Data_obc[20],Data_gnd[20],p3=0,p2=0;


unsigned short crc,crct;
uint8_t crc0,crc1;

void deframing_ssp (uint8_t frame[]){
    length0 = 0;
    zeros_arr(ptr);
    Search(frame);
    Byte_Unsttuffing(ptr);
    crc = Calculate_CRC(&ptr[1],length0-4);
    crc0 = crc;
    crc = crc>>8;
    crc1 = crc;

    if (crc0 == ptr[length0-3] && crc1 == ptr[length0-2]){
       Packet_Analysis(ptr);}
    else{
      error_count_OBC++; //add crc error to arry obc 
      }
      }

void Search (uint8_t frame[])
{
    if (frame[0]==FEND){                          //validating of the frame.
        int index = 1;
        while(frame[index]!=FEND){                //finding the length of the frame.
            if(frame[index]==ESC)
              index++;
              index++;
        }
        length0 = index+1;
        int i;
        for( i=0 ; i<length0; i++){
            ptr[i] = frame[i];
            
        }
    }

}
uint8_t get_len0 (uint8_t frame[]){
  if (frame[0]==FEND){                          //validating of the frame.
        int index = 1;
        while(frame[index]!=FEND){                //finding the length of the frame.
            if(frame[index]==ESC)
              index++;
              index++;
        }
        length0 = index+1;
  
  }
return length0;

}

uint8_t get_len1 (){

return length1;

}
void Byte_Unsttuffing (uint8_t *p){
    int i;
    for(i=0 ; i<length0 ; i++){
        if(p[i]==ESC){
            int j;
            for( j=i ; j<length0-1 ; j++){
                p[j] = p[j+1];
            }
            length0--;
        }
      
    }
}

unsigned short Calculate_CRC(uint8_t *p1, int length1){
    # define POLY 0x8408         // bits reversed for LSB-first
    unsigned short crc = 0xffff;
    uint8_t *bufp = p1;
    int len;
    int i;
    for (len = length1; len > 0; len--) {
        uint8_t ch = *bufp++;
        for (i = 8; i > 0; i--) {
            crc = (crc >> 1) ^(((ch ^crc) & 0x01) ? POLY : 0 );
            ch >>= 1;
    }
        }
    return crc;
}

void Packet_Analysis(uint8_t *p){
    uint8_t type0=p[3];


      
        
    
    
}


void Generate_Response(uint8_t type,uint8_t DES){
     
    zeros_arr(ptr1);
    length1 = 0;
    ptr1[0] = FEND;
    ptr1[1] = DES;
    ptr1[2] = COMM;
    ptr1[3] = type;
    length1+=4;
    GET_DATA(ptr1[3],DES);
    crct = Calculate_CRC(ptr1+1,length1-1);
    ptr1[length1] = crct;
    crct = crct>>8;
    ptr1[length1+1] = crct;
    length1+=2;
    Byte_Sttuffing (&ptr1[1]);
    ptr1[length1] = FEND;
    length1++;
   
    if(DES==GND){
      Get_SSP_Data(ptr1,length1);
      ax_25_make_I_frame(); }
    else if(DES==OBC){
      tx_SSP_buff_flag=1;}
}



void Framing(uint8_t type,uint8_t DES){

    zeros_arr(ptr1);
    length1 = 0;
    ptr1[0] = FEND;
    ptr1[1] = DES;
    ptr1[2] = GND;
    ptr1[3] = type;
    length1+=4;
    crct = Calculate_CRC(ptr1+1,length1-1);
    ptr1[length1] = crct;
    crct = crct>>8;
    ptr1[length1+1] = crct;
    length1+=2;

    Byte_Sttuffing (&ptr1[1]);
    ptr1[length1] = FEND;
    length1++;

   
       Get_SSP_Data(ptr1,length1);
       ax_25_make_I_frame();


    


}


void GET_DATA(uint8_t type,uint8_t des){


}

void Byte_Sttuffing(uint8_t *p){
    int i;
    for(i=0 ; i<length1 ; i++){
        if(p[i] == FEND || p[i] == ESC){
            int j;
            for(j=length1 ; j>i ; j--){
                p[j] = p[j-1];
            }
            p[i] = ESC;
            ++i;
            length1++;
        }
    }
}

void zeros_arr(uint8_t arr[]){
    int i=0;
    while(i<length1){
        arr[i]=0;
        i++;
    }

}


void set_login_obc(uint8_t ty ){
  switch(ty){
    case GET_TEL_1:case GET_PACKET_2:case GET_PACKET_3:case INIT:case PING_ :
    Data_obc[p2]=ty;
    p2++;
    if(p2>19)p2=0;
    break;

    default:
    Data_obc[p2]=type_error;
    p2++;
    if(p2>19)p2=0;
 
    }
}
 void set_login_grd(uint8_t ty ){
  switch(ty){
    case GET_TEL_1:case GET_PACKET_2:case GET_PACKET_3:case INIT:case PING_ :
    Data_gnd[p3]=ty;
    p3++;
    if(p3>19)p3=0;
    break;

    default:
    Data_gnd[p3]=type_error;
    p3++;
    if(p3>19)p3=0;
    
    } 
  
  
  }








void Routing(uint8_t d){
  
  zeros_arr(ptr1);
  length1=length0-1;
  memcpy(ptr1,ptr,length0-1);
  Byte_Sttuffing(&ptr1[1]);
  ptr1[length1] = FEND;
  length1++;
  
  if(d==OBC){
    tx_SSP_buff_flag=1;}
  else if(d==GND){
     Get_SSP_Data(ptr1,length1);
     ax_25_make_I_frame();
    }
  }



  
