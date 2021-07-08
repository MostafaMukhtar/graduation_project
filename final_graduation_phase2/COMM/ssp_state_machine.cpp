#include "ssp_state_machine.h"
#include "SSP_LIBRARY.h"
#include "obc_interface.h"
#include <Arduino.h>
State current_state_ssp = ssp_Disconnected;
State next_state_ssp = ssp_Disconnected;
Event event_triggered_ssp = ssp_No_Event;
uint8_t type;
uint8_t able_to_establish = 1;
uint8_t time_out = 0;

void Get_Event(uint8_t type){
    switch(type){
    case INIT:
        event_triggered_ssp= Init_Event;
        break;
    case PING_:
        event_triggered_ssp = Ping_Event;
        break;
    case GET_TEL_1:
        event_triggered_ssp = Get_Tel1_Event;
        break;
    case GET_PACKET_2:
        event_triggered_ssp = Get_Packet2_Event;
        break;
    case GET_PACKET_3:
        event_triggered_ssp = Get_Packet3_Event;
        break;   
    case DISREQ:
        event_triggered_ssp = Disconected_Event;
    default:
    
    break;
    }
}

void Disconnected_Events_Handler(){
  get_obc_event();
    switch(event_triggered_ssp){
    case Init_Event:
    
        if (able_to_establish = 1){
            type = ACK;
            Generate_Response(type,ptr[2]);
            next_state_ssp = ssp_Connected;
            event_triggered_ssp = ssp_No_Event;
        }
        else{
            type = NACK;
            Generate_Response(type,ptr[2]);
            next_state_ssp = ssp_Disconnected;
            event_triggered_ssp = ssp_No_Event;
        }
        break;
    case Ping_Event:
        type = NACK;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Disconnected;
        event_triggered_ssp = ssp_No_Event;
        break;
    case Get_Tel1_Event:
        type = NACK;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Disconnected;
        event_triggered_ssp = ssp_No_Event;
        break;
    case Get_Packet2_Event:
        type = NACK;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Disconnected;
        event_triggered_ssp = ssp_No_Event;
        break;
        case Get_Packet3_Event:
        type = NACK;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Disconnected;
        event_triggered_ssp = ssp_No_Event;
        break;
     case Disconected_Event:
        type = ACK;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Disconnected;
        event_triggered_ssp = ssp_No_Event;
        break;
    default:break;
    }
    State_Transition();
}

void Connected_Events_Handler(){
get_obc_event();
    switch(event_triggered_ssp){
    case Init_Event:
        if(time_out == 0){
            type = ACK;
            Generate_Response(type,ptr[2]);
            next_state_ssp = ssp_Connected;
            event_triggered_ssp = ssp_No_Event;
        }
        else{
            next_state_ssp = ssp_Waiting;
        }
        break;
    case Ping_Event:
        if(time_out == 0){
            type = PING_;
            Generate_Response(type,ptr[2]);
            next_state_ssp = ssp_Connected;
            event_triggered_ssp = ssp_No_Event;
        }
        else{
            next_state_ssp = ssp_Waiting;
        }

        break;
    case Get_Tel1_Event:
        if(time_out == 0){
            type = TEL_1_RESPONSE;
            Generate_Response(type,ptr[2]);
            next_state_ssp = ssp_Connected;
            event_triggered_ssp = ssp_No_Event;
        }
        else{
            next_state_ssp = ssp_Waiting;
        }
        break;
    case Get_Packet2_Event:
        if(time_out == 0){
            type = PACKET_2_RESPONSE;
            Generate_Response(type,ptr[2]);
            next_state_ssp = ssp_Connected;
            event_triggered_ssp = ssp_No_Event;
        }
        else{
            next_state_ssp = ssp_Waiting;
        }
        break;


        case Get_Packet3_Event:
        if(time_out == 0){
          
            type = PACKET_3_RESPONSE;
            Generate_Response(type,ptr[2]);
            next_state_ssp = ssp_Connected;
            event_triggered_ssp = ssp_No_Event;
        }
        else{
            next_state_ssp = ssp_Waiting;
        }
        break;
        

        
        case Disconected_Event:
        type = ACK;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Disconnected;
        event_triggered_ssp = ssp_No_Event ;
        break;
    
    default:break;
    
    
    
    }
State_Transition();
}

void Waiting_Events_Handler(){
get_obc_event();
    switch(event_triggered_ssp){
    case Init_Event:
        type = ACK;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Connected;
        event_triggered_ssp = ssp_No_Event;
        break;
    case Ping_Event:
        type = PING_;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Connected;
        event_triggered_ssp = ssp_No_Event;
        break;
    case Get_Tel1_Event:
        type = TEL_1_RESPONSE;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Connected;
        event_triggered_ssp = ssp_No_Event;
        break;
     case Get_Packet2_Event:
        type = PACKET_2_RESPONSE;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Connected;
        event_triggered_ssp = ssp_No_Event;
        break;

         case Get_Packet3_Event:
        type =PACKET_3_RESPONSE;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Connected;
        event_triggered_ssp = ssp_No_Event;
        break;
       case Disconected_Event:
        type = ACK;
        Generate_Response(type,ptr[2]);
        next_state_ssp = ssp_Disconnected;
        event_triggered_ssp = ssp_No_Event;
        break;
    default:break;
    
    }
State_Transition();
}

void State_Transition(){

    current_state_ssp=next_state_ssp;
}




  void get_obc_event(){
    
  if(rx_SSP_buff_flag==1){
 


    
  Serial.print("RX:\n");//stm32
  deframing_ssp(obc_rx_ssp);
   int j=0;
  for(;j<count1;j++){
    Serial.print(obc_rx_ssp[j],HEX);//stm32
    Serial.print(" ");//stm32
   
    }
    Serial.print("\n");//stm32
     Serial.print("-----------------------------------------");//stm32
     Serial.print("\n");//stm32
  zeroing_236(obc_rx_ssp);
 
  rx_SSP_buff_flag=0;
  
  }
 
  } 
    
    
    
    
