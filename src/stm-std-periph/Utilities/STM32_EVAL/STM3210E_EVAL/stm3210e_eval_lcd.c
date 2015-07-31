/**
  ******************************************************************************
  * @file    stm3210e_eval_lcd.c
  * @author  MCD Application Team
  * @version V4.2.0
  * @date    04/16/2010
  * @brief   This file includes the LCD driver for AM-240320L8TNQW00H 
  *          (LCD_ILI9320) and AM-240320LDTNQW00H (LCD_SPFD5408B) Liquid Crystal
  *          Display Module of STM3210E-EVAL board.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */  
    
    /* Includes ------------------------------------------------------------------ */ 
#include "stm3210e_eval_lcd.h"
#include "../Common/fonts.c"
    
/** @addtogroup Utilities
  * @{
  */ 
    
/** @addtogroup STM32_EVAL
  * @{
  */ 
    
/** @addtogroup STM3210E_EVAL
  * @{
  */ 
    
/** @defgroup STM3210E_EVAL_LCD 
  * @brief This file includes the LCD driver for AM-240320L8TNQW00H 
  *        (LCD_ILI9320) and AM-240320LDTNQW00H (LCD_SPFD5408B) Liquid Crystal
  *        Display Module of STM3210E-EVAL board.
  * @{
  */ 
    
/** @defgroup STM3210E_EVAL_LCD_Private_TypesDefinitions
  * @{
  */ 
typedef struct 
{
    
    



/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_LCD_Private_Defines
  * @{
  */ 
    /* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */ 
#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0C000000))
#define LCD                ((LCD_TypeDef *) LCD_BASE)
#define MAX_POLY_CORNERS   200
#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))                                
/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_LCD_Private_Macros
  * @{
  */ 
#define ABS(X)  ((X) > 0 ? (X) : -(X))    
/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_LCD_Private_Variables
  * @{
  */ 
static sFONT* LCD_Currentfonts;


    /* Global variables to set the written text color */ 
static __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;


/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_LCD_Private_FunctionPrototypes
  * @{
  */ 
#ifndef USE_Delay
static void delay (vu32 nCount);


#endif  /* USE_Delay*/
static void PutPixel (int16_t x, int16_t y);



/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_LCD_Private_Functions
  * @{
  */ 
    
/**
  * @brief  DeInitializes the LCD.
  * @param  None
  * @retval None
  */ 
void LCD_DeInit (void) 
{
    
    
        /* !< LCD Display Off */ 
        LCD_DisplayOff ();
    
        /* BANK 4 (of NOR/SRAM Bank 1~4) is disabled */ 
        FSMC_NORSRAMCmd (FSMC_Bank1_NORSRAM4, ENABLE);
    
        /* !< LCD_SPI DeInit */ 
        FSMC_NORSRAMDeInit (FSMC_Bank1_NORSRAM4);
    
        /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
        GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | 
    
    
    
        /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
        GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
    
    
        /* Set PF.00(A0 (RS)) as alternate function push pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    
    
        /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    


/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval None
  */ 
void STM3210E_LCD_Init (void) 
{
    
        /* Configure the LCD Control pins -------------------------------------------- */ 
        LCD_CtrlLinesConfig ();
    
        /* Configure the FSMC Parallel interface ------------------------------------- */ 
        LCD_FSMCConfig ();
    
    
        /* Check if the LCD is SPFD5408B Controller */ 
        if (LCD_ReadReg (0x00) == 0x5408)
        
    {
        
            /* Start Initial Sequence ------------------------------------------------ */ 
            LCD_WriteReg (LCD_REG_1, 0x0100);   /* Set SS bit */
        
        
        
        
        
        
        
        
        
        
            /* Power On sequence ----------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_16, 0x0000);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            /* Adjust the Gamma Curve (SPFD540---------------------------------------- */ 
            LCD_WriteReg (LCD_REG_48, 0x0b0d);
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            /* Set GRAM area --------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_80, 0x0000);  /* Horizontal GRAM Start Address */
        
        
        
        
        
        
        
            /* Partial Display Control ----------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_128, 0x0000);
        
        
        
        
        
        
            /* Panel Control --------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_144, 0x0010);
        
        
        
        
        
        
            /* Set GRAM write direction and BGR=1
               writing direction) */ 
            LCD_WriteReg (LCD_REG_3, 0x1018);
        
        
        
    
    
        /* Start Initial Sequence ---------------------------------------------------- */ 
        LCD_WriteReg (LCD_REG_229, 0x8000); /* Set the internal vcore voltage */
    
    
    
    
    
    
    
    
    
    
    
    
        /* Power On sequence --------------------------------------------------------- */ 
        LCD_WriteReg (LCD_REG_16, 0x0000);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* Adjust the Gamma Curve ---------------------------------------------------- */ 
        LCD_WriteReg (LCD_REG_48, 0x0006);
    
    
    
    
    
    
    
    
    
    
        /* Set GRAM area ------------------------------------------------------------- */ 
        LCD_WriteReg (LCD_REG_80, 0x0000);  /* Horizontal GRAM Start Address */
    
    
    
    
    
    
    
        /* Partial Display Control --------------------------------------------------- */ 
        LCD_WriteReg (LCD_REG_128, 0x0000);
    
    
    
    
    
    
        /* Panel Control ------------------------------------------------------------- */ 
        LCD_WriteReg (LCD_REG_144, 0x0010);
    
    
    
    
    
    
        /* Set GRAM write direction and BGR = 1 */ 
        /* I/D=01 (Horizontal : increment, Vertical : decrement) */ 
        /* AM=1 (address is updated in vertical writing direction) */ 
        LCD_WriteReg (LCD_REG_3, 0x1018);
    
    



/**
  * @brief  Sets the LCD Text and Background colors.
  * @param  _TextColor: specifies the Text Color.
  * @param  _BackColor: specifies the Background Color.
  * @retval None
  */ 
void LCD_SetColors (__IO uint16_t _TextColor, __IO uint16_t _BackColor) 
{
    
    


/**
  * @brief  Gets the LCD Text and Background colors.
  * @param  _TextColor: pointer to the variable that will contain the Text 
            Color.
  * @param  _BackColor: pointer to the variable that will contain the Background 
            Color.
  * @retval None
  */ 
void LCD_GetColors (__IO uint16_t * _TextColor, __IO uint16_t * _BackColor) 
{
    
    *_BackColor = BackColor;


/**
  * @brief  Sets the Text color.
  * @param  Color: specifies the Text color code RGB(5-6-5).
  * @retval None
  */ 
void LCD_SetTextColor (__IO uint16_t Color) 
{
    


/**
  * @brief  Sets the Background color.
  * @param  Color: specifies the Background color code RGB(5-6-5).
  * @retval None
  */ 
void LCD_SetBackColor (__IO uint16_t Color) 
{
    


/**
  * @brief  Sets the Text Font.
  * @param  fonts: specifies the font to be used.
  * @retval None
  */ 
void LCD_SetFont (sFONT * fonts) 
{
    


/**
  * @brief  Gets the Text Font.
  * @param  None.
  * @retval the used font.
  */ 
    sFONT * LCD_GetFont (void) 
{
    



/**
  * @brief  Clears the selected line.
  * @param  Line: the Line to be cleared.
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..n
  * @retval None
  */ 
void LCD_ClearLine (uint8_t Line) 
{
    
    
        /* Send the string character by character on lCD */ 
        while (((refcolumn + 1) & 0xFFFF) >= LCD_Currentfonts->Width)
        
    {
        
            /* Display one character on LCD */ 
            LCD_DisplayChar (Line, refcolumn, ' ');
        
            /* Decrement the column position by 16 */ 
            refcolumn -= LCD_Currentfonts->Width;
    



/**
  * @brief  Clears the hole LCD.
  * @param  Color: the color of the background.
  * @retval None
  */ 
void LCD_Clear (uint16_t Color) 
{
    
    
    
    
        
    {
        
    



/**
  * @brief  Sets the cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position. 
  * @retval None
  */ 
void LCD_SetCursor (uint8_t Xpos, uint16_t Ypos) 
{
    
    


/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */ 
void LCD_DrawChar (uint8_t Xpos, uint16_t Ypos, const uint16_t * c) 
{
    
    
    
    
    
        
    {
        
        
            
        {
            
                    ((0x80 << ((LCD_Currentfonts->Width / 12) * 8)) >> i)) ==
                   0x00) && (LCD_Currentfonts->Width <= 12)) || 
                
            {
                
            
            
            else
                
            {
                
            
        
        
        
    



/**
  * @brief  Displays one character (16dots width, 24dots height).
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  Column: start column address.
  * @param  Ascii: character ascii code, must be between 0x20 and 0x7E.
  * @retval None
  */ 
void LCD_DisplayChar (uint8_t Line, uint16_t Column, uint8_t Ascii) 
{
    
    


/**
  * @brief  Displays a maximum of 20 char on the LCD.
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  *ptr: pointer to string to display on LCD.
  * @retval None
  */ 
void LCD_DisplayStringLine (uint8_t Line, uint8_t * ptr) 
{
    
    
        /* Send the string character by character on lCD */ 
        while ((*ptr != 0) & (((refcolumn + 1) & 0xFFFF) >= LCD_Currentfonts->Width))
        
    {
        
            /* Display one character on LCD */ 
            LCD_DisplayChar (Line, refcolumn, *ptr);
        
            /* Decrement the column position by 16 */ 
            refcolumn -= LCD_Currentfonts->Width;
        
            /* Point on the next character */ 
            ptr++;
    



/**
  * @brief  Sets a display window
  * @param  Xpos: specifies the X buttom left position.
  * @param  Ypos: specifies the Y buttom left position.
  * @param  Height: display window height.
  * @param  Width: display window width.
  * @retval None
  */ 
void LCD_SetDisplayWindow (uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width) 
{
    
        /* Horizontal GRAM Start Address */ 
        if (Xpos >= Height)
        
    {
        
    
    
    else
        
    {
        
    
    
        /* Horizontal GRAM End Address */ 
        LCD_WriteReg (LCD_REG_81, Xpos);
    
        /* Vertical GRAM Start Address */ 
        if (Ypos >= Width)
        
    {
        
    
    
    else
        
    {
        
    
    
        /* Vertical GRAM End Address */ 
        LCD_WriteReg (LCD_REG_83, Ypos);
    



/**
  * @brief  Disables LCD Window mode.
  * @param  None
  * @retval None
  */ 
void LCD_WindowModeDisable (void) 
{
    
    


/**
  * @brief  Displays a line.
  * @param Xpos: specifies the X position.
  * @param Ypos: specifies the Y position.
  * @param Length: line length.
  * @param Direction: line direction.
  *   This parameter can be one of the following values: Vertical or Horizontal.
  * @retval None
  */ 
void LCD_DrawLine (uint8_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction) 
{
    
    
    
        
    {
        
        
            
        {
            
        
    
    
    else
        
    {
        
            
        {
            
            
            
            
        
    



/**
  * @brief  Displays a rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: display rectangle height.
  * @param  Width: display rectangle width.
  * @retval None
  */ 
void LCD_DrawRect (uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width) 
{
    
    
    
    


/**
  * @brief  Displays a circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */ 
void LCD_DrawCircle (uint8_t Xpos, uint16_t Ypos, uint16_t Radius) 
{
    
    
    
    
    
    
    
        
    {
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            
        {
            
        
        
        else
            
        {
            
            
        
        
    



/**
  * @brief  Displays a monocolor picture.
  * @param  Pict: pointer to the picture array.
  * @retval None
  */ 
void LCD_DrawMonoPict (const uint32_t * Pict) 
{
    
    
    
    
        
    {
        
            
        {
            
                
            {
                
            
            
            else
                
            {
                
            
        
    



/**
  * @brief  Displays a bitmap picture loaded in the internal Flash.
  * @param  BmpAddress: Bmp picture address in the internal Flash.
  * @retval None
  */ 
void LCD_WriteBMP (uint32_t BmpAddress) 
{
    
    
        /* Read bitmap size */ 
        size = *(__IO uint16_t *) (BmpAddress + 2);
    
    
        /* Get bitmap data address offset */ 
        index = *(__IO uint16_t *) (BmpAddress + 10);
    
    
    
    
        /* Set GRAM write direction and BGR = 1 */ 
        /* I/D=00 (Horizontal : decrement, Vertical : decrement) */ 
        /* AM=1 (address is updated in vertical writing direction) */ 
        LCD_WriteReg (LCD_REG_3, 0x1008);
    
    
        
    {
        
        
    
    
        /* Set GRAM write direction and BGR = 1 */ 
        /* I/D = 01 (Horizontal : increment, Vertical : decrement) */ 
        /* AM = 1 (address is updated in vertical writing direction) */ 
        LCD_WriteReg (LCD_REG_3, 0x1018);



/**
  * @brief  Displays a full rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: rectangle height.
  * @param  Width: rectangle width.
  * @retval None
  */ 
void LCD_DrawFullRect (uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height) 
{
    
    
    
    
    
    
    
    
    
    
        
    {
        
    
    



/**
  * @brief  Displays a full circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */ 
void LCD_DrawFullCircle (uint16_t Xpos, uint16_t Ypos, uint16_t Radius) 
{
    
    
    
    
    
    
    
    
        
    {
        
            
        {
            
            
        
        
            
        {
            
            
        
        
            
        {
            
        
        
        else
            
        {
            
            
        
        
    
    
    



/**
  * @brief  Displays an uni line (between two points).
  * @param  x1: specifies the point 1 x position.
  * @param  y1: specifies the point 1 y position.
  * @param  x2: specifies the point 2 x position.
  * @param  y2: specifies the point 2 y position.
  * @retval None
  */ 
void LCD_DrawUniLine (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) 
{
    
        0, 
    
    
    
    
    
        
    {
        
        
    
    
    else    /* The x-values are decreasing */
        
    {
        
        
    
    
        
    {
        
        
    
    
    else    /* The y-values are decreasing */
        
    {
        
        
    
    
        
    {
        
        
        
        
        
        
    
    
    else    /* There is at least one y-value for every x-value */
        
    {
        
        
        
        
        
        
    
    
        
    {
        
        
        
            
        {
            
            
            
        
        
        
    



/**
  * @brief  Displays an polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */ 
void LCD_PolyLine (pPoint Points, uint16_t PointCount) 
{
    
    
        
    {
        
    
    
        
    {
        
        
        
        
    



/**
  * @brief  Displays an relative polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @param  Closed: specifies if the draw is closed or not.
  *           1: closed, 0 : not closed.
  * @retval None
  */ 
static void LCD_PolyLineRelativeClosed (pPoint Points, uint16_t PointCount, uint16_t Closed) 
{
    
    
    
        
    {
        
    
    
    
    
        
    {
        
        
        
        
    
    
        
    {
        
    



/**
  * @brief  Displays a closed polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */ 
void LCD_ClosedPolyLine (pPoint Points, uint16_t PointCount) 
{
    
    


/**
  * @brief  Displays a relative polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */ 
void LCD_PolyLineRelative (pPoint Points, uint16_t PointCount) 
{
    


/**
  * @brief  Displays a closed relative polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */ 
void LCD_ClosedPolyLineRelative (pPoint Points, uint16_t PointCount) 
{
    


/**
  * @brief  Displays a  full polyline (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */ 
void LCD_FillPolyLine (pPoint Points, uint16_t PointCount) 
{
    
        /* public-domain code by Darel Rex Finley, 2007 */ 
        uint16_t nodes = 0, nodeX[MAX_POLY_CORNERS], pixelX = 0, pixelY = 0, i = 0, 
    
    
    
    
        
    {
        
        
            
        {
            
        
        
            
        {
            
        
        
        
            
        {
            
        
        
            
        {
            
        
    
    
    
        /* Loop through the rows of the image. */ 
        for (pixelY = IMAGE_TOP; pixelY < IMAGE_BOTTOM; pixelY++)
        
    {
        
            /* Build a list of nodes. */ 
            nodes = 0;
        j = PointCount - 1;
        
            
        {
            
                
            {
                
            
            
        
            /* Sort the nodes, via a simple �Bubble� sort. */ 
            i = 0;
        
            
        {
            
                
            {
                
                
                
                
                    
                {
                    
                
            
            
            else
                
            {
                
            
        
        
            /* Fill the pixels between node pairs. */ 
            for (i = 0; i < nodes; i += 2)
            
        {
            
                
            {
                
            
            
                
            {
                
                    
                {
                    
                
                
                    
                {
                    
                
                
                
                
                
                
                
                    /* for (j=nodeX[i]; j<nodeX[i+1]; j++) PutPixel(j,pixelY); */ 
            }
        
    
    
        /* draw the edges */ 
        LCD_SetTextColor (TextColor);



/**
  * @brief  Writes to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @param  LCD_RegValue: value to write to the selected register.
  * @retval None
  */ 
void LCD_WriteReg (uint8_t LCD_Reg, uint16_t LCD_RegValue) 
{
    
        /* Write 16-bit Index, then Write Reg */ 
        LCD->LCD_REG = LCD_Reg;
    
        /* Write 16-bit Reg */ 
        LCD->LCD_RAM = LCD_RegValue;


/**
  * @brief  Reads the selected LCD Register.
  * @param  LCD_Reg: address of the selected register.
  * @retval LCD Register Value.
  */ 
    uint16_t LCD_ReadReg (uint8_t LCD_Reg) 
{
    
        /* Write 16-bit Index (then Read Reg) */ 
        LCD->LCD_REG = LCD_Reg;
    
        /* Read 16-bit Reg */ 
        return (LCD->LCD_RAM);



/**
  * @brief  Prepare to write to the LCD RAM.
  * @param  None
  * @retval None
  */ 
void LCD_WriteRAM_Prepare (void) 
{
    


/**
  * @brief  Writes to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */ 
void LCD_WriteRAM (uint16_t RGB_Code) 
{
    
        /* Write 16-bit GRAM Reg */ 
        LCD->LCD_RAM = RGB_Code;


/**
  * @brief  Reads the LCD RAM.
  * @param  None
  * @retval LCD RAM Value.
  */ 
    uint16_t LCD_ReadRAM (void) 
{
    
        /* Write 16-bit Index (then Read Reg) */ 
        LCD->LCD_REG = LCD_REG_34;  /* Select GRAM Reg */
    
        /* Read 16-bit Reg */ 
        return LCD->LCD_RAM;



/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */ 
void LCD_PowerOn (void) 
{
    
        /* Power On sequence --------------------------------------------------------- */ 
        LCD_WriteReg (LCD_REG_16, 0x0000);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    
    
    
    
    
    
    
    
    
    
    
    
    


/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */ 
void LCD_DisplayOn (void) 
{
    
        /* Display On */ 
        LCD_WriteReg (LCD_REG_7, 0x0173);   /* 262K color and display ON */


/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */ 
void LCD_DisplayOff (void) 
{
    
        /* Display Off */ 
        LCD_WriteReg (LCD_REG_7, 0x0);


/**
  * @brief  Configures LCD Control lines (FSMC Pins) in alternate function mode.
  * @param  None
  * @retval None
  */ 
void LCD_CtrlLinesConfig (void) 
{
    
    
        /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */ 
        RCC_AHBPeriphClockCmd (RCC_AHBPeriph_FSMC, ENABLE);
    
                             
    
        /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
           pull */ 
        GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | 
    
    
    
    
        /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
        GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
    
    
        /* Set PF.00(A0 (RS)) as alternate function push pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    
    
        /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    


/**
  * @brief  Configures the Parallel interface (FSMC) for LCD(Parallel mode)
  * @param  None
  * @retval None
  */ 
void LCD_FSMCConfig (void) 
{
    
    
    
/*-- FSMC Configuration ------------------------------------------------------*/ 
/*----------------------- SRAM Bank 4 ----------------------------------------*/ 
        /* FSMC_Bank1_NORSRAM4 configuration */ 
        p.FSMC_AddressSetupTime = 1;
    
    
    
    
    
    
    
        /* Color LCD configuration ------------------------------------
           SRAM
        FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* BANK 4 (of NOR/SRAM Bank 1~4) is enabled */ 
        FSMC_NORSRAMCmd (FSMC_Bank1_NORSRAM4, ENABLE);


/**
  * @brief  Displays a pixel.
  * @param  x: pixel x.
  * @param  y: pixel y.  
  * @retval None
  */ 
static void PutPixel (int16_t x, int16_t y) 
{
    
        
    {
        
    
    



#ifndef USE_Delay
/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */ 
static void delay (vu32 nCount) 
{
    
    
        
    {
    



#endif  /* USE_Delay*/
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 