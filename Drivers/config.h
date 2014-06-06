/***********************************************************************
 * $Id:  config.h
 *
 * Project: NXP LPC4300 LCD example
 *
 * Description: Platform specific definitions
 *
 * Copyright(C) 2011, NXP Semiconductor
 * All rights reserved.
 *
 ***********************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

#ifndef __CONFIG_H
#define __CONFIG_H


#define RTC_CLK     (   32768UL)        // RTC oscillator frequency          
#define IRC_OSC     (12000000UL)        // Internal RC oscillator frequency  
#define IRC_TRIM_VAL 0x34A 				// IRC trim value for 12MHz output   
#define XTAL_FREQ	(12000000UL)		// Frequency of external xtal 


#endif /* end __CONFIG_H */

