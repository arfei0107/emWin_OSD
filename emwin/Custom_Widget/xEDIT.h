#ifndef __xEDIT_H__
#define __xEDIT_H__

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"
#include "Custom_Widget.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


/*********************************************************************
*
*       Typedef
*/

/*********************************************************************
*
*       xEDIT_Obj
*/
typedef struct {
  GUI_CONST_STORAGE GUI_BITMAP* Bmp;
  const GUI_FONT *pFont;
  GUI_COLOR       TextColor;
  GUI_COLOR       aBkColor[4];
}xEDIT_Obj;

/*********************************************************************
*
*       Public Functions
*/
void xEDIT_Callback(WM_MESSAGE * pMsg);

#endif
