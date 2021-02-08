/*
 * lm75.h
 *
 *  Created on: Feb 6, 2021
 *      Author: khlod
 */

#ifndef HAL_DRIVERS_INC_LM75_H_
#define HAL_DRIVERS_INC_LM75_H_



#endif /* HAL_DRIVERS_INC_LM75_H_ */

/* LM75 defines */
#define LM75_ADDR                     0x90 // LM75 address

/* LM75 registers */
#define LM75_REG_TEMP                 0x00 // Temperature
#define LM75_REG_CONF                 0x01 // Configuration
#define LM75_REG_THYS                 0x02 // Hysteresis
#define LM75_REG_TOS                  0x03 // Overtemperature shutdown


uint8_t LM75_Init(uint32_t SPI_Clock_Speed);

void LM75_WriteReg(uint8_t reg, uint16_t value);
uint16_t LM75_ReadReg(uint8_t reg);
uint8_t LM75_ReadConf(void);
void LM75_WriteConf(uint8_t value);

void LM75_Shutdown(FunctionalState newstate);
int16_t LM75_Temperature(void);
