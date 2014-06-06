#ifndef __xKB_BUTTON_H__
#define __xKB_BUTTON_H__

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"
#include "Custom_Widget.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


#define xKB_BTN_H2P(h) ((xKB_BTN_Obj*) GUI_ALLOC_h2p(h))

typedef enum
{
    xKB_BTN_DISABLE = 0,
    xKB_BTN_NORMAL  = 1,
    xKB_BTN_FOCUSED = 2,
    xKB_BTN_PRESSED = 3,
}eKB_BTN_STATE;

typedef struct
{
    int x;
    int y;
    
}tKB_XY;


typedef struct
{
    WM_HWIN *pKB_Table;
    tKB_XY   KB_TableSize;
    tKB_XY   KB_KeyPosition;
    int      KeyCode;
}tKB_DATA;


typedef struct
{
    const char *pBtnText;
    int         KeyCode;
}tKB_KEY;


/*********************************************************************
*
*       Typedef
*/
typedef WM_HMEM xKB_BTN_Handle;

/*********************************************************************
*
*       xKB_BTN_OBJ
*/
typedef struct {
  WIDGET Widget;
  eKB_BTN_STATE eButtonState;
  GUI_CONST_STORAGE GUI_BITMAP* aBmp[4];
  const char     *pText;
  int             TextAlign;
  GUI_RECT        TextRect;
  const GUI_FONT *pFont;
  GUI_COLOR       aTextColor[4];
  GUI_COLOR       aBkColor[4];
  tKB_DATA        KB_SoftKey;
  int             NumExtraBytes;
}xKB_BTN_Obj;

/*********************************************************************
*
*       Public Functions
*/
xKB_BTN_Handle xKB_BTN_CreateEx(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id);
xKB_BTN_Handle xKB_BTN_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
int xKB_BTN_GetUserData(xKB_BTN_Handle hWin, void * pDest, int SizeOfBuffer);
int xKB_BTN_SetUserData(xKB_BTN_Handle hWin, void * pSrc, int SizeOfBuffer);

#endif
