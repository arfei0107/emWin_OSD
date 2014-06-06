/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2011  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.12 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "GUI.h"



/*********************************************************************
*
*       Global data
*/


/*********************************************************************
*
*      Timing:
*                 GUI_X_GetTime()
*                 GUI_X_Delay(int)

  Some timing dependent routines require a GetTime
  and delay function. Default time unit (tick), normally is
  1 ms.
*/

int GUI_X_GetTime (void)
{ 
    return (int) xTaskGetTickCount(); 
}


void GUI_X_Delay (int ms)
{ 
		int configTICK_RATE_HZ = 1000;
    vTaskDelay((configTICK_RATE_HZ * ms)/1000);
}


/*********************************************************************
*
*       GUI_X_ExecIdle
*
* Note:
*  Called if WM is in idle state
*/

void GUI_X_ExecIdle(void)
{
    GUI_X_Delay(1);
}

/*********************************************************************
*
*      Multitasking:
*
*                 GUI_X_InitOS()
*                 GUI_X_GetTaskId()
*                 GUI_X_Lock()
*                 GUI_X_Unlock()
*
* Note:
*   The following routines are required only if emWin is used in a
*   true multi task environment, which means you have more than one
*   thread using the emWin API.
*   In this case the
*                       #define GUI_OS 1
*  needs to be in GUIConf.h
*/

xTaskHandle GUI_TASK_Handle;

static xSemaphoreHandle* pGUI_Semaphore;

void GUI_X_InitOS(void)
{
    pGUI_Semaphore = xSemaphoreCreateBinary();
    if(pGUI_Semaphore != NULL)
    {
        xSemaphoreGive(pGUI_Semaphore);
    }
    else
    {
        DEBUGSTR("GUI_X_InitOS():xSemaphoreCreateBinary() is failed!\r\n");
    }
}

void GUI_X_Unlock(void)
{
    if(pGUI_Semaphore)
    {
        if(xSemaphoreGive( pGUI_Semaphore ) != pdTRUE )
        {
            DEBUGSTR("GUI_X_Unlock():xSemaphoreGive() is failed!\r\n");
        }
    }
    else
    {
        DEBUGSTR("GUI_X_Unlock():pGUI_Semaphore is NULL!\r\n");
    }
}

void GUI_X_Lock(void)
{
    if(pGUI_Semaphore)
    {
        if( xSemaphoreTake( pGUI_Semaphore, configTICK_RATE_HZ * 2) == pdFALSE )
        {
            DEBUGSTR("GUI_X_Lock():xSemaphoreTake() 2 seconds is timeout!\r\n");
        }
    }
    else
    {
        DEBUGSTR("GUI_X_Lock():pGUI_Semaphore is NULL!\r\n");
    }
}

U32  GUI_X_GetTaskId(void)
{
    return 0;
    
}
/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/

void GUI_X_Log     (const char *s) { DEBUGSTR((char*)s); }
void GUI_X_Warn    (const char *s) { DEBUGSTR((char*)s); }
void GUI_X_ErrorOut(const char *s) { DEBUGSTR((char*)s); }

/*********************************************************************
*
*       GUI_X_Init()
*
* Note:
*     GUI_X_Init() is called from GUI_Init is a possibility to init
*     some hardware which needs to be up and running before the GUI.
*     If not required, leave this routine blank.
*/

void GUI_X_Init(void) { }

/*************************** End of file ****************************/



