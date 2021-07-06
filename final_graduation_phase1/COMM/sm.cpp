#include"sm.h"
#include"AX_25_LIB.h"
#include <Arduino.h>
State_dl current_state=Disconnected;
State_dl next_state=Disconnected;
SM_Event Event_Triggered=No_Event;


void Disconnected_event_handler(){
    get_dlevent();
    switch(Event_Triggered){
    case UA_Frame:
        next_state=Disconnected;
        break;
    case DM_Frame:
        next_state=Disconnected;
        break;
    case DISC_Frame:
        ax_25_make_S_U_frame(U_DM);
        next_state=Disconnected;
        break;
    case SABM_Frame:
        if(1){
            ax_25_make_S_U_frame(U_UA);
            reset_parameter();
            next_state=Connected;
        }
        else{
              ax_25_make_S_U_frame(U_DM);
              next_state=Disconnected;
        }
        break;
    
    case LocalStart:
         ax_25_make_S_U_frame(U_SABM);
         next_state=WaitingConnection;
         break;
         
    case No_Event:break;
 
    default: break;
    }
    Event_Triggered=No_Event;
    state_transition();
}

void WaitingConnection_event_handler(){
    get_dlevent();
    switch (Event_Triggered)
    {
      case UA_Frame:
          reset_parameter();
          next_state= Connected;
          break;

     case SABM_Frame:
          ax_25_make_S_U_frame(U_UA);
          reset_parameter();
          next_state=Connected;
          break;
  
      case DISC_Frame:
          ax_25_make_S_U_frame(U_DM);
          next_state=Disconnected;
          break;
  
      case DM_Frame:
          next_state=Disconnected;
  
      case No_Event: break;
  
      default:
          next_state=WaitingConnection;
          break;

    }
  Event_Triggered=No_Event;
  state_transition();
}


void WaitingRelease_event_handler(){
    get_dlevent();
    switch(Event_Triggered){

    case SABM_Frame:
        ax_25_make_S_U_frame(U_DM);
        next_state=Disconnected;
        break;

    case DISC_Frame:
        ax_25_make_S_U_frame(U_UA);
        next_state=Disconnected;
        break;

    case UA_Frame:
        next_state=Disconnected;
        break;

    case No_Event: break;

    default:
      next_state=WaitingRelease;
      break;
    }
    Event_Triggered=No_Event;
    state_transition();
}


void Connected_event_handler(){
  get_dlevent();

    switch(Event_Triggered)
    {
        case UA_Frame:
        next_state=Connected;
        break;

        case DM_Frame:
            reset_parameter();
            next_state=Disconnected;
            break;

        case DISC_Frame:
            reset_parameter();
            ax_25_make_S_U_frame(U_UA);
            next_state =Disconnected;
            break;

        case LocalEnd:
            ax_25_make_S_U_frame(U_DISC);
            next_state=WaitingRelease;
            break;

        case SABM_Frame:
            ax_25_make_S_U_frame(U_UA);
            reset_parameter();
            next_state= Connected;
            break;
            
        case RR_Frame:
            gs_busy=0;
            ack_NR(GET_NR());
            next_state= Connected;
            break;

        case RNR_Frame:
            gs_busy=1;
            ack_NR(GET_NR());
            next_state= Connected;
            break;

        case REJ_Frame:
            ack_NR(GET_NR());
            Rej_Condtion(GET_NR());
            next_state = Connected;
            break;

        case SREJ_Frame:
            ack_NR(GET_NR()-1);
            Srej_Condtion(GET_NR());
            next_state= Connected;
            break;

        case Tx_I_frame:
            ax_25_make_I_frame();
            next_state= Connected;
            break;

        case Rx_I_frame:
            ack_NR(GET_NR());
            if(rx_buf_busy==1)
             {
                 ax_25_make_S_U_frame(S_RNR);
                 next_state =Connected;
             }

            else{

             if(Get_VR()!=GET_NS()){
                    if((GET_NS()-Get_VR())>1){
                        ax_25_make_S_U_frame(S_REJ);
                        //rx_rej_cond=1;
                         next_state =Connected;
                         }
                    else{
                       /* if(rx_rej_cond==0){
                           ax_25_make_S_U_frame(S_SREJ);

                        }*/

                         ax_25_make_S_U_frame(S_SREJ);
                        next_state =Connected;
                        }




                   }
                   else{
                     
                        Extract_I_data();
                        next_state =Connected;

                   }
                }
                break;

        case No_Event:break;
        default :break;

            }
  Event_Triggered=No_Event;
  state_transition();
}

void state_transition(){
  current_state=next_state;
 }

void get_dlevent(){
  if(rx_buffer_flag==1){
    deframing();
    rx_buffer_flag=0;
    }
 }
