
#include <Arduino.h>
#include "obc_interface.h"
#include"AX_25_LIB.h"

uint8_t receiving_ssp=0,stuffing_flag=0;
uint8_t obc_rx_ssp[236];
uint8_t count1=0;
uint8_t count2=0;



void rx_obc(){
 uint8_t byt;
  if(Serial1.available()){//stm32
    byt=Serial1.read();//stm32
    if(receiving_ssp==1){
        if(stuffing_flag==0){
            if(byt==0xab)stuffing_flag=1;
            else if(byt==0xc0){
            receiving_ssp=0;
            rx_SSP_buff_flag=1;
                } 
              }
         else{stuffing_flag=0;}
         obc_rx_ssp[count1]=byt;
         count1++;   
   }
   
   else if (byt==0xc0) {   
    receiving_ssp=1;
    count1=0;
    obc_rx_ssp[count1]=byt;
    count1++;  
     }
    }
  }

void tx_ssp(){
  uint8_t i=0;
  while(i<length1){
    Serial1.write(ptr1[i]);//stm32
    Serial.print(ptr1[i],HEX);//stm32
    Serial.print(" ");//stm32
  i++;
  } 
  Serial.print("\n");//stm32
  }

    
void zeroing_236(uint8_t arr[]){
  int i=0;
  for(;i<236;i++)arr[i]=0; 
}

void tx_obc(){
  if(tx_SSP_buff_flag==1){
  tx_ssp();
  tx_SSP_buff_flag=0;
  } 
  }

  
