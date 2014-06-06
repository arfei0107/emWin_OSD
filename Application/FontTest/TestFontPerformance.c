#include <string.h>
#include "GUI.h"

//--------------------- Include Article -------------------------
#include "TraditionalCHN_Article.c"
#include "SimplifiedCHN_Article.c"
#include "Japanese_Article.c"


//---------------Declare using fonts ----------------------------
extern GUI_CONST_STORAGE GUI_FONT GUI_FontAR_Mingti_Medium_B523;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontArial19;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHG_GB_Gothic23;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHGGothicB19;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontHGPGothicB19;


 
void DisplayArticle(const char* pArticle)
{
    int i,j;
    char  cString[51];
    const char* pIndex;
    
    GUI_GotoXY(0,0);
    GUI_DispString(pArticle);
    /*
    pIndex = pArticle;
    i=j=0;
    
    while(1)
    {
        if( strlen (&pIndex[i]))
        {
            memset(cString, 0, sizeof(cString));
            strncpy(cString, &pIndex[i], 50);
            GUI_DispStringAt(cString,0,j*24);
            i+=strlen(cString);
            if(++j >=25)
            {
                j = 0;
                GUI_Clear();
            }
        }
        else
        {
            break;
        }
    } 
     */
}

void Test_Font_Drawing_Performance()
{
    GUI_TIMER_TIME StartTime, EndTime;
    int Sec, ms;
    char cString[65];
    
    GUI_UC_SetEncodeUTF8();
    
    //繁體中文 速度測試
    GUI_MULTIBUF_Begin();
    GUI_Clear();
    GUI_SetFont(&GUI_FontAR_Mingti_Medium_B523);
    StartTime = GUI_GetTime();
    DisplayArticle((const char*)_acTraditionalCHN_Article);
    EndTime = GUI_GetTime();
    Sec = (EndTime - StartTime) / 1000;
    ms  = (EndTime - StartTime) % 1000;
    GUI_MULTIBUF_End();
    GUI_Delay(1500); 
    GUI_MULTIBUF_Begin();
    GUI_Clear();
    GUI_DispStringAt("繁體中文字數",280,200);
    snprintf(cString, sizeof(cString)-1,"%d", sizeof(_acTraditionalCHN_Article)/2);
    GUI_DispStringAt(cString,500,200);
    GUI_DispStringAt("總花費時間",280,280);
    snprintf(cString, sizeof(cString)-1,"%d.%d",Sec,ms);
    GUI_DispStringAt(cString,460,280);
    GUI_DispStringAt("秒",600,280);
    GUI_MULTIBUF_End();
    GUI_Delay(3000);
    
    
    //簡體中文 速度測試 
    GUI_MULTIBUF_Begin();
    GUI_Clear();
    GUI_SetFont(&GUI_FontHG_GB_Gothic23);
    StartTime = GUI_GetTime();
    DisplayArticle((const char*)_acSimplifiedCHN_Article);
    EndTime = GUI_GetTime();
    Sec = (EndTime - StartTime) / 1000;
    ms  = (EndTime - StartTime) % 1000;
    GUI_MULTIBUF_End();
    GUI_Delay(1500);
    GUI_MULTIBUF_Begin();
    GUI_Clear();
    GUI_DispStringAt("简体中文字数",280,200);
    snprintf(cString, sizeof(cString)-1,"%d", sizeof(_acSimplifiedCHN_Article)/2);
    GUI_DispStringAt(cString,500,200);
    GUI_DispStringAt("总花费时间",280,280);
    snprintf(cString, sizeof(cString)-1,"%d.%d",Sec,ms);
    GUI_DispStringAt(cString,460,280);
    GUI_DispStringAt("秒",600,280);
    GUI_MULTIBUF_End();
    GUI_Delay(3000); 
    
    //日文 速度測試 
    GUI_MULTIBUF_Begin();
    GUI_Clear();
    GUI_SetFont(&GUI_FontHGGothicB19);
    StartTime = GUI_GetTime();
    DisplayArticle((const char*)_acJapanese_Article);
    EndTime = GUI_GetTime();
    Sec = (EndTime - StartTime) / 1000;
    ms  = (EndTime - StartTime) % 1000;
    GUI_MULTIBUF_End();
    GUI_Delay(1500);
    GUI_MULTIBUF_Begin();
    GUI_Clear();
    GUI_DispStringAt("日文字數",280,200);
    snprintf(cString, sizeof(cString)-1,"%d", sizeof(_acJapanese_Article)/2);
    GUI_DispStringAt(cString,440,200);
    GUI_DispStringAt("總花費時間：",280,280);
    snprintf(cString, sizeof(cString)-1,"%d.%d",Sec,ms);
    GUI_DispStringAt(cString,460,280);
    GUI_DispStringAt("秒",600,280);
    GUI_MULTIBUF_End();
    GUI_Delay(3000);
}


