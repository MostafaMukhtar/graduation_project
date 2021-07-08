
#include"AX_25_LIB.h"
#include"TS.h"

SoftwareSerial mySerial(10,11);

void setup() {
  
/***BUADRATES***/  
Serial.begin(9600);
Serial1.begin(9600);
mySerial.begin(9600);

}

void loop() {


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



/***OBC INTERFACE***/
rx_obc();
tx_obc();

}

































  
