#include"ph.h"
#include"AX_25_LIB.h"
#include <Arduino.h>

unsigned int counter1=0;

State_ph current_Phstate=idle;
State_ph next_Phstate=idle;
ph_Event PhEvent_Triggered=No_phEvent;

void get_phevent(){
  if(1){
    uint8_t byt;
  if(mySerial.available()){  //stm32
    byt=mySerial.read();     //stm32
  if (byt==0x7e){
    counter1=0;
    received_ax_25_frame[counter1]=byt;
    counter1++;
    PhEvent_Triggered=rx_event;
    }
  }
 }
  if (tx_buffer_flag==1){
    PhEvent_Triggered=tx_event;
    }
}

void transmiting_event_handler(){
   int i=0;
   if(rej_cond==1){
        
        int j=1;
        for(;j<tx_buf_size;j++){
        memcpy(tx_frame,tx_buf[s+j],AX_25_FRAME_LEN);
        for(;i<AX_25_FRAME_LEN;i++){
        mySerial.write(tx_frame[i]); //stm32
    }
   
   }
   s+=tx_buf_size;
   }

   else{
        int i =0;
        for(;i<AX_25_FRAME_LEN;i++){
            mySerial.write(tx_frame[i]);   //stm32
           }
            }
        tx_buffer_flag=0;
        PhEvent_Triggered=No_phEvent;
        next_Phstate=idle;
        phstate_transition();


if(sr==1){
  delay(500);
 
     deframing_ssp(BACKUP);
     VR=VR+1;
    if(VR>7)VR=0;
    sr=0;
    }
  
  }



void idle_event_handler(){
      get_phevent();
    switch(PhEvent_Triggered){
      case tx_event:next_Phstate=transmiting;break;
      case rx_event:next_Phstate=receiving;break;
      default:break;
    }
      phstate_transition();
}


void receiving_event_handler(){
     uint8_t byt;
    if(mySerial.available()){  //stm32
       byt=mySerial.read();     //stm32
       received_ax_25_frame[counter1]=byt;
       counter1++;

    if(counter1==AX_25_FRAME_LEN){
       rx_buf_size++;
       r++;
       if(r==3)r=0;
       if(rx_buf_size==3){
        rx_buf_busy=1;
        }
       rx_buffer_flag=1;
       PhEvent_Triggered=No_phEvent;
       next_Phstate=idle;
       phstate_transition();
       //int i=0;
       //for(;i<AX_25_FRAME_LEN;i++)Serial.println(received_ax_25_frame[i],HEX);  //stm32
        }
    }
}


void phstate_transition(){
    current_Phstate=next_Phstate;
}
