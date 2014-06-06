/*********************************************************************
*                Golden-IC Technology Co.,Ltd                        *
*                       www.golden-ic.com                            *
**********************************************************************
*        (c) 2007 - 2014 Golden-IC Technology Co., Ltd               *
*                                                                    *
**********************************************************************
*/
#include <stdlib.h>

#include "GUI.h"
#include "Custom_Widget.h"
#include "xBUTTON.h"
#include "xDIALOG.h"
#include "DIALOG.h"
#include "xSLIDER.h"
#include "SLIDER.h"
#include "DROPDOWN.h"
#include "xDROPDOWN.h"

#include "board.h"

/*********************************************************************
*
*       Font Type
*
**********************************************************************
*/
extern GUI_CONST_STORAGE GUI_FONT GUI_FontAR_Mingti_Medium_B523;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontArial19;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHG_GB_Gothic23;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHGGothicB19;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHGPGothicB19;

/*********************************************************************
*
*       BMP data
*
**********************************************************************
*/
extern GUI_CONST_STORAGE GUI_BITMAP bmbt_w470_h36_n;
extern GUI_CONST_STORAGE GUI_BITMAP bmbt_w470_h36_f;
extern GUI_CONST_STORAGE GUI_BITMAP bmbt_w470_h36_h;
extern GUI_CONST_STORAGE GUI_BITMAP bmbt_w174_h30_f;
extern GUI_CONST_STORAGE GUI_BITMAP bmbt_w190_h26_f_1;
extern GUI_CONST_STORAGE GUI_BITMAP bmbt_w190_h26_n_a;
extern GUI_CONST_STORAGE GUI_BITMAP bmbt_w190_h26_a;
extern GUI_CONST_STORAGE GUI_BITMAP bmbase_44_26;

extern GUI_CONST_STORAGE GUI_BITMAP bmmark_slider_off;
extern GUI_CONST_STORAGE GUI_BITMAP bmmark_slider_on;
extern GUI_CONST_STORAGE GUI_BITMAP bmbase_slider_off;
extern GUI_CONST_STORAGE GUI_BITMAP bmbase_slider_on;
extern GUI_CONST_STORAGE GUI_BITMAP bmbase_slider_on_blue;
extern GUI_CONST_STORAGE GUI_BITMAP bmbase_slider_on_blue_pixel_v;
extern GUI_CONST_STORAGE GUI_BITMAP bmbase_slider_on_red;
extern GUI_CONST_STORAGE GUI_BITMAP bmbase_slider_on_red_pixel_v;
extern GUI_CONST_STORAGE GUI_BITMAP bmbase_slider_on_green;

extern GUI_CONST_STORAGE GUI_BITMAP bmmark_check;



/*********************************************************************
*
*       Widget ID
*
**********************************************************************
*/
#define ID_SLIDER_START (xID_SLIDER_START + 0)
#define ID_SLIDER0      (ID_SLIDER_START + 0)
#define ID_SLIDER1      (ID_SLIDER_START + 1)
#define ID_SLIDER2      (ID_SLIDER_START + 2)
#define ID_SLIDER3      (ID_SLIDER_START + 3)
#define ID_SLIDER4      (ID_SLIDER_START + 4)
#define ID_SLIDER5      (ID_SLIDER_START + 5)
#define ID_SLIDER6      (ID_SLIDER_START + 6)
#define ID_SLIDER7      (ID_SLIDER_START + 7)
#define ID_SLIDER8      (ID_SLIDER_START + 8)
#define ID_SLIDER9      (ID_SLIDER_START + 9)

#define ID_DROPDOWN_START (xID_DROPDOWN_START + 0)
#define ID_DROPDOWN0   (ID_DROPDOWN_START + 0)
#define ID_DROPDOWN1   (ID_DROPDOWN_START + 1)
#define ID_DROPDOWN2   (ID_DROPDOWN_START + 2)
#define ID_DROPDOWN3   (ID_DROPDOWN_START + 3)
#define ID_DROPDOWN4   (ID_DROPDOWN_START + 4)
#define ID_DROPDOWN5   (ID_DROPDOWN_START + 5)
#define ID_DROPDOWN6   (ID_DROPDOWN_START + 6)
#define ID_DROPDOWN7   (ID_DROPDOWN_START + 7)
#define ID_DROPDOWN8   (ID_DROPDOWN_START + 8)
#define ID_DROPDOWN9   (ID_DROPDOWN_START + 9)

#define ID_TEXT_START  (xID_TEXT_START + 0)
#define ID_TEXT0       (ID_TEXT_START + 0)
#define ID_TEXT1       (ID_TEXT_START + 1)
#define ID_TEXT2       (ID_TEXT_START + 2)
#define ID_TEXT3       (ID_TEXT_START + 3)
#define ID_TEXT4       (ID_TEXT_START + 4)
#define ID_TEXT5       (ID_TEXT_START + 5)
#define ID_TEXT6       (ID_TEXT_START + 6)
#define ID_TEXT7       (ID_TEXT_START + 7)
#define ID_TEXT8       (ID_TEXT_START + 8)
#define ID_TEXT9       (ID_TEXT_START + 9)
#define ID_TEXT10      (ID_TEXT_START + 10)
#define ID_TEXT11      (ID_TEXT_START + 11)
#define ID_TEXT12      (ID_TEXT_START + 12)
#define ID_TEXT13      (ID_TEXT_START + 13)
#define ID_TEXT14      (ID_TEXT_START + 14)
#define ID_TEXT15      (ID_TEXT_START + 15)
#define ID_TEXT16      (ID_TEXT_START + 16)
#define ID_TEXT17      (ID_TEXT_START + 17)
#define ID_TEXT18      (ID_TEXT_START + 18)
#define ID_TEXT19      (ID_TEXT_START + 19)
#define ID_TEXT20      (ID_TEXT_START + 20)


#define ID_WIN_START   (xID_WINDOW_START + 0)
#define ID_WIN0        (ID_WIN_START + 0)
#define ID_WIN1        (ID_WIN_START + 1)
#define ID_WIN2        (ID_WIN_START + 2)
#define ID_WIN3        (ID_WIN_START + 3)
#define ID_WIN4        (ID_WIN_START + 4)
#define ID_WIN5        (ID_WIN_START + 5)
#define ID_WIN6        (ID_WIN_START + 6)
#define ID_WIN7        (ID_WIN_START + 7)
#define ID_WIN8        (ID_WIN_START + 8)
#define ID_WIN9        (ID_WIN_START + 9)

#define ID_BTN_START   (xID_BTN_START + 0)
#define ID_BTN0        (ID_BTN_START + 0)
#define ID_BTN1        (ID_BTN_START + 1)
#define ID_BTN2        (ID_BTN_START + 2)
#define ID_BTN3        (ID_BTN_START + 3)
#define ID_BTN4        (ID_BTN_START + 4)
#define ID_BTN5        (ID_BTN_START + 5)
#define ID_BTN6        (ID_BTN_START + 6)
#define ID_BTN7        (ID_BTN_START + 7)
#define ID_BTN8        (ID_BTN_START + 8)
#define ID_BTN9        (ID_BTN_START + 9)
#define ID_BTN10       (ID_BTN_START + 10)
#define ID_BTN11       (ID_BTN_START + 11)

#define ID_IMAGE_START (xID_IMAGE_START+0)
#define ID_IMAGE0      (ID_IMAGE_START+0)
#define ID_IMAGE1      (ID_IMAGE_START+1)
#define ID_IMAGE2      (ID_IMAGE_START+2)
#define ID_IMAGE3      (ID_IMAGE_START+3)
#define ID_IMAGE4      (ID_IMAGE_START+4)
#define ID_IMAGE5      (ID_IMAGE_START+5)
#define ID_IMAGE6      (ID_IMAGE_START+6)
#define ID_IMAGE7      (ID_IMAGE_START+7)
#define ID_IMAGE8      (ID_IMAGE_START+8)
#define ID_IMAGE9      (ID_IMAGE_START+9)


/*********************************************************************
*
*       xBUTTON
*/
static const xBUTTON_Obj xBUTTON0 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "HDMI"        ,                    //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,      //TextAlign
  {13,0,456,36},                     //GUI_RECT TextRect;
  &GUI_FontHGPGothicB19,             //GUI_FONT* pFont
  {                                  //TextColor;
    GUI_TEXT_COLOR_DISABLE,
    GUI_TEXT_COLOR_NORMAL,
    GUI_TEXT_COLOR_FOCUS,
    GUI_TEXT_COLOR_HISTORY
  },
  0                                  //NumExtraBytes;
};


/*********************************************************************
*
*       Dialog Widget
*/
static const GUI_WIDGET_CREATE_INFO _DialogWindow[] =
{
  { WINDOW_CreateIndirect,                 NULL, ID_WIN0,    0,   0,  480, 460, FRAMEWIN_CF_MOVEABLE },
  
  { TEXT_CreateIndirect,"Input"                , ID_TEXT0 ,  24,  18,  162,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"Resolution"           , ID_TEXT1 ,  24,  54,  162,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"H Frequency"          , ID_TEXT2 ,  24,  90,  162,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"V Frequency"          , ID_TEXT3 ,  24, 126,  162,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"Deep Color"           , ID_TEXT4 ,  24, 162,  162,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"Lamp Time"            , ID_TEXT5 ,  24, 198,  162,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"Soft Ver"             , ID_TEXT6 ,  24, 234,  162,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  
  { TEXT_CreateIndirect,":"                    , ID_TEXT7 , 225,  18,   14,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,":"                    , ID_TEXT8 , 225,  54,   14,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,":"                    , ID_TEXT9 , 225,  90,   14,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,":"                    , ID_TEXT10, 225, 126,   14,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,":"                    , ID_TEXT11, 225, 162,   14,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,":"                    , ID_TEXT12, 225, 198,   14,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,":"                    , ID_TEXT13, 225, 234,   14,  18, TEXT_CF_LEFT    | TEXT_CF_VCENTER},
  
  { TEXT_CreateIndirect,"HDMI-1"               , ID_TEXT14, 265,  18,  162,  18, TEXT_CF_HCENTER | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"800x600"              , ID_TEXT15, 265,  54,  162,  18, TEXT_CF_HCENTER | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"37.87 KHz"            , ID_TEXT16, 265,  90,  162,  18, TEXT_CF_HCENTER | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"60.31 Hz"             , ID_TEXT17, 265, 126,  162,  18, TEXT_CF_HCENTER | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"8 bit"                , ID_TEXT18, 265, 162,  162,  18, TEXT_CF_HCENTER | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"88 H"                 , ID_TEXT19, 265, 198,  162,  18, TEXT_CF_HCENTER | TEXT_CF_VCENTER},
  { TEXT_CreateIndirect,"0.31"                 , ID_TEXT20, 265, 234,  162,  18, TEXT_CF_HCENTER | TEXT_CF_VCENTER},
};
  



/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Win_Callback
*/
static void _Win_Callback(WM_MESSAGE * pMsg)
{
    WM_HWIN hItem;
    WM_HWIN hDlg;
    
    hDlg = pMsg->hWin;
    
    switch (pMsg->MsgId)
    {
      case WM_INIT_DIALOG:
          //hItem = WM_GetDialogItem(hDlg, GUI_ID_MULTIEDIT0);
          //MULTIEDIT_SetText(hItem, "MULTIEDIT widget");
          //MULTIEDIT_SetInsertMode(hItem, 1);
        break;
        
      default:
        WM_DefaultProc(pMsg);
        break;
    }
}


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
WM_HWIN InformationWin_Init(WM_HWIN hMultiPage)
{
    WM_HWIN hDialog;
    WM_HWIN hItem;
    int i, Id;
     
    hDialog = GUI_CreateDialogBox(_DialogWindow, GUI_COUNTOF(_DialogWindow), NULL, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hMultiPage, hDialog, "Information");
    DEBUGOUT("InformationWin_Init(): MULTIPAGE_AddPage(): hDialog:0x%08x\r\n", hDialog);
    
    for( i=0, Id=ID_TEXT0; Id<=ID_TEXT13; Id++, i++)
    {
        hItem = WM_GetDialogItem(hDialog, Id);
        if(hItem)
        {
            TEXT_SetFont(hItem, &GUI_FontHGPGothicB19);
            TEXT_SetTextColor(hItem, GUI_UI_COLOR1);
            DEBUGOUT("InformationWin_Init():TEXT_Set...(): hItem: 0x%08x\r\n", hItem);
        }
    }
    
    for( i=0, Id=ID_TEXT14; Id<=ID_TEXT20; Id++, i++)
    {
        hItem = WM_GetDialogItem(hDialog, Id);
        if(hItem)
        {
            TEXT_SetFont(hItem, &GUI_FontHGPGothicB19);
            TEXT_SetTextColor(hItem, GUI_UI_COLOR4);
            DEBUGOUT("InformationWin_Init():TEXT_Set...(): hItem: 0x%08x\r\n", hItem);
        }
    }
    return hDialog;
}
