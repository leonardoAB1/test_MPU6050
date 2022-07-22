/**
  ******************************************************************************
  * @file		i2c.c
  * @author	Leonardo Acha Boiano
  * @date		10 July 2022
  * @note		Re-write from Book
  ******************************************************************************
  */

#include "i2c.h"

void i2c_init(){
	RCC		->APB2ENR |= (1<<2)|(1<<3); 		//enable clocks for PORT_A and PORT_B
	RCC		->APB1ENR |= (1<<21); 					//enable clock for I2C1:RCC_APB1ENR_I2C1EN
	GPIOB	->CRL 		|= 0xFF000000;				//configure PB6 and PB7 as alt. func open drain
																				//MODE6 & MODE7 bits to 11 -> Output 50MHz
																				//CNF6 & CNF7		bits to 11   -> Alt. func open drain

	I2C1->CR2				=	 0x0020;						//(0000 0000 0010 0000)
	I2C1->CCR				=	 0x00B4;						//(0000 0000 1011 0100)
	I2C1->TRISE			=	 37;								//TRISE=(PCLK/1M)+1; PCLK1=36M
	I2C1->CR1 			=  1; 								//PE=1
}

void i2c_waitForReady(){
	while((I2C1->SR2&(1<<1)) != 0);					//check bus busy
}

void i2c_sendStart(){
	I2C1->CR1 	|= (1<<8);								//start
	while((I2C1->SR1&(1<<0))==0); 				//wait for SB
	int stat    = I2C1	->SR2;
}

void i2c_sendStop(){
	I2C1->CR1 	|= (1<<9); 								//stop
	while((I2C1->SR2&(1<<0))!=0); 				//wait for becoming slave
}

uint8_t i2c_sendAddr(uint8_t addr){
	I2C1->DR=addr;
	int stat;
	do{
		stat=I2C1->SR1;
		if((stat&(1<<9))!=0) 								//arbitration lost
			return 1;
		
		if((stat&(1<<1))!=0) 								//address sent
		{
			stat=I2C1->SR2; 									//read SR2 to clear ADDR flag
			return 0;
		}
	}   while(1);
}

uint8_t i2c_sendAddrForRead(uint8_t addr){
	return i2c_sendAddr((addr<<1)+1); 		//addr+Read(1)
}

uint8_t i2c_sendAddrForWrite(uint8_t addr){
	return i2c_sendAddr((addr<<1));				//addr+Write(0)
}

uint8_t i2c_sendData(uint8_t data){
	I2C1->DR=data;
	int stat1;
	do{
		stat1=I2C1->SR1;
		if((stat1&(1<<7))!=0) 							//TxE=1
			return 0;
	}   while(1);
}

uint8_t i2c_readData(uint8_t ack){
	if(ack!=0)
		I2C1->CR1|=1<<10;
	else
		I2C1->CR1&=~(1<<10);
	while((I2C1->SR1&(1<<6))==0); 				//waiting for RcNE
	return I2C1->DR;
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
