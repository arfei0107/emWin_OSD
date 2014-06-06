#ifndef __xDROPDOWN_H__
#define __xDROPDOWN_H__

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"
#include "Custom_Widget.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

typedef enum
{
    xDROPDOWN_ITEM_DISABLE = 0,
    xDROPDOWN_ITEM_ENABLE  = 1,
}eDROPDOWN_ITEM_STATE;


typedef enum
{
    xDROPDOWN_DISABLE = 0,
    xDROPDOWN_ENABLE  = 1,
    xDROPDOWN_FOCUSED = 2,
    xDROPDOWN_PRESSED = 3
}eDROPDOWN_STATE;


typedef struct
{
    const char *pText;
    eDROPDOWN_ITEM_STATE  State;
}xDROPDOWN_ITEM;


/*
typedef struct
{
    xDROPDOWN_ITEM *paDropDownItems;
    int NumItems;
}xDROPDOWN_ITEM_LIST;
*/

typedef struct
{
    eDROPDOWN_STATE      State;
    xDROPDOWN_ITEM      *paDropDownItems;
    int                  NumItems;
    
    GUI_CONST_STORAGE GUI_BITMAP* pBtnBmp;
    GUI_COLOR            BarBkColor;
    GUI_COLOR            BarTextColor[4];
    const GUI_FONT      *pBarTextFont;
    
    GUI_RECT             ListBoxRect;
    GUI_COLOR            ListBoxRectBkColor[2]; //Color[0]: Outline, Color[1]:Fill RECT
    GUI_COLOR            ListBoxTextColor[3];
    const GUI_FONT      *pListBoxTextFont;
    int                  ListBoxItemHeight;
    int                  ListBoxItemAlignY0;
    int                  ListBoxTextAlignX0;
    int                  ListBoxItemFocusBmpAlignX0;
    int                  ListBoxIdx;
    GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemFocusBmp;
    
    int                  ListBoxItemCheckedBmpAlignX0;
    int                  ListBoxItemCheckedBmpAlignY0;
    GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemCheckedBmp;
    
    WM_HWIN              hListBox;
    WM_HWIN              hDropdown;
    int                  WidgetInit;
}xDROPDOWN_Obj;

void xDROPDOWN_Callback(WM_MESSAGE * pMsg);

#endif
