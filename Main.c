/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
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
#include "FreeRTOS.h"
#include "task.h"
#include "GUI.h"
#include "GUI_User_Task.h"

static int KeyCode2GUI_KeyCode_Table[18][2]=
{
  {8,        GUI_KEY_BACKSPACE},
  {9,        GUI_KEY_TAB      },
  {13,       GUI_KEY_ENTER    },
  {0x5B44,   GUI_KEY_LEFT     },
  {0x5B41,   GUI_KEY_UP       },
  {0x5B43,   GUI_KEY_RIGHT    },
  {0x5B42,   GUI_KEY_DOWN     },
  {0x5B31,   GUI_KEY_HOME     },
  {0x5B34,   GUI_KEY_END      },
  {16,       GUI_KEY_SHIFT    },
  {17,       GUI_KEY_CONTROL  },
  {27,       GUI_KEY_ESCAPE   },
  {0x5B32,   GUI_KEY_INSERT   },
  {0x7F,     GUI_KEY_DELETE   },
  {32,       GUI_KEY_SPACE    },
  {0x5B35,   GUI_KEY_PGUP     },
  {0x5B36,   GUI_KEY_PGDOWN   },
  {0,0},
};

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	
	DEBUGOUT("CPU @ %d Hz\r\n", SystemCoreClock);
	DEBUGOUT("MainPLL: %u Hz\r\n",Chip_Clock_GetClockInputHz(CLKIN_MAINPLL));
	DEBUGOUT("LCD_CLK: %u Hz\r\n",Chip_Clock_GetRate(CLK_MX_LCD));
	DEBUGOUT("EMC_CLK: %u Hz\r\n",Chip_Clock_GetEMCRate());
	
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters)
{
	int i;
	
	DEBUGSTR("vLEDTask1() Enrty.\r\n");
	
	i=0;
	while (1)
	{
		Board_LED_Set(0, false);
		Board_LED_Set(1, false);
		Board_LED_Set(i++, true);
		
		if(i>=2) i=0;

		/* About a 3Hz on/off toggle rate */
		vTaskDelay(configTICK_RATE_HZ/2);
	}
}

/* LED2 toggle thread */
static void vLEDTask2(void *pvParameters) {
	int i;

	DEBUGSTR("vLEDTask2() Enrty.\r\n");
	
	i=2;
	while (1) {
		Board_LED_Set(2, false);
		Board_LED_Set(3, false);
		Board_LED_Set(4, false);
		Board_LED_Set(5, false);
		Board_LED_Set(i++, true);
		
		if(i>=6) i=2;

		/* About a 7Hz on/off toggle rate */
		vTaskDelay(configTICK_RATE_HZ/10);
	}
}

/* UART (or output) thread */
static void vUARTTask(void *pvParameters)
{
    int tickCnt = 0, _1secCnt = 0, i, extKey;
    char cKey, cKey1, cKey2;
    
    DEBUGSTR("vUARTTask() Enrty.\r\n");
    
    while (1)
    {
        if((cKey = DEBUGIN()) != ((char)EOF))
        {
            if(cKey == 0x0D)
            {
                if((cKey1 = DEBUGIN()) == 0x0A)
                {
                    extKey = 0x0D;
                }
                else
                {
                    extKey = 0x0D;
                }
            }
            else if(cKey == 27)
            {
                //check special code
                if( ((cKey1 = DEBUGIN()) != ((char)EOF)) && ((cKey2 = DEBUGIN()) != ((char)EOF)) )
                {
                    extKey = (int)cKey1<<8 | cKey2;
                }
                else
                {
                    extKey = (int)cKey;
                }
            }
            else
            {
                extKey = (int)cKey;
            }
            
            DEBUGOUT("\r\nKey:%x\r\n",extKey);
            
            for(i=0; i< (sizeof(KeyCode2GUI_KeyCode_Table)/2); i++)
            {
                if(extKey == KeyCode2GUI_KeyCode_Table[i][0])
                {
                    GUI_StoreKeyMsg(KeyCode2GUI_KeyCode_Table[i][1], 1);
                    GUI_StoreKeyMsg(KeyCode2GUI_KeyCode_Table[i][1], 0);
                    DEBUGOUT("GUI_Key:%d\r\n",KeyCode2GUI_KeyCode_Table[i][1]);
                    break;
                }
                else if(KeyCode2GUI_KeyCode_Table[i][0] == 0)
                {
                    GUI_StoreKeyMsg(extKey, 1);
                    GUI_StoreKeyMsg(extKey, 0);
                    break;
                }
            }
        }
        
        /* About a 1s delay here */
        vTaskDelay(configTICK_RATE_HZ/100);
        
        if(++_1secCnt == 100)
        {
            _1secCnt = 0;
            DEBUGOUT("Tick: %d \r\n", tickCnt++);
        }
        
    }
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	DEBUGSTR("Main() Entry point.\r\n");
	prvSetupHardware();
	DEBUGSTR("prvSetupHardware() is done.\r\n");
	
	/* LED1 toggle thread */
	xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
				(xTaskHandle *) NULL);
	
	DEBUGSTR("xTaskCreate() --> vLEDTask1() is done.\r\n");

	/* LED2 toggle thread */
	xTaskCreate(vLEDTask2, (signed char *) "vTaskLed2",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
				(xTaskHandle *) NULL);
	
	DEBUGSTR("xTaskCreate() --> vTaskLed2() is done.\r\n");

	/* UART output thread, simply counts seconds */
	xTaskCreate(vUARTTask, (signed char *) "vTaskUart",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 4UL),
				(xTaskHandle *) NULL);
				
    DEBUGSTR("xTaskCreate() --> vUARTTask() is done.\r\n");
				
	GUI_User_Task_Init();
	
	DEBUGSTR("GUI_Task_Init() is done.\r\n");
	
	DEBUGSTR("RTOS Scheduler is taking over control.\r\n");

	/* Start the scheduler */
	vTaskStartScheduler();
	
	DEBUGSTR("RTOS Scheduler is fault to stop and exit to Main()!\r\n");

	/* Should never arrive here */
	return 1;
}
