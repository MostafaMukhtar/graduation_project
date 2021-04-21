#ifndef SM_H_INCLUDED
#define SM_H_INCLUDED
typedef enum
{
Disconnected,
Connected,
WaitingConnection,
WaitingRelease,

}State_dl;

typedef enum
{
UA_Frame,
DM_Frame,
DISC_Frame,
SABM_Frame,
RR_Frame,
RNR_Frame,
SREJ_Frame,
REJ_Frame,
Rx_I_frame,
Tx_I_frame,
No_Event,
LocalStart,
LocalEnd,
}SM_Event;

extern State_dl next_state;
extern State_dl current_state;


void Disconnected_event_handler(SM_Event e);
void Connected_event_handler(SM_Event e);
void WaitingConnection_event_handler(SM_Event e);
void WaitingRelease_event_handler(SM_Event e);
void state_transition();


#endif // SM_H_INCLUDED
