#include "SSP_LIBRARY.h"

uint8_t *ptr;
int length;
unsigned short crc;
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
        printf("\nTrue");
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

/*void PacketAnalysis(){
    switch (*(ptr+1)){
    case COMM:
        UnStuffing();
        break;
    case OBC:
        Routing();
    }
}
*/

/*void Forming_Frame ()
{
    char Frame [236];
    unsigned short CRC;
    int length_of_data = 1;
    Frame[0] = Fend;
    Frame[1] = DEST;
    Frame[2] = SRC;
    Frame[3] = Type;
    //check the length of data and according to it the length of frame determined
    Frame[4] = Data;
    CRC = Calculate_CRC(&Frame[4],lenght_of_data);
    Frame[5] = (unsigned char)CRC;
    CRC=CRC>>8;
    Frame[6]=(unsigned char)CRC;
    Frame[7] = Fend;
}*/
