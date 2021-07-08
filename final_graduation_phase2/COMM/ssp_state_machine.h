#ifndef SSP_STATE_MACHINE_H_INCLUDED
#define SSP_STATE_MACHINE_H_INCLUDED
#include "SSP_LIBRARY.h"
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include <string.h>

/**ssp states**/
typedef enum {
    ssp_Disconnected,
    ssp_Connected,
    ssp_Waiting,
}State;
/**ssp events**/
typedef enum {  
    Init_Event,
    Ping_Event,
    Get_Tel1_Event,
    Get_Packet2_Event,
    Get_Packet3_Event,
    Disconected_Event,
    ssp_No_Event,
}Event;

/**ssp state machine parameters**/
extern State current_state_ssp;
extern Event event_triggered_ssp;

/*function name: Disconnected_Events_Handler
 *function arguments: void
 *function return void
 *function description: handling triggered event in disconnected state
 * */
void Disconnected_Events_Handler(void);

/*function name: Connected_Events_Handler
 *function arguments: void
 *function return void
 *function description: handling triggered event in Connected state
 * */
void Connected_Events_Handler(void);

/*function name: Waiting_Events_Handler
 *function arguments: void
 *function return void
 *function description: handling triggered event in Waiting state
 * */
void Waiting_Events_Handler(void);

/*function name: State_Transition
 *function arguments: void
 *function return void
 *function description: transfer between next state and current state
 * */
void State_Transition(void);

/*function name: Get_Event
 *function arguments: uint8_t type
 *function return void
 *function description: returning the triggerd ssp event 
 * */
void Get_Event(uint8_t type);

/*function name: get_obc_event
 *function arguments: void
 *function return void
 *function description: get event from ssp obc frame
 * */
void get_obc_event(void);

#endif // SSP_STATE_MACHINE_H_INCLUDED
