#ifndef __CUSTOM_SLIDER1_H__
#define __CUSTOM_SLIDER1_H__

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

typedef enum
{
    WIDGET_DISABLE = 0,
    WIDGET_ENABLE = 1
}eWIDGET_STATE;

typedef struct
{
    int Min;
    int Max;
}tRANGE;


/*********************************************************************
*
* xSLIDER_Obj
*/
typedef struct
{
    eWIDGET_STATE State;
    tRANGE Range;
    int Value;
    int H_Space;
    
    GUI_CONST_STORAGE GUI_BITMAP *pEnable_BkBmp;
    GUI_CONST_STORAGE GUI_BITMAP *pDisable_BkBmp;
    
    GUI_CONST_STORAGE GUI_BITMAP *pEnable_Slider_Bmp;
    GUI_CONST_STORAGE GUI_BITMAP *pDisable_Slider_Bmp;
    
} xSLIDER_Obj;


/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  GUI_COLOR aBkColor[2];
  GUI_COLOR aColor[2];
  int Min, Max, v;
  int Flags;
  int NumTicks;
  I16 Width;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} SLIDER_Obj;

#define SLIDER_H2P(h) (SLIDER_Obj*) GUI_ALLOC_h2p(h)

void xSLIDER_Callback(WM_MESSAGE * pMsg);

#endif
