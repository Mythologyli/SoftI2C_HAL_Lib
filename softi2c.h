/**
 * @file    softi2c.h
 * @author  Myth
 * @version 0.1
 * @date    2021.10.12
 * @brief   STM32 SoftI2C Library
 */

#ifndef __SOFTI2C_H
#define __SOFTI2C_H

#include "softi2c_conf.h"

/**
  * @brief  SoftI2C Configuration Structure definition
  */
typedef struct
{
    GPIO_TypeDef *SDA_GPIO;
    uint32_t SDA_Pin;

    GPIO_TypeDef *SCL_GPIO;
    uint32_t SCL_Pin;

    uint32_t Delay_Time;
} SoftI2C_TypeDef;

HAL_StatusTypeDef SoftI2C_Init(SoftI2C_TypeDef *SoftI2Cx);

void SoftI2C_Start(SoftI2C_TypeDef *SoftI2Cx);
void SoftI2C_Stop(SoftI2C_TypeDef *SoftI2Cx);
void SoftI2C_WriteByte(SoftI2C_TypeDef *SoftI2Cx, uint8_t byte);
uint8_t SoftI2C_ReadByte(SoftI2C_TypeDef *SoftI2Cx);
void SoftI2C_Ack(SoftI2C_TypeDef *SoftI2Cx);
void SoftI2C_NAck(SoftI2C_TypeDef *SoftI2Cx);
uint8_t SoftI2C_WaitAck(SoftI2C_TypeDef *SoftI2Cx);

#endif
