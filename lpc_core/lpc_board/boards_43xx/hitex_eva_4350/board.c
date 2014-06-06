/*
 * @brief Hitex EVA 1850/4350 board file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "string.h"

/* Include other sources files specific to this board */
#include "retarget.h"

/** @ingroup BOARD_HITEX_EVA_18504350
 * @{
 */

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Port and bit mapping for LEDs on GPIOs */
static const uint8_t ledports[] = {7, 7, 7, 7, 7, 7};
static const uint8_t ledbits[]  = {9,10,19,20,21,22};

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* System configuration variables used by chip driver */
const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;

/*****************************************************************************
 * Private functions
 ****************************************************************************/


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize pin muxing for a UART */
void Board_UART_Init(LPC_USART_T *pUART)
{
	if (pUART == LPC_USART0) {
		Chip_SCU_PinMuxSet(0xF, 10, (SCU_MODE_PULLDOWN | SCU_MODE_FUNC1));	/* PF.10 : UART0_TXD */
		Chip_SCU_PinMuxSet(0xF, 11, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC1));	/* PF.11 : UART0_RXD */
	}
	else if (pUART == LPC_UART1) {
		Chip_SCU_PinMuxSet(0xC, 13, (SCU_MODE_PULLDOWN | SCU_MODE_FUNC2));	/* PC.13 : UART1_TXD - pin 1 of SV14 */
		Chip_SCU_PinMuxSet(0xC, 14, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC2));	/* PC.14 : UART1_RX - pin 2 of SV14 */
	}
	else if (pUART == LPC_USART2) {
		/* P1.15 : UART2_TXD - pin 11 of SV6, P1.16 : UART2_RXD - pin 3 of SV6 */
		Chip_SCU_PinMuxSet(0x1, 15, (SCU_MODE_PULLDOWN | SCU_MODE_FUNC1));
		Chip_SCU_PinMuxSet(0x1, 16, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC1));
	}
	else if (pUART == LPC_USART3) {
		/* P9.3 : UART3_TXD - pin 15 of SV6, P9.4 : UART3_RXD - pin 7 of SV3 */
		Chip_SCU_PinMuxSet(0x9, 3, (SCU_MODE_PULLDOWN | SCU_MODE_FUNC7));
		Chip_SCU_PinMuxSet(0x9, 4, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC7));
	}
}

/* Initialize debug output via UART for board */
void Board_Debug_Init(void)
{
#if defined(DEBUG_UART)
	Board_UART_Init(DEBUG_UART);

	Chip_UART_Init(DEBUG_UART);
	Chip_UART_SetBaud(DEBUG_UART, 115200);
	Chip_UART_ConfigData(DEBUG_UART, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);

	/* Enable UART Transmit */
	Chip_UART_TXEnable(DEBUG_UART);
#endif
}

/* Sends a character on the UART */
void Board_UARTPutChar(char ch)
{
#if defined(DEBUG_UART)
	/* Wait for space in FIFO */
	while ((Chip_UART_ReadLineStatus(DEBUG_UART) & UART_LSR_THRE) == 0) {}
	Chip_UART_SendByte(DEBUG_UART, (uint8_t) ch);
#endif
}

/* Gets a character from the UART, returns EOF if no character is ready */
int Board_UARTGetChar(void)
{
#if defined(DEBUG_UART)
	if (Chip_UART_ReadLineStatus(DEBUG_UART) & UART_LSR_RDR) {
		return (int) Chip_UART_ReadByte(DEBUG_UART);
	}
#endif
	return EOF;
}

/* Outputs a string on the debug UART */
void Board_UARTPutSTR(char *str)
{
#if defined(DEBUG_UART)
	while (*str != '\0') {
		Board_UARTPutChar(*str++);
	}
#endif
}

/* Initializes board LED(s) */
static void Board_LED_Init()
{
	int i;

	/* Set ports as outputs with initial states off */
	for (i = 0; i < (sizeof(ledports) / sizeof(ledports[0])); i++) {
		Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, ledports[i], ledbits[i]);
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, ledports[i], ledbits[i], true);
	}
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, ledports[0], ledbits[0], false);
}

/* Sets the state of a board LED to on or off */
void Board_LED_Set(uint8_t LEDNumber, bool On)
{
	if (LEDNumber < (sizeof(ledports) / sizeof(ledports[0])))
	{
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, ledports[LEDNumber], ledbits[LEDNumber], !On);
	}
}

/* Returns the current state of a board LED */
bool Board_LED_Test(uint8_t LEDNumber)
{
	bool On = false;

	if (LEDNumber < (sizeof(ledports) / sizeof(ledports[0])))
	{
		On = (bool) !Chip_GPIO_GetPinState(LPC_GPIO_PORT, ledports[LEDNumber], ledbits[LEDNumber]);
	}

	return On;
}

void Board_LED_Toggle(uint8_t LEDNumber)
{
	Board_LED_Set(LEDNumber, !Board_LED_Test(LEDNumber));
}

/* Initialize button(s) interface on board */
void Board_Buttons_Init(void)	// FIXME not functional ATM
{
	Chip_SCU_PinMuxSet(0xD, 7, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC4));			// GPIO6[21]
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, BUTTONS_BUTTON1_GPIO_PORT_NUM, BUTTONS_BUTTON1_GPIO_BIT_NUM);	// input
}

/* Returns button(s) state on board */
uint32_t Buttons_GetStatus(void)
{
	uint8_t ret = NO_BUTTON_PRESSED;
	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, BUTTONS_BUTTON1_GPIO_PORT_NUM, BUTTONS_BUTTON1_GPIO_BIT_NUM) == 0) {
		ret |= BUTTONS_BUTTON1;
	}
	return ret;
}

/* Initialize joystick interface on board */
void Board_Joystick_Init(void)
{}

/* Returns joystick states on board */
uint8_t Joystick_GetStatus(void)
{
	return NO_BUTTON_PRESSED;
}

/* Returns the MAC address assigned to this board */
void Board_ENET_GetMacADDR(uint8_t *mcaddr)
{
	const uint8_t boardmac[] = {0x00, 0x60, 0x37, 0x12, 0x34, 0x56};

	memcpy(mcaddr, boardmac, 6);
}

/* Set up and initialize all required blocks and functions related to the
   board hardware */
void Board_Init(void)
{
	/* Sets up DEBUG UART */
	//DEBUGINIT(); //Stan Mask, this has been call before Main() Entry.

	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO_PORT);

#if defined(USE_USB)
	/* Setup GPIOs for USB demos */
#if 0	/* FIXME: the following call removed on the Hitex board as it interferes with muxed MII state */
		//	Chip_SCU_PinMuxSet(0x9, 5, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC2));			// P9_5 USB1_VBUS_EN, USB1 VBus function
#endif
	Chip_SCU_PinMuxSet(0x2, 5, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC2));	// P2_5 USB1_VBUS, MUST CONFIGURE THIS SIGNAL FOR USB1 NORMAL OPERATION
	Chip_SCU_PinMuxSet(0x6, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC1));			// P6_3 USB0_PWR_EN, USB0 VBus function
#endif
	
	/* Initialize LEDs */
	Board_LED_Init();

#if defined(USE_RMII)
	Chip_ENET_RMIIEnable(LPC_ETHERNET);
#else
	Chip_ENET_MIIEnable(LPC_ETHERNET);
#endif
}

/* Sets up board specific ADC interface */
void Board_ADC_Init(void)
{
	/* Analog function ADC1_2 selected on pin PF_9 */
	Chip_SCU_ADC_Channel_Config(1, 2);
}

/* Sets up board specific I2C interface */
void Board_I2C_Init(I2C_ID_T id)
{
	if (id == I2C1) {
		/* Configure pin function for I2C1 on PE.13 (I2C1_SDA) and PE.15 (I2C1_SCL) */
		Chip_SCU_PinMuxSet(0xE, 13, (SCU_MODE_ZIF_DIS | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC2));
		Chip_SCU_PinMuxSet(0xE, 15, (SCU_MODE_ZIF_DIS | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC2));
	}
	else {
		Chip_SCU_I2C0PinConfig(I2C0_STANDARD_FAST_MODE);
	}
}

/* Initialize LCD Interface */
void Board_LCD_Init(void)
{
	/* Reset LCD and wait for reset to complete */
	Chip_RGU_TriggerReset(RGU_LCD_RST);
	while (Chip_RGU_InReset(RGU_LCD_RST)) {}

	//lcdPinConfig();
	//Board_InitLCDController();
}


/* Initialize pin muxing for SDMMC interface */
void Board_SDMMC_Init(void)
{
	Chip_SCU_PinMuxSet(0xc, 9, (SCU_MODE_INACT | SCU_MODE_FUNC7));				/* Pc.9 SDIO power */
	Chip_SCU_PinMuxSet(0xc, 2, (SCU_MODE_INACT | SCU_MODE_FUNC7));				/* Pc.2 SDIO LED */
	Chip_SCU_PinMuxSet(0xf, 10, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC6));	/* Pf.10 SDIO WP */
	Chip_SCU_PinMuxSet(0xc, 8, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC7));	/* Pc.8 SDIO CD */
	Chip_SCU_PinMuxSet(0xc, 6, (SCU_PINIO_FAST | SCU_MODE_FUNC7));		/* Pc.6 SDIO D2 */
	Chip_SCU_PinMuxSet(0xc, 5, (SCU_PINIO_FAST | SCU_MODE_FUNC7));		/* Pc.5 SDIO D1 */
	Chip_SCU_PinMuxSet(0xc, 4, (SCU_PINIO_FAST | SCU_MODE_FUNC7));		/* Pc.4 SDIO D0 */
	Chip_SCU_PinMuxSet(0xc, 0, (SCU_MODE_INACT | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC7));	/* Pc.0 SDIO clock */
	Chip_SCU_PinMuxSet(0xc, 10, (SCU_PINIO_FAST | SCU_MODE_FUNC7));		/* Pc.10 SDIO command */
	Chip_SCU_PinMuxSet(0xc, 7, (SCU_PINIO_FAST | SCU_MODE_FUNC7));		/* Pc.7 SDIO D3 */
}

/* Initialize pin muxing for SSP interface */
void Board_SSP_Init(LPC_SSP_T *pSSP)
{
	if (pSSP == LPC_SSP0) {
		/* Set up clock and muxing for SSP0 interface */
		// #if !defined(HITEX_LCD_TERM)
		/* PC.11 connected to GPIO = SSEL_MUX_A, PC.12 connected to GPIO = SSEL_MUX_B */
		Chip_SCU_PinMuxSet(0xC, 11, (SCU_MODE_INACT | SCU_MODE_FUNC4));
		Chip_SCU_PinMuxSet(0xC, 12, (SCU_MODE_INACT | SCU_MODE_FUNC4));
		Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0x6, 10);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0x6, 11);
		// #endif
		/* PF.0 connected to SCL/SCLK	SCU_MODE_FUNC2=SSP0 SCK0 */
		Chip_SCU_PinMuxSet(0xF, 0, (SCU_PINIO_FAST | SCU_MODE_FUNC0));
		/* PF.1 connected to nCS		SCU_MODE_FUNC2=SSP0 SSEL0 */
		Chip_SCU_PinMuxSet(0xF, 1, (SCU_PINIO_FAST | SCU_MODE_FUNC2));
		/* PF.2 connected to SO			SCU_MODE_FUNC2=SSP0 MISO0 */
		Chip_SCU_PinMuxSet(0xF, 2, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC2));
		/* PF.3 connected to nSI		SCU_MODE_FUNC2=SSP0 MOSI0 */
		Chip_SCU_PinMuxSet(0xF, 3, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC2));
	}
	else if (pSSP == LPC_SSP1) {
		/* Set up clock and muxing for SSP1 interface */
		/* P1.19 connected to SCL/SCLK	SCU_MODE_FUNC1=SSP1 SCK1 */
		Chip_SCU_PinMuxSet(0x1, 19, (SCU_PINIO_FAST | SCU_MODE_FUNC1));
		/* P1.20 connected to nCS		SCU_MODE_FUNC1=SSP1 SSEL1 */
		Chip_SCU_PinMuxSet(0x1, 20, (SCU_PINIO_FAST | SCU_MODE_FUNC1));
		/* P0.0 connected to SO			SCU_MODE_FUNC1=SSP1 MISO1 */
		Chip_SCU_PinMuxSet(0x0, 0, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC1));
		/* P0.1 connected to nSI		SCU_MODE_FUNC2=SSP1 MOSI1 */
		Chip_SCU_PinMuxSet(0x0, 1, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC1));
	}
}



/* FIXME */
void Serial_CreateStream(void *Stream)
{
	// implement later
}

/**
 * @}
 */
