#include "SSP_LIBRARY.h"

uint8_t ptr[236],ptr1[236];
uint8_t tx_SSP_buff_flag=0;
uint8_t rx_SSP_buff_flag=0;
int length0,length1;
unsigned short crc,crct;
uint8_t crc0,crc1;

void deframing_ssp (uint8_t frame[]){
    length0 = 0;
    zeros_arr(ptr);
    Search(frame);
    printf("\n");
    rx_SSP_buff_flag = 1;
    Byte_Unsttuffing(ptr);
    crc = Calculate_CRC(&ptr[1],length0-4);
    crc0 = crc;
    crc = crc>>8;
    crc1 = crc;
    //printf("\n%x\t%x",crc0,crc1);
    if (crc0 == ptr[length0-3] && crc1 == ptr[length0-2]){
       // printf("\nTrue\n");
       Generate_Action(ptr);
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
            printf("%x\t",ptr[i]);
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
        printf("%x\t",p[i]);
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
        if(p[1] == COMM){
            Generate_Response(p[3],GND);
            printf("\nCOMM");
        }
        else if(p[1] == OBC){
            //Routing();
            printf("\nOBC");
        }
    }
    else if(p[2] == OBC){
        if(p[1] == COMM){
            Generate_Response(p[3],OBC);
           // printf("\nCOMM");
        }
        else if(p[1] == GND){
            //Routing();
            printf("\nGND");
        }
    }
}

void Generate_Response(uint8_t type,uint8_t DES){
   //zeros_arr(ptr1);
    length1 = 0;
    ptr1[0] = FEND;
    ptr1[1] = DES;
    ptr1[2] = COMM;
    //Find_Type_of_Frame(type);
    length1+=4;
    GET_DATA(ptr1[3]);

    crct = Calculate_CRC(ptr1+1,length1-1);
    ptr1[length1] = crct;
    crct = crct>>8;
    ptr1[length1+1] = crct;
    length1+=2;
    printf("\n");
    int i;
     for (i=1;i<length1;i++){
        printf("%x\t",*(ptr1+i));
    }
    printf("\n");
    Byte_Sttuffing (&ptr1[1]);
    ptr1[length1] = FEND;
    length1++;
    tx_SSP_buff_flag=1;


    for (int i=0;i<length1;i++){
        printf("%x\t",ptr1[i]);
    }
    printf("\n%d",length1);
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
    int i;
    for (i=1;i<length1;i++){
        printf("%x\t",*(ptr1+i));
    }
    printf("\n");
    Byte_Sttuffing (&ptr1[1]);
    ptr1[length1] = FEND;
    length1++;
    tx_SSP_buff_flag=1;
    for (int i=0;i<length1;i++){
        printf("%x\t",ptr1[i]);
    }
    printf("\n%d\n",length1);
    tx_SSP_buff_flag=1;
}

void Find_Type_of_Frame(uint8_t type){
    switch(type){
    case GET_TEL_1:
        ptr1[3] = TEL_1_RESPONSE;
        break;
    case GET_TEL_2:
        ptr1[3] = TEL_2_RESPONSE;
        break;
    case INIT:
        ptr1[3] = ACK;
        break;
    case PING:
        ptr1[3] = PING;
        break;
    }
}

void GET_DATA(uint8_t type){
    if(type == TEL_1_RESPONSE){
        Read_Sensor1();
    }
    else if (type == TEL_2_RESPONSE){
        Read_Sensor2();
    }
    /*else if(type == INIT){

    }*/
   /*else if(type == PING){

        char arr[]="Comm_Ping";
        int i = 0;
        while(arr[i]!='\0'){
            *(ptr1+4+i) = arr[i];
            i++;
        }
    }*/
}

void Read_Sensor1(){
    ptr1[4] =  0xc0;
    length1++;
}

void Read_Sensor2(){
    ptr1[4] =  0xab;
    length1++;
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

void test_(){
    Generate_Response(INIT,OBC);
    zeros_arr(ptr1);
    Generate_Response(PING,OBC);
    zeros_arr(ptr1);
    Generate_Response(INIT,OBC);
    zeros_arr(ptr1);
}
