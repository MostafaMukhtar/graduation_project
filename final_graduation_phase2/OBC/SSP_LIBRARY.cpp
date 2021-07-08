#include "SSP_LIBRARY.h"
#include "ssp_state_machine.h"
#include <Arduino.h>
uint8_t ptr[236],ptr1[236];
uint8_t tx_SSP_buff_flag=0;
uint8_t rx_SSP_buff_flag=0;
int length0,length1;
unsigned short crc,crct;
uint8_t crc0,crc1;
uint8_t tel1[10];
uint8_t tel2[23];
uint8_t tel3[23];
void deframing_ssp (uint8_t frame[]){
    length0 = 0;
    zeros_arr(ptr);
    Search(frame);
    //printf("\n");
    //rx_SSP_buff_flag = 1;
    Byte_Unsttuffing(ptr);
    crc = Calculate_CRC(&ptr[1],length0-4);
    crc0 = crc;
    crc = crc>>8;
    crc1 = crc;
    //printf("\n%x\t%x",crc0,crc1);
    if (crc0 == ptr[length0-3] && crc1 == ptr[length0-2]){
       // printf("\nTrue\n");
       Packet_Analysis(ptr);

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
            //printf("%x\t",ptr[i]);
        }
    }

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
        //printf("%x\t",p[i]);
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



    if(p[2] == GND){
        if(p[1] == OBC){
            Get_Event(p[3]);
            
        }

    }
    else if(p[2] == COMM){
        if(p[1] == OBC){
          
          switch(p[3]){
            
            case TEL_1_RESPONSE:
           
           memcpy(tel1,&p[4],10);
            Generate_Response(TEL_1_RESPONSE,GND);
             
             
            break;
            case PACKET_2_RESPONSE:
            memcpy(tel2,&p[4],23);
            Generate_Response(PACKET_2_RESPONSE,GND);
            
            break;
            case PACKET_3_RESPONSE:
           memcpy(tel3,&p[4],23);
            Generate_Response(PACKET_3_RESPONSE,GND);
            
            break;
            
            
            
            
            
            
            
            
            
            } 
       


            
         
        }

    }
}

void Generate_Response(uint8_t type,uint8_t DES){

    zeros_arr(ptr1);
    length1 = 0;
    ptr1[0] = FEND;
    ptr1[1] = DES;
    ptr1[2] = OBC;
    //Find_Type_of_Frame(type);
    ptr1[3] = type;
    length1+=4;
    GET_DATA(ptr1[3]);
    crct = Calculate_CRC(ptr1+1,length1-1);
    ptr1[length1] = crct;
    crct = crct>>8;
    ptr1[length1+1] = crct;
    length1+=2;
    Byte_Sttuffing (&ptr1[1]);
    ptr1[length1] = FEND;
    length1++;
    tx_SSP_buff_flag=1;

}

void Framing(uint8_t type,uint8_t DES){

    zeros_arr(ptr1);
    length1 = 0;
    ptr1[0] = FEND;
    ptr1[1] = DES;
    ptr1[2] = OBC;
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
    tx_SSP_buff_flag=1;
}


void GET_DATA(uint8_t type){
 if(type == TEL_1_RESPONSE){
    
        uint8_t i=0;
        for(;i<10;i++){
            ptr1[length1+i]=tel1[i];
            }
        length1+=10;

        
    }
    else if (type == PACKET_2_RESPONSE){
       
        uint8_t i=0;
        for(;i<23;i++){
            ptr1[length1+i]=tel2[i];
          }
        length1+=23;
      
    }
    else if (type == PACKET_3_RESPONSE){     
        
        uint8_t i=0;
        for(;i<23;i++){
          ptr1[length1+i]=tel3[i];
          
          }
        length1+=23;

        }

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
