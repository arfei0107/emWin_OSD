#ifndef __xBUTTON_H__
#define __xBUTTON_H__

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"
#include "Custom_Widget.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

typedef enum
{
    xBUTTON_DISABLE = 0,
    xBUTTON_NORMAL  = 1,
    xBUTTON_FOCUSED = 2,
    xBUTTON_PRESSED = 3,
}eBUTTON_STATE;


/*********************************************************************
*
*       Color indices
*/
#define xBUTTON_CI_UNPRESSED 0
#define xBUTTON_CI_PRESSED   1
#define xBUTTON_CI_DISABLED  2

/*********************************************************************
*
*       Typedef
*/
typedef WM_HMEM xBUTTON_Handle;

/*********************************************************************
*
*       xBUTTON_Obj
*/
typedef struct {
  eBUTTON_STATE eButtonState;
  GUI_CONST_STORAGE GUI_BITMAP* aBmp[4];
  const char     *pText;
  int             TextAlign;
  GUI_RECT        TextRect;
  const GUI_FONT *pFont;
  GUI_COLOR       aTextColor[4];
  int             NumExtraBytes;
}xBUTTON_Obj;

//#define SLIDER_H2P(h) (SLIDER_Obj*) GUI_ALLOC_h2p(h)

/*********************************************************************
*
*       Public Functions
*/
xBUTTON_Handle xBUTTON_CreateEx(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id);
xBUTTON_Handle xBUTTON_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
int xBUTTON_GetUserData(xBUTTON_Handle hWin, void * pDest, int SizeOfBuffer);
int xBUTTON_SetUserData(xBUTTON_Handle hWin, void * pSrc, int SizeOfBuffer);
    
#endif
