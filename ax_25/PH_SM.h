#ifndef PH_SM_H_INCLUDED
#define PH_SM_H_INCLUDED


typedef enum
{

PH_Transmitting,
PH_Receiving,
PH_Idle,
}PH_State;

typedef enum
{
TX_PH_Event,
RX_PH_Event,
Idle_event,

}PH_Event;


PH_State_Transition();
PH_Event Get_PH_Evnet();
void Transmitting_Event_handler();
void Receving_Event_handler();
void Idle_Event_handler();









#endif // PH_SM_H_INCLUDED
