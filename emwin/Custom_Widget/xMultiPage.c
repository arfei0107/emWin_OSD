/*********************************************************************
*                Golden-IC Technology Co.,Ltd                        *
*                       www.golden-ic.com                            *
**********************************************************************
*        (c) 2007 - 2014 Golden-IC Technology Co., Ltd               *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: MultiPage.c                                           *
*                                                                    *
**********************************************************************
*/
#include <string.h>
#include "GUI.h"
#include "MULTIPAGE.h"
#include "xMultiPage.h"
#include "board.h"

#if 1
#undef  DEBUGOUT
#undef  DEBUGSTR
#define DEBUGOUT(...)
#define DEBUGSTR(str)
#endif

/*********************************************************************
*
*       _xMultiPage_Create
*/

static void _xMultiPage_Create(MULTIPAGE_Obj* pObj, WM_HWIN hObj, WIDGET_MULTIPAGE_Obj *ptWidget)
{
    static GUI_RECT r;
    static WM_HWIN hPageWin;
    static int fInitSet = 0;
    int xsize, ysize;
    
    if( fInitSet == 0)
    {
        hPageWin = WM_GetFirstChild(hObj);
        WM_GetWindowRectEx(hPageWin, &r);
        r.y0 += ptWidget->pBmpTable[0][SELECTED]->YSize - GUI_GetYSizeOfFont(pObj->Font);
        fInitSet = 1;
    }
    DEBUGOUT("ClientWIN(%d,%d,%d,%d)\r\n",r.x0, r.y0, r.x1, r.y1);
    xsize = r.x1 - r.x0;
    ysize = r.y1 - r.y0;
    WM_SetWindowPos(hPageWin, r.x0, r.y0, xsize, ysize);
}


/*********************************************************************
*
*       _Paint
*/
static void _Paint(MULTIPAGE_Obj* pObj, WM_HWIN hObj)
{
    static WIDGET_MULTIPAGE_Obj tWidget;
    static char PageText[32];
    GUI_CONST_STORAGE GUI_BITMAP *pBmp;
    WM_HWIN hPageWin;
    GUI_RECT r, PageWinRect;//,TextRect;
    int i, x0;
    
    hPageWin = WM_GetFirstChild(hObj);
    
    WIDGET__GetClientRect(&pObj->Widget, &r);
    
    MULTIPAGE_GetUserData(hObj, &tWidget, sizeof(WIDGET_MULTIPAGE_Obj));
    
    DEBUGOUT("xMultiPage():_Paint: WIN(%d,%d,%d,%d)\r\n",r.x0, r.y0, r.x1, r.y1);
    
    DEBUGOUT("xMultiPage():_Paint: Re-size PageWin\r\n");
    PageWinRect = tWidget.PageWinRect;
    WM_SetWindowPos(hPageWin, PageWinRect.x0, PageWinRect.y0, PageWinRect.x1 - PageWinRect.x0, PageWinRect.y1 - PageWinRect.y0);
    DEBUGOUT("\tPageWIN(%d,%d,%d,%d)\r\n",PageWinRect.x0, PageWinRect.y0, PageWinRect.x1, PageWinRect.y1);
    
    GUI_SetColor(tWidget.PageIconAreaBkColor);
    GUI_FillRectEx(&tWidget.PageIconAreaRect);
    
    x0 = r.x0 + 2;
    for (i = 0; tWidget.pBmpTable[i][NOT_SELECTED] != NULL; i++)
    {
        DEBUGOUT("\tDraw Page Icon:%d\r\n",i);
        if(i == MULTIPAGE_GetSelection(hObj))
        {
            pBmp = (tWidget.PageState[i] == ENTERED) ?  tWidget.pBmpTable[i][ENTERED] : tWidget.pBmpTable[i][SELECTED];
            GUI_DrawBitmap(pBmp, x0, r.y0);
            //Draw Page Text
            MULTIPAGE_GetPageText(hObj, i, PageText, sizeof(PageText));
            DEBUGOUT("\t    PageText:%s\r\n",PageText);
            
            GUI_SetFont(pObj->Font);
            GUI_SetColor((tWidget.PageState[i] == ENTERED) ? tWidget.PageTextColor[ENTERED] : tWidget.PageTextColor[SELECTED]);
            GUI_SetTextMode(GUI_TM_TRANS);
            GUI_DispStringAt(PageText, x0 + ((pBmp->XSize - GUI_GetStringDistX(PageText))/2), r.y0 + pBmp->YSize - GUI_GetYSizeOfFont(pObj->Font) - 10);
            
            x0 += pBmp->XSize + 7;
        }
        else
        {
            tWidget.PageState[i] = NOT_SELECTED;
            MULTIPAGE_SetUserData(hObj, &tWidget, sizeof(WIDGET_MULTIPAGE_Obj));
            
            pBmp = tWidget.pBmpTable[i][NOT_SELECTED];
            GUI_DrawBitmap(pBmp, x0, r.y0 + (tWidget.pBmpTable[i][ENTERED]->YSize - pBmp->YSize)/2);
            
            x0 += pBmp->XSize + 14;
        }
    }
}


/*********************************************************************
*
*       _xMultiPage_KeyProcess
*/
static void _xMultiPage_KeyProcess(WM_HWIN hObj, int Key)
{
    static WIDGET_MULTIPAGE_Obj tWidget;
    int PageIdx;
    
    MULTIPAGE_GetUserData(hObj, &tWidget, sizeof(WIDGET_MULTIPAGE_Obj));
    PageIdx = MULTIPAGE_GetSelection(hObj);
    
    switch(Key)
    {
      case GUI_KEY_ENTER:
        DEBUGOUT("Page(%d):Enter\r\n", PageIdx);
        //memset(&tWidget.PageState[0], NOT_SELECTED, sizeof(tWidget.PageState));
        GUI__memset((U8*)&tWidget.PageState[0], 0, sizeof(tWidget.PageState));
        tWidget.PageState[PageIdx] = ENTERED;
        MULTIPAGE_SetUserData(hObj, &tWidget, sizeof(WIDGET_MULTIPAGE_Obj));
        WM_InvalidateWindow(hObj);
        break;
      case GUI_KEY_ESCAPE:
        DEBUGOUT("Page(%d):Esc\r\n", PageIdx);
        tWidget.PageState[PageIdx] = SELECTED;
        MULTIPAGE_SetUserData(hObj, &tWidget, sizeof(WIDGET_MULTIPAGE_Obj));
        WM_InvalidateWindow(hObj);
        break;
    }

}


void xMultiPage_Callback(WM_MESSAGE * pMsg)
{
    MULTIPAGE_Handle hObj = pMsg->hWin;
    MULTIPAGE_Obj* pObj;
    const WM_KEY_INFO * pInfo;
    WM_HWIN hScrollBar;
    int PageNum;
    
    pObj    = MULTIPAGE_H2P(hObj);
    
    if( (hScrollBar = WM_GetScrollbarH(hObj)) != 0)
    {
        if(WM_IsVisible(hScrollBar))
        {
            WM_HideWindow(hScrollBar);
            DEBUGOUT("Hide MPage Scrollbar\r\n");
        }
    }
    
    switch (pMsg->MsgId)
    {
      case WM_PAINT:
        _Paint(pObj, hObj);
        break;
      case WM_KEY:
        pInfo = pMsg->Data.p;
        switch(pInfo->Key)
        {
          case GUI_KEY_ENTER:
          case GUI_KEY_ESCAPE:
            if(pInfo->PressedCnt >0)
            {
                _xMultiPage_KeyProcess(hObj, pInfo->Key);
            }
            break;
          
          case GUI_KEY_LEFT:
            PageNum = MULTIPAGE_GetSelection(hObj);
            if(PageNum > 0) 
            {
                PageNum--;
            }
            else
            {
                PageNum = 6;
            }
            MULTIPAGE_SelectPage(hObj, PageNum);
            break;
            
          case GUI_KEY_RIGHT:
            PageNum = MULTIPAGE_GetSelection(hObj);
            if(++PageNum >= 6) 
            {
                PageNum = 0;
            }
            MULTIPAGE_SelectPage(hObj, PageNum);
            break;
            
          case GUI_KEY_PGUP:
          case GUI_KEY_PGDOWN:
            break;
            
          default:
            MULTIPAGE_Callback(pMsg);
            break;
        }
        break;
         
      default:
        MULTIPAGE_Callback(pMsg);
        break;
    }
}
  

   
    
/*************************** End of file ****************************/
