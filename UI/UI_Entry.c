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
#include "MULTIPAGE.h"
#include "xMultiPage.h"
#include "board.h"

#include "ImageAdjustWin.h"
#include "InputSignalWin.h"
#include "InstallationWin.h"
#include "DisplaySetupWin.h"
#include "FunctionWin.h"
#include "InformationWin.h"


    
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
*       BMP
*
**********************************************************************
*/
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_1f;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_1h;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_1n;

extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_2f;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_2h;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_2n;

extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_3f;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_3h;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_3n;

extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_4f;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_4h;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_4n;

extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_5f;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_5h;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_5n;

extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_6f;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_6h;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_1_6n;

/*********************************************************************
*
*       Multipage Icon data
*
**********************************************************************
*/
const WIDGET_MULTIPAGE_Obj WidgetxMultiPageSetting =
{
    {NOT_SELECTED,NOT_SELECTED,NOT_SELECTED,NOT_SELECTED,NOT_SELECTED,NOT_SELECTED},
    {
        {&bmicon_1_1n,&bmicon_1_1f,&bmicon_1_1h},
        {&bmicon_1_2n,&bmicon_1_2f,&bmicon_1_2h},
        {&bmicon_1_3n,&bmicon_1_3f,&bmicon_1_3h},
        {&bmicon_1_4n,&bmicon_1_4f,&bmicon_1_4h},
        {&bmicon_1_5n,&bmicon_1_5f,&bmicon_1_5h},
        {&bmicon_1_6n,&bmicon_1_6f,&bmicon_1_6h},
    },
    {GUI_WHITE, GUI_UI_COLOR2, GUI_UI_COLOR1}, //PageTextColor
    GUI_UI_COLOR7,
    GUI_UI_COLOR6,
    {   0,   0, 479,  85},
    {   0,  86, 479, 545},
};


/*********************************************************************
*
*       UI_Entry
*/
void UI_Entry(void)
{
    WM_HWIN hMultiPage;
    WM_HWIN hDialog;
    WM_HWIN hItem;
    int i, Id;
    
    WINDOW_SetDefaultBkColor(GUI_UI_COLOR6);
    GUI_UC_SetEncodeUTF8();
    
    // Create the MULTIPAGE widget
    MULTIPAGE_SetDefaultFont(&GUI_FontHGPGothicB19);
    MULTIPAGE_SetDefaultBkColor(GUI_UI_COLOR6, 1);
    MULTIPAGE_SetDefaultBkColor(GUI_UI_COLOR7, 0);
    MULTIPAGE_SetDefaultTextColor(GUI_WHITE, 1);
    MULTIPAGE_SetDefaultTextColor(GUI_LIGHTGRAY, 0);
    
    
    hMultiPage = MULTIPAGE_CreateUser(0, 0, 480, 600, NULL, WM_CF_SHOW, 0, 0, sizeof(WIDGET_MULTIPAGE_Obj));
    WM_SetCallback(hMultiPage, xMultiPage_Callback);
    DEBUGOUT("MainTask():MULTIPAGE_CreateUser(): hWin:0x%08x\r\n", hMultiPage);
    MULTIPAGE_SetUserData(hMultiPage, &WidgetxMultiPageSetting , sizeof(WIDGET_MULTIPAGE_Obj));
    MULTIPAGE_SetAlign(hMultiPage, MULTIPAGE_ALIGN_LEFT | MULTIPAGE_ALIGN_TOP);
    
    
    //Call each Page Window Init()
    ImageAdjustWin_Init(hMultiPage);
    GUI_Delay(1);
    InputSignalWin_Init(hMultiPage);
    GUI_Delay(1);
    InstallationWin_Init(hMultiPage);
    GUI_Delay(1);
    DisplaySetupWin_Init(hMultiPage);
    GUI_Delay(1);
    FunctionWin_Init(hMultiPage);
    GUI_Delay(1);
    InformationWin_Init(hMultiPage);
    
    MULTIPAGE_SelectPage(hMultiPage, 0);
}

/*************************** End of file ****************************/
