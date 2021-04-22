#ifndef SSP_STATE_MACHINE_H_INCLUDED
#define SSP_STATE_MACHINE_H_INCLUDED
#include "SSP_LIBRARY.h"

enum events get_event();
void state_transition(enum states nstate);
void event_handler_disconnected(enum events e);
void event_handler_connected(enum events e);
void event_handler_waiting(enum events e);
void Generate_Action(uint8_t ptr[]);
#endif // SSP_STATE_MACHINE_H_INCLUDED
