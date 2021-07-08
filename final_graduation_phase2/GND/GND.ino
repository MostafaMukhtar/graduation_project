#include"AX_25_LIB.h"

SoftwareSerial mySerial(10,11);
 uint8_t t2;
void setup() {
  
/***BUADRATES***/  
Serial.begin(115200);
mySerial.begin(9600);

}

void loop() {

//TEST2();
//TEST3();

if(Serial.available()){
  switch(Serial.read()){
    case '1':
    Event_Triggered=LocalStart;break;
    case '2':
    local_start();break;

    case '3':
    Framing(PING_ ,COMM);break;
      case '4':
    Framing(GET_TEL_1,COMM);break;
         case '5':
    Framing(GET_PACKET_2,COMM);break;
         case '6':
    Framing(GET_PACKET_3,COMM);break;
       case '7':
    local_end();break;
    case '8':
    Event_Triggered=LocalEnd;break;




      
    case 'q':
    Event_Triggered=LocalStart;break;
    case 'w':
    local_start();break;
    case 'e':
    Framing(PING_ ,OBC);break;
      case 'r':
    Framing(GET_TEL_1,OBC);break;
         case 't':
    Framing(GET_PACKET_2,OBC);break;
         case 'y':
    Framing(GET_PACKET_3,OBC);break;
       case 'u':
    local_end();break;
    case 'i':
    Event_Triggered=LocalEnd;
    break;
    


    
    
    


    

    
    
    }
  }











  
  
/***AX_25 DATALINK STATE MACHINE***/
    switch(current_state){
    case Disconnected:
        Disconnected_event_handler();
        break;
    case Connected:
        Connected_event_handler();
        break;
    case WaitingConnection:
        WaitingConnection_event_handler();
        break;
    case WaitingRelease:
        WaitingRelease_event_handler();
        break;
    default:break;
    }
    
/***AX_25 PHYSICAL LAYER STATE MACHINE***/
    switch(current_Phstate){
        case idle:
          idle_event_handler();
          break;
        case transmiting:
          transmiting_event_handler();
          break;
        case receiving:
          receiving_event_handler();
          break;
        default:break;
         }

/***SSP STATE MACHINE***/
      switch(current_state_ssp){
          case ssp_Disconnected:
            Disconnected_Events_Handler();
            break;
          case ssp_Connected:
            Connected_Events_Handler();
            break;
          case ssp_Waiting:
            Waiting_Events_Handler();
            break;
          default:break;
        }




}






void local_start(){
  
  next_state_ssp=ssp_Waiting;
  State_Transition();
  Framing(INIT,COMM);
  
  
  }


void local_end(){
  
  next_state_ssp=ssp_Disconnected;
  State_Transition();
  Framing(DISREQ,COMM);
  
  
  }









void TEST2(){


  if(Serial.available()){
     
    t2=Serial.read();
    
    }
   
if(done==0 && t2=='1'){
  switch(t1){
    case '1':
    Event_Triggered=LocalStart;break;
    case '2':
    local_start();break;
    case '3':
    Framing(PING_ ,COMM);break;
      case '4':
    Framing(GET_TEL_1,COMM);break;
         case '5':
    Framing(GET_PACKET_2,COMM);break;
         case '6':
    Framing(GET_PACKET_3,COMM);break;
       case '7':
    local_end();break;
    case '8':
    Event_Triggered=LocalEnd;
    t1='0';
    t2='0';
    break;
    


    
    
    }
  
  done=1;
  }
  
    //t2='0';
  }

  


  
void TEST3(){


  if(Serial.available()){
     
    t2=Serial.read();
    
    }
   
if(done==0 && t2=='2'){
  switch(t1){
    case '1':
    Event_Triggered=LocalStart;break;
    case '2':
    local_start();break;
    case '3':
    
    Framing(PING_ ,OBC);break;
      case '4':
    Framing(GET_TEL_1,OBC);break;
         case '5':
    Framing(GET_PACKET_2,OBC);break;
         case '6':
    Framing(GET_PACKET_3,OBC);break;
       case '7':
    local_end();break;
    case '8':
    Event_Triggered=LocalEnd;
    t1='0';
    t2='0';
    break;
    


    
    
    }
  
  done=1;
  }
  
  
  }















  
