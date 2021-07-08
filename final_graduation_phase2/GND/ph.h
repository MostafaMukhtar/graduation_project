#ifndef PH_H_INCLUDED
#define PH_H_INCLUDED
#include <Arduino.h>
#include <SoftwareSerial.h> //stm32

/**physical layer states**/
typedef enum
{
  idle,
  transmiting,
  receiving,

}State_ph;
/**physical layer events**/
typedef enum
{
  tx_event,
  rx_event,
  No_phEvent,
}ph_Event;

/***state machine parameters***/
extern State_ph next_Phstate;
extern State_ph current_Phstate;
extern ph_Event PhEvent_Triggered;
extern SoftwareSerial mySerial;//stm32
 
 /*********************************************/

/*function name: idle_event_handler
 *function arguments: void
 *function return void
 *function description: used to handle triggerd event in idle state
 * */
void idle_event_handler(void);

/*function name: transmiting_event_handler
 *function arguments: void
 *function return void
 *function description: used to handle triggerd event in transmiting state
 * */
void transmiting_event_handler(void);

/*function name: receiving_event_handler
 *function arguments: void
 *function return void
 *function description: used to handle triggerd event in receiving state
 * */
void receiving_event_handler(void);

/*function name: phstate_transition
 *function arguments: void
 *function return void
 *function description: used to transfer between the next state and current state
 * */
void phstate_transition(void);

/*function name: get_phevent
 *function arguments: void
 *function return void
 *function description:used to return a triggered event  
 * */
void get_phevent(void);


#endif // PH_H_INCLUDED
