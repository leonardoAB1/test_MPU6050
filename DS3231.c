/**
  ******************************************************************************
  * @file		DS3231.c
  * @author	Leonardo Acha Boiano
  * @date		12 July 2022
  * @note		Re-write from Book
  ******************************************************************************
  */

#include "DS3231.h"

//gets BCD number and converts it to binary
// 0x40 -> 40
uint8_t DS3231_bcd2int(uint8_t hex){
	return ((hex&0xF0)>>4)*10+(hex&0x0F);
}

void DS3231_setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day_week, 
										uint8_t day_month, uint8_t month, uint8_t year){
	do{
		i2c_waitForReady();										//wait while the bus is busy
		i2c_sendStart();											//generate start condition
	}while(i2c_sendAddrForWrite(0x68)!=0); 	//send slave addr. 0x68 for write
	
	i2c_sendData(0x0);											//reg. pointer to 0x0
	i2c_sendData(sec);											//second * writes 35 to location 0x0
	i2c_sendData(min);											//min
	i2c_sendData(hour);											//hour
	i2c_sendData(day_week);									//day of week
	i2c_sendData(day_month);								//day of month
	i2c_sendData(month);										//month
	i2c_sendData(year);											//year
	
	i2c_sendStop();							
	}

void DS3231_getTime(uint8_t *year, uint8_t *month, uint8_t *day,
							uint8_t *hour, uint8_t *min, uint8_t *sec){
	
	do{
		i2c_waitForReady(); //wait while the bus is busy
		i2c_sendStart();		//generate start condition
	}while(i2c_sendAddrForWrite(0x68)!=0);
	
	i2c_sendData(0x00);		//set reg. pointer to 0
	i2c_sendStop();				//generate stop condition						
		
	do{
		i2c_waitForReady(); //wait while the bus is busy
		i2c_sendStart();		//generate restart condition
	}while(i2c_sendAddrForRead(0x68)!=0);
	
	*sec	=DS3231_bcd2int(i2c_readData(0x01)); //read sec
	*min	=DS3231_bcd2int(i2c_readData(0x01));	//read min
	*hour	=DS3231_bcd2int(i2c_readData(0x01));	//read hour
	DS3231_bcd2int(i2c_readData(0x01));				//read day of week
	*day	=DS3231_bcd2int(i2c_readData(0x01));	//read day of month
	*month=DS3231_bcd2int(i2c_readData(0x01));	//read month
	*year	=DS3231_bcd2int(i2c_readData(0x00));	//read year(last read)
	
	i2c_sendStop();				//generate stop
	
	}

/********************************* END OF FILE ********************************/
/******************************************************************************/
