#ifndef SSP_STATE_MACHINE_H_INCLUDED
#define SSP_STATE_MACHINE_H_INCLUDED
#include "SSP_LIBRARY.h"
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include <string.h>

/**ssp states**/
typedef enum {
    Disconnected,
    Connected,
    Waiting,
}State;
/**ssp events**/
typedef enum {
    Init_Event,
    Ping_Event,
    Get_Tel1_Event,
    Get_Packet2_Event,
    Get_Packet3_Event,
    Disconected_Event,
    ACK_Event,
    NACK_Event,
    No_Event,
}Event;
/**ssp state machine parameters**/
extern State current_state;
extern Event event_triggered;
extern State next_state;



/*function name: Disconnected_Events_Handler
 *function arguments: void
 *function return void
 *function description: handling triggered event in disconnected state
 * */
void Disconnected_Events_Handler();

/*function name: Connected_Events_Handler
 *function arguments: void
 *function return void
 *function description: handling triggered event in Connected state
 * */
void Connected_Events_Handler();

/*function name: Waiting_Events_Handler
 *function arguments: void
 *function return void
 *function description: handling triggered event in Waiting state
 * */
void Waiting_Events_Handler();

/*function name: State_Transition
 *function arguments: void
 *function return void
 *function description: transfer between next state and current state
 * */
void State_Transition();

/*function name: Get_Event
 *function arguments: uint8_t type
 *function return void
 *function description: returning the triggerd ssp event 
 * */
void Get_Event(uint8_t type);
#endif // SSP_STATE_MACHINE_H_INCLUDED
