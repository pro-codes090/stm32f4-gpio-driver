# stm32f4-gpio-driver

GPIO Bare metal drivers for stm32 f4 family of microcontrollers written in C from scratch .The driver allows user to configure the gpio pins of stm32 microcontroller in Input Mode , Output mode , Alternate function mode , interrupt mode and configure interrupt priority . The driver also exposes apis to read and write data to and from gpio pins and enable and disable interrupts .

## Project file structure

**Src** : The Src folder contains the main application file ( main.c ) . The user might change the contents of the file if needed . The folder contains example code each example with its own source file .

**drivers** : folder contains further sub folder **Src** and **Inc** .

- **Src** : Src folder contains driver source (.c) file which has all the driver apis the application file uses
- **Inc** : Inc folder contains the driver header (.h) file which has all the function prototypes and configuration macros .

# driver apis Usage

All the examples and code have been tested on [Stm32f407vgt6 disc1 board](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) if you own a different board from st of F4 family no changes should be made to the code

## GPIO_PeripClockControl ()

#### Enable or disable the clock for various PORTS on stm32f4 microcontroller

_Parameters_

- `GPIO_RegDef_t *pGPIOx ` : Base address of Gpio Port . base address for Ports are defined in **Stm32f407xx.h** header file as **`GPIOA`** ,**`GPIOB`** ,**`GPIOC`** .... ,**`GPIOK`**

- `uint8_t EnorDi` : Enable or Disable . macros used are ,**`ENABLE`** , **`DISABLE`** .

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

The driver offers three apis to work with gpio interrupts like trigger an interrupt event on a falling edge or rising edge and so on .

| Api name                 | Description                                                                                                                  | Optional |
| ------------------------ | ---------------------------------------------------------------------------------------------------------------------------- | -------- |
| GPIO_IRQConfig()         | Use to Enable or Disable interrupt for a GPIO pin                                                                            | no       |
| GPIO_IRQ_ProrityConfig() | Use to configure priority level of a interrupt                                                                               | yes      |
| GPIO_IRQHandling()       | This function should be called inside an isr hanlder . The function disables the interrupt and logs data to itm data console | yes      |
