/**
  ******************************************************************************
  * @file		MPU6050.c
  * @author	Leonardo Acha Boiano
  * @date		15 July 2022
  * @note		Based on InvenSense MPU-6050 register map document rev. 4.2
	*					Re-write from I2Cdev library collection - MPU6050 I2C device class
	*													2012 Jeff Rowberg
	*													2014 Marton Sebok
  ******************************************************************************
  */

#include "MPU6050.h"

void MPU6050_initialize(void){
	do{
		i2c_waitForReady();										//wait while the bus is busy
		i2c_sendStart();											//generate start condition
	}while(i2c_sendAddrForWrite(MPU6050_ADDRESS_AD0_HIGH)!=0);
	
	i2c_sendData(MPU6050_RA_PWR_MGMT_1);		//reg. pointer to 0x6B
	i2c_sendData((MPU6050_CLOCK_PLL_XGYRO)|(0<<MPU6050_PWR1_SLEEP_BIT));
	
	i2c_sendStop();
	
	do{
		i2c_waitForReady();										//wait while the bus is busy
		i2c_sendStart();											//generate repeated start condition
	}while(i2c_sendAddrForWrite(MPU6050_ADDRESS_AD0_HIGH)!=0);
	
	i2c_sendData(MPU6050_RA_SMPLRT_DIV);		//reg. pointer to 0x19
	i2c_sendData(MPU6050_SMPLRT_DIV);				//0x19
	i2c_sendData(0);												//0x1A
	i2c_sendData(MPU6050_GYRO_FS_250);			//0x1B
	i2c_sendData(MPU6050_ACCEL_FS_2);				//0x1C
	
	i2c_sendStop();
}

uint8_t MPU6050_testConnection(void){
		do{
		i2c_waitForReady(); 									//wait while the bus is busy
		i2c_sendStart();											//generate start condition
	}while(i2c_sendAddrForWrite(MPU6050_ADDRESS_AD0_HIGH)!=0);
	
	i2c_sendData(MPU6050_RA_WHO_AM_I);			//set reg. pointer to MPU6050_RA_WHO_AM_I
		
	do{
		i2c_waitForReady(); 									//wait while the bus is busy
		i2c_sendStart();											//generate repeated start condition
	}while(i2c_sendAddrForRead(MPU6050_ADDRESS_AD0_HIGH)!=0);
	
	uint8_t check=(i2c_readData(0x00)>>1);
	i2c_sendStop();													//generate stop
	
	if (check==0x34){
		return 1;
	}
	else return 0;	
}

void MPU6050_getAcceleration(int16_t *x, int16_t *y, int16_t *z){
	
	do{
		i2c_waitForReady(); 									//wait while the bus is busy
		i2c_sendStart();											//generate start condition
	}while(i2c_sendAddrForWrite(MPU6050_ADDRESS_AD0_HIGH)!=0);
	
	i2c_sendData(MPU6050_RA_ACCEL_XOUT_H);	//set reg. pointer				
		
	do{
		i2c_waitForReady(); 									//wait while the bus is busy
		i2c_sendStart();											//generate repeated start condition
	}while(i2c_sendAddrForRead(MPU6050_ADDRESS_AD0_HIGH)!=0);
	
	*x	=((i2c_readData(0x01))<<8)|(i2c_readData(0x01));
	*y	=((i2c_readData(0x01))<<8)|(i2c_readData(0x01));
	*z	=((i2c_readData(0x01))<<8)|(i2c_readData(0x00));
	
	i2c_sendStop();													//generate stop
	
}

void MPU6050_getRotation(int16_t *x, int16_t *y, int16_t *z){
	
	do{
		i2c_waitForReady(); 									//wait while the bus is busy
		i2c_sendStart();											//generate start condition
	}while(i2c_sendAddrForWrite(MPU6050_ADDRESS_AD0_HIGH)!=0);
	
	i2c_sendData(MPU6050_RA_GYRO_XOUT_H);		//set reg. pointer
		
	do{
		i2c_waitForReady(); 									//wait while the bus is busy
		i2c_sendStart();											//generate repeated start condition
	}while(i2c_sendAddrForRead(MPU6050_ADDRESS_AD0_HIGH)!=0);
	
	*x	=((i2c_readData(0x01))<<8)|(i2c_readData(0x01));
	*y	=((i2c_readData(0x01))<<8)|(i2c_readData(0x01));
	*z	=((i2c_readData(0x01))<<8)|(i2c_readData(0x00));
	
	i2c_sendStop();													//generate stop
	
}



/********************************* END OF FILE ********************************/
/******************************************************************************/
