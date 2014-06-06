/*********************************************************************
*                Golden-IC Technology Co.,Ltd                        *
*                       www.golden-ic.com                            *
**********************************************************************
*        (c) 2007 - 2014 Golden-IC Technology Co., Ltd               *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: xDROPDOWN.c                                           *
*                                                                    *
**********************************************************************
*/
#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include "GUI.h"
#include "WM.h"
#include "xDROPDOWN.h"
#include "DROPDOWN.h"
#include "LISTBOX.h"
#include "DIALOG.h"
#include "board.h"

#if 1
#undef  DEBUGOUT
#undef  DEBUGSTR
#define DEBUGOUT(...)
#define DEBUGSTR(str)
#endif

/*********************************************************************
*
*       _PaintDropdownListBox
*/

void _PaintDropdownListBox(WM_HWIN hWin, WM_HWIN hParent, xDROPDOWN_Obj* pWidget)
{
    GUI_RECT rWin, r;
    static char Text[32];
    int NumItems, ListBoxIdx, DropdownSelIdx, x, y, i;
    
    WM_GetClientRect(&rWin);
    DEBUGOUT("_PaintDropdownListBox: Win(%d,%d,%d,%d)\r\n", rWin.x0, rWin.x1, rWin.y0, rWin.y1);
    NumItems = DROPDOWN_GetNumItems(hParent);
    ListBoxIdx = pWidget->ListBoxIdx;
    DropdownSelIdx = DROPDOWN_GetSel(hParent);
    
    //Draw Window Background area
    GUI_SetColor(pWidget->ListBoxRectBkColor[1]); //Base Color
    GUI_FillRoundedRect(rWin.x0+1,rWin.y0+1,rWin.x1-1,rWin.y1-1, 2);
    GUI_SetColor(pWidget->ListBoxRectBkColor[0]); //OutLine Color
    GUI_DrawRoundedRect(rWin.x0,rWin.y0,rWin.x1,rWin.y1, 2);
    
    //Draw Focus Bar Bmp
    x = rWin.x0 + pWidget->ListBoxItemFocusBmpAlignX0;
    y = rWin.y0 + (ListBoxIdx * pWidget->ListBoxItemHeight) + pWidget->ListBoxItemAlignY0;
    GUI_DrawBitmap(pWidget->pListBoxItemFocusBmp, x,  y);
    
    //Draw Text Items
    GUI_SetFont(pWidget->pListBoxTextFont);
    GUI_SetTextMode(GUI_TM_TRANS);
    for (i = 0; i< NumItems; i++)
    {
        DROPDOWN_GetItemText(hParent, i, Text, sizeof(Text));
        if( i == ListBoxIdx)  //選到的字顏色
        {
            //Set Text to Focus Color
            GUI_SetColor(pWidget->ListBoxTextColor[xDROPDOWN_FOCUSED]);
        }
        else
        {
            if( !DROPDOWN_GetItemDisabled(hParent, i) )
            {
                //Set Text to Disable Color
                GUI_SetColor(pWidget->ListBoxTextColor[xDROPDOWN_DISABLE]);
            }
            else
            {
                //Set Text to Enable Color
                GUI_SetColor(pWidget->ListBoxTextColor[xDROPDOWN_ENABLE]);
            }
        }
        r.x0 = rWin.x0 + pWidget->ListBoxTextAlignX0;
        r.y0 = rWin.y0 + (i * pWidget->ListBoxItemHeight) + pWidget->ListBoxItemAlignY0;
        r.x1 = r.x0 + pWidget->pListBoxItemFocusBmp->XSize - 20;
        r.y1 = r.y0 + pWidget->ListBoxItemHeight;
        
        GUI_DispStringInRect(Text, &r, GUI_TA_VCENTER | GUI_TA_LEFT);
    }
    
    //Draw checked(selected) tag "V" bmp;
    x = pWidget->ListBoxItemCheckedBmpAlignX0;
    y = (DropdownSelIdx * pWidget->ListBoxItemHeight) + pWidget->ListBoxItemAlignY0 + pWidget->ListBoxItemCheckedBmpAlignY0;
    GUI_DrawBitmap(pWidget->pListBoxItemCheckedBmp, rWin.x0 + x, rWin.y0 + y);
}

/*********************************************************************
*
*       _ListBoxIndexAdd
*
* Value: can be positibe or negative value.
*
* return valid new selected Index number.
*
*/

int _ListBoxIndexAdd(int Value, int NumItems, WM_HWIN hWin, WM_HWIN hParent, xDROPDOWN_Obj* pWidget)
{
    int NewIdx, i = 0;
    
    
    NewIdx = (pWidget->ListBoxIdx + Value) % NumItems;
    
    if(Value > 0)
    {
        while( !DROPDOWN_GetItemDisabled(hParent, NewIdx) )
        {
            NewIdx = (NewIdx + 1) % NumItems;
            if(++i > NumItems)
            {
                //Not found enable item, return original value.
                return pWidget->ListBoxIdx;
            }
        }
    }
    else if(Value < 0)
    {
        if(NewIdx < 0)
        {
            NewIdx += NumItems;
        }
        
        while( !DROPDOWN_GetItemDisabled(hParent, NewIdx) )
        {
            if(--NewIdx < 0)
            {
                NewIdx = NumItems;
            }
            if(++i > NumItems)
            {
                //Not found enable item, return original value.
                return pWidget->ListBoxIdx;
            }
        }
    }
    
    //Found next enable item.
    pWidget->ListBoxIdx = NewIdx;
    return NewIdx;
}

/*********************************************************************
*
*       _DropDownListBox_CallBack
*/
void _DropDownListBox_CallBack(WM_MESSAGE * pMsg) {
  WM_HWIN hWin, hParent;
  WM_KEY_INFO * pKeyInfo;
  xDROPDOWN_Obj* pWidget;
  int NumItems;
  
  hWin = pMsg->hWin;
  
  DEBUGOUT("_DropDownListBox_CallBack: hWin:0x%08x\r\n", hWin);
  
  WM_GetUserData(hWin, &pWidget, sizeof(xDROPDOWN_Obj*));
  hParent = pWidget->hDropdown;
  NumItems = DROPDOWN_GetNumItems(hParent);
  
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      _PaintDropdownListBox(hWin, hParent, pWidget);
      break;
      
    case WM_KEY:
      pKeyInfo = (WM_KEY_INFO *)pMsg->Data.p;
      if(pKeyInfo->PressedCnt >0)
      {
          switch(pKeyInfo->Key)
          {
            case GUI_KEY_ENTER:
              //Save Current selected Index, and Hide ListBox Win.
              DEBUGOUT("DropDownListBox <- KEY_ENTER Idx: %d\r\n", pWidget->ListBoxIdx);
              DROPDOWN_SetSel(hParent, pWidget->ListBoxIdx);
              WM_SetFocus(WM_GetParent(pWidget->hDropdown));
              WM_HideWindow(hWin);
              break;
            
            case GUI_KEY_ESCAPE:
              DEBUGOUT("DropDownListBox <- KEY_ESCAPE Idx: %d\r\n", pWidget->ListBoxIdx);
              WM_SetFocus(WM_GetParent(pWidget->hDropdown));
              WM_HideWindow(hWin);
              break;
            
            case GUI_KEY_UP:
              _ListBoxIndexAdd(-1, NumItems, hWin, hParent, pWidget);
              DEBUGOUT("DropDownListBox <- KEY_UP Idx: %d\r\n", pWidget->ListBoxIdx);
              WM_InvalidateWindow(hWin);
              break;
            
            case GUI_KEY_DOWN:
              _ListBoxIndexAdd(1, NumItems, hWin, hParent, pWidget);
              DEBUGOUT("DropDownListBox <- KEY_DOWN Idx: %d\r\n", pWidget->ListBoxIdx);
              WM_InvalidateWindow(hWin);
              break;
              
            default:
              //DROPDOWN_Callback(pMsg);
              break;
          }
      }
      break;

	// 可以移除 -->>
    case WM_SET_FOCUS:
      if (pMsg->Data.v)
      {
          pMsg->Data.v = 0;
          DEBUGOUT("xDROPDOWN:ListBox(0x%08x) Has Focus\r\n",hWin);
      }
      else
      {
          DEBUGOUT("xDROPDOWN:ListBox(0x%08x) lost Focus\r\n",hWin);
      }
      WM_InvalidateWindow(hWin);
      break;
    // <<--
    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

      
/*********************************************************************
*
*       DROPDOWN_Expand
*/
void xDROPDOWN_Expand(DROPDOWN_Handle hObj, xDROPDOWN_Obj *pWidget)
{
    int xSize, ySize, NumItems;
    WM_HWIN hLst;
    GUI_RECT r;
    xDROPDOWN_Obj* pComp;
    
    if (hObj)
    {
        if(pWidget->hListBox == 0)
        {
            NumItems = DROPDOWN_GetNumItems(hObj);
            r = pWidget->ListBoxRect;
            r.y1 = r.y0 + (pWidget->ListBoxItemAlignY0 * 2) + (pWidget->ListBoxItemHeight * NumItems);
            xSize = r.x1 - r.x0;
            ySize = r.y1 - r.y0;
            DEBUGOUT("xDROPDOWN Expand ListBox(%d,%d,%d,%d): %d items\r\n",r.x0,r.y0,r.x1,r.y1, NumItems);
            
            hLst = WM_CreateWindowAsChild(r.x0, r.y0, xSize, ySize,
                                     NULL,       //hParent -->> null 為Destop的child
                                     WM_CF_SHOW, //WinFlags -->> style
                                     NULL,       //WM_CALLBACK * cb
                                     sizeof(xDROPDOWN_Obj*)
                                     );
            
            pWidget->hListBox = hLst;
            pWidget->ListBoxIdx = DROPDOWN_GetSel(hObj);
            DROPDOWN_SetUserData(hObj, pWidget, sizeof(xDROPDOWN_Obj));
            
            WM_SetUserData(hLst, &pWidget, sizeof(xDROPDOWN_Obj*));
            WM_GetUserData(hLst, &pComp,   sizeof(xDROPDOWN_Obj*)); //無作用，可捨去
            WM_SetCallback(hLst, _DropDownListBox_CallBack);
            WM_SetFocus(hLst);
        }
        else
        {
            pWidget->ListBoxIdx = DROPDOWN_GetSel(hObj);
            DROPDOWN_SetUserData(hObj, pWidget, sizeof(xDROPDOWN_Obj));
            WM_ShowWindow(pWidget->hListBox);
            WM_SetFocus(pWidget->hListBox);
        }
    }
}

/*********************************************************************
*
*       xDROPDOWN_Collapse
*/
void xDROPDOWN_Collapse(DROPDOWN_Handle hObj, xDROPDOWN_Obj *pWidget)
{
  if (hObj) {
    WM_LOCK();
    if (pWidget->hListBox)
    {
      //WM_SetFocus(WM_GetParent(hObj));
      WM_DeleteWindow(pWidget->hListBox);
      pWidget->hListBox = 0;
      DROPDOWN_SetUserData(hObj, pWidget, sizeof(xDROPDOWN_Obj));
    }
    WM_UNLOCK();
  }
}


    
/*********************************************************************
*
*       xDROPDOWN_Callback
*/
void xDROPDOWN_Callback(WM_MESSAGE * pMsg) {
  WM_HWIN hWin;
  WM_KEY_INFO * pKeyInfo;
  static xDROPDOWN_Obj tWidget;
  int ItemIndex, LoopCnt;
  GUI_RECT rWin;
  static char SelText[32];
  WM_MESSAGE tMsg;
  static WM_KEY_INFO tKEY_Info;
  
  hWin = pMsg->hWin;
  
  DROPDOWN_GetUserData(hWin, &tWidget, sizeof(xDROPDOWN_Obj));
  
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      //Draw Window Background.
      WM_GetClientRect(&rWin);
      DEBUGOUT("xDROPDOWN Win(%d,%d,%d,%d)\r\n",rWin.x0,rWin.y0,rWin.x1,rWin.y1);
      if(tWidget.WidgetInit==0)
      {
          WM_SetYSize(hWin, WM_GetWindowSizeY(hWin)+7); //回覆到原來的大小
          WM_GetClientRect(&rWin);
          DEBUGOUT("xDROPDOWN Modified Win(%d,%d,%d,%d)\r\n",rWin.x0,rWin.y0,rWin.x1,rWin.y1);
          tWidget.hDropdown = hWin;
          tWidget.WidgetInit = 1;
          DROPDOWN_SetUserData(hWin, &tWidget, sizeof(xDROPDOWN_Obj));
      }
      
      //GUI_SetBkColor(tWidget.BarBkColor);
      //GUI_Clear();
           
      //GUI_SetClipRect(&rWin);
      //Draw xDROPDOWN Button Bmp for background
      GUI_DrawBitmap(tWidget.pBtnBmp, rWin.x0, rWin.y0);
      //Draw Text
      DROPDOWN_GetItemText(hWin, DROPDOWN_GetSel(hWin), SelText, sizeof(SelText));
      GUI_SetFont(tWidget.pBarTextFont);
      GUI_SetColor(tWidget.BarTextColor[tWidget.State]);
      GUI_SetTextMode(GUI_TM_TRANS);
      GUI_DispStringInRect(SelText, &rWin, GUI_TA_VCENTER | GUI_TA_HCENTER);
      //GUI_SetClipRect(NULL);
      break;
      
    case WM_KEY:
      pKeyInfo = (WM_KEY_INFO *)pMsg->Data.p;
      if(pKeyInfo->PressedCnt >0)
      {
          switch(pKeyInfo->Key)
          {
            case GUI_KEY_SPACE:
            case GUI_KEY_ENTER:
              DEBUGOUT("DropDown <- KEY_ENTER, xDROPDOWN_Expand()\r\n");
              xDROPDOWN_Expand(hWin, &tWidget);
              break;
            /*
            case GUI_KEY_ESCAPE:
              DROPDOWN_Collapse(hWin);
              WM_SendMessage(WM_GetParent(hWin), pMsg);
              WM_SetFocus(WM_GetParent(hWin));
              break;
            */
            case GUI_KEY_LEFT:
              LoopCnt = 0;
              __GoPrevDropdownItem:
              ItemIndex = DROPDOWN_GetSel(hWin);
              if(ItemIndex > 0)
              {
                  DROPDOWN_DecSel(hWin);
                  ItemIndex--;
              }
              else
              {
                  ItemIndex = DROPDOWN_GetNumItems(hWin) - 1;
                  DROPDOWN_SetSel(hWin,ItemIndex);
              }
              ItemIndex = DROPDOWN_GetSel(hWin);
              DEBUGOUT("DropDown: --Idx: %d\r\n", ItemIndex);
              if(tWidget.paDropDownItems[ItemIndex].State == xDROPDOWN_ITEM_DISABLE)
              {
                  if(++LoopCnt < DROPDOWN_GetNumItems(hWin))
                  {
                      goto __GoPrevDropdownItem;
                  }
              }
              break;
              
            case GUI_KEY_RIGHT:
              LoopCnt = 0;
              __GoNextDropdownItem:
              ItemIndex = DROPDOWN_GetSel(hWin);
              if(ItemIndex >= DROPDOWN_GetNumItems(hWin) - 1)
              {
                  DROPDOWN_SetSel(hWin, 0);
              }
              else
              {
                  DROPDOWN_IncSel(hWin);
              }
              ItemIndex = DROPDOWN_GetSel(hWin);
              DEBUGOUT("DropDown: ++Idx: %d\r\n", ItemIndex);
              if(tWidget.paDropDownItems[ItemIndex].State == xDROPDOWN_ITEM_DISABLE)
              {
                  if(++LoopCnt < DROPDOWN_GetNumItems(hWin))
                  {
                      goto __GoNextDropdownItem;
                  }
              }
              break;
            
            case GUI_KEY_UP:
            case GUI_KEY_DOWN:
              if(tWidget.hListBox == 0)
              {
                  WM_SetFocus(WM_GetParent(hWin));
              }
              return;
              
            default:
              DROPDOWN_Callback(pMsg);
              break;
          }
      }
      break;
    
      
    case WM_SET_FOCUS:
      if (pMsg->Data.v)
      {
          pMsg->Data.v = 0;
          DEBUGOUT("xDROPDOWN(0x%08x) Has Focus\r\n",hWin);
          
          if(tWidget.hListBox == 0)
          {
              tMsg.MsgId = WM_KEY;
              tMsg.hWinSrc = hWin;
              tMsg.Data.p = &tKEY_Info;
              tKEY_Info.Key = GUI_KEY_ESCAPE;
              tKEY_Info.PressedCnt = 1;
              WM_SendMessage(WM_GetParent(hWin), &tMsg);
              WM_SendMessage(WM_GetParent(hWin), &tMsg);
          }
      }
      else
      {
          //if(tWidget.State == xDROPDOWN_FOCUSED)
          //{
          //    tWidget.State = xDROPDOWN_ENABLE;
          //    WM_SetUserData(hWin, &tWidget, sizeof(xDROPDOWN_Obj));
          //}
          DEBUGOUT("xDROPDOWN(0x%08x) lost Focus\r\n",hWin);
      }
      WM_InvalidateWindow(hWin);
      break;
    
    default:
      DROPDOWN_Callback(pMsg);
      break;
  }
}
