#include "FreeRTOS.h"
#include "task.h"
#include "GUI.h"
#include "WM.h"
#include "UI_Entry.h"


/**********************************************************************
* GUI Task processing
*
* This task does the background processing.
* The main job is to update invalid windows, but other things such as
* evaluating mouse or touch input may also be done.
*/
static void GUI_task (void *pvParameters)
{
    int i,j;
    
    (void) pvParameters;
    
    DEBUGSTR("GUI_task() Enrty.\r\n");
    
    WM_SetCreateFlags(WM_CF_MEMDEV);
    
    GUI_Init();
    
    WM_SetDesktopColor(GUI_BLACK);
    GUI_Clear();
    GUI_Delay(100);
    
    DEBUGSTR("GUI_Init() is done.\r\n");
    DEBUGOUT("emWin version: %s\r\n", GUI_GetVersionString());
    GUI_SetFont(&GUI_Font20_ASCII);
    GUI_DispStringAt("emWin Version: ",350,286);
    GUI_DispString(GUI_GetVersionString());
    GUI_Delay(100);
    
    UI_Entry();
    
    DEBUGSTR("GUI_Task() While loop start...\r\n");
    
    i=0, j=0;
    while(1)
    {
        GUI_Exec(); /* Do the background work ... Update windows etc.) */
        GUI_X_ExecIdle(); /* Nothing left to do for the moment ... Idle processing */
        if(++i > 1000)
        {
            i=0;
            DEBUGOUT("GUI_Task() loop %d times.\r\n", ++j);
        }
    }
}

int GUI_User_Task_Init(void)
{
    int i;
    /* UART output thread, simply counts seconds */
	i = xTaskCreate(GUI_task, (signed char *) "GUI_task", 2048, NULL, (tskIDLE_PRIORITY + 2UL),	(xTaskHandle *) NULL);
	return i;
}
