#include "ssp_state_machine.h"

uint8_t can_connect = 1;
uint8_t time_out = 0;
uint8_t disconnected_flag = 1;
    enum states
{
    disconnected,
    connected,
    waiating
}state,next_state;

enum events
{
    init_event,
    ping_event,
    get_tel1_event,
    get_tel2_event,
    no_event
}event;

enum events get_event(uint8_t ptr[])
{
    if (ptr[3] == INIT)
        return init_event;
    else if (ptr[3] == PING)
        return ping_event;
    else if (ptr[3] == GET_TEL_1)
        return get_tel1_event;
    else if (ptr[3] == GET_TEL_2)
        return get_tel2_event;
}

/*void state_transition(enum states nstate){
    state = nstate;
}*/

void event_handler_disconnected(enum events e){
    switch (e){
    case init_event:
        if (can_connect == 1){
            ptr1[3] = ACK;
            disconnected_flag = 0;
            next_state = connected;
        }
        else {
            ptr1[3] = NACK;
            next_state = disconnected;
        }
        break;
    case ping_event:
        ptr1[3] = NACK;
        next_state = disconnected;
        break;
    case get_tel1_event:
        ptr1[3] = NACK;
        next_state = disconnected;
        break;
    case get_tel2_event:
        ptr1[3] = NACK;
        next_state = disconnected;
        break;
    }
}

void event_handler_connected(enum events e){
    switch (e){
    case init_event:
        if (time_out == 0){
            ptr1[3] = ACK;
            next_state = connected;
        }
        else {
            next_state = waiating;
        }
        break;
    case ping_event:
        if (time_out == 0){
            ptr1[3] = PING;
            next_state = connected;
        }
        else {
            next_state = waiating;
        }
        break;
    case get_tel1_event:
        if (time_out == 0){
            ptr1[3] = TEL_1_RESPONSE;
            next_state = connected;
        }
        else {
            next_state = waiating;
        }
        break;
    case get_tel2_event:
        if (time_out == 0){
            ptr1[3] = TEL_2_RESPONSE;
            next_state = connected;
        }
        else {
            next_state = waiating;
        }
        break;
    }
}

void event_handler_waiting(enum events e){
    switch (e){
    case init_event:
            ptr1[3] = ACK;
            next_state = connected;
        break;
    case ping_event:
            ptr1[3] = PING;
            next_state = connected;
        break;
    case get_tel1_event:
            ptr1[3] = TEL_1_RESPONSE;
            next_state = connected;
        break;
    case get_tel2_event:
            ptr1[3] = TEL_2_RESPONSE;
            next_state = connected;
        break;
    }
}

void Generate_Action(uint8_t ptr[]){
    zeros_arr(ptr1);
    event = get_event(ptr);
    if (disconnected_flag == 1){
        event_handler_disconnected(event);
        //tate_transition(next_state);
        state = next_state;
        printf("\ndisconnected\n");
    }
    else {
        if(state == connected){
            event_handler_connected(event);
            //state_transition(next_state);
            state = next_state;
            printf("\nconnected\n");
        }
        else if(state == waiating){
            event_handler_waiting(event);
            //state_transition(next_state);
            state = next_state;
            printf("\nwaiating\n");
        }
    }
}
