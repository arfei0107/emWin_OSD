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
#include "xBUTTON.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "board.h"

#if 1
#undef  DEBUGOUT
#undef  DEBUGSTR
#define DEBUGOUT(...)
#define DEBUGSTR(str)
#endif

/*********************************************************************
*
*       xBUTTON_Default
*/
const xBUTTON_Obj xBUTTON_Default =
{
  xBUTTON_NORMAL,                                   //eButtonState
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW}, //aTextColor[4];
  0                                  //NumExtraBytes;
};


/*********************************************************************
*
*       _Paint
*/
void _Paint(xBUTTON_Handle hWin, xBUTTON_Obj *pWidget)
{
    GUI_RECT          WinRect;
    
    DEBUGOUT("xBtn hWin = 0x%08x\r\n", hWin);
    WM_GetWindowRectEx(hWin, &WinRect);
    GUI_MoveRect(&WinRect, -WinRect.x0, -WinRect.y0);
    DEBUGOUT("BtnPaint(%d,%d,%d,%d)\r\n",WinRect.x0, WinRect.y0, WinRect.x1, WinRect.y1);
  
    if(pWidget->aBmp[pWidget->eButtonState])
    {
        DEBUGOUT("Btn State: %d\r\n",pWidget->eButtonState);
        DEBUGOUT("BtnPaint(pBmp:0x%08x)\r\n",(U32)(pWidget->aBmp[pWidget->eButtonState]));
        GUI_DrawBitmap(pWidget->aBmp[pWidget->eButtonState], WinRect.x0, WinRect.y0);
    }
    GUI_SetFont(pWidget->pFont);
    GUI_SetColor(pWidget->aTextColor[pWidget->eButtonState]);
    GUI_SetTextMode(GUI_TM_TRANS);
    
    DEBUGOUT("Btn Draw Text: %s\r\n",pWidget->pText);
    if( (pWidget->TextRect.x0 | pWidget->TextRect.x1 | pWidget->TextRect.y1 | pWidget->TextRect.y1) == 0)
    {
        GUI_DispStringInRect(pWidget->pText, &WinRect, GUI_TA_VCENTER | GUI_TA_LEFT);
    }
    else
    {
        GUI_DispStringInRect(pWidget->pText, &pWidget->TextRect, (pWidget->TextAlign != 0) ?  pWidget->TextAlign : (GUI_TA_VCENTER | GUI_TA_LEFT) );
    }
}

/*********************************************************************
*
*       _GotoPrevBtn
*/
void _GotoPrevBtn(xBUTTON_Handle hWin)
{
    xBUTTON_Handle hWinNext, hWinIndex;
    xBUTTON_Obj    tBtn, tNextBtn;
    int fTurnAround = 0;
    
    if(!hWin) return;
    
    hWinNext = hWinIndex = hWin;
    
    while(hWinIndex != NULL)
    {
        hWinNext = WM_GetPrevSibling(hWinIndex);
        if(hWinNext)
        {
            WM_GetUserData(hWinNext, &tNextBtn, sizeof(xBUTTON_Obj));
            if(tNextBtn.eButtonState != xBUTTON_DISABLE )
            {
               //Found next enabled Btn, exit loop
                WM_SetFocus(hWinNext);
                return;
            }
            else
            {
                hWinIndex = hWinNext;
            }
        }
        else  // go to tail
        {
            //On First Sibling, go to last Sibling
            if( fTurnAround == 1) return;
            
            fTurnAround = 1;
            
            hWinIndex = hWinNext = hWin;
            while( hWinNext != 0)
            {
                hWinIndex = hWinNext;
                hWinNext  = WM_GetNextSibling(hWinIndex);
            }
            
            if(hWinIndex)
            {
                hWinNext = hWinIndex;
                WM_GetUserData(hWinNext, &tNextBtn, sizeof(xBUTTON_Obj));
                if( tNextBtn.eButtonState != xBUTTON_DISABLE )
                {
                    WM_SetFocus(hWinNext);
                    return;
                }
                else
                {
                    hWinIndex = hWinNext;
                }
            }
            else
            {
                DEBUGOUT("Btn(Win:0x%08x has GUI_KEY_UP, but NextWin is invalid.\r\n",hWin);
                return;
            }
        }
    }
}



/*********************************************************************
*
*       _GotoNextBtn
*/
void _GotoNextBtn(xBUTTON_Handle hWin)
{
    xBUTTON_Handle hWinNext, hWinIndex;
    xBUTTON_Obj    tBtn, tNextBtn;
    int fTurnAround = 0;
    
    if(!hWin) return;
    
    hWinNext = hWinIndex = hWin;
    
    while(hWinIndex != NULL)
    {
        hWinNext = WM_GetNextSibling(hWinIndex);
        if(hWinNext)
        {
            WM_GetUserData(hWinNext, &tNextBtn, sizeof(xBUTTON_Obj));
            if(tNextBtn.eButtonState != xBUTTON_DISABLE )
            {
               //Found next enabled Btn, exit loop
                WM_SetFocus(hWinNext);
                return;
            }
            else
            {
                hWinIndex = hWinNext;
            }
        }
        else
        {
            //On First Sibling, go to last Sibling
            if( fTurnAround == 1) return;
            
            fTurnAround = 1;
            
            hWinIndex = WM_GetParent(hWin);
            hWinIndex = WM_GetFirstChild(hWinIndex);
            if(hWinIndex)
            {
                hWinNext = hWinIndex;
                WM_GetUserData(hWinNext, &tNextBtn, sizeof(xBUTTON_Obj));
                if( tNextBtn.eButtonState != xBUTTON_DISABLE )
                {
                    WM_SetFocus(hWinNext);
                    return;
                }
                else
                {
                    hWinIndex = hWinNext;
                }
            }
            else
            {
                DEBUGOUT("Btn(Win:0x%08x has GUI_KEY_DOWN, but NextWin is invalid.\r\n",hWin);
                return;
            }
        }
    }
}
/*********************************************************************
*
*       xBUTTON_Callback
*/
void xBUTTON_Callback(WM_MESSAGE * pMsg) {
  xBUTTON_Handle    hWin, NextWin, hWinIndex;
  WM_KEY_INFO     * pKeyInfo;
  xBUTTON_Obj       tWidget, tNextBtn;
  int WinID;
  static char Text[10];
  int SliderValue;
  
  hWin = pMsg->hWin;
  WM_GetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
  
  switch (pMsg->MsgId)
  {
  case WM_PAINT:
    _Paint(hWin, &tWidget);
    break;
    
  case WM_KEY:
    pKeyInfo = (WM_KEY_INFO *)pMsg->Data.p;
    
    switch(pKeyInfo->Key)
    {
      case GUI_KEY_ENTER:
    //case GUI_KEY_SPACE:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xBtn <- KEY_ENTER\r\n");
            tWidget.eButtonState = xBUTTON_PRESSED;
            WM_SetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
            WM_InvalidateWindow(hWin);
            WM_SendMessage(WM_GetFirstChild(hWin), pMsg);
            //WM_SetFocus(WM_GetFirstChild(hWin));
        }
        break;
        
      case GUI_KEY_ESCAPE:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xBtn <- KEY_ESCAPE\r\n");
            tWidget.eButtonState = xBUTTON_FOCUSED;
            WM_SetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
            WM_SetFocus(hWin);
            WM_InvalidateWindow(hWin);  // reDraw
        }
        break;
      
      case GUI_KEY_UP:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xBtn(0x%08x) <- KEY_UP\r\n",hWin);
            
            _GotoPrevBtn(hWin);
        }
        break;
        
      case GUI_KEY_DOWN:
        if(pKeyInfo->PressedCnt >0)
        {
            DEBUGOUT("xBtn(0x%08x) <- GUI_KEY_DOWN\r\n",hWin);
            _GotoNextBtn(hWin);
        }
        break;
        
      case GUI_KEY_LEFT:
      case GUI_KEY_RIGHT:
        WM_SendMessage(WM_GetFirstChild(hWin), pMsg);
        break;
        
      default:
        WM_DefaultProc(pMsg);
        break;
    }
    break;
    
  case WM_SET_FOCUS:
    if (pMsg->Data.v)  // set focus
    {
      pMsg->Data.v = 0;
      
      if(tWidget.eButtonState != xBUTTON_DISABLE)
      {
          tWidget.eButtonState = xBUTTON_FOCUSED;
          WM_SetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
      }
      else
      {
          _GotoNextBtn(hWin);
      }
      DEBUGOUT("xBtn(0x%08x) Has Focus\r\n",hWin);
    }
    else  // lost fcuus
    {
      DEBUGOUT("xBtn(0x%08x) Lost Focus\r\n",hWin);
      if(tWidget.eButtonState == xBUTTON_FOCUSED)
      {
          tWidget.eButtonState = xBUTTON_NORMAL;
          WM_SetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
      }
    }
    WM_InvalidateWindow(hWin);
    break;
    
  case WM_NOTIFY_PARENT:
    switch (pMsg->Data.v)
      {
        case WM_NOTIFICATION_VALUE_CHANGED:
          DEBUGOUT("xBtn <- Child(Value Changed)\r\n");
          //Find Child(Text Widget) and update Text
          
          hWinIndex = WM_GetFirstChild(hWin);
          while( hWinIndex != 0)
          {
              WinID = WM_GetId(hWinIndex);
              DEBUGOUT("\t CHK Child ID:%d\r\n", WinID);
              if( (WinID>=xID_TEXT_START) && (WinID<=xID_TEXT_END) )
              {
                  //Found ID, update Text
                  //    Get SLIDER VALUE
                  SliderValue = SLIDER_GetValue(WM_GetFirstChild(hWin));
                  snprintf(Text,sizeof(Text),"%d",SliderValue);
                  DEBUGOUT("\t TextWidget ID:%d String(%s)\r\n",WinID, Text);
                  TEXT_SetText(hWinIndex, (const char*)Text);
                  break;
              }
              else
              {
                  //Goto Next Win
                  hWinIndex = WM_GetNextSibling(hWinIndex);
              }
          }
          break;
      }
      break;
      
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       xBUTTON_GetUserData
*/
int xBUTTON_GetUserData(xBUTTON_Handle hWin, void * pDest, int SizeOfBuffer) {
  xBUTTON_Obj   tWidget;
  int            NumBytes;
  U8           * pExtraBytes;
  if (SizeOfBuffer <= 0) {
    return 0;
  }
  WM_GetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
  pExtraBytes = (U8 *)malloc(sizeof(xBUTTON_Obj) + tWidget.NumExtraBytes);
  if (pExtraBytes) {
    WM_GetUserData(hWin, pExtraBytes,
                   sizeof(xBUTTON_Obj) + tWidget.NumExtraBytes);
    if (SizeOfBuffer >= tWidget.NumExtraBytes) {
      NumBytes = tWidget.NumExtraBytes;
    } else {
      NumBytes = SizeOfBuffer;
    }
    GUI_MEMCPY(pDest, pExtraBytes + sizeof(xBUTTON_Obj), NumBytes);
    free(pExtraBytes);
    return NumBytes;
  }
  return 0;
}

/*********************************************************************
*
*       xBUTTON_SetUserData
*/
int xBUTTON_SetUserData(xBUTTON_Handle hWin, void * pSrc, int SizeOfBuffer) {
  xBUTTON_Obj   tWidget;
  int            NumBytes;
  U8           * pExtraBytes;
  if (SizeOfBuffer <= 0) {
    return 1;
  }
  WM_GetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
  pExtraBytes = (U8 *)malloc(sizeof(xBUTTON_Obj) + tWidget.NumExtraBytes);
  if (pExtraBytes) {
    WM_GetUserData(hWin, pExtraBytes,
                   sizeof(xBUTTON_Obj) + tWidget.NumExtraBytes);
    if (SizeOfBuffer >= tWidget.NumExtraBytes) {
      NumBytes = tWidget.NumExtraBytes;
    } else {
      NumBytes = SizeOfBuffer;
    }
    GUI_MEMCPY(pExtraBytes + sizeof(xBUTTON_Obj), pSrc, NumBytes);
    WM_SetUserData(hWin, pExtraBytes,
                   sizeof(xBUTTON_Obj) + tWidget.NumExtraBytes);
    free(pExtraBytes);
    return 0;
  }
  return 1;
}

/*********************************************************************
*
*       xBUTTON_SetText
*/
void xBUTTON_SetText(xBUTTON_Handle hObj, const char* s)
{
  xBUTTON_Obj   tWidget;
  
  if (hObj)
  {
    WM_GetUserData(hObj, &tWidget, sizeof(xBUTTON_Obj));
    tWidget.pText = s;
    WM_SetUserData(hObj, &tWidget, sizeof(xBUTTON_Obj));
    WM_InvalidateWindow(hObj);
  }
}

/*********************************************************************
*
*       xBUTTON_SetBmp
*/
void xBUTTON_SetBmp(xBUTTON_Handle hObj, GUI_CONST_STORAGE GUI_BITMAP* pBmp, eBUTTON_STATE xBtnState)
{
    xBUTTON_Obj   tWidget;
    
    if( (hObj) && (pBmp) )
    {
        WM_GetUserData(hObj, &tWidget, sizeof(xBUTTON_Obj));
        if(xBtnState <= xBUTTON_PRESSED)
        {
            tWidget.aBmp[xBtnState] = pBmp;
            WM_SetUserData(hObj, &tWidget, sizeof(xBUTTON_Obj));
        }
    }
}

/*********************************************************************
*
*       xBUTTON_CreateEx
*/
xBUTTON_Handle xBUTTON_CreateEx(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id)
{
  xBUTTON_Handle   hWin;
  xBUTTON_Obj      tWidget;
  
  tWidget               = xBUTTON_Default;
  
  hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent, WinFlags,
                                xBUTTON_Callback, sizeof(xBUTTON_Obj));
  WM_SetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
  return hWin;
}


/*********************************************************************
*
*       xBUTTON_CreateUser
*/
xBUTTON_Handle xBUTTON_CreateUser(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id, int NumExtraBytes)
{
  xBUTTON_Handle   hWin;
  xBUTTON_Obj      tWidget;
  
  tWidget               = xBUTTON_Default;
  tWidget.NumExtraBytes = NumExtraBytes;
  
  hWin = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent, WinFlags,
                                xBUTTON_Callback, sizeof(xBUTTON_Obj) + NumExtraBytes);
  WM_SetUserData(hWin, &tWidget, sizeof(xBUTTON_Obj));
  return hWin;
}


/*********************************************************************
*
*       BUTTON_CreateIndirect
*/
xBUTTON_Handle xBUTTON_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb)
{
  xBUTTON_Handle  hThis;
  xBUTTON_Obj     *ptWidget;
  
  hThis = xBUTTON_CreateUser(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0,
                          pCreateInfo->xSize, pCreateInfo->ySize,
                          hWinParent, 0, pCreateInfo->Flags, pCreateInfo->Id, pCreateInfo->NumExtraBytes);
  if(pCreateInfo->Para)
  {
    ptWidget = (xBUTTON_Obj*) pCreateInfo->Para;
    WM_SetUserData(hThis, ptWidget, sizeof(xBUTTON_Obj));
    if(!ptWidget->pText)
    {
        xBUTTON_SetText(hThis, pCreateInfo->pName);
    }
  }
  else
  {
    xBUTTON_SetText(hThis, pCreateInfo->pName);
  }
  
  WM_SetHasTrans(hThis);  // 
  
  if(cb)
  {
    WM_SetCallback(hThis, cb);
  }
  
  return hThis;
}

