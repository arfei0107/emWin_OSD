#ifndef __xDIALOG_H__
#define __xDIALOG_H__

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"
#include "Custom_Widget.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


/*********************************************************************
*
*       xDIALOGBOX_Obj
*/
typedef struct {
  const GUI_WIDGET_CREATE_INFO  *paWidget;
  int                            NumWidgets;
  WM_CALLBACK                   *cb;
}xDIALOGBOX_Obj;

WM_HWIN xCreateDialogBoxArray(const xDIALOGBOX_Obj* paDialogBox, 
                              int NumDialogBox,
                              WM_CALLBACK* cb,
                              WM_HWIN hParent,
                              int x0, int y0);

#endif
