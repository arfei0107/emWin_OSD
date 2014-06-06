#ifndef __xMOVE_BUTTON_H__
#define __xMOVE_BUTTON_H__

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"
#include "Custom_Widget.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

typedef enum
{
    xM_BTN_DISABLE = 0,
    xM_BTN_NORMAL  = 1,
    xM_BTN_FOCUSED = 2,
    xM_BTN_PRESSED = 3,
}eMOVE_BTN_STATE;

typedef struct
{
    int Min;
    int Max;
}tV_RANGE;


typedef int (*xMOVE_BTN_SET_VALUE_cb)(WM_HWIN hWin);

/*********************************************************************
*
*       Typedef
*/
typedef WM_HMEM xMOVE_BTN_Handle;

/*********************************************************************
*
*       xBUTTON_Obj
*/
typedef struct {
  eMOVE_BTN_STATE eButtonState;
  GUI_CONST_STORAGE GUI_BITMAP* aBmp[4];
  const char     *pText;
  int             TextAlign;
  GUI_RECT        TextRect;
  const GUI_FONT *pFont;
  GUI_COLOR       aTextColor[4];
  GUI_COLOR       aBkColor[4];
  tV_RANGE        tVrange;
  int             VHeight;
  int             Vidx;
  int             BtnNum;
  xMOVE_BTN_SET_VALUE_cb pfSetValue;
  int             NumExtraBytes;
}xMOVE_BTN_Obj;

//#define SLIDER_H2P(h) (SLIDER_Obj*) GUI_ALLOC_h2p(h)

/*********************************************************************
*
*       Public Functions
*/
xMOVE_BTN_Handle xMOVE_BTN_CreateEx(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id);
xMOVE_BTN_Handle xMOVE_BTN_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
int xMOVE_BTN_GetUserData(xMOVE_BTN_Handle hWin, void * pDest, int SizeOfBuffer);
int xMOVE_BTN_SetUserData(xMOVE_BTN_Handle hWin, void * pSrc, int SizeOfBuffer);

#endif
