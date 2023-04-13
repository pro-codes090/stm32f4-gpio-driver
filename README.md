# stm32f4-gpio-driver

GPIO Bare metal drivers for stm32 f4 family of microcontrollers written in C from scratch. The driver allows user to configure the gpio pins of stm32 microcontroller in Input Mode, Output mode, Alternate function mode, interrupt mode and configure interrupt priority. The driver also exposes apis to read and write data to and from gpio pins and enable and disable interrupts.

## Project file structure

**Src** : The Src folder contains the main application file ( main.c ). The user might change the contents of the file if needed. The folder contains example code each example with its own source file.

**drivers** : folder contains further sub folder **Src** and **Inc**.

- **Src** : Src folder contains driver source (.c) file which has all the driver apis the application file uses
- **Inc** : Inc folder contains the driver header (.h) file which has all the function prototypes and configuration macros.

# driver apis Usage

All the examples and code have been tested on [Stm32f407vgt6 disc1 board](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) if you own a different board from ST of F4 family no changes should be made to the code

## GPIO_PeripClockControl ()

#### Enable or disable the clock for various PORTS on stm32f4 microcontroller

_Parameters_

- `GPIO_RegDef_t *pGPIOx `: Base address of Gpio Port . base address for Ports are defined in **Stm32f407xx.h** header file as **`GPIOA`** ,**`GPIOB`** ,**`GPIOC`** .... ,**`GPIOK`**

- `uint8_t EnorDi`: Enable or Disable . macros used are: **`ENABLE`** , **`DISABLE`** .

## GPIO_Init()

Initializes a GPIO port's pin as per the configuration given to `Gpio_Handle_t` . see example code in the Src directory

_Parameters_

- `GPIO_Handle_t* pGPIOHandle ` : Pointer to `Gpio_Handle_t` configuration structure . `Gpio_Handle_t` has member elements which serves as configuration parameters to` GPIO_Init` function

**GPIO_Handle_t member elements**
|type |Member element | Purpose
|--|--|--|
|GPIO_RegDef_t \*| pGPIOx| Set this with base addr of the port who's pin is to be configured
|GPIO_PinConfig_t|GPIO_PinConfig| This stores the configuration which gets applied to the pin which is to be configured

**GPIO_PinConfig_t member elements**
|Type |Member Element |Purpose|
|-- |-- |--|
|uint8_t| GPIO_PinNumber | Set the pin number to be configured |
|uint8_t|GPIO_PinMode | Set the pin mode (input , output , interrupt , alternate function ) |
|uint8_t|GPIO_PinSpeed | Set the pin speed ( low , medium , high , very high |
|uint8_t|GPIO_PinPUPDControl| Set internal pull up or pull down |
|uint8_t|GPIO_PinOPType | Set the pins output type (push pull or open drain ) |
|uint8_t|GPIO_PinAltFunMode | Set the pin for alternate functionality . set it to zero when not using |

## GPIO_ReadFromInputPin()

Return type : `uint8_t`

Return the value of a gpio pin of a certain PORT (A,BC,....K) which is either 0 or 1 . when a pin configured in input mode and depending on where the pin is connected either to GND or VDD the function returns 0 or 1 .

Refer to example code in Src directory .

_Parameters_

- `GPIO_RegDef_t *pGPIOx ` : Base address of Gpio Port . base address for Ports are defined in **Stm32f407xx.h** header file as **`GPIOA`** ,**`GPIOB`** ,**`GPIOC`** .... ,**`GPIOK`**

- `uint8_t PinNumber` : Pin number to read data from . for most stm32 micros each port has 16 pins from 0 to 15 .PinNumber definition macros are defined in **Stm32f407xx.h** header file as \*PinNumber**\*x** ( **x** : 0 ,1 ,2 ,3 .... 15 ) .

## GPIO_WriteToOutputPin()

Return type : `Void`

Writes the Data value to a gpio pin of a certain PORT (A,BC,....K) which is either 0 or 1 . when a pin configured in Output mode and if the `PinOPType`is set to ` GPIO_OP_TYPE_PP` then a pin can have 2 states either **0** or **1** .when `PinOPType`is set to ` GPIO_OP_TYPE_OD` then a pin can only connect to only GND or floating state

Refer to example code in Src directory .

_Parameters_

- `GPIO_RegDef_t *pGPIOx ` : Base address of Gpio Port . base address for Ports are defined in **Stm32f407xx.h** header file as **`GPIOA`** ,**`GPIOB`** ,**`GPIOC`** .... ,**`GPIOK`**

- `uint8_t PinNumber` : Pin number to write data to . Most stm32 micros each port has 16 pins from 0 to 15 .PinNumber definition macros are defined in **Stm32f407xx.h** header file as \*PinNumber**\*x** ( **x** : 0 ,1 ,2 ,3 .... 15 ) .

- `uint8_t Value` : The value / Data to be written to a gpio pin . eiither 0 or 1 can be written to the output pin . any value other than **0** is considered as **1**

## GPIO_ToggleOutputPin()

Return type : `Void`

Toggles the output of a gpio pin of a certain PORT (A,BC,....K) which is from **0** or **1** or from **1** to **0** when a pin configured in Output mode and if the `PinOPType`is set to ` GPIO_OP_TYPE_PP` then a pin can have 2 states either **0** or **1** .when `PinOPType`is set to ` GPIO_OP_TYPE_OD` then a pin can only connect to only GND or floating state

Refer to example code in Src directory .

_Parameters_

- `GPIO_RegDef_t *pGPIOx ` : Base address of Gpio Port . base address for Ports are defined in **Stm32f407xx.h** header file as **`GPIOA`** ,**`GPIOB`** ,**`GPIOC`** .... ,**`GPIOK`**

- `uint8_t PinNumber` : Pin number to write data to . Most stm32 micros each port has 16 pins from 0 to 15 .PinNumber definition macros are defined in **Stm32f407xx.h** header file as \*PinNumber**\*x** ( **x** : 0 ,1 ,2 ,3 .... 15 ) .

# Interrupt Related APIS

#### How interrupts work in Stm32 microcontroller ?

As per Arm cortex mx specification a microcontroller can support up to 240 different interrupts these interrupts gets issued to the processor core through a peripheral called as NVIC which stands for Nested Vectored Interrupt Controller which is a part of arm architecture . In case of stm32f4 microcontroller which is based on arm cortex m4 architecture out of 240 available interrupts only 82 interrupts have been implemented for **STM32F405xx/07xx and STM32F415xx/17xx** microcontrollers . All the gpio interrupts first goes through EXTI peripheral which is hard wired before it reaches to NVIC and then issues interrupt to the m4 core some interrupt lines reaches directly to NVIC while some goes through EXTI . This is specific to ST's microcontroller and differs from vendor to vendor .

The driver offers three apis to work with gpio interrupts like trigger an interrupt event on a falling edge or rising edge , setting the priority level and a default IRQ handler .

| Api name                   | Description                                                                                                                  | Optional |
| -------------------------- | ---------------------------------------------------------------------------------------------------------------------------- | -------- |
| `GPIO_IRQConfig()`         | Use to Enable or Disable interrupt for a GPIO pin                                                                            | no       |
| `GPIO_IRQ_ProrityConfig()` | Use to configure priority level of an interrupt                                                                              | yes      |
| `GPIO_IRQHandling()`       | This function should be called inside an isr hanlder at start it clears the interrupt flag and logs data to itm data console | no       |

## GPIO_IRQConfig()

Return type : `Void`

Use to Enable or Disable interrupt for a GPIO pin . This will have effect if and only if the pin is already configured in interrupt mode (either rising or falling ) . This can be done by setting `GPIO_PinMode` to `GPIO_MODE_IT_FT` or`GPIO_MODE_IT_RT`or`GPIO_MODE_IT_RFT`

> **Note:** Same pins on other ports cannot be used as interrupt pin if one is already configured on some other port . i.e if pin 14 of PORTD is configured as an interrupt pin then pin 14 of any other port cannot be used for interrupt functionality , this is by design of the microcontroller itself .

Refer to example code in Src directory .

_Parameters_

- `uint8_t IRQ_Number` : IRQ number for any PORT having same pin number have same IRQ number , this information can be found in the reference manual on page no 372 and 377

| Pin number | IRQ Number | Associated macros  |
| ---------- | ---------- | ------------------ |
| 0          | 6          | `IRQ_NO_EXTI0`     |
| 1          | 7          | `IRQ_NO_EXTI1`     |
| 2          | 8          | `IRQ_NO_EXTI2`     |
| 3          | 9          | `IRQ_NO_EXTI3`     |
| 4          | 10         | `IRQ_NO_EXTI4`     |
| 5 - 9      | 23         | `IRQ_NO_EXTI9_5`   |
| 10 - 15    | 40         | `IRQ_NO_EXTI15_10` |

- ` uint8_t EnorDi` : Enable or disable the Interrupt its either 0 or 1 any non zero vaue is recognized as 1 use macro `ENABLE` or `DISABLE` better readability .

## GPIO_IRQ_ProrityConfig()

Return type : `Void`

> every interrupt has a default priority which can be configured if needed . refer page no 372 of reference manual to find the default priority for your isr .

Configures the priority for an interrupt (i.e IRQ number ) . there are 16 priority levels (0 ,1 ,2 , ...15) for any configurable interrupt , also lower is the priority number higher is the priority i .e interrupt with a priority of zero has the highest priority and interrupt with a priority of 15 has the lowest priority .

Refer to example code in Src directory .

_Parameters_

- `uint8_t IRQ_Number` : IRQ number of the interrupt to enable .

- `uint32_t Interrupt_Prority ` : Priority level which ranges from ( 0 ,1 ,2 ,3 .... 15 ) .

## GPIO_IRQHandling()

Return type : `Void`

Default ISR handler which the user should explicitly call at the very start of the ISR routine . ISR routine is just like any other C function which the hardware call the name for these functions can be found in the startup file of stm32 project which gets auto generated and is provided by ST .

Names of ISR handler for GPIO interrupts

| Pin Number | Hanlder Name         |
| ---------- | -------------------- |
| 0          | `EXTI0_IRQHandler`   |
| 1          | `EXTI1_IRQHandler`   |
| 2          | `EXTI2_IRQHandler`   |
| 3          | `EXTI3_IRQHandler`   |
| 4          | `EXTI4_IRQHandler`   |
| 5 - 9      | `EXTI9_5_IRQHandler` |
| 10 - 15    | `EXTI9_5_IRQHandler` |

**How to implement a basic isr in main application file ?**

```c
#include <stdint.h>
#include <stdio.h>

#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"

int main(void) {
  GPIO_Handle_t Gpiobtn;

  Gpiobtn.pGPIOx = GPIOD;
  Gpiobtn.GPIO_PinConfig.GPIO_PinNumber         = GPIO_PIN_NO_12;
  Gpiobtn.GPIO_PinConfig.GPIO_PinMode           = GPIO_MODE_OUTPUT;
  Gpiobtn.GPIO_PinConfig.GPIO_PinOPType         = GPIO_OP_TYPE_PP;
  Gpiobtn.GPIO_PinConfig.GPIO_PinSpeed          = GPIO_SPEED_HIGH;
  Gpiobtn.GPIO_PinConfig.GPIO_PinPUPDControl    = GPIO_NO_PUPD;
  Gpiobtn.GPIO_PinConfig.GPIO_PinAltFunMode     = 0;

  GPIO_IRQConfig(IRQ_NO_EXTI2, ENABLE);
  GPIO_IRQ_ProrityConfig(IRQ_NO_EXTI2, 13);

  while (1) {
    /* TODO */
  }
  return 0;
}

void EXTI2_IRQHandler(void) {
  GPIO_IRQHandling(GPIO_PIN_NO_2);

  while (1) {
    /* TODO */
  }
}
```

Refer to example code in Src directory for more .

_Parameters_

- `uint8_t PinNumber` : Pin number to write data to . Most stm32 micros each port has 16 pins from 0 to 15 .PinNumber definition macros are defined in **Stm32f407xx.h** header file as \*PinNumber**\*x** ( **x** : 0 ,1 ,2 ,3 .... 15 ) .

# Least used APIS

`GPIO_WriteToOutputPort() `

Writes the Value to whole PORT**x** (**x**: A,B,C...K) . overrides the previous values ;

` GPIO_ReadFromInputPort()`

Returns the Value of type `uint16_t` of a whole PORT**x** (**x**: A,B,C...K) .

`GPIO_DeInit()`

De-initializes a GPIO PORT **x** (**x**: A,B,C...K) . i.e overrides the registers of a PORT**x** (**x**: A,B,C...K) to their reset state .
