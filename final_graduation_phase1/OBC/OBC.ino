#include "SSP_LIBRARY.h"
#include "ssp_state_machine.h"
#include "DISPLAY.h"

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX


 uint8_t t2;
uint8_t receiving=0,stuffing_flag=0;
uint8_t arrr[236];
uint8_t counter1=0;
uint8_t counter2=0;




void setup() { 
  Serial.begin(115200);
  mySerial.begin(9600);
}

void loop() {
TEST1();
/*if(Serial.available()){
  
  switch(Serial.read()){    
    case '1':
     
    local_start();break;
    case '2':
    
    Framing(PING_,COMM);break;
    case '3':
    
    Framing(GET_TEL_1,COMM);break;
    case '4':
     
    Framing(GET_PACKET_2,COMM);break;
     case '5':
    
    Framing(GET_PACKET_3,COMM);break;    
       case '6':
   
    local_end();break;     
    }
  
  
  }
*/

switch(current_state){
    case Disconnected:
        Disconnected_Events_Handler();
        break;
    case Connected:
        Connected_Events_Handler();
        break;
    case Waiting:
        Waiting_Events_Handler();
        break;
    default:break;
        }


 rx_ssp();



if(tx_SSP_buff_flag==1){
  tx_ssp();
  tx_SSP_buff_flag=0;
 
  } 





if(rx_SSP_buff_flag==1){
  
    
    deframing_ssp(arrr);
    
dis_ssp(arrr,counter1,0);
    zeroing_236(arrr);
    rx_SSP_buff_flag=0;
  
  }






















  
 

}









void tx_ssp(){
  uint8_t i=0;
  while(i<length1){
  mySerial.write(ptr1[i]); 
  i++;
  } 
  dis_ssp(ptr1,length1,1);
  
  }



void rx_ssp(){
 uint8_t byt;
  if(mySerial.available()){
    byt=mySerial.read();
    if(receiving==1){
      if(stuffing_flag==0){
        if(byt==0xab)stuffing_flag=1;
        else if(byt==0xc0){
            receiving=0;
            rx_SSP_buff_flag=1;
            }
         }
      else{stuffing_flag=0;}
      arrr[counter1]=byt;
      counter1++; 
      
   }
   
   else if (byt==0xc0) { 
    receiving=1;
    counter1=0;
    arrr[counter1]=byt;
    counter1++;
   }
    }  
  }



void local_start(){
  
  //next_state=Waiting;
 // State_Transition();
  Framing(INIT,COMM);
  
  
  }

void local_end(){
  
  //next_state=Disconnected;
 // State_Transition();
  Framing(DISREQ,COMM);
  
  
  }

void TEST1(){


  if(Serial.available()){
     
    t2=Serial.read();
    
    }
   
if(done==0 && t2=='1'){
   
    switch(t1){    
    case '1':    
    local_start();break;
    case '2':
    
    Framing(PING_,COMM);break;
    case '3':
    
    Framing(GET_TEL_1,COMM);break;
    case '4':
     
    Framing(GET_PACKET_2,COMM);break;
     case '5':
    
    Framing(GET_PACKET_3,COMM);break;    
       case '6':
   
    local_end();
    t1='1';
    t2='0';
    break;     
    }
  
  done=1;
  }

  
  
  }

    
void zeroing_236(uint8_t arr[]){
  int i=0;
  for(;i<236;i++)arr[i]=0;
  }
  
