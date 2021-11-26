/*
 * Gpio_interrupt.c
 *
 *  Created on: Nov 25, 2021
 *      Author: pro
 */


#include <stdint.h>
#include <stdio.h>
#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"

int main(void) {

	GPIO_Handle_t GpioLed ,GPIObutton ;
	GpioLed.pGPIOx = GPIOD ;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12 ;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT ;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP ;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH ;
	GpioLed.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_NO_PUPD ;
	GpioLed.GPIO_PinConfig.GPIO_PinAltFunMode = 0 ;

	GPIOD_CLOCK_ENABLE() ;
	GPIO_Init(&GpioLed) ;

	GPIObutton.pGPIOx = GPIOD ;
	GPIObutton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8 ;
	GPIObutton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT ;
	GPIObutton.GPIO_PinConfig.GPIO_PinOPType = 0 ;
	GPIObutton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH ;
	GPIObutton.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_PIN_PU;
	GPIObutton.GPIO_PinConfig.GPIO_PinAltFunMode = 0 ;
	GPIO_Init(&GPIObutton) ;

	GPIObutton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6 ;
	GPIObutton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT ;
	GPIObutton.GPIO_PinConfig.GPIO_PinOPType = 0 ;
	GPIObutton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH ;
	GPIObutton.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_PIN_PU;
	GPIObutton.GPIO_PinConfig.GPIO_PinAltFunMode = 0 ;
	GPIO_Init(&GPIObutton) ;

	GPIObutton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3 ;
	GPIObutton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT ;
	GPIObutton.GPIO_PinConfig.GPIO_PinOPType = 0 ;
	GPIObutton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH ;
	GPIObutton.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_PIN_PU;
	GPIObutton.GPIO_PinConfig.GPIO_PinAltFunMode = 0 ;
	GPIO_Init(&GPIObutton) ;

	GPIObutton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2 ;
	GPIObutton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT ;
	GPIObutton.GPIO_PinConfig.GPIO_PinOPType = 0 ;
	GPIObutton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH ;
	GPIObutton.GPIO_PinConfig.GPIO_PinPUPDControl = GPIO_PIN_PU ;
	GPIObutton.GPIO_PinConfig.GPIO_PinAltFunMode = 0 ;
	GPIO_Init(&GPIObutton) ;


	//IRQ configurations


	GPIO_IRQConfig(IRQ_NO_EXTI9_5,  ENABLE) ;
	GPIO_IRQ_ProrityConfig(IRQ_NO_EXTI9_5, 15) ;

	GPIO_IRQConfig(IRQ_NO_EXTI9_5,  ENABLE) ;
	GPIO_IRQ_ProrityConfig(IRQ_NO_EXTI9_5, 15) ;

	GPIO_IRQConfig(IRQ_NO_EXTI3,  ENABLE) ;
	GPIO_IRQ_ProrityConfig(IRQ_NO_EXTI3 , 14) ;

	GPIO_IRQConfig(IRQ_NO_EXTI2,  ENABLE) ;
	GPIO_IRQ_ProrityConfig(IRQ_NO_EXTI2 , 13) ;

	while(1) ;

	return 0 ;
}

void EXTI2_IRQHandler(void){
	GPIO_IRQHandling(GPIO_PIN_NO_2) ;
while(1);
}

void EXTI3_IRQHandler(void){
	GPIO_IRQHandling(GPIO_PIN_NO_3) ;
while(1) ;
}

void EXTI9_5_IRQHandler(void){

	GPIO_IRQHandling(GPIO_PIN_NO_6) ;
	GPIO_IRQHandling(GPIO_PIN_NO_8) ;
		while(1) ;

}
