/*
 * adc.c
 *
 *  Created on: Dec 31, 2020
 *      Author: kholoud
 */

#include "adc.h"



RCC_TypeDef *clock;
ADC_Common_TypeDef *adc_comm;
ADC_TypeDef *adc;
GPIO_TypeDef *gpio;

void ADC_init(void)
{
	clock=RCC;
	adc=ADC3;

	//enable the ADC and port (ApB2)
	clock->APB2ENR |= RCC_APB2ENR_ADC3EN;  //bit 8 is for ADC3EN (1<<8)

	//ADC prescaler (divided by 4 )(1<<16)
	SET_BIT(adc_comm->CCR,ADC_CCR_ADCPRE_0);
	CLEAR_BIT(adc_comm->CCR,ADC_CCR_ADCPRE_1);

	//clock mode
	//Enable ADC /*we need to know the voltage*/
	adc->CR2 |= ADC_CR2_ADON; //ADON BIT(1<<1)

	//RESOLUTION 10 bit
	adc->CR1 |= ADC_CR1_RES_0;//(1<<24)
	adc->CR1 &= ~(ADC_CR1_RES_1);


	//single conversion mode
	adc->CR2 &= ~(ADC_CR2_CONT); //CONT bit (1<<1)

	//select sample time
	//adc->SMPR1 |= ((1<<0) |(1<<1)); //56 cycle
	SET_BIT(adc->SMPR1,ADC_SMPR1_SMP10_0);
	SET_BIT(adc->SMPR1,ADC_SMPR1_SMP10_1);
	CLEAR_BIT(adc->SMPR1,ADC_SMPR1_SMP10_2);


}


void ADC_startConversion(void)
{
	//start conversion
	adc->CR2 |= ADC_CR2_SWSTART; //SWST
	//wait until end of conversion
	while(BIT_IS_CLEAR(adc->SR,ADC_SR_EOC));
}

uint16_t ADC_DATA(void){
	//get data
	uint16_t data;
	data = adc->DR;
	return data;
}
