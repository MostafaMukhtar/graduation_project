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
case No_Event:break;

default:
        ax_25_make_S_U_frame(U_DM);
        next_state=Disconnected;
    break;

}
}

void state_transition(){
current_state=next_state;
printf("%d",current_state);
}








