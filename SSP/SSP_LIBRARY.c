#include "SSP_LIBRARY.h"

uint8_t *ptr,*ptr1;
int length,length1;
unsigned short crc,crct;
uint8_t crc0,crc1;

void deframing (uint8_t frame[]){
    Search(frame);
    printf("\n");
    Byte_Unsttuffing(ptr);
    crc = Calculate_CRC(ptr+1,length-4);
    crc0 = crc;
    crc = crc>>8;
    crc1 = crc;
    printf("\n%x\t%x",crc0,crc1);
    if (crc0 == *(ptr+length-3) && crc1 == *(ptr+length-2)){
        printf("\nTrue\n");
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
        length = index+1;
        ptr = (uint8_t *)malloc((length)*sizeof(uint8_t));          //putting SSP frame in dynamic array
        for(int i=0 ; i<length ; i++){
            *(ptr+i) = frame[i];
            printf("%x\t",*(ptr+i));
        }
    }
}

void Byte_Unsttuffing (uint8_t *p){
    for(int i=0 ; i<length ; i++){
        if(*(p+i)==ESC){
            for(int j=i ; j<length-1 ; j++){
                *(p+j) = *(p+j+1);
            }
            length--;
        }
        printf("%x\t",*(p+i));
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
    if(*(p+2) == GND){
        if(*(p+1) == COMM){
            Generate_Response(*(p+3),GND);
            printf("\nCOMM");
        }
        else if(*(p+1) == OBC){
            //Routing();
            printf("\nOBC");
        }
    }
    else if(*(p+2) == OBC){
        if(*(p+1) == COMM){
            Generate_Response(*(p+3),OBC);
            printf("\nCOMM");
        }
        else if(*(p+1) == GND){
            //Routing();
            printf("\nGND");
        }
    }
}

void Generate_Response(uint8_t type,uint8_t DES){
    ptr1 = (uint8_t *)malloc((236)*sizeof(uint8_t));
    //length1 = Find_Length_of_Frame(type);
    *(ptr1) = FEND;
    *(ptr1+1) = DES;
    *(ptr1+2) = COMM;
    *(ptr1+3) = Find_Type_of_Frame(type);
    GET_DATA(type,3);
    length1+=4;
    crct = Calculate_CRC(ptr1+1,length1-1);
    *(ptr1+length1) = crct;
    crct = crct>>8;
    *(ptr1+length1+1) = crct;
    length1+=2;
     for (int i=1;i<length1;i++){
        printf("%x\t",*(ptr1+i));
    }
    printf("\n");
    Byte_Sttuffing (ptr1+1);
    *(ptr1+length1) = FEND;
    length1++;
    for (int i=0;i<length1;i++){
        printf("%x\t",*(ptr1+i));
    }
}

uint8_t Find_Type_of_Frame(uint8_t type){
    uint8_t t;
    switch(type){
    case GET_TEL_1:
        t = TEL_1_Reading;
        break;
    case GET_TEL_2:
        t = TEL_2_Reading;
        break;
    case INIT:
        t = ACK;
        break;
    case PING:
        t = Comm_Ping;
        break;
    }
    return t;
}

void GET_DATA(uint8_t type,uint8_t len){
    if(type == GET_TEL_1)
        Read_Sensor1(len);
    else if (type == GET_TEL_2)
        Read_Sensor2(len);
    else if(type == INIT)
        length1 = 0;
    else if(type == PING){
        char arr[]="Comm_Ping";
        int i = 0;
        while(arr[i]!='\0'){
            *(ptr1+4+i) = arr[i];
            i++;
        }
        length1 = 9;
    }
}

void Read_Sensor1(int len){
    for(int i=0 ; i<len ; i++){
        *(ptr1+i+4) =  0xc0;  //call function that read from first sensor
    }
    length1 = len;
}

void Read_Sensor2(int len){
    for(int i=0 ; i<len ; i++){
        *(ptr1+i+4) =  0xab;  //call function that read from second sensor
    }
    length1 = len;
}

void Byte_Sttuffing(uint8_t *p){
    for(int i=0 ; i<length1 ; i++){
        if(*(p+i) == FEND || *(p+i) == ESC){
            for(int j=length1 ; j>i ; j--){
                *(p+j) = *(p+j-1);
            }
            *(p+i) = ESC;
            ++i;
            length1++;
        }
    }
}

