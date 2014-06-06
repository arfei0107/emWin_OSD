#ifndef __xMUITIPAGE_H__
#define __xMUITIPAGE_H__

#include "WM.h"
#include "DIALOG.h"      /* Req. for Create indirect data structure */
#include "GUI_ARRAY.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

#define MULTIPAGE_STATE_SCROLLMODE  WIDGET_STATE_USER0

typedef enum
{
    NOT_SELECTED = 0,
    SELECTED     = 1,
    ENTERED      = 2
}eMULTIPAGE_PAGE_STATE;


#define xMULTIPAGE_Max_Page 10
/* Define colors */
#define MULTIPAGE_NUMCOLORS 2

/*********************************************************************
*
* WIDGET_SLIDER1_Obj
*/
typedef struct
{
    eMULTIPAGE_PAGE_STATE PageState[xMULTIPAGE_Max_Page];
    const GUI_BITMAP* pBmpTable[xMULTIPAGE_Max_Page][3];
    GUI_COLOR PageTextColor[3];
    GUI_COLOR PageIconAreaBkColor;
    GUI_COLOR PageWinBkColor;
    GUI_RECT  PageIconAreaRect;
    GUI_RECT  PageWinRect;
} WIDGET_MULTIPAGE_Obj;


/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WM_HWIN hWin;
  U8      Status;
  char    acText;
} MULTIPAGE_PAGE;


typedef struct {
  WIDGET          Widget;
  WM_HWIN         hClient;
  GUI_ARRAY       Handles;
  unsigned        Selection;
  int             ScrollState;
  unsigned        Align;
  const GUI_FONT GUI_UNI_PTR * Font;
  GUI_COLOR       aBkColor[MULTIPAGE_NUMCOLORS];
  GUI_COLOR       aTextColor[MULTIPAGE_NUMCOLORS];
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} MULTIPAGE_Obj;

#define MULTIPAGE_H2P(h) (MULTIPAGE_Obj*) WM_H2P(h)

void xMultiPage_Callback(WM_MESSAGE * pMsg);

#endif
