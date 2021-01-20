/*
 * adc.h
 *
 *  Created on: Jan 18, 2021
 *      Author: Noor
 */

#ifndef MCAL_DRIVERS_INC_ADC_H_
#define MCAL_DRIVERS_INC_ADC_H_

#include "stm32f4xx.h"

void ADC_init(void);

void ADC_startConversion(void);

uint16_t ADC_DATA(void);

#endif /* MCAL_DRIVERS_INC_ADC_H_ */
