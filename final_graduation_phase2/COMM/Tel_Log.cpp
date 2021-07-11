#include"Tel_Log.h"
#include"TS.h"

uint8_t packet1[Telemetry_packet_len];
uint8_t packet2[Comm_obc_packet_len];
uint8_t packet3[Comm_grd_packet_len];

uint8_t *packet_telemty1(uint8_t des,uint8_t error_count_GND,uint8_t error_count_OBC)
{
     if(des == GND)packet1[0]=VN_ground;
     else  packet1[0]=VN_OBC;

     packet1[1]=100;
     packet1[2]= Telemetry_packet_Data_len;

     packet1[3]=CAL_Temp_Sen1();  //get_sensor1
     packet1[4]=CAL_Temp_Sen2();  //get_sensor2
     packet1[5]=CAL_Temp_Sen3();  //get_sensor3

     if(error_count_OBC>3 && error_count_OBC<=5) packet1[6]=12;
     else if(error_count_OBC>5) packet1[6]=13;
      else if(error_count_OBC==0) packet1[6]=14;
     else  packet1[6]=15;

     if(error_count_GND>3 && error_count_GND<=5) packet1[7]=12;
     else if(error_count_GND>5) packet1[7]=13;
      else if(error_count_GND==0) packet1[7]=14;
     else {packet1[7]=15;}

     packet1[8]= 0xff;
     return packet1;
}

uint8_t *packet_telemty2(uint8_t des , uint8_t *Data_obc)
{
    if(des == GND)packet2[0]=VN_ground;
    else  packet2[0]=VN_OBC;
    packet2[1]=101;
    packet2[2]=comm_obc_Data_len;
    int i =0;
    for(;i<20;i++){
        packet2[3+i]= Data_obc[i];
    }
    return packet2;
}


uint8_t *packet_telemty3(uint8_t des, uint8_t *Data_gnd)
{
    if(des == GND)packet3[0]=VN_ground;
    else  packet3[0]=VN_OBC;
    packet3[1]=0x07;
    packet3[2]=comm_grd_Data_len;
    int i =0;
    for(;i<20;i++){
        packet3[3+i]= Data_gnd[i];
    }
    return packet3;
}
