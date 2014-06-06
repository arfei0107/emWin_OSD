/*
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
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
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */
#include "ustdlib.h"
#include "board.h"
#include "emc_LPC18xx_43xx.h"
#define LPC_SCU_CLK(LPC_SCU_BASE, c) (*(volatile int *) ((LPC_SCU_BASE) +0xC00 + ((c) * 0x4)))

/* The System initialization code is called prior to the application and
   initializes the board for run-time operation. */

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Structure for initial base clock states */
struct CLK_BASE_STATES {
	CHIP_CGU_BASE_CLK_T clk;	/* Base clock */
	CHIP_CGU_CLKIN_T clkin;	/* Base clock source, see UM for allowable souorces per base clock */
	bool autoblock_enab;/* Set to true to enable autoblocking on frequency change */
	bool powerdn;		/* Set to true if the base clock is initially powered down */
};

/* Initial base clock states are mostly on */
STATIC const struct CLK_BASE_STATES InitClkStates[] = {
	{CLK_BASE_SAFE, CLKIN_IRC, true, false},
	{CLK_BASE_APB1, CLKIN_MAINPLL, true, false},
	{CLK_BASE_APB3, CLKIN_MAINPLL, true, false},
	{CLK_BASE_USB0, CLKIN_USBPLL, true, true},
	{CLK_BASE_PERIPH, CLKIN_MAINPLL, true, false},
	{CLK_BASE_SPI, CLKIN_MAINPLL, true, false},
	{CLK_BASE_ADCHS, CLKIN_MAINPLL, true, true},
	{CLK_BASE_PHY_TX, CLKIN_ENET_TX, true, false},
#if defined(USE_RMII)
	{CLK_BASE_PHY_RX, CLKIN_ENET_TX, true, false},
#else
	{CLK_BASE_PHY_RX, CLKIN_ENET_RX, true, false},
#endif
	{CLK_BASE_SDIO, CLKIN_MAINPLL, true, false},
	{CLK_BASE_SSP0, CLKIN_MAINPLL, true, false},
	{CLK_BASE_SSP1, CLKIN_MAINPLL, true, false},
	{CLK_BASE_UART0, CLKIN_MAINPLL, true, false},
	{CLK_BASE_UART1, CLKIN_MAINPLL, true, false},
	{CLK_BASE_UART2, CLKIN_MAINPLL, true, false},
	{CLK_BASE_UART3, CLKIN_MAINPLL, true, false},
	{CLK_BASE_OUT, CLKINPUT_PD, true, false},
	{CLK_BASE_APLL, CLKINPUT_PD, true, false},
	{CLK_BASE_CGU_OUT0, CLKINPUT_PD, true, false},
	{CLK_BASE_CGU_OUT1, CLKINPUT_PD, true, false},

	/* Clocks derived from dividers */
	{CLK_BASE_LCD, CLKIN_MAINPLL, true, false},
	{CLK_BASE_USB1, CLKIN_IDIVD, true, true}
};

/* SPIFI high speed pin mode setup */
STATIC const PINMUX_GRP_T spifipinmuxing[] = {
	{0x3, 3,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},	/* SPIFI CLK */
	{0x3, 4,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},	/* SPIFI D3 */
	{0x3, 5,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},	/* SPIFI D2 */
	{0x3, 6,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},	/* SPIFI D1 */
	{0x3, 7,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)},	/* SPIFI D0 */
	{0x3, 8,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)}	/* SPIFI CS/SSEL */
};

STATIC const PINMUX_GRP_T pinmuxing[] = {
#if defined(USE_RMII)
	/* RMII pin group */
	{0x1, 19,
	 (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC0)},
	{0x0, 1,  (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC6)},
	{0x1, 18, (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
	{0x1, 20, (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
	{0x1, 17,
	 (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
	{0xC, 1,  (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
	{0x1, 16,
	 (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC7)},
	{0x1, 15,
	 (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC3)},
	{0x0, 0,
	 (SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC2)},
#else
	 #if defined(USE_MII)
	/* MII pin group */
	{0x1, 19, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC0)},
	{0x0, 1,  (SCU_MODE_INACT | SCU_MODE_FUNC6)},
	{0x1, 18, (SCU_MODE_INACT | SCU_MODE_FUNC3)},
	{0x1, 20, (SCU_MODE_INACT | SCU_MODE_FUNC3)},
	{0x1, 17, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC3)},
	{0xC, 1,  (SCU_MODE_INACT | SCU_MODE_FUNC3)},
	{0x1, 16, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC7)},
	{0x1, 15, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC3)},
	{0x0, 0,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC2)},
	{0x9, 4,  (SCU_MODE_INACT | SCU_MODE_FUNC5)},
	{0x9, 5,  (SCU_MODE_INACT | SCU_MODE_FUNC5)},
	{0xC, 0,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC3)},
	{0x9, 0,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC5)},
	{0x9, 1,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC5)},
	{0x9, 6,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC5)},
	{0x9, 3,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC5)},
	{0x9, 2,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC5)},
	{0xC, 8,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_FUNC4)},
	#endif
#endif
	/* External data lines D0 .. D15 */
	{0x1, 7,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 8,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 9,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 10,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 11,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 12,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 13,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 14,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x5, 4,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x5, 5,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x5, 6,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x5, 7,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x5, 0,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x5, 1,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x5, 2,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x5, 3,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	/* Address lines A0 .. A14 */
	{0x2, 9,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x2, 10,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x2, 11,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x2, 12,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x2, 13,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 0,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x1, 1,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x1, 2,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x2, 8,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x2, 7,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x2, 6,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x2, 2,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x2, 1,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x2, 0,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0x6, 8,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC1)},
	 //A15 .. A23
#if defined(USE_EMC_A15_A23)
	{0x6, 7,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC1)},
	{0xD, 16,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0xD, 15,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
	{0xE, 0,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0xE, 1,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0xE, 2,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0xE, 3,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0xE, 4,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0xA, 4,
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
#endif
	 
	/* EMC control signals */
#if defined(USE_EMC_BLS0)
	{0x1, 4, //EMC_BLS0
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
#endif

#if defined(USE_EMC_BLS1)
	{0x6, 6, //EMC_BLS1
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC1)},
#endif

#if defined(USE_EMC_BLS2)
	{0xD, 13, //EMC_BLS2
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
#endif
	 
#if defined(USE_EMC_BLS3)
	{0xD, 10, //EMC_BLS3
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
#endif
	 
	{0x6, 9, //EMC_DYCS0
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x1, 6, //EMC_WE
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x6, 4, //EMC_CAS
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x6, 5, //EMC_RAS
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x6, 11,//EMC_CKE0
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x6, 12,//EMC_DQM0
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	{0x6, 10,//EMC_DQM1
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
	 
#if defined(USE_EMC_DQM2)
	{0xD, 0, //EMC_DQM2
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC2)},
#endif

#if defined(USE_EMC_DQM3)
	{0xE, 13,//EMC_DQM3
	 (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC3)},
#endif

#if defined(EXT_STAT_MEM)	 
	{0x1, 3,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)}, //EMC_OE 
	{0x1, 4,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)}, //EMC_BLS0 
	{0x6, 6,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)}, //EMC_BLS1 
	{0x1, 5,  (SCU_PINIO_FAST | SCU_MODE_FUNC3)}, //EMC_CS0 
#endif
	
	/* LCD interface, 24bpp */
	//{0xD, 0, ( SCU_MODE_PULLUP | SCU_MODE_FUNC4)}, //LCD_RESET @ PD.0 ,Stan Mask, unused
	{0x4, 7, ( SCU_MODE_PULLUP | SCU_MODE_FUNC0)}, //LCD_DCLK @ P4.7
	{0x7, 0, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, //LCD_LE @ P7.0 ,Stan Mask, unused
	{0x4, 5, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, //LCD_FP @ P4.5
	{0x7, 6, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, //LCD_LP @ P7.6 
	{0x7, 7, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, //LCD_PWR @ P7.7 ,Stan Mask, unused
	{0x4, 6, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, //LCD_EN @ P4.6
	
	//{0x4, 1, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_0 @ P4.1 ,Stan Mask, unused
	//{0x4, 4, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_1 @ P4.4 ,Stan Mask, unused
	{0x4, 3, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_2 @ P4.3
	{0x4, 2, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_3 @ P4.2
	{0x8, 7, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_4 @ P8.7
	{0x8, 6, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_5 @ P8.6
	{0x8, 5, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_6 @ P8.5
	{0x8, 4, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_7 @ P8.4
	//{0x7, 5, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_8 @ P7.5 ,Stan Mask,unused
	//{0x4, 8, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_9 @ P4.8 ,Stan Mask,unused
	{0x4, 10, (SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_10 @ P4.10 
	{0x4, 9, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_11 @ P4.9 
	{0x8, 3, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_12 @ P8.3 
	{0xB, 6, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_13 @ PB.6 
	{0xB, 5, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_14 @ PB.5 
	{0xB, 4, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_15 @ PB.4 
	//{0x7, 4, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_16 @ P7.4 ,Stan Mask, unused
	//{0x7, 3, ( SCU_MODE_PULLUP | SCU_MODE_FUNC0)}, // LCD_VD_17 @ P7.3 ,Stan Mask, unused
	{0x7, 2, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_18 @ P7.2 
	{0x7, 1, ( SCU_MODE_PULLUP | SCU_MODE_FUNC3)}, // LCD_VD_19 @ P7.1 
	{0xB, 3, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_20 @ PB.3 
	{0xB, 2, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_21 @ PB.2 
	{0xB, 1, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_22 @ PB.1 
	{0xB, 0, ( SCU_MODE_PULLUP | SCU_MODE_FUNC2)}, // LCD_VD_23 @ PB.0 
	
	
	/* Board LEDs */
	{0xE, 9, ( SCU_MODE_INBUFF_EN | SCU_MODE_PULLDOWN | SCU_MODE_FUNC4)},   // P7.9
	{0xE,10, ( SCU_MODE_INBUFF_EN | SCU_MODE_PULLDOWN | SCU_MODE_FUNC4)},	// P7.10
	{0xF, 5, ( SCU_MODE_INBUFF_EN | SCU_MODE_PULLDOWN | SCU_MODE_FUNC4)},	// P7.19
	{0xF, 6, ( SCU_MODE_INBUFF_EN | SCU_MODE_PULLDOWN | SCU_MODE_FUNC4)},	// P7.20
	{0xF, 7, ( SCU_MODE_INBUFF_EN | SCU_MODE_PULLDOWN | SCU_MODE_FUNC4)},	// P7.21
	{0xF, 8, ( SCU_MODE_INBUFF_EN | SCU_MODE_PULLDOWN | SCU_MODE_FUNC4)},	// P7.22
};

/* Pin clock mux values, re-used structure, value in first index is meaningless */
STATIC const PINMUX_GRP_T pinclockmuxing[] = {
	{0, 0,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC0)},
	{0, 1,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC0)},
	{0, 2,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC0)},
	{0, 3,  (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_HIGHSPEEDSLEW_EN | SCU_MODE_FUNC0)},
};

/* EMC clock delay */
#define CLK0_DELAY 7


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Setup system clocking */
void Board_SetupXtalClocking(void)
{
	int i;

	/* Switch main system clocking to crystal */
	Chip_Clock_EnableCrystal();
	Chip_Clock_SetBaseClock(CLK_BASE_MX, CLKIN_CRYSTAL, true, false);

	/* Setup PLL for 100MHz and switch main system clocking */
	Chip_Clock_SetupMainPLLHz(CLKIN_CRYSTAL, OscRateIn, 100 * 1000000, 100 * 1000000);
	Chip_Clock_SetBaseClock(CLK_BASE_MX, CLKIN_MAINPLL, true, false);

	/* Setup PLL for maximum clock */
	Chip_Clock_SetupMainPLLHz(CLKIN_CRYSTAL, OscRateIn, MAX_CLOCK_FREQ, MAX_CLOCK_FREQ);

	/* Setup system base clocks and initial states. This won't enable and
	   disable individual clocks, but sets up the base clock sources for
	   each individual peripheral clock. */
	for (i = 0; i < (sizeof(InitClkStates) / sizeof(InitClkStates[0])); i++) {
		Chip_Clock_SetBaseClock(InitClkStates[i].clk, InitClkStates[i].clkin,
								InitClkStates[i].autoblock_enab, InitClkStates[i].powerdn);
	}

	/* Reset and enable 32Khz oscillator */
	LPC_CREG->CREG0 &= ~((1 << 3) | (1 << 2));
	LPC_CREG->CREG0 |= (1 << 1) | (1 << 0);

	/* SPIFI pin setup is done prior to setting up system clocking */
	for (i = 0; i < (sizeof(spifipinmuxing) / sizeof(spifipinmuxing[0])); i++) {
		Chip_SCU_PinMuxSet(spifipinmuxing[i].pingrp, spifipinmuxing[i].pinnum,
						   spifipinmuxing[i].modefunc);
	}

	/* Setup a divider E for main PLL clock switch SPIFI clock to that divider.
	   Divide rate is based on CPU speed and speed of SPI FLASH part. */
#if (MAX_CLOCK_FREQ > 180000000)
	Chip_Clock_SetDivider(CLK_IDIV_E, CLKIN_MAINPLL, 5);
#else
	Chip_Clock_SetDivider(CLK_IDIV_E, CLKIN_MAINPLL, 4);
#endif
	Chip_Clock_SetBaseClock(CLK_BASE_SPIFI, CLKIN_IDIVE, true, false);

	/* Attach main PLL clock to divider C with a divider of 2 */
	Chip_Clock_SetDivider(CLK_IDIV_C, CLKIN_MAINPLL, 2);
}

/* Setup system clocking */
void Board_SetupIrcClocking(void)
{}

/* Sets up system pin muxing */
void Board_SetupMuxing(void)
{
	int i;

	/* Setup system level pin muxing */
	Chip_SCU_SetPinMuxing(pinmuxing, sizeof(pinmuxing) / sizeof(PINMUX_GRP_T));

	/* Clock pins only */
	for(i=0; i< sizeof(pinclockmuxing) / sizeof(PINMUX_GRP_T); i++)
	{
		Chip_SCU_ClockPinMuxSet(pinclockmuxing[i].pinnum, pinclockmuxing[i].modefunc);
	}
}

/* Setup external memories */
void Board_SetupExtMemory(void)
{
	/* Setup EMC Delays */
	/* Move all clock delays together */
	LPC_SCU->EMCDELAYCLK = ((CLK0_DELAY) | (CLK0_DELAY << 4) | (CLK0_DELAY << 8) | (CLK0_DELAY << 12));
	

	/* Setup EMC Clock Divider for divide by 2 - this is done in both the CCU (clocking)
       and CREG. For frequencies over 120MHz, a divider of 2 must be used. For frequencies
	   less than 120MHz, a divider of 1 or 2 is ok. */
	Chip_Clock_EnableOpts(CLK_MX_EMC_DIV, true, true, 2);
	LPC_CREG->CREG6 |= (1 << 16);

	/* Enable EMC clock */
	Chip_Clock_Enable(CLK_MX_EMC);

	/* Init EMC Controller -Enable-LE mode */
	//Chip_EMC_Init(1, 0, 0);
	/* Init EMC Dynamic Controller */
	//Chip_EMC_Dynamic_Init((IP_EMC_DYN_CONFIG_T *) &EM63A165TS_6G_config);
	/* Init EMC Static Controller CS2 */
	//Chip_EMC_Static_Init((IP_EMC_STATIC_CONFIG_T *) &IS62WV25616_config);
	/* Init EMC Static Controller CS0 */
	//Chip_EMC_Static_Init((IP_EMC_STATIC_CONFIG_T *) &SST39VF320_config);

	/* Enable Buffer for External Flash */
	//LPC_EMC->STATICCONFIG0 |= 1 << 19;
}

/* Set up and initialize hardware prior to call to main */
void Board_SystemInit(void)
{
	#define SDRAM_TEST_SIZE (0x02000000 >> 2)
	unsigned long *pSDRAM;
	unsigned long i;
  char cString[32];
  
	/* Setup system clocking and memory. This is done early to allow the
	   application and tools to clear memory and use scatter loading to
	   external memory. */
	Board_SetupXtalClocking();
	SystemCoreClockUpdate();
	Board_SetupMuxing();
	DEBUGINIT();
	DEBUGSTR("UART0 is up\r\n");
	
	usprintf(cString, "CPU @ %d Hz\r\n", SystemCoreClock);
	DEBUGSTR(cString);
	
	// Initialise the external memory interface (static and dynamic).
	// A check for defines (e.g. EXT_STAT_MEMetc) will be done in EMC_Init().
	Board_SetupExtMemory();
	DEBUGSTR("Set EMC Clock is done\r\n");
	EMC_Init(); 
	DEBUGSTR("Ext Memory is done\r\n");
	usprintf(cString, "SDRAM @ %d Hz\r\n", Chip_Clock_GetEMCRate());
	DEBUGSTR(cString);
	
	DEBUGSTR("SDRAM test start...\r\n");
	//SDRAM test
	pSDRAM = (void*)0x28000000;
	// Write Data
	for(i=0; i< SDRAM_TEST_SIZE; i++)
	{
		pSDRAM[i] = i;
	}
	// Read back and compare
	for(i=0; i< SDRAM_TEST_SIZE; i++)
	{
		if( pSDRAM[i] != i )
		{
			DEBUGOUT("SDRAM_Test_Fail Address = 0x%lx !\r\n", i << 2);
			break;
		}
		else
		{
		    pSDRAM[i] = 0;
		}
	}
	if( i == SDRAM_TEST_SIZE)
	{
		DEBUGSTR("SDRAM_Test OK.\r\n");
	}
}
