/*********************************************************************
*                Golden-IC Technology Co.,Ltd                        *
*                       www.golden-ic.com                            *
**********************************************************************
*        (c) 2007 - 2014 Golden-IC Technology Co., Ltd               *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: xBUTTON.c                                           *
*                                                                    *
**********************************************************************
*/
#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include "GUI.h"
#include "WM.h"
#include "xKBbtn.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "board.h"

#if 0
#undef  DEBUGOUT
#undef  DEBUGSTR
#define DEBUGOUT(...)
#define DEBUGSTR(str)
#endif

/*********************************************************************
*
*       xBUTTON_Default
*/
const xKB_BTN_Obj xKB_BTN_Default =
{
  {0},
	xKB_BTN_NORMAL,                                           //eKB_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR2, GUI_UI_COLOR11, GUI_UI_COLOR11},  //aBkColor[4];
  {                                                 //tKB_DATA KB_SoftKey
    NULL,                                           //WM_HWIN*pKB_Table
    {0,0},                                          //tKB_XY  KB_TableSize;
    {0,0},                                          //tKB_XY  KB_KeyPosition;
    0x00,                                            //int     KeyCode;
  },
  0                                                 //NumExtraBytes;
};


/*********************************************************************
*
*       _Paint
*/
static void _Paint(xKB_BTN_Handle hWin, xKB_BTN_Obj *pWidget)
{
    GUI_RECT          WinRect;
    
    DEBUGOUT("xKBbtn hWin = 0x%08x\r\n", hWin);
    WM_GetWindowRectEx(hWin, &WinRect);
    GUI_MoveRect(&WinRect, -WinRect.x0, -WinRect.y0);
    DEBUGOUT("xKBbtnPaint(%d,%d,%d,%d)\r\n",WinRect.x0, WinRect.y0, WinRect.x1, WinRect.y1);
  
    if(pWidget->aBmp[pWidget->eButtonState])
    {
        DEBUGOUT("xKBbtn State: %d\r\n",pWidget->eButtonState);
        DEBUGOUT("xKBbtnPaint(pBmp:0x%08x)\r\n",(U32)(pWidget->aBmp[pWidget->eButtonState]));
        GUI_DrawBitmap(pWidget->aBmp[pWidget->eButtonState], WinRect.x0, WinRect.y0);
    }
    else
    {
        //Draw Window Frame Outline, and Background.
        if(pWidget->eButtonState == xKB_BTN_FOCUSED)
        {
            GUI_DrawGradientRoundedV(WinRect.x0, WinRect.y0, WinRect.x1, WinRect.y1,1, pWidget->aBkColor[2], pWidget->aBkColor[3]);
        }
        else
        {
            GUI_DrawGradientRoundedV(WinRect.x0, WinRect.y0, WinRect.x1, WinRect.y1,1, pWidget->aBkColor[0], pWidget->aBkColor[1]);
        }
    }
    
    if(pWidget->pFont)
    {
        GUI_SetFont(pWidget->pFont);
    }
    GUI_SetColor(pWidget->aTextColor[pWidget->eButtonState]);
    GUI_SetTextMode(GUI_TM_TRANS);
    
    if(pWidget->pText)
    {
        DEBUGOUT("xKBbtn Draw Text: %s\r\n",pWidget->pText);
        if( (pWidget->TextRect.x0 | pWidget->TextRect.x1 | pWidget->TextRect.y1 | pWidget->TextRect.y1) == 0)
        {
            GUI_DispStringInRect(pWidget->pText, &WinRect, GUI_TA_VCENTER | GUI_TA_LEFT);
        }
        else
        {
            GUI_DispStringInRect(pWidget->pText, &pWidget->TextRect, (pWidget->TextAlign != 0) ?  pWidget->TextAlign : (GUI_TA_VCENTER | GUI_TA_LEFT) );
        }
    }
}

/*********************************************************************
*
*       _H_GotoPrevBtn
*/
static void _H_GotoPrevBtn(xKB_BTN_Handle hBtn)
{
    xKB_BTN_Handle hNextBtn;
    xKB_BTN_Obj    tBtn;
    tKB_XY         BtnXY, TableSize;
    int            CntFindSteps = 0;
    
    if(!hBtn) return;
    
    WM_GetUserData(hBtn, &tBtn, sizeof(xKB_BTN_Obj));
    
    DEBUGOUT("_H_GotoPrevBtn:pKB_Table = %08x\r\n", tBtn.KB_SoftKey.pKB_Table);
    
    if(!tBtn.KB_SoftKey.pKB_Table) return;
    
    DEBUGOUT("_H_GotoPrevBtn\r\n");
    
    BtnXY     = tBtn.KB_SoftKey.KB_KeyPosition;
    TableSize = tBtn.KB_SoftKey.KB_TableSize;
    
    while(1)
    {
        if(--BtnXY.x < 0)
        {
            //Go up 1 row at last colume.
            BtnXY.x = TableSize.x-1;
            if(--BtnXY.y < 0)
            {
                //trun around to buttom row
                BtnXY.y = TableSize.y-1;
            }
        }
        
        if(tBtn.KB_SoftKey.pKB_Table[(BtnXY.y*TableSize.x) + BtnXY.x] != hBtn)
        {
            //found next Key
            hNextBtn = tBtn.KB_SoftKey.pKB_Table[(BtnXY.y*TableSize.x) + BtnXY.x];
            //Found next enabled Btn, exit loop
            WM_SetFocus(hNextBtn);
            DEBUGOUT("GUI_KEY_LEFT, Goto New xKBbtn(hWin:0x%08x) @XY(%d,%d)\r\n",hNextBtn, BtnXY.x, BtnXY.y);
            break;
        }
        
        if(++CntFindSteps >= (TableSize.x * TableSize.y) )
        {
            //Not Found, No move, and Stay in Same Btn
            DEBUGOUT("GUI_KEY_LEFT, xKBbtn(hWin:0x%08x) @XY(%d,%d) not found previous valid Btn!!!\r\n",hBtn,BtnXY.x, BtnXY.y);
            break;
        }
    }
}

/*********************************************************************
*
*       _H_GotoNextBtn
*/
static void _H_GotoNextBtn(xKB_BTN_Handle hBtn)
{
    xKB_BTN_Handle hNextBtn;
    xKB_BTN_Obj    tBtn;
    tKB_XY         BtnXY, TableSize;
    int            CntFindSteps = 0;
    
    if(!hBtn) return;
    
    WM_GetUserData(hBtn, &tBtn, sizeof(xKB_BTN_Obj));
    
    if(!tBtn.KB_SoftKey.pKB_Table) return;
    
    DEBUGOUT("_H_GotoNextBtn\r\n");
    
    
    BtnXY     = tBtn.KB_SoftKey.KB_KeyPosition;
    TableSize = tBtn.KB_SoftKey.KB_TableSize;
    
    while(1)
    {
        if(++BtnXY.x >= TableSize.x)
        {
            //Go down 1 row at 1st colume.
            BtnXY.x = 0;
            if(++BtnXY.y >= TableSize.y)
            {
                //trun around to 1st row
                BtnXY.y = 0;
            }
        }
        
        if(tBtn.KB_SoftKey.pKB_Table[(BtnXY.y*TableSize.x) + BtnXY.x]!= hBtn)
        {
            //found next Key
            hNextBtn = tBtn.KB_SoftKey.pKB_Table[(BtnXY.y*TableSize.x) + BtnXY.x];
            //Found next enabled Btn, exit loop
            WM_SetFocus(hNextBtn);
            DEBUGOUT("GUI_KEY_RIGHT, Goto New xKBbtn(hWin:0x%08x) @XY(%d,%d)\r\n",hNextBtn, BtnXY.x, BtnXY.y);
            break;
        }
        
        if(++CntFindSteps >= (TableSize.x * TableSize.y) )
        {
            //Not Found, No move, and Stay in Same Btn
            DEBUGOUT("GUI_KEY_RIGHT, xKBbtn(hWin:0x%08x) @XY(%d,%d) not found previous valid Btn!!!\r\n",hBtn,BtnXY.x, BtnXY.y);
            break;
        }
    }
}


/*********************************************************************
*
*       _V_GotoPrevBtn
*/
static void _V_GotoPrevBtn(xKB_BTN_Handle hBtn)
{
    xKB_BTN_Handle hNextBtn;
    xKB_BTN_Obj    tBtn;
    tKB_XY         BtnXY, TableSize;
    int            CntFindSteps = 0;
    
    if(!hBtn) return;
    
    WM_GetUserData(hBtn, &tBtn, sizeof(xKB_BTN_Obj));
    
    if(!tBtn.KB_SoftKey.pKB_Table) return;
    
    DEBUGOUT("_V_GotoPrevBtn\r\n");
    
    BtnXY     = tBtn.KB_SoftKey.KB_KeyPosition;
    TableSize = tBtn.KB_SoftKey.KB_TableSize;
    
    while(1)
    {
        if(--BtnXY.y < 0)
        {
            //Go to Buttom row
            BtnXY.y = TableSize.y-1;
        }
        
        if(tBtn.KB_SoftKey.pKB_Table[(BtnXY.y*TableSize.x) + BtnXY.x] != hBtn)
        {
            //found next Key
            hNextBtn = tBtn.KB_SoftKey.pKB_Table[(BtnXY.y*TableSize.x) + BtnXY.x];
            //Found next enabled Btn, exit loop
            WM_SetFocus(hNextBtn);
            DEBUGOUT("GUI_KEY_UP, Goto New xKBbtn(hWin:0x%08x) @XY(%d,%d)\r\n",hNextBtn, BtnXY.x, BtnXY.y);
            break;
        }
        
        if(++CntFindSteps >= TableSize.y )
        {
            //Not Found, No move, and Stay in Same Btn
            DEBUGOUT("GUI_KEY_UP, xKBbtn(hWin:0x%08x) @XY(%d,%d) not found previous valid Btn!!!\r\n",hBtn,BtnXY.x, BtnXY.y);
            break;
        }
    }
}

/*********************************************************************
*
*       _V_GotoNextBtn
*/
static void _V_GotoNextBtn(xKB_BTN_Handle hBtn)
{
    xKB_BTN_Handle hNextBtn;
    xKB_BTN_Obj    tBtn;
    tKB_XY         BtnXY, TableSize;
    int            CntFindSteps = 0;
    
    if(!hBtn) return;
    
    WM_GetUserData(hBtn, &tBtn, sizeof(xKB_BTN_Obj));
    
    if(!tBtn.KB_SoftKey.pKB_Table) return;
    
    DEBUGOUT("_V_GotoNextBtn\r\n");
    
    BtnXY     = tBtn.KB_SoftKey.KB_KeyPosition;
    TableSize = tBtn.KB_SoftKey.KB_TableSize;
    
    while(1)
    {
        if(++BtnXY.y >= TableSize.y)
        {
            //Go to Top row
            BtnXY.y = 0;
        }
        
        if(tBtn.KB_SoftKey.pKB_Table[(BtnXY.y*TableSize.x) + BtnXY.x] != hBtn)
        {
            //found next Key
            hNextBtn = tBtn.KB_SoftKey.pKB_Table[(BtnXY.y*TableSize.x) + BtnXY.x];
            //Found next enabled Btn, exit loop
            WM_SetFocus(hNextBtn);
            DEBUGOUT("GUI_KEY_DOWN, Goto New xKBbtn(hWin:0x%08x) @XY(%d,%d)\r\n",hNextBtn, BtnXY.x, BtnXY.y);
            break;
        }
        
        if(++CntFindSteps >= TableSize.y)
        {
            //Not Found, No move, and Stay in Same Btn
            DEBUGOUT("GUI_KEY_DOWN, xKBbtn(hWin:0x%08x) @XY(%d,%d) not found previous valid Btn!!!\r\n",hBtn,BtnXY.x, BtnXY.y);
            break;
        }
    }
}

/*********************************************************************
*
*       xKB_BTN_Callback
*/
void xKBbtn_Callback(WM_MESSAGE * pMsg) {
  xKB_BTN_Handle    hWin;
  WM_KEY_INFO     * pKeyInfo;
  xKB_BTN_Obj       tWidget;
  int Notification;
  
  hWin = pMsg->hWin;
  WM_GetUserData(hWin, &tWidget, sizeof(xKB_BTN_Obj));
  
  switch (pMsg->MsgId)
  {
  case WM_PAINT:
    _Paint(hWin, &tWidget);
    break;
    
  case WM_KEY:
    pKeyInfo = (WM_KEY_INFO *)pMsg->Data.p;
    
    switch(pKeyInfo->Key)
    {
      //case GUI_KEY_ESCAPE:
      //  if(pKeyInfo->PressedCnt >0)
      //  {
      //      DEBUGOUT("xBtn <- KEY_ESCAPE\r\n");
      //      tWidget.eButtonState = xKB_BTN_FOCUSED;
      //      WM_SetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
      //      WM_SetFocus(hWin);
      //      WM_InvalidateWindow(hWin);
      //  }
      //  break;
      
      case GUI_KEY_ENTER:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xKBbtn(0x%08x) <- KEY_ENTER\r\n",hWin);
            Notification = WM_NOTIFICATION_CLICKED;
        }
        else
        {
            Notification = WM_NOTIFICATION_RELEASED;
        }
        WM_NotifyParent(hWin, Notification);
        break;
        
      case GUI_KEY_LEFT:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xKBbtn(0x%08x) <- KEY_LEFT\r\n",hWin);
            
            _H_GotoPrevBtn(hWin);
        }
        break;
        
      case GUI_KEY_RIGHT:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xKBbtn(0x%08x) <- KEY_RIGHT\r\n",hWin);
            _H_GotoNextBtn(hWin);
        }
        break;
        
      case GUI_KEY_UP:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xKBbtn(0x%08x) <- GUI_KEY_UP\r\n",hWin);
            _V_GotoPrevBtn(hWin);
        }
        break;
        
      case GUI_KEY_DOWN:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xKBbtn(0x%08x) <- GUI_KEY_DOWN\r\n",hWin);
            _V_GotoNextBtn(hWin);
        }
        break;
        
      default:
        WM_DefaultProc(pMsg);
        break;
    }
    break;
    
  case WM_SET_FOCUS:
    if (pMsg->Data.v)
    {
      pMsg->Data.v = 0;
      
      if(tWidget.eButtonState != xKB_BTN_DISABLE)
      {
          tWidget.eButtonState = xKB_BTN_FOCUSED;
          WM_SetUserData(hWin, &tWidget, sizeof(xKB_BTN_Obj));
      }
      else
      {
          _H_GotoNextBtn(hWin);
      }
      DEBUGOUT("xKB_BTN(0x%08x) Has Focus\r\n",hWin);
    }
    else
    {
      DEBUGOUT("xKB_BTN(0x%08x) Lost Focus\r\n",hWin);
      if(tWidget.eButtonState == xKB_BTN_FOCUSED)
      {
          tWidget.eButtonState = xKB_BTN_NORMAL;
          WM_SetUserData(hWin, &tWidget, sizeof(xKB_BTN_Obj));
      }
    }
    WM_InvalidateWindow(hWin);
    break;
      
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       xKB_BTN_GetUserData
*/
int xKB_BTN_GetUserData(xKB_BTN_Handle hWin, void * pDest, int SizeOfBuffer) {
  xKB_BTN_Obj   tWidget;
  int            NumBytes;
  U8           * pExtraBytes;
  if (SizeOfBuffer <= 0) {
    return 0;
  }
  WM_GetUserData(hWin, &tWidget, sizeof(xKB_BTN_Obj));
  pExtraBytes = (U8 *)malloc(sizeof(xKB_BTN_Obj) + tWidget.NumExtraBytes);
  if (pExtraBytes) {
    WM_GetUserData(hWin, pExtraBytes,
                   sizeof(xKB_BTN_Obj) + tWidget.NumExtraBytes);
    if (SizeOfBuffer >= tWidget.NumExtraBytes) {
      NumBytes = tWidget.NumExtraBytes;
    } else {
      NumBytes = SizeOfBuffer;
    }
    GUI_MEMCPY(pDest, pExtraBytes + sizeof(xKB_BTN_Obj), NumBytes);
    free(pExtraBytes);
    return NumBytes;
  }
  return 0;
}

/*********************************************************************
*
*       xKB_BTN_SetUserData
*/
int xKB_BTN_SetUserData(xKB_BTN_Handle hWin, void * pSrc, int SizeOfBuffer) {
  xKB_BTN_Obj   tWidget;
  int            NumBytes;
  U8           * pExtraBytes;
  if (SizeOfBuffer <= 0) {
    return 1;
  }
  WM_GetUserData(hWin, &tWidget, sizeof(xKB_BTN_Obj));
  pExtraBytes = (U8 *)malloc(sizeof(xKB_BTN_Obj) + tWidget.NumExtraBytes);
  if (pExtraBytes) {
    WM_GetUserData(hWin, pExtraBytes,
                   sizeof(xKB_BTN_Obj) + tWidget.NumExtraBytes);
    if (SizeOfBuffer >= tWidget.NumExtraBytes) {
      NumBytes = tWidget.NumExtraBytes;
    } else {
      NumBytes = SizeOfBuffer;
    }
    GUI_MEMCPY(pExtraBytes + sizeof(xKB_BTN_Obj), pSrc, NumBytes);
    WM_SetUserData(hWin, pExtraBytes,
                   sizeof(xKB_BTN_Obj) + tWidget.NumExtraBytes);
    free(pExtraBytes);
    return 0;
  }
  return 1;
}

/*********************************************************************
*
*       xKB_BTN_SetText
*/
void xKB_BTN_SetText(xKB_BTN_Handle hObj, const char* s)
{
  xKB_BTN_Obj   tWidget;
  
  if (hObj)
  {
    WM_GetUserData(hObj, &tWidget, sizeof(xKB_BTN_Obj));
    tWidget.pText = s;
    WM_SetUserData(hObj, &tWidget, sizeof(xKB_BTN_Obj));
    WM_InvalidateWindow(hObj);
  }
}

/*********************************************************************
*
*       xKB_BTN_SetBmp
*/
void xKB_BTN_SetBmp(xKB_BTN_Handle hObj, GUI_CONST_STORAGE GUI_BITMAP* pBmp, eKB_BTN_STATE xBtnState)
{
    xKB_BTN_Obj   tWidget;
    
    if( (hObj) && (pBmp) )
    {
        WM_GetUserData(hObj, &tWidget, sizeof(xKB_BTN_Obj));
        if(xBtnState <= xKB_BTN_PRESSED)
        {
            tWidget.aBmp[xBtnState] = pBmp;
            WM_SetUserData(hObj, &tWidget, sizeof(xKB_BTN_Obj));
        }
    }
}

/*********************************************************************
*
*       xKB_BTN_CreateEx
*/
xKB_BTN_Handle xKB_BTN_CreateEx(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id)
{
  xKB_BTN_Handle   hWin;
  xKB_BTN_Obj      tWidget;
  
  tWidget               = xKB_BTN_Default;
  
  /* Create the window */
  WM_LOCK();
  
  hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent, WinFlags,
                                xKBbtn_Callback, sizeof(xKB_BTN_Obj));
  if( hWin)
  {
    WM_SetUserData(hWin, &tWidget, sizeof(xKB_BTN_Obj));
    WM_SetId(hWin, Id);
  }
  else
  {
    DEBUGOUT("xKB_BTN create failed!!!\r\n",hWin);
  }
  return hWin;
}


/*********************************************************************
*
*       xKB_BTN_CreateUser
*/
xKB_BTN_Handle xKB_BTN_CreateUser(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id, int NumExtraBytes)
{
  xKB_BTN_Handle   hWin;
  xKB_BTN_Obj      tWidget;
  
  tWidget               = xKB_BTN_Default;
  tWidget.NumExtraBytes = NumExtraBytes;
  
  hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent, WinFlags,
                                xKBbtn_Callback, sizeof(xKB_BTN_Obj) + NumExtraBytes);
  if( hWin)
  {
    WM_SetUserData(hWin, &tWidget, sizeof(xKB_BTN_Obj));
    WM_SetId(hWin, Id);
  }
  else
  {
    DEBUGOUT("xKB_BTN create failed!!!\r\n",hWin);
  }
  return hWin;
}


/*********************************************************************
*
*       xKB_BTN_CreateIndirect
*/
xKB_BTN_Handle xKB_BTN_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb)
{
  xKB_BTN_Handle  hThis;
  xKB_BTN_Obj     *ptWidget;
  
  hThis = xKB_BTN_CreateUser(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0,
                          pCreateInfo->xSize, pCreateInfo->ySize,
                          hWinParent, 0, pCreateInfo->Flags, pCreateInfo->Id, pCreateInfo->NumExtraBytes);
  if(pCreateInfo->Para)
  {
    ptWidget = (xKB_BTN_Obj*) pCreateInfo->Para;
    WM_SetUserData(hThis, ptWidget, sizeof(xKB_BTN_Obj));
    if(!ptWidget->pText)
    {
        xKB_BTN_SetText(hThis, pCreateInfo->pName);
    }
  }
  else
  {
    xKB_BTN_SetText(hThis, pCreateInfo->pName);
  }
  
  WM_SetHasTrans(hThis);
  
  if(cb)
  {
    WM_SetCallback(hThis, cb);
  }
  
  return hThis;
}

