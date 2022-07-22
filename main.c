/**
  ******************************************************************************
  * @file		main.c
  * @author	Leonardo Acha Boiano
  * @date		09 July 2022
  ******************************************************************************
  */

#include "main.h"

int main()
{
	char str[30];
	uint8_t year, month, day, hour, min, sec;
	int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
	
	RCC->APB2ENR |= (0xFC|(1<<14));					//enable GPIO clocks and USART1 clock
	RCC->APB1ENR |= (1<<0);									//enable TIM2 clock
		
	usart1_init();
	i2c_init();
		
	usart1_sendStr("\n\rDate and Time");
	
	DS3231_setTime(0x30,0x35,0x12,0x02,0x12,0x07,0x22);
	
	MPU6050_initialize();
	
	if (MPU6050_testConnection()){
		usart1_sendStr("\n\rMPU6050 iniciado correctamente");
	}
  else {
		usart1_sendStr("\n\rError al iniciar el sensor");
	}
	
	while(1)
	{
		DS3231_getTime(&year, &month, &day, &hour, &min, &sec);
		sprintf(str,"\n\r%d/%d/%d %d:%d:%d", 
						day, month, year, hour, min, sec);
		usart1_sendStr(str);
		
		usart1_sendStr("1");
		MPU6050_getAcceleration(&Acc_rawX, &Acc_rawY, &Acc_rawZ);
		usart1_sendStr("2");
		MPU6050_getRotation(&Gyr_rawX, &Gyr_rawY, &Gyr_rawZ);
		usart1_sendStr("3");
		sprintf(str,"\n\r%d-%d-%d-%d-%d-%d",
						Acc_rawX, Acc_rawY, Acc_rawZ, 
						Gyr_rawX, Gyr_rawY, Gyr_rawZ);
		
		usart1_sendStr(str);
		
		delay_ms(1000);												//wait 1 second
	}
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
