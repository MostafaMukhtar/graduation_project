#include "ssp_state_machine.h"
#include "SSP_LIBRARY.h"
State current_state = Connected;
State next_state = Connected;
Event event_triggered = No_Event;
uint8_t type;
uint8_t able_to_establish = 1;
uint8_t time_out = 0;




void Get_Event(uint8_t type){
    switch(type){
    case INIT:
        event_triggered = Init_Event;
        break;
    case PING_:
        event_triggered = Ping_Event;
        break;
     case GET_TEL_1:
     T=1;
     event_triggered = Get_Tel1_Event;
     break;   
     case GET_PACKET_2:
     T=1;
     event_triggered = Get_Packet2_Event;
     break;  
     case GET_PACKET_3:
     T=1;
     event_triggered = Get_Packet3_Event;
     break;   

    case DISREQ:
        event_triggered = Disconected_Event;
    default:break;
    }
}

void Disconnected_Events_Handler(){
    switch(event_triggered){
    case Init_Event:
        if (able_to_establish = 1){
            type = ACK;
            Generate_Response(type,ptr[2]);
            next_state = Connected;
            event_triggered = No_Event;
        }
        else{
            type = NACK;
            Generate_Response(type,ptr[2]);
            next_state = Disconnected;
            event_triggered = No_Event;
        }
        break;
    case Ping_Event:
        type = NACK;
        Generate_Response(type,ptr[2]);
        next_state = Disconnected;
        event_triggered = No_Event;
        break;
    case Get_Tel1_Event:
        type = NACK;
        Generate_Response(type,ptr[2]);
        next_state = Disconnected;
        event_triggered = No_Event;
        break;
    case Get_Packet2_Event:
        type = NACK;
        Generate_Response(type,ptr[2]);
        next_state = Disconnected;
        event_triggered = No_Event;
        break;
     case Get_Packet3_Event:
        type = NACK;
        Generate_Response(type,ptr[2]);
        next_state = Disconnected;
        event_triggered = No_Event;
        break;
/*
     case Disconected_Event:
        type = ACK;
        Generate_Response(type,ptr[2]);
        next_state = Disconnected;
        event_triggered = No_Event;
        break;*/
    default:break;
    }
    State_Transition();
}

void Connected_Events_Handler(){

    switch(event_triggered){
    case Init_Event:
        if(time_out == 0){
            type = ACK;
            Generate_Response(type,ptr[2]);
            next_state = Connected;
            event_triggered = No_Event;
        }
        else{
            next_state = Waiting;
        }
        break;
    case Ping_Event:
        if(time_out == 0){
            type = PING_;
            Generate_Response(type,ptr[2]);
            next_state = Connected;
            event_triggered = No_Event;
        }
        else{
            next_state = Waiting;
        }

        break;
    case Get_Tel1_Event:
        if(time_out == 0){
            type = GET_TEL_1;
            Generate_Response(type,COMM);
            next_state = Connected;
            event_triggered = No_Event;
        }
        else{
            next_state = Waiting;
        }
        break;
        
        case Get_Packet2_Event:
        if(time_out == 0){
            type = GET_PACKET_2;
            Generate_Response(type,COMM);
            next_state = Connected;
            event_triggered = No_Event;
        }
        else{
            next_state = Waiting;
        }
        break;

        case Get_Packet3_Event:
        if(time_out == 0){
            type = GET_PACKET_3;
            Generate_Response(type,COMM);
            next_state = Connected;
            event_triggered = No_Event;
        }
        else{
            next_state = Waiting;
        }
        break;




        












        
   /*
        case Disconected_Event:
        type = ACK;
        Generate_Response(type,ptr[2]);
        next_state = Disconnected;
        event_triggered = No_Event;
        break;*/
    
    default:break;
    
    
    
    }
State_Transition();
}

void Waiting_Events_Handler(){

    switch(event_triggered){
    case ACK_Event:
        next_state = Connected;
        event_triggered = No_Event;
        break;
    case NACK_Event:
        next_state = Disconnected;
        event_triggered = No_Event;
        break;    
    
    case Init_Event:
        type = ACK;
        Generate_Response(type,ptr[2]);
        next_state = Connected;
        event_triggered = No_Event;
        break;
    case Ping_Event:
        type = PING_;
        Generate_Response(type,ptr[2]);
        next_state = Connected;
        event_triggered = No_Event;
        break;


       case Disconected_Event:
        type = ACK;
        Generate_Response(type,ptr[2]);
        next_state = Disconnected;
        event_triggered = No_Event;
        break;
    default:break;
    
    }
State_Transition();
}

void State_Transition(){

    current_state=next_state;
}
