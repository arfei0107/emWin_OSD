#ifndef __CUSTOM_WIDGET_H__
#define __CUSTOM_WIDGET_H__

#define GUI_MAKE_COLOR(R,G,B)           (R + (G<<8) + (B<<16))
#define GUI_MAKE_COLOR_ALPHA(R,G,B,A)   (R + (G<<8) + (B<<16) + (A<<24))

#define GUI_TEXT_COLOR_NORMAL    GUI_MAKE_COLOR(224,224,224)
#define GUI_TEXT_COLOR_HISTORY   GUI_MAKE_COLOR(224,224,224)
#define GUI_TEXT_COLOR_FOCUS     GUI_MAKE_COLOR(48,48,48)
#define GUI_TEXT_COLOR_DISABLE   GUI_MAKE_COLOR(144,144,144)
#define GUI_TEXT_COLOR_VALUE     GUI_MAKE_COLOR(112,176,240)
#define GUI_TEXT_COLOR_OTHERS    GUI_MAKE_COLOR(244,244,0)

#define GUI_UI_COLOR1            GUI_MAKE_COLOR_ALPHA(224,224,224, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR2            GUI_MAKE_COLOR_ALPHA( 48, 48, 48, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR3            GUI_MAKE_COLOR_ALPHA(144,144,144, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR4            GUI_MAKE_COLOR_ALPHA(112,176,240, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR5            GUI_MAKE_COLOR_ALPHA(244,244,  0, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR6            GUI_MAKE_COLOR_ALPHA( 48, 48, 48, 0)//(int)(255 * 0.80) )
#define GUI_UI_COLOR7            GUI_MAKE_COLOR_ALPHA( 16, 16, 16, 0)//(int)(255 * 0.80) )
#define GUI_UI_COLOR8            GUI_MAKE_COLOR_ALPHA(  0,  0,  0, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR9            GUI_MAKE_COLOR_ALPHA(128,128,128, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR10           GUI_MAKE_COLOR_ALPHA( 16, 16, 16, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR11           GUI_MAKE_COLOR_ALPHA(240,144,  0, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR12           GUI_MAKE_COLOR_ALPHA(128, 80,  0, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR13           GUI_MAKE_COLOR_ALPHA(144, 96,  0, 0)//(int)(255 * 1.00) )
#define GUI_UI_COLOR14           GUI_MAKE_COLOR_ALPHA( 32, 32, 32, 0)//(int)(255 * 1.00) )


#define xID_WINDOW_START         (GUI_ID_USER + 1)
#define xID_WINDOW_END           (GUI_ID_USER + 100)

#define xID_TEXT_START           (GUI_ID_USER + 101)
#define xID_TEXT_END             (GUI_ID_USER + 200)

#define xID_DROPDOWN_START       (GUI_ID_USER + 201)
#define xID_DROPDOWN_END         (GUI_ID_USER + 300)

#define xID_SLIDER_START         (GUI_ID_USER + 301)
#define xID_SLIDER_END           (GUI_ID_USER + 400)

#define xID_BTN_START            (GUI_ID_USER + 401)
#define xID_BTN_END              (GUI_ID_USER + 500)

#define xID_IMAGE_START          (GUI_ID_USER + 501)
#define xID_IMAGE_END            (GUI_ID_USER + 600)

#endif
