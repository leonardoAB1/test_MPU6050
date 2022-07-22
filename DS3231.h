/**
  ******************************************************************************
  * @file		DS3231.h
  * @author	Leonardo Acha Boiano
  * @date		12 July 2022
  * @note		Re-write from Book
  ******************************************************************************
  */
	
#ifndef __DS3231_H
#define __DS3231_H

#include "i2c.h"

uint8_t DS3231_bcd2int(uint8_t hex);
void DS3231_setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day_week, 
										uint8_t day_month, uint8_t month, uint8_t year);
void DS3231_getTime(uint8_t *year, uint8_t *month, uint8_t *day,
							uint8_t *hour, uint8_t *min, uint8_t *sec);

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
