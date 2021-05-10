#include "PH_SM.h"
#include "ax_25.h"


PH_Event PH_Event_Trig= Idle_event;
PH_State PH_Current_State =PH_Idle;
PH_State PH_Next_State = PH_Idle;



PH_Event Get_PH_Evnet()
{
    if (tx_buff_flag==1)    {return TX_PH_Event;}

    else if (rx_buff_flag==1)   {return RX_PH_Event;}

    else return Idle_event;

}

void Transmitting_Event_handler()
{



    PH_Next_State = PH_Idle;
    PH_State_Transition();
}
void Receving_Event_handler()
{






    PH_Next_State = PH_Idle;
    PH_State_Transition();
}

void Idle_Event_handler()
{
    PH_Event_Trig=Get_PH_Evnet;

    Switch (PH_Event_Trig){

    case TX_PH_Event:
        PH_Next_State = PH_Transmitting;
        break;

    case RX_PH_Event:
        PH_Next_State = PH_Receiving;
        break;

    case Idle_event:
        break;
    default: break;

    }


    PH_State_Transition();
}

void PH_State_Transition()
{
    PH_Current_State=PH_Next_State;
}








