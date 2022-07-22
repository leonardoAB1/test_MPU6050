/**
  ******************************************************************************
  * @file		i2c.h
  * @author	Leonardo Acha Boiano
  * @date		10 July 2022
  * @note		Re-write from Book
  ******************************************************************************
  */
	
#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"

void i2c_init(void);
void i2c_waitForReady(void);
void i2c_sendStart(void);
void i2c_sendStop(void);
uint8_t i2c_sendAddr(uint8_t addr);
uint8_t i2c_sendAddrForRead(uint8_t addr);
uint8_t i2c_sendAddrForWrite(uint8_t addr);
uint8_t i2c_sendData(uint8_t data);
uint8_t i2c_readData(uint8_t ack);


#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
