/**
 * @file    softi2c.c
 * @author  Myth
 * @version 0.1
 * @date    2021.10.12
 * @brief   STM32 SoftI2C Library
 */

#include "softi2c.h"

#define SDA_Mode_In SoftI2C_SDA_Mode_In(SoftI2Cx)
#define SDA_Mode_Out SoftI2C_SDA_Mode_Out(SoftI2Cx)

#define SDA_Set HAL_GPIO_WritePin(SoftI2Cx->SDA_GPIO, SoftI2Cx->SDA_Pin, GPIO_PIN_SET)
#define SDA_Clr HAL_GPIO_WritePin(SoftI2Cx->SDA_GPIO, SoftI2Cx->SDA_Pin, GPIO_PIN_RESET)

#define SDA_Read HAL_GPIO_ReadPin(SoftI2Cx->SDA_GPIO, SoftI2Cx->SDA_Pin)

#define SCL_Set HAL_GPIO_WritePin(SoftI2Cx->SCL_GPIO, SoftI2Cx->SCL_Pin, GPIO_PIN_SET)
#define SCL_Clr HAL_GPIO_WritePin(SoftI2Cx->SCL_GPIO, SoftI2Cx->SCL_Pin, GPIO_PIN_RESET)

#define Delay SoftI2C_Delay_us(SoftI2Cx->Delay_Time)
#define Delay_Double SoftI2C_Delay_us(SoftI2Cx->Delay_Time * 2)

uint8_t SoftI2C_GPIOx_Pin_Init(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull);
void SoftI2C_SDA_Mode_In(SoftI2C_TypeDef *SoftI2Cx);
void SoftI2C_SDA_Mode_Out(SoftI2C_TypeDef *SoftI2Cx);

HAL_StatusTypeDef SoftI2C_Init(SoftI2C_TypeDef *SoftI2Cx)
{
    if (!SoftI2C_GPIOx_Pin_Init(SoftI2Cx->SDA_GPIO, SoftI2Cx->SDA_Pin, GPIO_MODE_OUTPUT_OD, GPIO_NOPULL))
        return HAL_ERROR;

    if (!SoftI2C_GPIOx_Pin_Init(SoftI2Cx->SCL_GPIO, SoftI2Cx->SCL_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL))
        return HAL_ERROR;

    return HAL_OK;
}

void SoftI2C_Start(SoftI2C_TypeDef *SoftI2Cx)
{
    SDA_Set;
    Delay_Double;
    SCL_Set;
    Delay_Double;
    SDA_Clr;
    Delay_Double;
    SCL_Clr;
    Delay_Double;
}

void SoftI2C_Stop(SoftI2C_TypeDef *SoftI2Cx)
{
    SDA_Clr;
    Delay_Double;
    SCL_Set;
    Delay_Double;
    SDA_Set;
    Delay_Double;
}

void SoftI2C_WriteByte(SoftI2C_TypeDef *SoftI2Cx, uint8_t byte)
{
    SCL_Clr;

    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (byte & 0x80)
            SDA_Set;
        else
            SDA_Clr;

        byte <<= 1;

        Delay;
        SCL_Set;
        Delay;
        SCL_Clr;
        Delay;
    }
}

uint8_t SoftI2C_ReadByte(SoftI2C_TypeDef *SoftI2Cx)
{
    uint8_t i;
    uint8_t data = 0;

    SDA_Mode_In;
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        SCL_Clr;
        Delay;
        SCL_Set;
        Delay;

        if (SDA_Read == GPIO_PIN_SET)
            data |= 0x01;
    }
    SDA_Mode_Out;

    return data;
}

void SoftI2C_Ack(SoftI2C_TypeDef *SoftI2Cx)
{
    SDA_Clr;
    Delay;
    SCL_Set;
    Delay;
    SCL_Clr;
}

void SoftI2C_NAck(SoftI2C_TypeDef *SoftI2Cx)
{
    SCL_Clr;
    SDA_Set;
    Delay;
    SCL_Set;
    Delay;
    SCL_Clr;
}

uint8_t SoftI2C_WaitAck(SoftI2C_TypeDef *SoftI2Cx)
{
    uint8_t i = 0;

    SDA_Set;
    Delay;
    SCL_Set;
    Delay;

    SDA_Mode_In;
    while (SDA_Read == GPIO_PIN_SET)
    {
        i++;
        if (i > 250)
            return 1;
    }
    SDA_Mode_Out;

    SCL_Clr;
    Delay;

    return 0;
}

uint8_t SoftI2C_GPIOx_Pin_Init(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull)
{
    switch ((uint32_t)(GPIOx))
    {
    case (uint32_t)GPIOA:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure);
    }
    break;

    case (uint32_t)GPIOB:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    }
    break;

    case (uint32_t)GPIOC:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOC_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOC, &GPIO_Initure);
    }
    break;

    case (uint32_t)GPIOD:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOD_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOD, &GPIO_Initure);
    }
    break;

    default:
        return 0;
    }

    return 1;
}

void SoftI2C_SDA_Mode_In(SoftI2C_TypeDef *SoftI2Cx)
{
    GPIO_InitTypeDef GPIO_Initure;

    GPIO_Initure.Pin = SoftI2Cx->SDA_Pin;
    GPIO_Initure.Mode = GPIO_MODE_INPUT;
    GPIO_Initure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SoftI2Cx->SDA_GPIO, &GPIO_Initure);
}

void SoftI2C_SDA_Mode_Out(SoftI2C_TypeDef *SoftI2Cx)
{
    GPIO_InitTypeDef GPIO_Initure;

    GPIO_Initure.Pin = SoftI2Cx->SDA_Pin;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SoftI2Cx->SDA_GPIO, &GPIO_Initure);
}
