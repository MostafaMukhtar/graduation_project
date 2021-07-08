#ifndef OBC_INTERFACE_H_INCLUDED
#define OBC_INTERFACE_H_INCLUDED




extern uint8_t receiving_ssp,stuffing_flag;
extern uint8_t obc_rx_ssp[236];
extern uint8_t count1;
extern uint8_t count2;


 /*function name: rx_obc
 *function arguments: void
 *function return void
 *function description: receiving obc frame from uart 2
 * */
void rx_obc(void);

/*function name: tx_obc
 *function arguments: void
 *function return void
 *function description: transmitting obc frame from uart 2
 * */
void tx_obc(void);

/*function name: tx_ssp
 *function arguments: void
 *function return void
 *function description: display transmitted ssp frame
 * */
void tx_ssp(void);

/*function name: zeroing_236
 *function arguments: void
 *function return void
 *function description: zeroing array of 236 element
 * */
void zeroing_236(uint8_t arr[]);









#endif // OBC_INTERFACE_H_INCLUDED
