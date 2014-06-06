/***********************************************************************
 * $Id$   scu_LPC18xx_43xx.c
 *
 * Project: NXP LPC4300 LCD example
 *
 * Description:  Function to select and configure the required I/Os
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

#include "CMSIS.h"
#include "chip.h"
#include "type.h"




/**********************************************************************
 * Function name:		
 *
 * Description:		
 *						
 * Parameters:			
 *
 * Returned value:		
 **********************************************************************/
void scu_pinmux(unsigned port, unsigned pin, unsigned mode, unsigned func)
{
  volatile unsigned int * const scu_base=(unsigned int*)(LPC_SCU_BASE);
  scu_base[(PORT_OFFSET*port+PIN_OFFSET*pin)/4]=mode+func;
} 

