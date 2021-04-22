#include"sm.h"
#include"ax_25.h"
State_dl current_state=Disconnected;
State_dl next_state=Disconnected;


void Disconnected_event_handler(SM_Event e){
switch(e){

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

default:
        ax_25_make_S_U_frame(U_DM);
        next_state=Disconnected;
    break;

}
}



void WaitingConnection_event_handler(SM_Event e){

    switch (e)
    {
    case UA_Frame:
        reset_parameter();
        next_state= Connected;
        break;

    case SABM_Frame:
        ax_25_make_S_U_frame(U_UA);
        next_state=WaitingConnection;
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
}



void WaitingRelease_event_handler(SM_Event e){

    switch(e){

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
}


void Connected_event_handler(SM_Event e){

    switch(e)
    {
        case UA_Frame:
        next_state=Connected;
        break;

        case DM_Frame:
            ClearWindow();
            next_state=Disconnected;
            break;

        case DISC_Frame:
            ClearWindow();
            ax_25_make_S_U_frame(U_UA);
            next_state =Disconnected;
            break;

        case LocalEnd:
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

           if(rej_cond==0){
                SetRejectVariable();
                ack_NR(GET_NR());
           }

           Rej_Condtion();
           next_state = Connected;
           break;

        case SREJ_Frame:
              ack_NR(GET_NR());
              Srej_Condtion(GET_NR());
              next_state= Connected;

           break;

        case Tx_I_frame:
            ax_25_make_I_frame();
            next_state= Connected;
            break;
    }


















}





void state_transition(){
current_state=next_state;
printf("%d",current_state);
}








