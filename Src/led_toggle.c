/*
 * led_toggle.c
 *
 *  Created on: Nov 25, 2021
 *      Author: pro
 */

#include <stdint.h>
#include <stdio.h>
#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"

void delay (void){
	for (uint32_t i = 0; i < 100000; i++) {

	}
}

int main (void ){
	GPIO_Handle_t GpioLed ;
	GpioLed.pGPIOx = GPIOD ;
	GPIOD_CLOCK_ENABLE() ;

	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12 ;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT ;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD ;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH ;
	GpioLed.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_NO_PUPD ;
	GpioLed.GPIO_PinConfig.GPIO_PinAltFunMode = 0 ;
	GPIO_Init(&GpioLed);

	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13 ;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT ;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP ;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH ;
	GpioLed.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_NO_PUPD ;
	GpioLed.GPIO_PinConfig.GPIO_PinAltFunMode = 0 ;
	GPIO_Init(&GpioLed) ;



	GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, GPIO_PIN_SET);

	while(1){
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
		delay();
	}
	return 0 ;
}

