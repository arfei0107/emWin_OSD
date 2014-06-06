/*********************************************************************
*                SEGGER MICROCONTROLLER GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2003-2010     SEGGER Microcontroller GmbH & Co KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

//--------------------------------------------------------------------
//                   Include Header files
//--------------------------------------------------------------------
#include <stdlib.h>   // for rand() function
#include "board.h"
#include "GUI.h"
#include "GUIDRV_Lin.h"
#include "WM.h"


//--------------------------------------------------------------------
//                   Define LCD Setting
//--------------------------------------------------------------------
#define SET_LCD_800x600_16BPP
//#define SET_LCD_800x600_24BPP
//#define SET_LCD_1024x768_16BPP_30Hz
//#define SET_LCD_1024x768_16BPP_40Hz
//#define SET_LCD_1024x768_16BPP_50Hz
//#define SET_LCD_1024x768_24BPP_30Hz
//#define SET_LCD_1024x768_24BPP_40Hz

//--------------------------------------------------------------------
//                   Local File, Global VAR
//--------------------------------------------------------------------

#ifdef SET_LCD_800x600_16BPP
    // Physical display size
    #define XSIZE_PHYS        800
    #define YSIZE_PHYS        600
    LCD_CONFIG_T tTFT_800x600 =
    {
        64,                   //uint8_t  HBP;	       // Horizontal back porch in clocks
	    40,                   //uint8_t  HFP;	       // Horizontal front porch in clocks
	    168,                  //uint8_t  HSW;	       // HSYNC pulse width in clocks
	    XSIZE_PHYS,           //uint16_t PPL;	       // Pixels per line
	    23,	                  //uint8_t  VBP;	       // Vertical back porch in clocks
	    1,                    //uint8_t  VFP;	       // Vertical front porch in clocks
	    4,	                  //uint8_t  VSW;	       // VSYNC pulse width in clocks
	    YSIZE_PHYS,           //uint16_t LPP;	       // Lines per panel
	    0,                    //uint8_t  IOE;	       // Invert output enable, 1 = invert
	    1,                    //uint8_t  IPC;	       // Invert panel clock, 1 = invert
	    0,                    //uint8_t  IHS;	       // Invert HSYNC, 1 = invert
	    0,                    //uint8_t  IVS;	       // Invert VSYNC, 1 = invert
	    1,                    //uint8_t  ACB;	       // AC bias frequency in clocks (not used)
	    LCD_BPP_16BPP_1_5_5_5,//uint8_t  BPP;	       // Maximum bits per pixel the display supports
	    5,                    //uint8_t  pcd;        // Add by Stan, panel clock divisor
        LCD_TFT,              //LCD_PANEL_OPT_T  // LCD panel type
        LCD_COLOR_FORMAT_RGB, //LCD_COLOR_FORMAT_OPT_T // BGR or RGB
        0                     //uint8_t  Dual;// Dual panel, 1 = dual panel display
    };
    #define LCD_CONFIG        tTFT_800x600
    // Color conversion
    #define COLOR_CONVERSION  GUICC_555   //  16bits/Pixel
    // Display driver
    #define DISPLAY_DRIVER    &GUIDRV_Lin_16_API  // EmWin Driver for 16-bits/Pixel
    // Pixel width in bytes
    #define PIXEL_WIDTH_NOM   2
#endif

#ifdef SET_LCD_800x600_24BPP

    // Physical display size
    #define XSIZE_PHYS        800
    #define YSIZE_PHYS        600
    LCD_CONFIG_T tTFT_800x600 =
    {
        56,                   //uint8_t  HBP; // Horizontal back porch in clocks
        8,                    //uint8_t  HFP; // Horizontal front porch in clocks
        176,                  //uint8_t  HSW; // HSYNC pulse width in clocks
        XSIZE_PHYS,           //uint16_t PPL; // Pixels per line
        35,                   //uint8_t  VBP; // Vertical back porch in clocks
        10,                   //uint8_t  VFP; // Vertical front porch in clocks
        4,                    //uint8_t  VSW; // VSYNC pulse width in clocks
        YSIZE_PHYS,           //uint16_t LPP; // Lines per panel
        0,                    //uint8_t  IOE; // Invert output enable, 1 = invert
        1,                    //uint8_t  IPC; // Invert panel clock, 1 = invert
        0,                    //uint8_t  IHS; // Invert HSYNC, 1 = invert
        0,                    //uint8_t  IVS; // Invert VSYNC, 1 = invert
        1,                    //uint8_t  ACB; // AC bias frequency in clocks (not used)
        LCD_BPP_24BPP,        //uint8_t  BPP; // Maximum bits per pixel the display supports
        8,                    //uint8_t  pcd; // Add by Stan, panel clock divisor
        LCD_TFT,              //LCD_PANEL_OPT_T  // LCD panel type
        LCD_COLOR_FORMAT_RGB, //LCD_COLOR_FORMAT_OPT_T // BGR or RGB
        0                     //uint8_t  Dual;// Dual panel, 1 = dual panel display
    };
    #define LCD_CONFIG        tTFT_800x600                                              
    // Color conversion                                                          
    #define COLOR_CONVERSION  GUICC_8888   //  32bits/Pixel                       
    // Display driver                                                            
    #define DISPLAY_DRIVER    &GUIDRV_Lin_32_API  // EmWin Driver for 32-bits/Pixel
    // Pixel width in bytes                                                      
    #define PIXEL_WIDTH_NOM   4                                                
 #endif
  
#ifdef SET_LCD_1024x768_16BPP_30Hz
    // Physical display size
    #define XSIZE_PHYS       1024
    #define YSIZE_PHYS        768
    LCD_CONFIG_T tTFT_1024x768 =
    {
        232,                  //uint8_t  HBP; // Horizontal back porch in clocks
        232,                  //uint8_t  HFP; // Horizontal front porch in clocks
        176,                  //uint8_t  HSW; // HSYNC pulse width in clocks
        XSIZE_PHYS,           //uint16_t PPL; // Pixels per line
        35,                   //uint8_t  VBP; // Vertical back porch in clocks
        10,                   //uint8_t  VFP; // Vertical front porch in clocks
        4,                    //uint8_t  VSW; // VSYNC pulse width in clocks
        YSIZE_PHYS,           //uint16_t LPP; // Lines per panel
        0,                    //uint8_t  IOE; // Invert output enable, 1 = invert
        1,                    //uint8_t  IPC; // Invert panel clock, 1 = invert
        0,                    //uint8_t  IHS; // Invert HSYNC, 1 = invert
        0,                    //uint8_t  IVS; // Invert VSYNC, 1 = invert
        1,                    //uint8_t  ACB; // AC bias frequency in clocks (not used)
        LCD_BPP_16BPP_1_5_5_5,//uint8_t  BPP; // Maximum bits per pixel the display supports
        5,                    //uint8_t  pcd; // Add by Stan, panel clock divisor
        LCD_TFT,              //LCD_PANEL_OPT_T  // LCD panel type
        LCD_COLOR_FORMAT_RGB, //LCD_COLOR_FORMAT_OPT_T // BGR or RGB
        0,                    //uint8_t  Dual;// Dual panel, 1 = dual panel display
    };
    #define LCD_CONFIG tTFT_1024x768
    // Color conversion
    #define COLOR_CONVERSION  GUICC_555   //  16bits/Pixel
    // Display driver
    #define DISPLAY_DRIVER    &GUIDRV_Lin_16_API  // EmWin Driver for 16-bits/Pixel
    // Pixel width in bytes
    #define PIXEL_WIDTH_NOM   2
#endif
    
#ifdef SET_LCD_1024x768_16BPP_40Hz
    // Physical display size
    #define XSIZE_PHYS       1024
    #define YSIZE_PHYS        768
    LCD_CONFIG_T tTFT_1024x768 =
    {
        56,                   //uint8_t  HBP; // Horizontal back porch in clocks
        8,                    //uint8_t  HFP; // Horizontal front porch in clocks
        176,                  //uint8_t  HSW; // HSYNC pulse width in clocks
        XSIZE_PHYS,           //uint16_t PPL; // Pixels per line
        35,                   //uint8_t  VBP; // Vertical back porch in clocks
        10,                   //uint8_t  VFP; // Vertical front porch in clocks
        4,                    //uint8_t  VSW; // VSYNC pulse width in clocks
        YSIZE_PHYS,           //uint16_t LPP; // Lines per panel
        0,                    //uint8_t  IOE; // Invert output enable, 1 = invert
        1,                    //uint8_t  IPC; // Invert panel clock, 1 = invert
        0,                    //uint8_t  IHS; // Invert HSYNC, 1 = invert
        0,                    //uint8_t  IVS; // Invert VSYNC, 1 = invert
        1,                    //uint8_t  ACB; // AC bias frequency in clocks (not used)
        LCD_BPP_16BPP_1_5_5_5,//uint8_t  BPP; // Maximum bits per pixel the display supports
        5,                    //uint8_t  pcd; // Add by Stan, panel clock divisor
        LCD_TFT,              //LCD_PANEL_OPT_T  // LCD panel type
        LCD_COLOR_FORMAT_RGB, //LCD_COLOR_FORMAT_OPT_T // BGR or RGB
        0,                    //uint8_t  Dual;// Dual panel, 1 = dual panel display
    };
    #define LCD_CONFIG        tTFT_1024x768
    // Color conversion
    #define COLOR_CONVERSION  GUICC_555   //  16bits/Pixel
    // Display driver
    #define DISPLAY_DRIVER    &GUIDRV_Lin_16_API  // EmWin Driver for 16-bits/Pixel
    // Pixel width in bytes
    #define PIXEL_WIDTH_NOM   2
#endif

#ifdef SET_LCD_1024x768_16BPP_50Hz
    // Physical display size
    #define XSIZE_PHYS       1024
    #define YSIZE_PHYS        768
    LCD_CONFIG_T tTFT_1024x768 =
    {
        56,                   //uint8_t  HBP; // Horizontal back porch in clocks
        8,                    //uint8_t  HFP; // Horizontal front porch in clocks
        176,                  //uint8_t  HSW; // HSYNC pulse width in clocks
        XSIZE_PHYS,           //uint16_t PPL; // Pixels per line
        24,                    //uint8_t  VBP; // Vertical back porch in clocks
        10,                    //uint8_t  VFP; // Vertical front porch in clocks
        4,                    //uint8_t  VSW; // VSYNC pulse width in clocks
        YSIZE_PHYS,           //uint16_t LPP; // Lines per panel
        0,                    //uint8_t  IOE; // Invert output enable, 1 = invert
        1,                    //uint8_t  IPC; // Invert panel clock, 1 = invert
        0,                    //uint8_t  IHS; // Invert HSYNC, 1 = invert
        0,                    //uint8_t  IVS; // Invert VSYNC, 1 = invert
        1,                    //uint8_t  ACB; // AC bias frequency in clocks (not used)
        LCD_BPP_16BPP_1_5_5_5,//uint8_t  BPP; // Maximum bits per pixel the display supports
        4,                    //uint8_t  pcd; // Add by Stan, panel clock divisor
        LCD_TFT,              //LCD_PANEL_OPT_T  // LCD panel type
        LCD_COLOR_FORMAT_RGB, //LCD_COLOR_FORMAT_OPT_T // BGR or RGB
        0,                    //uint8_t  Dual;// Dual panel, 1 = dual panel display
    };
    #define LCD_CONFIG        tTFT_1024x768
    // Color conversion
    #define COLOR_CONVERSION  GUICC_555   //  16bits/Pixel
    // Display driver
    #define DISPLAY_DRIVER    &GUIDRV_Lin_16_API  // EmWin Driver for 16-bits/Pixel
    // Pixel width in bytes
    #define PIXEL_WIDTH_NOM   2
#endif

#ifdef SET_LCD_1024x768_24BPP_30Hz
    // Physical display size
    #define XSIZE_PHYS       1024
    #define YSIZE_PHYS        768
    LCD_CONFIG_T tTFT_1024x768 =
    {
        232,                  //uint8_t  HBP; // Horizontal back porch in clocks
        232,                  //uint8_t  HFP; // Horizontal front porch in clocks
        176,                  //uint8_t  HSW; // HSYNC pulse width in clocks
        XSIZE_PHYS,           //uint16_t PPL; // Pixels per line
        35,                   //uint8_t  VBP; // Vertical back porch in clocks
        10,                   //uint8_t  VFP; // Vertical front porch in clocks
        4,                    //uint8_t  VSW; // VSYNC pulse width in clocks
        YSIZE_PHYS,           //uint16_t LPP; // Lines per panel
        0,                    //uint8_t  IOE; // Invert output enable, 1 = invert
        1,                    //uint8_t  IPC; // Invert panel clock, 1 = invert
        0,                    //uint8_t  IHS; // Invert HSYNC, 1 = invert
        0,                    //uint8_t  IVS; // Invert VSYNC, 1 = invert
        1,                    //uint8_t  ACB; // AC bias frequency in clocks (not used)
        LCD_BPP_24BPP,        //uint8_t  BPP; // Maximum bits per pixel the display supports
        5,                    //uint8_t  pcd; // Add by Stan, panel clock divisor
        LCD_TFT,              //LCD_PANEL_OPT_T  // LCD panel type
        LCD_COLOR_FORMAT_RGB, //LCD_COLOR_FORMAT_OPT_T // BGR or RGB
        0,                    //uint8_t  Dual;// Dual panel, 1 = dual panel display
    };
    #define LCD_CONFIG        tTFT_1024x768
    // Color conversion
    #define COLOR_CONVERSION  GUICC_8888  //  32bits/Pixel
    // Display driver
    #define DISPLAY_DRIVER    &GUIDRV_Lin_32_API  // EmWin Driver for 32-bits/Pixel
    // Pixel width in bytes
    #define PIXEL_WIDTH_NOM   4
#endif

#ifdef SET_LCD_1024x768_24BPP_40Hz
    // Physical display size
    #define XSIZE_PHYS       1024
    #define YSIZE_PHYS        768
    LCD_CONFIG_T tTFT_1024x768 =
    {
        56,                   //uint8_t  HBP; // Horizontal back porch in clocks
        8,                    //uint8_t  HFP; // Horizontal front porch in clocks
        176,                  //uint8_t  HSW; // HSYNC pulse width in clocks
        XSIZE_PHYS,           //uint16_t PPL; // Pixels per line
        35,                   //uint8_t  VBP; // Vertical back porch in clocks
        10,                   //uint8_t  VFP; // Vertical front porch in clocks
        4,                    //uint8_t  VSW; // VSYNC pulse width in clocks
        YSIZE_PHYS,           //uint16_t LPP; // Lines per panel
        0,                    //uint8_t  IOE; // Invert output enable, 1 = invert
        1,                    //uint8_t  IPC; // Invert panel clock, 1 = invert
        0,                    //uint8_t  IHS; // Invert HSYNC, 1 = invert
        0,                    //uint8_t  IVS; // Invert VSYNC, 1 = invert
        1,                    //uint8_t  ACB; // AC bias frequency in clocks (not used)
        LCD_BPP_24BPP,        //uint8_t  BPP; // Maximum bits per pixel the display supports
        5,                    //uint8_t  pcd; // Add by Stan, panel clock divisor
        LCD_TFT,              //LCD_PANEL_OPT_T  // LCD panel type
        LCD_COLOR_FORMAT_RGB, //LCD_COLOR_FORMAT_OPT_T // BGR or RGB
        0,                    //uint8_t  Dual;// Dual panel, 1 = dual panel display
    }; 
    #define LCD_CONFIG        tTFT_1024x768
    // Color conversion
    #define COLOR_CONVERSION  GUICC_8888  //  32bits/Pixel
    // Display driver
    #define DISPLAY_DRIVER    &GUIDRV_Lin_32_API  // EmWin Driver for 32-bits/Pixel
    // Pixel width in bytes
    #define PIXEL_WIDTH_NOM   4
#endif    


static volatile int _PendingBuffer = -1;
#define NUM_BUFFERS  3 // Number of multiple Frame(Video) buffers to be used
    
    
// Virtual display size
#define VXSIZE_PHYS (XSIZE_PHYS)
#define VYSIZE_PHYS (YSIZE_PHYS)
    
/* Video RAM address */
#define VRAM_ADDR_PHYS  (U32)&_aVRAM[0]
#define VRAM_ADDR_VIRT  VRAM_ADDR_PHYS

#define PIXEL_WIDTH_DENOM   1

#ifndef   ABS
  #define ABS(x)                       (((int32_t)(x)) < 0 ? (-x) : (x))
#endif


/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VRAM_ADDR_VIRT
  #define VRAM_ADDR_VIRT  0
#endif



/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/* Video RAM */
#ifdef __ICCARM__
    #pragma data_alignment=8  // 8 byte align frame buffer to be on the safe side (some display controllers need this)
    #pragma location="VRAM"
    static __no_init U8 _aVRAM[VXSIZE_PHYS * VYSIZE_PHYS * PIXEL_WIDTH_NOM * NUM_BUFFERS];
#endif
#ifdef __CC_ARM
    U8 static _aVRAM[VXSIZE_PHYS * VYSIZE_PHYS * PIXEL_WIDTH_NOM * NUM_BUFFERS] __attribute__ ((section ("VRAM"), zero_init));
#endif
#ifdef __GNUC__
    static U8 _aVRAM[VXSIZE_PHYS * VYSIZE_PHYS * PIXEL_WIDTH_NOM * NUM_BUFFERS] __attribute__ ((section ("VRAM")));
#endif

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/***********************************************************************
 *
 * Function: LCD_IRQHandler
 *
 * Purpose: LCD interrupt handler.
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void LCD_IRQHandler(void)
{
  U32 Addr;
  uint32_t status;
  
  //Read LCD INT Status
  status = Chip_LCD_IntStatus(LPC_LCD);
  
  Chip_LCD_ClearInts(LPC_LCD,status);
  
  //DEBUGOUT("LCD:%x\r\n",status);
  
  if (status & LCD_INTMSK_LNBUIM)
  {  
    if (_PendingBuffer >= 0)
    {
      Addr = ( ((U32)&_aVRAM[0]) + (XSIZE_PHYS * YSIZE_PHYS * PIXEL_WIDTH_NOM * _PendingBuffer) );
      Chip_LCD_SetUPFrameBuffer(LPC_LCD, (void*)Addr);
      GUI_MULTIBUF_Confirm(_PendingBuffer);
      //DEBUGOUT("FB:%d\r\n",_PendingBuffer);
      _PendingBuffer = -1;
    }
  }
}

/*********************************************************************
*
*       _SetDisplayOrigin()
*/
static void _SetDisplayOrigin (int x, int y)
{
    (void)  x;

    /* Set start address for display data and enable LCD controller */
    LPC_LCD->UPBASE = VRAM_ADDR_PHYS + (y * YSIZE_PHYS * PIXEL_WIDTH_NOM);  // Needs to be set, before LCDC is enabled
}

/*********************************************************************
*
*       _InitLcdController()
*/
void _InitLcdController()
{
    _PendingBuffer = -1;
    
    Board_LCD_Init();
    Chip_LCD_Init(LPC_LCD, &LCD_CONFIG);
    Chip_LCD_DMA_WATERMARK_8(LPC_LCD);
    //memset((void*)VRAM_ADDR_PHYS,0,XSIZE_PHYS * YSIZE_PHYS * PIXEL_WIDTH_NOM);
    Chip_LCD_SetUPFrameBuffer(LPC_LCD, (void*)VRAM_ADDR_PHYS);
    Chip_LCD_EnableInts(LPC_LCD, LCD_INTMSK_LNBUIM);
    
    Chip_LCD_PowerOn(LPC_LCD);
    
    GUI_Delay(100);//Delay(100ms)
    
    Chip_LCD_Cursor_Disable(LPC_LCD, 0);
    //Enable LCD interrupts on NVIC level
    NVIC_EnableIRQ(LCD_IRQn);
}

/*********************************************************************
*
*       _InitLCD
*
* Function description:
*   Sets LCD configuration and initializes the LCD.
*/
static void _InitLCD (unsigned LayerIndex)
{
    /* emWin: Set display size and video-RAM address */
    LCD_SetSizeEx (XSIZE_PHYS, YSIZE_PHYS, LayerIndex);
    LCD_SetVSizeEx(VXSIZE_PHYS, VYSIZE_PHYS, LayerIndex);
    LCD_SetVRAMAddrEx(LayerIndex, (void*)VRAM_ADDR_PHYS);

    /* Init LCD */
    
    //_SetDisplayOrigin(0, 0);

    _InitLcdController(); //init LCD Controller registers.
}


/*********************************************************************
*
*       _InitController
*
* Function description:
*   Initializes the LCD controller and touch screen
*
*/
static void _InitController (unsigned LayerIndex)
{
    _InitLCD(LayerIndex);
}


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/** Set up the display driver configuration.
 *
 *  Called by emWIN library.
 */
void LCD_X_Config (void)
{
  #if (NUM_BUFFERS > 1)
    GUI_MULTIBUF_Config(NUM_BUFFERS);
    WM_MULTIBUF_Enable(1);
    DEBUGSTR("GUI_MULTIBUF_Config()...ok\r\n");
  #endif
  
    /* Set display driver and color conversion for 1st layer */
    GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);

    /* Display driver configuration, required for Lin-driver */
    LCD_SetPosEx     (0, 0, 0);
    if (LCD_GetSwapXYEx(0)) {
        LCD_SetSizeEx  (0, YSIZE_PHYS , XSIZE_PHYS);
        LCD_SetVSizeEx (0, VYSIZE_PHYS, VXSIZE_PHYS);
    }
    else {
        LCD_SetSizeEx  (0, XSIZE_PHYS , YSIZE_PHYS);
        LCD_SetVSizeEx (0, VXSIZE_PHYS, VYSIZE_PHYS);
    }
    LCD_SetVRAMAddrEx(0, (void*)VRAM_ADDR_VIRT);

    /* Set user palette data (only required if no fixed palette is used) */
  #if defined(PALETTE)
    LCD_SetLUTEx(0, PALETTE);
  #endif
}


/** Execute emWIN commands at run-time
 *
 *  This function is called by the display driver for several purposes.
 *  To support the according task the routine needs to be adapted to
 *  the display controller. Please note that the commands marked with
 *  'optional' are not cogently required and should only be adapted if
 *  the display controller supports these features.
 *
 *  \param[in] LayerIndex Index of layer to be configured
 *  \param[in] Cmd Please refer to the details in the switch statement below
 *  \param pData Pointer to a LCD_X_DATA structure
 *  \retval <-1 Error
 *  \retval -1 Command not handled
 *  \retval 0 Ok
 */
int LCD_X_DisplayDriver (unsigned LayerIndex, unsigned Cmd, void * pData)
{
    int r;
    LCD_X_SETORG_INFO      * pSetOrg;

    (void) LayerIndex;


    switch (Cmd) {
    case LCD_X_INITCONTROLLER:              /* Required! */
        //
        // Called during the initialization process in order to set up the
        // display controller and put it into operation. If the display
        // controller is not initialized by any external routine this needs
        // to be adapted by the customer...
        //
        // ...
        _InitController(0);
        return 0;

    case LCD_X_SETORG:
        //
        // Required for setting the display origin which is passed in the 'xPos' and 'yPos' element of p
        //
        pSetOrg = (LCD_X_SETORG_INFO *)pData;
        _SetDisplayOrigin(pSetOrg->xPos, pSetOrg->yPos);
        return 0;
  
  #if (NUM_BUFFERS > 1)
    case LCD_X_SHOWBUFFER:
    {
        LCD_X_SHOWBUFFER_INFO * pBuf;
        pBuf = (LCD_X_SHOWBUFFER_INFO *)pData;
        // Remember buffer index to be used by ISR
        _PendingBuffer = pBuf->Index;
        DEBUGOUT("FB:%d\r\n",_PendingBuffer);
        return 0;
    }
  #endif
    
    default:
        r = -1;
        break;
    }

    return r;
}
