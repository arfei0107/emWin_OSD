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
#include "xMoveBtn.h"
#include "BUTTON.h"
#include "xKBbtn.h"
#include "xEDIT.h"

#include "GammaFormula.h"

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
#define ID_BTN12       (ID_BTN_START + 12)
#define ID_BTN13       (ID_BTN_START + 13)
#define ID_BTN14       (ID_BTN_START + 14)
#define ID_BTN15       (ID_BTN_START + 15)
#define ID_BTN16       (ID_BTN_START + 16)
#define ID_BTN17       (ID_BTN_START + 17)
#define ID_BTN18       (ID_BTN_START + 18)
#define ID_BTN19       (ID_BTN_START + 19)
#define ID_BTN20       (ID_BTN_START + 20)

#define ID_BTN21       (ID_BTN_START + 21)
#define ID_BTN22       (ID_BTN_START + 22)
#define ID_BTN23       (ID_BTN_START + 23)
#define ID_BTN24       (ID_BTN_START + 24)
#define ID_BTN25       (ID_BTN_START + 25)
#define ID_BTN26       (ID_BTN_START + 26)
#define ID_BTN27       (ID_BTN_START + 27)
#define ID_BTN28       (ID_BTN_START + 28)
#define ID_BTN29       (ID_BTN_START + 29)
#define ID_BTN30       (ID_BTN_START + 30)

#define ID_BTN31       (ID_BTN_START + 31)
#define ID_BTN32       (ID_BTN_START + 32)
#define ID_BTN33       (ID_BTN_START + 33)
#define ID_BTN34       (ID_BTN_START + 34)
#define ID_BTN35       (ID_BTN_START + 35)
#define ID_BTN36       (ID_BTN_START + 36)
#define ID_BTN37       (ID_BTN_START + 37)
#define ID_BTN38       (ID_BTN_START + 38)
#define ID_BTN39       (ID_BTN_START + 39)
#define ID_BTN40       (ID_BTN_START + 40)

#define ID_BTN41       (ID_BTN_START + 41)
#define ID_BTN42       (ID_BTN_START + 42)
#define ID_BTN43       (ID_BTN_START + 43)
#define ID_BTN44       (ID_BTN_START + 44)
#define ID_BTN45       (ID_BTN_START + 45)
#define ID_BTN46       (ID_BTN_START + 46)
#define ID_BTN47       (ID_BTN_START + 47)
#define ID_BTN48       (ID_BTN_START + 48)
#define ID_BTN49       (ID_BTN_START + 49)
#define ID_BTN50       (ID_BTN_START + 50)

#define ID_BTN51       (ID_BTN_START + 51)
#define ID_BTN52       (ID_BTN_START + 52)
#define ID_BTN53       (ID_BTN_START + 53)
#define ID_BTN54       (ID_BTN_START + 54)
#define ID_BTN55       (ID_BTN_START + 55)
#define ID_BTN56       (ID_BTN_START + 56)
#define ID_BTN57       (ID_BTN_START + 57)
#define ID_BTN58       (ID_BTN_START + 58)
#define ID_BTN59       (ID_BTN_START + 59)
#define ID_BTN60       (ID_BTN_START + 60)

#define ID_BTN61       (ID_BTN_START + 61)
#define ID_BTN62       (ID_BTN_START + 62)
#define ID_BTN63       (ID_BTN_START + 63)
#define ID_BTN64       (ID_BTN_START + 64)
#define ID_BTN65       (ID_BTN_START + 65)
#define ID_BTN66       (ID_BTN_START + 66)
#define ID_BTN67       (ID_BTN_START + 67)
#define ID_BTN68       (ID_BTN_START + 68)
#define ID_BTN69       (ID_BTN_START + 69)
#define ID_BTN70       (ID_BTN_START + 70)

#define ID_BTN71       (ID_BTN_START + 71)
#define ID_BTN72       (ID_BTN_START + 72)
#define ID_BTN73       (ID_BTN_START + 73)
#define ID_BTN74       (ID_BTN_START + 74)
#define ID_BTN75       (ID_BTN_START + 75)
#define ID_BTN76       (ID_BTN_START + 76)
#define ID_BTN77       (ID_BTN_START + 77)
#define ID_BTN78       (ID_BTN_START + 78)
#define ID_BTN79       (ID_BTN_START + 79)
#define ID_BTN80       (ID_BTN_START + 80)

#define ID_BTN81       (ID_BTN_START + 81)
#define ID_BTN82       (ID_BTN_START + 82)
#define ID_BTN83       (ID_BTN_START + 83)
#define ID_BTN84       (ID_BTN_START + 84)
#define ID_BTN85       (ID_BTN_START + 85)
#define ID_BTN86       (ID_BTN_START + 86)
#define ID_BTN87       (ID_BTN_START + 87)
#define ID_BTN88       (ID_BTN_START + 88)
#define ID_BTN89       (ID_BTN_START + 89)
#define ID_BTN90       (ID_BTN_START + 90)

#define ID_BTN91       (ID_BTN_START + 91)
#define ID_BTN92       (ID_BTN_START + 92)
#define ID_BTN93       (ID_BTN_START + 93)
#define ID_BTN94       (ID_BTN_START + 94)
#define ID_BTN95       (ID_BTN_START + 95)
#define ID_BTN96       (ID_BTN_START + 96)
#define ID_BTN97       (ID_BTN_START + 97)
#define ID_BTN98       (ID_BTN_START + 98)
#define ID_BTN99       (ID_BTN_START + 99)
#define ID_BTN100      (ID_BTN_START + 100)


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
  "Picture Mode",                    //*pText
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

static const xBUTTON_Obj xBUTTON1 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Color Profile",                   //*pText
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

static const xBUTTON_Obj xBUTTON2 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Color Temp.",                     //*pText
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

static const xBUTTON_Obj xBUTTON3 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Gamma",                           //*pText
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

static const xBUTTON_Obj xBUTTON4 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Dark/Bright Level",               //*pText
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

static const xBUTTON_Obj xBUTTON5 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Picture Tones",                   //*pText
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

static const xBUTTON_Obj xBUTTON6 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Contrast",                        //*pText
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

static const xBUTTON_Obj xBUTTON7 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Brightness",                      //*pText
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

static const xBUTTON_Obj xBUTTON8 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Color",                           //*pText
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

static const xBUTTON_Obj xBUTTON9 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_n, 
    &bmbt_w470_h36_f,
    &bmbt_w470_h36_h
  },
  "Tint",                            //*pText
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

static const xBUTTON_Obj xBUTTON10 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w190_h26_n_a, 
    &bmbt_w190_h26_n_a, 
    &bmbt_w190_h26_f_1,
    &bmbt_w190_h26_f_1,
  },
  
  "Advanced",                        //*pText
  GUI_TA_HCENTER | GUI_TA_VCENTER,   //TextAlign
  {0,0,190,26},                      //GUI_RECT TextRect;
  &GUI_FontHGPGothicB19,             //GUI_FONT* pFont
  {                                  //TextColor;
    GUI_TEXT_COLOR_DISABLE,
    GUI_TEXT_COLOR_OTHERS,
    GUI_TEXT_COLOR_FOCUS,
    GUI_TEXT_COLOR_HISTORY
  },
  0                                  //NumExtraBytes;
};

static const xBUTTON_Obj xBUTTON11 =
{
  xBUTTON_NORMAL,                    //eButtonState
  
  {                                  //GUI_BITMAP* aBmp[4];
    &bmbt_w190_h26_n_a, 
    &bmbt_w190_h26_n_a, 
    &bmbt_w190_h26_f_1,
    &bmbt_w190_h26_f_1,
  },
  
  "Reset",                           //*pText
  GUI_TA_HCENTER | GUI_TA_VCENTER,   //TextAlign
  {0,0,190,26},                      //GUI_RECT TextRect;
  &GUI_FontHGPGothicB19,             //GUI_FONT* pFont
  {                                  //TextColor;
    GUI_TEXT_COLOR_DISABLE,
    GUI_TEXT_COLOR_OTHERS,
    GUI_TEXT_COLOR_FOCUS,
    GUI_TEXT_COLOR_HISTORY
  },
  0                                  //NumExtraBytes;
};


/*********************************************************************
*
*       xKB_BTN
*
**********************************************************************
*/
#define KEYBOARD_TABLE_ROWS 8
#define KEYBOARD_TABLE_COLUMNS 13

const tKB_KEY KeyBoard_CodeList[95] = 
{
    {"A",'A'}, {"B" ,'B' }, {"C",'C'}, {"D",'D'}, {"E",'E'}, {"F",'F'}, {"G",'G'}, {"H",'H'}, {"I",'I'}, {"J",'J'}, {"K",'K'}, {"L",'L'}, {"M",'M'},
    {"N",'N'}, {"O" ,'O' }, {"P",'P'}, {"Q",'Q'}, {"R",'R'}, {"S",'S'}, {"T",'T'}, {"U",'U'}, {"V",'V'}, {"W",'W'}, {"X",'X'}, {"Y",'Y'}, {"Z",'Z'},
    {"a",'a'}, {"b" ,'b' }, {"c",'c'}, {"d",'d'}, {"e",'e'}, {"f",'f'}, {"g",'g'}, {"h",'h'}, {"i",'i'}, {"j",'j'}, {"k",'k'}, {"l",'l'}, {"m",'m'},
    {"n",'n'}, {"o" ,'o' }, {"p",'p'}, {"q",'q'}, {"r",'r'}, {"s",'s'}, {"t",'t'}, {"u",'u'}, {"v",'v'}, {"w",'w'}, {"x",'x'}, {"y",'y'}, {"z",'z'},
    {"1",'1'}, {"2" ,'2' }, {"3",'3'}, {"4",'4'}, {"5",'5'}, {"6",'6'}, {"7",'7'}, {"8",'8'}, {"9",'9'}, {"0",'0'}, {",",','}, {".",'.'}, {"^",'^'},
    {"!",'!'}, {"\"",'\"'}, {"#",'#'}, {"$",'$'}, {"%",'%'}, {"&",'&'}, {"*",'*'}, {"+",'+'}, {"-",'-'}, {"/",'/'}, {"=",'='}, {"?",'?'}, {"@",'@'},
    {":",':'}, {";" ,';' }, {"|",'|'}, {"~",'~'}, {"(",'('}, {")",')'}, {"<",'<'}, {">",'>'}, {"[",'['}, {"]",']'}, {"{",'{'}, {"}",'}'}, {"\\",'\\'},
            {"SPACE",' '},                      {"CLEAR",8},                      {"ALL CLEAR",GUI_KEY_DELETE},                {"OK",13},
};


WM_HWIN hKeyBoardTable[KEYBOARD_TABLE_ROWS][KEYBOARD_TABLE_COLUMNS]=
{
    0
};


const xKB_BTN_Obj xKB_BTN_Init =
{
  xKB_BTN_NORMAL,                                   //eKB_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_HCENTER | GUI_TA_VCENTER,                  //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_BLACK, GUI_UI_COLOR14, GUI_UI_COLOR11, GUI_UI_COLOR13},  //aBkColor[4];
  {                                                 //tKB_DATA KB_SoftKey
    NULL,                                           //WM_HWIN*pKB_Table
    {0,0},                                          //tKB_XY  KB_TableSize;
    {0,0},                                          //tKB_XY  KB_KeyPosition;
    0x00,                                            //int     KeyCode;
  },
};



/*********************************************************************
*
*       xSLIDER
*
**********************************************************************
*/
#define SLIDER_H_SPACE 10

static const xSLIDER_Obj tSLIDER0 =
{
    WIDGET_ENABLE,
    {0,100},
    50,
    SLIDER_H_SPACE,
    &bmbase_slider_on,
    &bmbase_slider_off,
    &bmmark_slider_on,
    &bmmark_slider_off
};

static const xSLIDER_Obj tSLIDER1 =
{
    WIDGET_ENABLE,
    {0,100},
    50,
    SLIDER_H_SPACE,
    &bmbase_slider_on,
    &bmbase_slider_off,
    &bmmark_slider_on,
    &bmmark_slider_off
};

static const xSLIDER_Obj tSLIDER2 =
{
    WIDGET_ENABLE,
    {0,100},
    50,
    SLIDER_H_SPACE,
    &bmbase_slider_on,
    &bmbase_slider_off,
    &bmmark_slider_on,
    &bmmark_slider_off
};

static const xSLIDER_Obj tSLIDER3 =
{
    WIDGET_ENABLE,
    {0,100},
    50,
    SLIDER_H_SPACE,
    &bmbase_slider_on,
    &bmbase_slider_off,
    &bmmark_slider_on,
    &bmmark_slider_off
};

static const xSLIDER_Obj* pSliderSettingTable[] =
{
    (const xSLIDER_Obj*)&tSLIDER0,
    (const xSLIDER_Obj*)&tSLIDER1,
    (const xSLIDER_Obj*)&tSLIDER2,
    (const xSLIDER_Obj*)&tSLIDER3,
};

/*********************************************************************
*
*       aPictureModeItems
*
**********************************************************************
*/
static xDROPDOWN_ITEM aPictureModeItems[] = 
{
    {"Film"       ,xDROPDOWN_ITEM_ENABLE},
    {"Cinema"     ,xDROPDOWN_ITEM_ENABLE},
    {"Animation"  ,xDROPDOWN_ITEM_ENABLE},
    {"Natural"    ,xDROPDOWN_ITEM_ENABLE},
    {"Stage"      ,xDROPDOWN_ITEM_ENABLE},
    {"3D"         ,xDROPDOWN_ITEM_ENABLE},
    {"User1"      ,xDROPDOWN_ITEM_ENABLE},
    {"User2"      ,xDROPDOWN_ITEM_ENABLE},
    {"User3"      ,xDROPDOWN_ITEM_ENABLE},
    {"User4"      ,xDROPDOWN_ITEM_ENABLE},
    {"User5"      ,xDROPDOWN_ITEM_ENABLE},
    {"isf-DAY"    ,xDROPDOWN_ITEM_ENABLE},
    {"isf-NIGHT"  ,xDROPDOWN_ITEM_ENABLE},
};

static xDROPDOWN_ITEM aColorProfileItems[] = 
{
    {"Standard" ,xDROPDOWN_ITEM_ENABLE},
    {"Cinema"   ,xDROPDOWN_ITEM_ENABLE},
    {"Anime"    ,xDROPDOWN_ITEM_ENABLE},
    {"Natural"  ,xDROPDOWN_ITEM_ENABLE},
    {"Stage"    ,xDROPDOWN_ITEM_ENABLE},
    {"3D"       ,xDROPDOWN_ITEM_ENABLE},
    {"Off"      ,xDROPDOWN_ITEM_ENABLE},
};

static xDROPDOWN_ITEM aColorTempItems[] = 
{
    {"5500K"      ,xDROPDOWN_ITEM_ENABLE},
    {"6000K"      ,xDROPDOWN_ITEM_ENABLE},
    {"6500K"      ,xDROPDOWN_ITEM_ENABLE},
    {"7000K"      ,xDROPDOWN_ITEM_ENABLE},
    {"7500K"      ,xDROPDOWN_ITEM_ENABLE},
    {"8000K"      ,xDROPDOWN_ITEM_ENABLE},
    {"8500K"      ,xDROPDOWN_ITEM_ENABLE},
    {"9000K"      ,xDROPDOWN_ITEM_ENABLE},
    {"9500K"      ,xDROPDOWN_ITEM_ENABLE},
    {"High Bright",xDROPDOWN_ITEM_DISABLE},
    {"Custom1"    ,xDROPDOWN_ITEM_ENABLE},
    {"Custom2"    ,xDROPDOWN_ITEM_ENABLE},
    {"Custom3"    ,xDROPDOWN_ITEM_ENABLE},
};

static xDROPDOWN_ITEM aGammaItems[] = 
{
    {"Normal" ,xDROPDOWN_ITEM_ENABLE},
    {"A"      ,xDROPDOWN_ITEM_ENABLE},
    {"B"      ,xDROPDOWN_ITEM_ENABLE},
    {"C"      ,xDROPDOWN_ITEM_ENABLE},
    {"D"      ,xDROPDOWN_ITEM_ENABLE},
    {"E"      ,xDROPDOWN_ITEM_ENABLE},
    {"F"      ,xDROPDOWN_ITEM_ENABLE},
    {"G"      ,xDROPDOWN_ITEM_ENABLE},
    {"H"      ,xDROPDOWN_ITEM_ENABLE},
    {"Custom1",xDROPDOWN_ITEM_ENABLE},
    {"Custom2",xDROPDOWN_ITEM_ENABLE},
    {"Custom3",xDROPDOWN_ITEM_ENABLE},
};

/*
xDROPDOWN_ITEM aItems[] = 
{
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
    {""            ,xDROPDOWN_ITEM_ENABLE},
};
*/

static xDROPDOWN_Obj wPictureMode = 
{
    xDROPDOWN_ENABLE,                                              //eDROPDOWN_STATE      State;                                                            
    aPictureModeItems,                                             //xDROPDOWN_ITEM      *paDropDownItems;                                              
    GUI_COUNTOF(aPictureModeItems),                                //int                  NumItems;                                                     
    &bmbt_w190_h26_a,                                              //GUI_BITMAP*          pBtnBmp
    GUI_UI_COLOR8,
    {GUI_UI_COLOR3,GUI_UI_COLOR4,GUI_UI_COLOR4,GUI_UI_COLOR4},     //GUI_COLOR            BarTextColor[4];                                              
    &GUI_FontHGPGothicB19,                                         //const GUI_FONT      *pBarTextFont;
    {                                                              //GUI_RECT             ListBoxRect;
       479 - 75,// X0 = Physical X - 75
        94 - 27,// Y0 = Physical Y - 27 
       608,     //=X0 + 30 + 174,
         0,     // Y1: ignore, Widget will calculate it in run-time.
    },
    {GUI_UI_COLOR9,GUI_UI_COLOR2},                                 //GUI_COLOR            ListBoxRectBkColor[2]; //Color[0]: Outline, Color[1]:Fill RECT
    {GUI_UI_COLOR3,GUI_UI_COLOR1,GUI_UI_COLOR2},                   //GUI_COLOR            ListBoxTextColor[3];                                          
    &GUI_FontHGPGothicB19,                                         //const GUI_FONT      *pListBoxTextFont;                                             
    30,                                                            //int                  ListBoxItemHeight;                                            
    12,                                                            //int                  ListBoxItemAlignY0;                                           
    35,                                                            //int                  ListBoxTextAlignX0;                                           
    30,                                                            //int                  ListBoxItemFocusBmpAlignX0;                                   
    0,                                                             //int                  ListBoxIdx;                                                   
    &bmbt_w174_h30_f,                                              //GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemFocusBmp;                                
    2,                                                             //int                  ListBoxItemCheckedBmpAlignX0;                                 
    2,                                                             //int                  ListBoxItemCheckedBmpAlignY0;                                 
    &bmmark_check,                                                 //GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemCheckedBmp;                              
    NULL,                                                          //WM_HWIN              hListBox;                                                     
    NULL,                                                          //WM_HWIN              hDropdown;                                                    
    0                                                              //int                  WidgetInit;                                                   
};


static xDROPDOWN_Obj wColorProfile = 
{
    xDROPDOWN_ENABLE,                                              //eDROPDOWN_STATE      State;                                                            
    aColorProfileItems,                                            //xDROPDOWN_ITEM      *paDropDownItems;                                              
    GUI_COUNTOF(aColorProfileItems),                               //int                  NumItems;                                                     
    &bmbt_w190_h26_a,                                              //GUI_BITMAP*          pBtnBmp
    GUI_UI_COLOR8,
    {GUI_UI_COLOR3,GUI_UI_COLOR4,GUI_UI_COLOR4,GUI_UI_COLOR4},     //GUI_COLOR            BarTextColor[4];                                              
    &GUI_FontHGPGothicB19,                                         //const GUI_FONT      *pBarTextFont;
    {                                                              //GUI_RECT             ListBoxRect;
       479 - 75,// X0 = Physical X - 75
       144 - 27,// Y0 = Physical Y - 27 
       608,     //=X0 + 30 + 174,
         0,     // Y1: ignore, Widget will calculate it in run-time.
    },
    {GUI_UI_COLOR9,GUI_UI_COLOR2},                                 //GUI_COLOR            ListBoxRectBkColor[2]; //Color[0]: Outline, Color[1]:Fill RECT
    {GUI_UI_COLOR3,GUI_UI_COLOR1,GUI_UI_COLOR2},                   //GUI_COLOR            ListBoxTextColor[3];                                          
    &GUI_FontHGPGothicB19,                                         //const GUI_FONT      *pListBoxTextFont;                                             
    30,                                                            //int                  ListBoxItemHeight;                                            
    12,                                                            //int                  ListBoxItemAlignY0;                                           
    35,                                                            //int                  ListBoxTextAlignX0;                                           
    30,                                                            //int                  ListBoxItemFocusBmpAlignX0;                                   
    0,                                                             //int                  ListBoxIdx;                                                   
    &bmbt_w174_h30_f,                                              //GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemFocusBmp;                                
    2,                                                             //int                  ListBoxItemCheckedBmpAlignX0;                                 
    2,                                                             //int                  ListBoxItemCheckedBmpAlignY0;                                 
    &bmmark_check,                                                 //GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemCheckedBmp;                              
    NULL,                                                          //WM_HWIN              hListBox;                                                     
    NULL,                                                          //WM_HWIN              hDropdown;                                                    
    0                                                              //int                  WidgetInit;                                                   
};

static xDROPDOWN_Obj wColorTemp = 
{
    xDROPDOWN_ENABLE,                                              //eDROPDOWN_STATE      State;                                                            
    aColorTempItems,                                               //xDROPDOWN_ITEM      *paDropDownItems;                                              
    GUI_COUNTOF(aColorTempItems),                                  //int                  NumItems;                                                     
    &bmbt_w190_h26_a,                                              //GUI_BITMAP*          pBtnBmp
    GUI_UI_COLOR8,
    {GUI_UI_COLOR3,GUI_UI_COLOR4,GUI_UI_COLOR4,GUI_UI_COLOR4},     //GUI_COLOR            BarTextColor[4];                                              
    &GUI_FontHGPGothicB19,                                         //const GUI_FONT      *pBarTextFont;
    {                                                              //GUI_RECT             ListBoxRect;
       479 - 75,// X0 = Physical X - 75
       180 - 27,// Y0 = Physical Y - 27 
       608,     //=X0 + 30 + 174,
         0,     // Y1: ignore, Widget will calculate it in run-time.
    },
    {GUI_UI_COLOR9,GUI_UI_COLOR2},                                 //GUI_COLOR            ListBoxRectBkColor[2]; //Color[0]: Outline, Color[1]:Fill RECT
    {GUI_UI_COLOR3,GUI_UI_COLOR1,GUI_UI_COLOR2},                   //GUI_COLOR            ListBoxTextColor[3];                                          
    &GUI_FontHGPGothicB19,                                         //const GUI_FONT      *pListBoxTextFont;                                             
    30,                                                            //int                  ListBoxItemHeight;                                            
    12,                                                            //int                  ListBoxItemAlignY0;                                           
    35,                                                            //int                  ListBoxTextAlignX0;                                           
    30,                                                            //int                  ListBoxItemFocusBmpAlignX0;                                   
    0,                                                             //int                  ListBoxIdx;                                                   
    &bmbt_w174_h30_f,                                              //GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemFocusBmp;                                
    2,                                                             //int                  ListBoxItemCheckedBmpAlignX0;                                 
    2,                                                             //int                  ListBoxItemCheckedBmpAlignY0;                                 
    &bmmark_check,                                                 //GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemCheckedBmp;                              
    NULL,                                                          //WM_HWIN              hListBox;                                                     
    NULL,                                                          //WM_HWIN              hDropdown;                                                    
    0                                                              //int                  WidgetInit;                                                   
};


static xDROPDOWN_Obj wGamma = 
{
    xDROPDOWN_ENABLE,                                              //eDROPDOWN_STATE      State;                                                            
    aGammaItems,                                                   //xDROPDOWN_ITEM      *paDropDownItems;                                              
    GUI_COUNTOF(aGammaItems),                                      //int                  NumItems;                                                     
    &bmbt_w190_h26_a,                                              //GUI_BITMAP*          pBtnBmp
    GUI_UI_COLOR8,
    {GUI_UI_COLOR3,GUI_UI_COLOR4,GUI_UI_COLOR4,GUI_UI_COLOR4},     //GUI_COLOR            BarTextColor[4];                                              
    &GUI_FontHGPGothicB19,                                         //const GUI_FONT      *pBarTextFont;
    {                                                              //GUI_RECT             ListBoxRect;
       479 - 75,// X0 = Physical X - 75
       216 - 27,// Y0 = Physical Y - 27 
       608,     //=X0 + 30 + 174,
         0,     // Y1: ignore, Widget will calculate it in run-time.
    },
    {GUI_UI_COLOR9,GUI_UI_COLOR2},                                 //GUI_COLOR            ListBoxRectBkColor[2]; //Color[0]: Outline, Color[1]:Fill RECT
    {GUI_UI_COLOR3,GUI_UI_COLOR1,GUI_UI_COLOR2},                   //GUI_COLOR            ListBoxTextColor[3];                                          
    &GUI_FontHGPGothicB19,                                         //const GUI_FONT      *pListBoxTextFont;                                             
    30,                                                            //int                  ListBoxItemHeight;                                            
    12,                                                            //int                  ListBoxItemAlignY0;                                           
    35,                                                            //int                  ListBoxTextAlignX0;                                           
    30,                                                            //int                  ListBoxItemFocusBmpAlignX0;                                   
    0,                                                             //int                  ListBoxIdx;                                                   
    &bmbt_w174_h30_f,                                              //GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemFocusBmp;                                
    2,                                                             //int                  ListBoxItemCheckedBmpAlignX0;                                 
    2,                                                             //int                  ListBoxItemCheckedBmpAlignY0;                                 
    &bmmark_check,                                                 //GUI_CONST_STORAGE GUI_BITMAP* pListBoxItemCheckedBmp;                              
    NULL,                                                          //WM_HWIN              hListBox;                                                     
    NULL,                                                          //WM_HWIN              hDropdown;                                                    
    0                                                              //int                  WidgetInit;                                                   
};

static const xDROPDOWN_Obj* pDropdownSettingTable[]=
{
    (xDROPDOWN_Obj*)&wPictureMode,
    (xDROPDOWN_Obj*)&wColorProfile,
    (xDROPDOWN_Obj*)&wColorTemp,
    (xDROPDOWN_Obj*)&wGamma,
};


/*********************************************************************
*
*       xMOVE_BTN_Obj
*
**********************************************************************
*/

static int _GammaPoint_SetValue_cb(WM_HWIN hWin);

const xMOVE_BTN_Obj xMbtn1 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  84,                                               //Vidx;
  1,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};

const xMOVE_BTN_Obj xMbtn2 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  153,                                              //Vidx;
  2,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn3 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  215,                                              //Vidx;
  3,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn4 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  273,                                              //Vidx;
  4,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn5 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  379,                                              //Vidx;
  5,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn6 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  482,                                               //Vidx;
  6,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn7 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  581,                                              //Vidx;
  7,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn8 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  672,                                               //Vidx;
  8,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn9 =
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  764,                                              //Vidx;
  9,                                                //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn10=
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  850,                                              //Vidx;
  10,                                               //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn11=
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  938,                                              //Vidx;
  11,                                               //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};


const xMOVE_BTN_Obj xMbtn12=
{
  xM_BTN_NORMAL,                                           //eMOVE_BTN_STATE
  { NULL, NULL, NULL, NULL},                        //GUI_BITMAP* aBmp[4];
  NULL,                                             //*pText
  GUI_TA_LEFT | GUI_TA_VCENTER,                     //TextAlign
  {0,0,0,0},                                        //GUI_RECT TextRect;
  &GUI_Font13_1,                                    //GUI_FONT* pFont
  {GUI_DARKGRAY,GUI_WHITE, GUI_BLACK, GUI_YELLOW},  //aTextColor[4];
  {GUI_UI_COLOR1,GUI_UI_COLOR1, GUI_UI_COLOR11, GUI_UI_COLOR12},  //aBkColor[4];
  {0,1023},                                         //tVrange;
  256-1,                                            //VHeight;
  981,                                              //Vidx;
  12,                                               //BtnNum
  _GammaPoint_SetValue_cb,                          //pfSetValue
  0                                                 //NumExtraBytes;
};



/*********************************************************************
*
*       Dialog resource
*
*  These tables contain the information required to create the dialogs.
*  It has been created manually, but could also be created by the GUIBuilder.
*/

static const GUI_WIDGET_CREATE_INFO _DialogButton0[] ={
  { xBUTTON_CreateIndirect,   NULL, ID_BTN0,        12,  9, 470, 36,  0, (I32)&xBUTTON0},
  { DROPDOWN_CreateIndirect,  NULL, ID_DROPDOWN0,  248,  5, 190, 26,  0,             0x0, sizeof(xDROPDOWN_Obj)},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton1[] ={
  { xBUTTON_CreateIndirect,   NULL, ID_BTN1,        12, 60, 470, 36,  0, (I32)&xBUTTON1},
  { DROPDOWN_CreateIndirect,  NULL, ID_DROPDOWN1,  248,  5, 190, 26,  0,             0x0, sizeof(xDROPDOWN_Obj)},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton2[] ={
  { xBUTTON_CreateIndirect,   NULL, ID_BTN2,        12, 96, 470, 36,  0, (I32)&xBUTTON2},
  { DROPDOWN_CreateIndirect,  NULL, ID_DROPDOWN2,  248,  5, 190, 26,  0,             0x0, sizeof(xDROPDOWN_Obj)},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton3[] ={
  { xBUTTON_CreateIndirect,   NULL, ID_BTN3,        12,132, 470, 36,  0, (I32)&xBUTTON3},
  { DROPDOWN_CreateIndirect,  NULL, ID_DROPDOWN3,  248,  5, 190, 26,  0,             0x0, sizeof(xDROPDOWN_Obj)},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton4[] ={
  { xBUTTON_CreateIndirect,   NULL, ID_BTN4,        12,168, 470, 36,  0,(I32)&xBUTTON4},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton5[] ={
  { xBUTTON_CreateIndirect,   NULL, ID_BTN5,        12,204, 470, 36,  0,(I32)&xBUTTON5},
};


static const GUI_WIDGET_CREATE_INFO _DialogButton6[] ={
  { xBUTTON_CreateIndirect,   NULL,       ID_BTN6,            12, 240, 470,    36,  0, (I32)&xBUTTON6},
  { SLIDER_CreateIndirect,    NULL,       ID_SLIDER6,        248,   5, 190,    26,  0,             0x0, sizeof(xSLIDER_Obj) },
  { IMAGE_CreateIndirect,     NULL,       ID_IMAGE6,         192,   5,  44,    26,  WM_CF_SHOW },
  { TEXT_CreateIndirect,       "50",      ID_TEXT6,          192,   5,  44,    26,  TEXT_CF_HCENTER | TEXT_CF_VCENTER},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton7[] ={
  { xBUTTON_CreateIndirect,   NULL,       ID_BTN7,            12, 276, 470,    36,  0, (I32)&xBUTTON7},
  { SLIDER_CreateIndirect,    NULL,       ID_SLIDER7,        248,   5, 190,    26,  0,             0x0, sizeof(xSLIDER_Obj) },
  { IMAGE_CreateIndirect,     NULL,       ID_IMAGE7,         192,   5,  44,    26,  WM_CF_SHOW },
  { TEXT_CreateIndirect,       "50",      ID_TEXT7,          192,   5,  44,    26,  TEXT_CF_HCENTER | TEXT_CF_VCENTER},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton8[] ={
  { xBUTTON_CreateIndirect,   NULL,       ID_BTN8,            12, 312, 470,    36,  0, (I32)&xBUTTON8},
  { SLIDER_CreateIndirect,    NULL,       ID_SLIDER8,        248,   5, 190,    26,  0,             0x0, sizeof(xSLIDER_Obj) },
  { IMAGE_CreateIndirect,     NULL,       ID_IMAGE8,         192,   5,  44,    26,  WM_CF_SHOW },
  { TEXT_CreateIndirect,       "50",      ID_TEXT8,          192,   5,  44,    26,  TEXT_CF_HCENTER | TEXT_CF_VCENTER},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton9[] ={
  { xBUTTON_CreateIndirect,   NULL,       ID_BTN9,            12, 348, 470,    36,  0, (I32)&xBUTTON9},
  { SLIDER_CreateIndirect,    NULL,       ID_SLIDER9,        248,   5, 190,    26,  0,             0x0, sizeof(xSLIDER_Obj) },
  { IMAGE_CreateIndirect,     NULL,       ID_IMAGE9,         192,   5,  44,    26,  WM_CF_SHOW },
  { TEXT_CreateIndirect,       "50",      ID_TEXT9,          192,   5,  44,    26,  TEXT_CF_HCENTER | TEXT_CF_VCENTER},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton10[] ={
  { xBUTTON_CreateIndirect,   NULL, ID_BTN10,        20,432, 204, 26,  0,(I32)&xBUTTON10},
};

static const GUI_WIDGET_CREATE_INFO _DialogButton11[] ={
  { xBUTTON_CreateIndirect,   NULL, ID_BTN11,       260,432, 204, 26,  0,(I32)&xBUTTON11},
};


static const GUI_WIDGET_CREATE_INFO _DialogWindow[] ={
  { WINDOW_CreateIndirect,    NULL,       ID_WIN0,             0,   0, 480,   460, FRAMEWIN_CF_MOVEABLE },
};
    
static const xDIALOGBOX_Obj _DialogArray[] = 
{
  {_DialogWindow,  GUI_COUNTOF(_DialogWindow),  NULL},
  {_DialogButton0, GUI_COUNTOF(_DialogButton0), NULL},
  {_DialogButton1, GUI_COUNTOF(_DialogButton1), NULL},
  {_DialogButton2, GUI_COUNTOF(_DialogButton2), NULL},
  {_DialogButton3, GUI_COUNTOF(_DialogButton3), NULL},
  {_DialogButton4, GUI_COUNTOF(_DialogButton4), NULL},
  {_DialogButton5, GUI_COUNTOF(_DialogButton5), NULL},
  {_DialogButton6, GUI_COUNTOF(_DialogButton6), NULL},
  {_DialogButton7, GUI_COUNTOF(_DialogButton7), NULL},
  {_DialogButton8, GUI_COUNTOF(_DialogButton8), NULL},
  {_DialogButton9, GUI_COUNTOF(_DialogButton9), NULL},
  {_DialogButton10,GUI_COUNTOF(_DialogButton10),NULL},
  {_DialogButton11,GUI_COUNTOF(_DialogButton11),NULL},
};


//x[14]={0,12,25,38,51,76,102,128,153,179,204,230,243,255};
static const GUI_WIDGET_CREATE_INFO _DialogWindow1[] ={
  { WINDOW_CreateIndirect,    NULL,       ID_WIN1,             0,   0, 480,   460, FRAMEWIN_CF_MOVEABLE },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN1,            12,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn1 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN2,            25,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn2 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN3,            38,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn3 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN4,            51,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn4 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN5,            76,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn5 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN6,           102,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn6 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN7,           128,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn7 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN8,           153,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn8 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN9,           179,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn9 },
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN10,          204,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn10},
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN11,          230,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn11},
  { xMOVE_BTN_CreateIndirect, NULL,       ID_BTN12,          243,   0,   4,     4, WM_CF_MOTION_Y,  (I32)&xMbtn12},
};


static const GUI_WIDGET_CREATE_INFO _DialogWindow2[] ={
  { WINDOW_CreateIndirect,    NULL,       ID_WIN2,             0,   0, 480,   460, FRAMEWIN_CF_MOVEABLE },
  
  //btn 'A' ~ 'M'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN1,            40,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN2,            70,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN3,           100,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN4,           130,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN5,           160,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN6,           190,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN7,           220,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN8,           250,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN9,           280,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN10,          310,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN11,          340,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN12,          370,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN13,          400,  70,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  
  //btn 'N' ~ 'Z'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN14,           40, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN15,           70, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN16,          100, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN17,          130, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN18,          160, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN19,          190, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN20,          220, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN21,          250, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN22,          280, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN23,          310, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN24,          340, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN25,          370, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN26,          400, 110,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  
  //btn 'a' ~ 'm'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN27,           40, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN28,           70, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN29,          100, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN30,          130, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN31,          160, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN32,          190, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN33,          220, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN34,          250, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN35,          280, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN36,          310, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN37,          340, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN38,          370, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN39,          400, 150,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  
  //btn 'n' ~ 'z'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN40,           40, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN41,           70, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN42,          100, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN43,          130, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN44,          160, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN45,          190, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN46,          220, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN47,          250, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN48,          280, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN49,          310, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN50,          340, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN51,          370, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN52,          400, 190,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  
  //btn '1' ~ '^'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN53,           40, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN54,           70, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN55,          100, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN56,          130, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN57,          160, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN58,          190, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN59,          220, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN60,          250, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN61,          280, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN62,          310, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN63,          340, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN64,          370, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN65,          400, 230,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  
  //btn '!' ~ '@'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN66,           40, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN67,           70, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN68,          100, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN69,          130, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN70,          160, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN71,          190, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN72,          220, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN73,          250, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN74,          280, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN75,          310, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN76,          340, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN77,          370, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN78,          400, 270,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  
  //btn ':' ~ '\'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN79,           40, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN80,           70, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN81,          100, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN82,          130, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN83,          160, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN84,          190, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN85,          220, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN86,          250, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN87,          280, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN88,          310, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN89,          340, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN90,          370, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  { BUTTON_CreateIndirect,   NULL,       ID_BTN91,          400, 310,  24,    24, 0, 0, sizeof(xKB_BTN_Obj)},
  
  //btn 'Space'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN92,           40, 350,  84,    24, 0,  0, sizeof(xKB_BTN_Obj)},
  //btn 'Clear'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN93,          130, 350,  84,    24, 0,  0, sizeof(xKB_BTN_Obj)},
  //btn 'All Clear'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN94,          220, 350, 114,    24, 0,  0, sizeof(xKB_BTN_Obj)},
  //btn 'OK'
  { BUTTON_CreateIndirect,   NULL,       ID_BTN95,          340, 350,  84,    24, 0,  0, sizeof(xKB_BTN_Obj)},
  
  //Show Input String in EDIT widget
  {EDIT_CreateIndirect,      NULL,       GUI_ID_EDIT0,       60,  25, 270,    24, EDIT_CF_LEFT | EDIT_CF_VCENTER, 10, sizeof(xEDIT_Obj)},
};
  
const xEDIT_Obj xEdit1=
{
  NULL,
  &GUI_Font13_1,
  GUI_WHITE,
  {GUI_BLACK, GUI_UI_COLOR11, GUI_UI_COLOR11, GUI_UI_COLOR11}
};


    

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       xBtn_Advanced_Callback
*/
static void xBtn_Advanced_Callback(WM_MESSAGE * pMsg)
{
    
}



static int _GammaPoint_SetValue_cb(WM_HWIN hWin)
{
    xMOVE_BTN_Obj tBtn;
    int PointX;
    
    if(!hWin) return -1;
    
    WM_GetUserData(hWin, &tBtn, sizeof(xMOVE_BTN_Obj));
    PointX = GetGammaPointX_byIndex(tBtn.BtnNum);
    return SetGammaPoint(PointX, tBtn.Vidx);
}

/*********************************************************************
*
*       _WinDrawLines
*/
static void _WinDrawLines(WM_HWIN hWin)
{
    xMOVE_BTN_Handle hBtnIndex, hBtxNextIndex;
    GUI_RECT rBtn, rNextBtn;
    xMOVE_BTN_Obj tBtn;
    int i,PointX, TableSize;
    const WORD *pGammaTable;
    
    pGammaTable = GetGammaTable(&TableSize);
    if( ( pGammaTable ) && (TableSize > 0) )
    {
        GUI_SetColor(GUI_RED);
        GUI_SetLineStyle(GUI_LS_SOLID);
        
        for(i=0; i<TableSize; i++)
        {
            GUI_DrawPixel(i  , 480-18 - ((((int)(pGammaTable[i]))   * 255) / 1023) );
        }
        
            
        /*
        for(i=0; i<TableSize-1; i++)
        {
            //Draw Line
            GUI_DrawLine(i  , 480-18 - ((((int)(pGammaTable[i]))   * 255) / 1023),
                         i+1, 480-18 - ((((int)(pGammaTable[i+1])) * 255) / 1023));
        }
        */
        
    }
}

    
    
/*********************************************************************
*
*       _WinDrawLinesCallback
*/
static void _WinDrawLinesCallback(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin;
    
    hWin = pMsg->hWin;
    
    switch (pMsg->MsgId)
    {
      case WM_PAINT:
        DEBUGOUT("_WinDrawLinesCallback:WM_PAINT \r\n");
        WM_DefaultProc(pMsg);
        _WinDrawLines(hWin);
        break;
        
      case WM_NOTIFY_PARENT:
        switch (pMsg->Data.v)
        {
          case WM_NOTIFICATION_VALUE_CHANGED:
            DEBUGOUT("_WinDrawLinesCallback:WM_NOTIFICATION_VALUE_CHANGED\r\n");
            WM_InvalidateWindow(hWin);
            //_WinDrawLines(hWin);
            break;
          
          default:
            WM_DefaultProc(pMsg);
            break;
        }
        break;
        
      default:
        WM_DefaultProc(pMsg);
        break;
    }
}

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
        hItem = WM_GetDialogItem(hDlg, ID_WIN1);
        WM_SetCallback(hItem, _WinDrawLinesCallback);
        DEBUGOUT("Setup _WinDrawLinesCallback \r\n");
        break;
        
      default:
        WM_DefaultProc(pMsg);
        break;
    }
}


/*********************************************************************
*
*       _KB_Input_CallBack
*/
static void _KB_Input_CallBack(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin, hSrc, hItem;
    xKB_BTN_Obj tBtn;
    
    
    hWin = pMsg->hWin;
    hSrc = pMsg->hWinSrc;
    hItem = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
    
    switch (pMsg->MsgId)
    {
      case WM_NOTIFY_PARENT:
        switch (pMsg->Data.v)
        {
          case WM_NOTIFICATION_CLICKED:
            BUTTON_GetUserData(hSrc, &tBtn, sizeof(xKB_BTN_Obj));
            if(tBtn.KB_SoftKey.KeyCode == GUI_KEY_DELETE)
            {
                EDIT_SetText(hItem, "");
            }
            else
            {
                EDIT_AddKey(hItem, tBtn.KB_SoftKey.KeyCode);
                
            }
            DEBUGOUT("_KB_Input_CallBack():GotKey:%s\r\n", tBtn.pText);
            break;
          case WM_NOTIFICATION_RELEASED:
            break;
        }
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
WM_HWIN ImageAdjustWin_Init(WM_HWIN hMultiPage)
{
    WM_HWIN hDialog;
    WM_HWIN hItem;
    int i,Id;
    tKB_XY KeyIndex, TableSize;
    
    // for xKB_BTN testing
    hDialog = GUI_CreateDialogBox(_DialogWindow2, GUI_COUNTOF(_DialogWindow2), _KB_Input_CallBack, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hMultiPage, hDialog, "Image Adjust");
    DEBUGOUT("ImageAdjustWin_Init(): MULTIPAGE_AddPage(): hDialog:0x%08x\r\n", hDialog);
    
    
    KeyIndex.x = KeyIndex.y = 0;
    TableSize.x = KEYBOARD_TABLE_COLUMNS;
    TableSize.y = KEYBOARD_TABLE_ROWS;
    
    hItem = WM_GetDialogItem(hDialog, ID_WIN2);
    
    WM_SetCallback(hItem, _KB_Input_CallBack);
    
    hItem = WM_GetDialogItem(hDialog, GUI_ID_EDIT0);
    EDIT_SetUserData(hItem, &xEdit1, sizeof(xEDIT_Obj));
    WM_SetCallback(hItem, xEDIT_Callback);
    EDIT_SetFocussable(hItem, 0);
    
    
    for( i=0, Id=ID_BTN1; Id<=ID_BTN95; Id++)
    {
        hItem = WM_GetDialogItem(hDialog, Id);
        if(hItem)
        {
            xKB_BTN_Obj tBtn;
            tBtn = xKB_BTN_Init;
            
            DEBUGOUT("hItem:0x%08x\r\n", hItem);
            tBtn.pText = KeyBoard_CodeList[i].pBtnText;
            DEBUGOUT("Set xKB_BTN: %s \r\n", tBtn.pText);
            tBtn.KB_SoftKey.KeyCode= KeyBoard_CodeList[i].KeyCode;
            DEBUGOUT("Set xKB_BTN.KeyCode: %d \r\n", tBtn.KB_SoftKey.KeyCode);
            tBtn.KB_SoftKey.pKB_Table = &hKeyBoardTable[0][0];
            DEBUGOUT("Set xKB_BTN.pKB_Table: 0x%08x \r\n", tBtn.KB_SoftKey.pKB_Table);
            tBtn.KB_SoftKey.KB_TableSize = TableSize;
            DEBUGOUT("Set xKB_BTN.KB_TableSize: (%d,%d)\r\n", tBtn.KB_SoftKey.KB_TableSize.x, tBtn.KB_SoftKey.KB_TableSize.y);
            tBtn.KB_SoftKey.KB_KeyPosition = KeyIndex;
            DEBUGOUT("Set xKB_BTN.KB_KeyPosition: (%d,%d)\r\n", tBtn.KB_SoftKey.KB_KeyPosition.x, tBtn.KB_SoftKey.KB_KeyPosition.y);
            hKeyBoardTable[KeyIndex.y][KeyIndex.x] = hItem;
            DEBUGOUT("Set hKeyBoardTable[%d][%d] = 0x%08x\r\n", KeyIndex.x, KeyIndex.y, hKeyBoardTable[KeyIndex.y][KeyIndex.x]);
            BUTTON_SetUserData(hItem, &tBtn, sizeof(xKB_BTN_Obj));
            WM_SetCallback(hItem, xKBbtn_Callback);
            
            i++;
            if(++KeyIndex.x >= TableSize.x)
            {
                KeyIndex.x = 0;
                if(++KeyIndex.y >= TableSize.y)
                {
                    break;
                }
            }
            
            if( (Id == ID_BTN92) || (Id == ID_BTN93) || (Id == ID_BTN95) )
            {
                hKeyBoardTable[KeyIndex.y][KeyIndex.x++] = hItem;
                hKeyBoardTable[KeyIndex.y][KeyIndex.x++] = hItem;
            }
            
            else if(Id == ID_BTN94)
            {
                hKeyBoardTable[KeyIndex.y][KeyIndex.x++] = hItem;
                hKeyBoardTable[KeyIndex.y][KeyIndex.x++] = hItem;
                hKeyBoardTable[KeyIndex.y][KeyIndex.x++] = hItem;
            }
        }
    }
    
    
    /*for xMoveBtn testing
    hDialog = GUI_CreateDialogBox(_DialogWindow1, GUI_COUNTOF(_DialogWindow1), _WinDrawLinesCallback, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hMultiPage, hDialog, "Image Adjust");
    DEBUGOUT("ImageAdjustWin_Init(): MULTIPAGE_AddPage(): hDialog:0x%08x\r\n", hDialog);
    */
    
    /* for ImageAdjust UI
    hDialog = xCreateDialogBoxArray(_DialogArray, GUI_COUNTOF(_DialogArray), NULL, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hMultiPage, hDialog, "Image Adjust");
    DEBUGOUT("ImageAdjustWin_Init(): MULTIPAGE_AddPage(): hDialog:0x%08x\r\n", hDialog);
    
    for( i=0, Id=ID_IMAGE0; Id<=ID_IMAGE9; Id++, i++)
    {
        hItem = WM_GetDialogItem(hDialog, Id);
        if(hItem)
        {
            IMAGE_SetBitmap(hItem, &bmbase_44_26);
            DEBUGOUT("MainTask():IMAGE_SetBitmap(): hItem: 0x%08x\r\n", hItem);
        }
    }
    
    
    for( i=0, Id=ID_TEXT0; Id<=ID_TEXT9; Id++, i++)
    {
        hItem = WM_GetDialogItem(hDialog, Id);
        if(hItem)
        {
            TEXT_SetFont(hItem, &GUI_FontHGPGothicB19);
            TEXT_SetTextColor(hItem, GUI_UI_COLOR4);
            DEBUGOUT("MainTask():TEXT_Set...(): hItem: 0x%08x\r\n", hItem);
        }
    }
    
    for( i=0, Id=ID_SLIDER0; Id<=ID_SLIDER9; Id++)
    {
        hItem = WM_GetDialogItem(hDialog, Id);
        if(hItem)
        {
            const xSLIDER_Obj*   pSliderSetting;
            
            pSliderSetting = pSliderSettingTable[i++];
            SLIDER_SetUserData(hItem, pSliderSetting , sizeof(xSLIDER_Obj));
            SLIDER_SetRange(hItem, pSliderSetting->Range.Min,pSliderSetting->Range.Max);
            SLIDER_SetValue(hItem, pSliderSetting->Value);
            WM_SetCallback(hItem, xSLIDER_Callback);
            DEBUGOUT("MainTask():SLIDER_Set...(): hItem: 0x%08x\r\n", hItem);
        }
    }
    
    
    for( i=0, Id=ID_DROPDOWN0; Id<=ID_DROPDOWN9; Id++)
    {
        hItem = WM_GetDialogItem(hDialog, Id);
        if(hItem)
        {
            const xDROPDOWN_Obj* pDropdownSetting;
            int j;
            
            pDropdownSetting = pDropdownSettingTable[i++];
            DROPDOWN_SetUserData(hItem, pDropdownSetting, sizeof(xDROPDOWN_Obj));
            WM_SetCallback(hItem, xDROPDOWN_Callback);
            DROPDOWN_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
            for(j=0; j< pDropdownSetting->NumItems; j++)
            {
                DROPDOWN_AddString(hItem, pDropdownSetting->paDropDownItems[j].pText);
                DROPDOWN_SetItemDisabled(hItem, j, pDropdownSetting->paDropDownItems[j].State);
                DEBUGOUT("MainTask():DROPDOWN_AddString(%s): hItem: 0x%08x\r\n",  pDropdownSetting->paDropDownItems[j].pText, hItem);
            }
        }
    }
    
    hItem = WM_GetDialogItem(hDialog, ID_BTN10);
    if(hItem)
    {
        WM_SetCallback(hItem, xBtn_Advanced_Callback);
    }
    */
    
    return hDialog;
}    


/*************************** End of file ****************************/
