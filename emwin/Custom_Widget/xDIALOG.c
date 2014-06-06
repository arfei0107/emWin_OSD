/*********************************************************************
*                Golden-IC Technology Co.,Ltd                        *
*                       www.golden-ic.com                            *
**********************************************************************
*        (c) 2007 - 2014 Golden-IC Technology Co., Ltd               *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: xDIALOG.c                                             *
*                                                                    *
**********************************************************************
*/

#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include "GUI.h"
#include "WM.h"
#include "xDIALOG.h"
#include "board.h"

#if 1
#undef  DEBUGOUT
#undef  DEBUGSTR
#define DEBUGOUT(...)
#define DEBUGSTR(str)
#endif
/*********************************************************************
*
*       xCreateDialogBoxArray
*/
WM_HWIN xCreateDialogBoxArray(const xDIALOGBOX_Obj* paDialogBox,
                              int NumDialogBox,
                              WM_CALLBACK* cb,
                              WM_HWIN hParent,
                              int x0, int y0)
{
    WM_HWIN hDialog;
    WM_HWIN hDialogClient;
    
    if((NumDialogBox <= 0) || (paDialogBox==NULL) || (paDialogBox->paWidget->pfCreateIndirect==NULL) )return 0;
    
    //Creat Parent Window
    DEBUGOUT("xCreateDialogBoxArray: Create Parent Win\r\n");
    hDialog = paDialogBox->paWidget->pfCreateIndirect(paDialogBox->paWidget, hParent, x0, y0, cb);     /* Create parent window */
    hDialogClient = WM_GetClientWindow(hDialog);
    WIDGET_OrState(hDialog, paDialogBox->paWidget->Flags);
    WM_ShowWindow(hDialog);
    WM_ShowWindow(hDialogClient);
  
    while (--NumDialogBox > 0)
    {
        WM_HWIN hChildDialog;
        paDialogBox++;
        DEBUGOUT("xCreateDialogBoxArray: Create Child DownCounter:%d\r\n", NumDialogBox);
        hChildDialog = GUI_CreateDialogBox(paDialogBox->paWidget, paDialogBox->NumWidgets, paDialogBox->cb, hDialogClient, 0, 0); /* Create child Dialog */
        WM_ShowWindow(hChildDialog);
    }
    DEBUGOUT("xCreateDialogBoxArray: Create Child DownCounter:%d\r\n", NumDialogBox);
    DEBUGOUT("xCreateDialogBoxArray: Create Child OK\r\n", NumDialogBox);
    WM_SetFocusOnNextChild(hDialog);     /* Set the focus to the first child */
    WM_SendMessageNoPara(hDialogClient, WM_INIT_DIALOG);
    return hDialog;
}

