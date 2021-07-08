#ifndef SM_H_INCLUDED
#define SM_H_INCLUDED

/***DATA LINK STATES***/
typedef enum
{
Disconnected,
Connected,
WaitingConnection,
WaitingRelease,

}State_dl;

/***DATA LINK EVENTS***/
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
TEST_Frame,
}SM_Event;

/***DATA LINK STATE MACHINE PARAMETERS***/
extern State_dl next_state;
extern State_dl current_state;
extern SM_Event Event_Triggered;
/**************************************************************/


/*function name: Disconnected_event_handler
 *function arguments: void
 *function return void
 *function description: handling events in disconnected state 
 * */
void Disconnected_event_handler(void);


/*function name: Connected_event_handler
 *function arguments: void
 *function return void
 *function description: handling events in connected state 
 * */
void Connected_event_handler(void);

/*function name: WaitingConnection_event_handler
 *function arguments: void
 *function return void
 *function description: handling events in WaitingConnection state 
 * */
void WaitingConnection_event_handler(void);

/*function name: WaitingRelease_event_handler
 *function arguments: void
 *function return void
 *function description: handling events in WaitingRelease state 
 * */
void WaitingRelease_event_handler(void);

/*function name: state_transition
 *function arguments: void
 *function return void
 *function description: used to transfer between the next state and current state
 * */
void state_transition(void);

/*function name: get_dlevent
 *function arguments: void
 *function return void
 *function description: used to return a triggered event 
 * */
void get_dlevent(void);


#endif // SM_H_INCLUDED
