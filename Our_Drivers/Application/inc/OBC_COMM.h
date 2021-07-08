
/*
 * OBC_COMM.h
 *
 *  Created on: Apr 4, 2021
 *      Author: Nour
*/

#ifndef APPLICATION_INC_OBC_COMM_H_
#define APPLICATION_INC_OBC_COMM_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "our_stm32f407xx.h"
#include "main.h"

extern USART_Handle_t usart2_handle;


void Uart2Config ();
void UART2_SendChar (uint8_t c);
void UART2_SendString (char *string);
uint8_t UART2_GetChar (void);
void USART_IRQRecieveHandling(USART_Handle_t *pUSARTHandle);


#endif  APPLICATION_INC_OBC_COMM_H_

