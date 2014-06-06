#ifndef __xIconSelBtn_H__
#define __xIconSelBtn_H__

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
typedef WM_HMEM xIconSelBtn_Handle;

typedef struct
{
  GUI_CONST_STORAGE GUI_BITMAP* pBMP;
  int x0;
  int y0;
}xICON;

typedef struct
{
  int x0;
  int y0;
}xICON_CHECK_XY;

/*********************************************************************
*
*       xIconSelBtn_OBJ
*/
typedef struct {
  xICON xIconArray[10];
  xICON_CHECK_XY xIconCheckXyArray[10];
  GUI_COLOR aBkColor[4];
  GUI_CONST_STORAGE GUI_BITMAP* pBkBMP;
  GUI_CONST_STORAGE GUI_BITMAP* pCheckedBMP;
  int MovingIndex;
  int SelectedIndex;
  int NumItems;
  int IconFocusFrameHWidth;
  int IconFocusFrameVWidth;
  GUI_RECT PopupWinRECT;
  GUI_COLOR PopupWinBkColor[2];
  GUI_COLOR PopupWinIconFocusColor;
  WM_HWIN hPopupWin;
  WM_HWIN hThis;
}xIconSelBtn_OBJ;

/*********************************************************************
*
*       Public Functions
*/
void xIconSelBtn_Callback(WM_MESSAGE * pMsg);

#endif
