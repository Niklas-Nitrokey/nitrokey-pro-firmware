/**
  ******************************************************************************
  * @file    stm32100b_eval_lcd.c
  * @author  MCD Application Team
  * @version V4.2.0
  * @date    04/16/2010
  * @brief   This file includes the LCD driver for AM-240320LTNQW00H (LCD_HX8312),
  *          AM-240320L8TNQW00H (LCD_ILI9320), AM-240320LDTNQW00H (LCD_SPFD5408B)
  *          Liquid Crystal Display Module of STM32100B-EVAL board.
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
#include "stm32100b_eval_lcd.h"
#include "../Common/fonts.c"
    
/** @addtogroup Utilities
  * @{
  */ 
    
/** @addtogroup STM32_EVAL
  * @{
  */ 
    
/** @addtogroup STM32100B_EVAL
  * @{
  */ 
    
/** @defgroup STM32100B_EVAL_LCD 
  * @brief   This file includes the LCD driver for AM-240320LTNQW00H (LCD_HX8312),
  *          AM-240320L8TNQW00H (LCD_ILI9320), AM-240320LDTNQW00H (LCD_SPFD5408B)
  *          Liquid Crystal Display Module of STM32100B-EVAL board.
  * @{
  */ 
    
/** @defgroup STM32100B_EVAL_LCD_Private_Types
  * @{
  */ 
/**
  * @}
  */ 
    
/** @defgroup STM32100B_EVAL_LCD_Private_Defines
  * @{
  */ 
#define LCD_ILI9320        0x9320
#define LCD_HX8312         0x8312
#define LCD_SPFD5408       0x5408
#define START_BYTE         0x70
#define SET_INDEX          0x00
#define READ_STATUS        0x01
#define LCD_WRITE_REG      0x02
#define LCD_READ_REG       0x03
#define MAX_POLY_CORNERS   200
#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))
/**
  * @}
  */ 
    
/** @defgroup STM32100B_EVAL_LCD_Private_Macros
  * @{
  */ 
#define ABS(X)  ((X) > 0 ? (X) : -(X))  
/**
  * @}
  */ 
    
/** @defgroup STM32100B_EVAL_LCD_Private_Variables
  * @{
  */ 
static sFONT* LCD_Currentfonts;


    /* Global variables to set the written text color */ 
static __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;




/**
  * @}
  */ 
    
/** @defgroup STM32100B_EVAL_LCD_Private_Function_Prototypes
  * @{
  */ 
#ifndef USE_Delay
static void delay (vu32 nCount);


#endif  /* USE_Delay*/








/**
  * @}
  */ 
    
/** @defgroup STM32100B_EVAL_LCD_Private_Functions
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
    
        /* !< LCD_SPI disable */ 
        SPI_Cmd (LCD_SPI, DISABLE);
    
        /* !< LCD_SPI DeInit */ 
        SPI_I2S_DeInit (LCD_SPI);
    
        /* !< Disable SPI clock */ 
        RCC_APB1PeriphClockCmd (LCD_SPI_CLK, DISABLE);
    
        /* Configure NCS in Output Push-Pull mode */ 
        GPIO_InitStructure.GPIO_Pin = LCD_NCS_PIN;
    
    
    
        /* Configure NWR(RNW), RS in Output Push-Pull mode */ 
        GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN;
    
    
    
    
        /* Configure SPI pins: SCK, MISO and MOSI */ 
        GPIO_InitStructure.GPIO_Pin = LCD_SPI_SCK_PIN;
    
    
    
    
    


/**
  * @brief  Setups the LCD.
  * @param  None
  * @retval None
  */ 
void LCD_Setup (void) 
{
    
        /* Configure the LCD Control pins -------------------------------------------- */ 
        LCD_CtrlLinesConfig ();
    
        /* Configure the LCD_SPI interface ---------------------------------------------- */ 
        LCD_SPIConfig ();
    
        
    {
        
        
            /* Start Initial Sequence ------------------------------------------------ */ 
            LCD_WriteReg (LCD_REG_229, 0x8000); /* Set the internal vcore voltage */
        
        
        
        
        
        
        
        
        
        
        
        
            /* Power On sequence ----------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_16, 0x0000);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            /* Adjust the Gamma Curve ------------------------------------------------ */ 
            LCD_WriteReg (LCD_REG_48, 0x0006);
        
        
        
        
        
        
        
        
        
        
            /* Set GRAM area --------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_80, 0x0000);  /* Horizontal GRAM Start Address */
        
        
        
        
        
        
        
            /* Partial Display Control ----------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_128, 0x0000);
        
        
        
        
        
        
            /* Panel Control --------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_144, 0x0010);
        
        
        
        
        
        
            /* Set GRAM write direction and BGR = 1 */ 
            /* I/D=01 (Horizontal : increment, Vertical : decrement) */ 
            /* AM=1 (address is updated in vertical writing direction) */ 
            LCD_WriteReg (LCD_REG_3, 0x1018);
        
    
    
    else if (LCDType == LCD_SPFD5408)
        
    {
        
            /* Start Initial Sequence -------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_227, 0x3008); /* Set internal timing */
        
        
        
        
        
        
        
        
        
        
        
        
        
            /* Power On sequence ------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_16, 0x0000);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            /* Adjust the Gamma Curve -------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_48, 0x0007);
        
        
        
        
        
        
        
        
        
        
            /* Set GRAM area ----------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_80, 0x0000);  /* Horizontal GRAM Start Address */
        
        
        
        
        
        
        
            /* Partial Display Control ------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_128, 0x0000);
        
        
        
        
        
        
            /* Panel Control ----------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_144, 0x0010);
        
        
        
        
        
        
            /* Set GRAM write direction and BGR = 1
               writing direction) */ 
            LCD_WriteReg (LCD_REG_3, 0x1018);
        
    
    
    else if (LCDType == LCD_HX8312)
        
    {
        
            /* Enable the LCD Oscillator --------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_1, 0x10);
        
        
        
        
        
        
        
        
        
        
            /* LCD Power On ---------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_28, 0x73);
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            /* Chip Set -------------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_157, 0x00);
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
            /* Gamma Set ------------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_143, 0x10);
        
        
        
        
        
        
        
        
        
        
        
        
            /* Display On ------------------------------------------------------------ */ 
            LCD_WriteReg (LCD_REG_1, 0x50);
        
        
        
        
        
    



/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval None
  */ 
void STM32100B_LCD_Init (void) 
{
    
        /* Setups the LCD */ 
        LCD_Setup ();
    
        /* Try to read new LCD controller ID 0x9320 */ 
        if (LCD_ReadReg (LCD_REG_0) == LCD_ILI9320)
        
    {
        
    
    
    else
        
    {
        
        
            /* Setups the LCD */ 
            LCD_Setup ();
        
            /* Try to read new LCD controller ID 0x5408 */ 
            if (LCD_ReadReg (LCD_REG_0) != LCD_SPFD5408)
            
        {
            
            
                /* Setups the LCD */ 
                LCD_Setup ();
        
    
    



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
    
        
    {
        
        
    
    
    else if (LCDType == LCD_HX8312)
        
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
            
        
        
            
        {
            
                    ((0x80 << ((LCD_Currentfonts->Width / 12) * 8)) >> i)) ==
                   0x00) && (LCD_Currentfonts->Width <= 12)) || 
                
            {
                
            
            
            else
                
            {
                
            
        
        
            
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
    
    
    else if (LCDType == LCD_HX8312)
        
    {
        
        
        
        
        
        
        
        
    
    



/**
  * @brief  Disables LCD Window mode.
  * @param  None
  * @retval None
  */ 
void LCD_WindowModeDisable (void) 
{
    
        
    {
        
        
    
    
    else if (LCDType == LCD_HX8312)
        
    {
        
        
    



/**
  * @brief  Displays a line.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Length: line length.
  * @param  Direction: line direction.
  *   This parameter can be one of the following values: Vertical or Horizontal.
  * @retval None
  */ 
void LCD_DrawLine (uint8_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction) 
{
    
    
    
        
    {
        
            
        {
            
        
        
            
        {
            
        
        
            
        {
            
        
    
    
    else
        
    {
        
            
        {
            
                
            {
                
            
            
            else if (LCDType == LCD_HX8312)
                
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
            
        
        
        else if (LCDType == LCD_HX8312)
            
        {
            
        
        
        
            
        {
            
        
        
        else if (LCDType == LCD_HX8312)
            
        {
            
        
        
        
            
        {
            
        
        
        else if (LCDType == LCD_HX8312)
            
        {
            
        
        
        
            
        {
            
        
        
        else if (LCDType == LCD_HX8312)
            
        {
            
        
        
        
            
        {
            
        
        
        else if (LCDType == LCD_HX8312)
            
        {
            
        
        
        
            
        {
            
        
        
        else if (LCDType == LCD_HX8312)
            
        {
            
        
        
        
            
        {
            
        
        
        else if (LCDType == LCD_HX8312)
            
        {
            
        
        
        
            
        {
            
        
        
        else if (LCDType == LCD_HX8312)
            
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
            
                
            {
                
            
            
            else
                
            {
                
            
        
    
    
        
    {
        
    



#ifdef USE_LCD_DrawBMP 
/**
  * @brief  Displays a bitmap picture loaded in the SPI Flash.
  * @param  BmpAddress: Bmp picture address in the SPI Flash.
  * @retval None
  */ 
void LCD_DrawBMP (uint32_t BmpAddress) 
{
    
    
        /* Read bitmap size */ 
        SPI_FLASH_BufferRead ((uint8_t *) & size, BmpAddress + 2, 4);
    
        /* get bitmap data address offset */ 
        SPI_FLASH_BufferRead ((uint8_t *) & i, BmpAddress + 10, 4);
    
    
    
        /* Disable SPI1 */ 
        SPI_Cmd (SPI1, DISABLE);
    
        /* SPI in 16-bit mode */ 
        SPI_DataSizeConfig (SPI1, SPI_DataSize_16b);
    
        /* Enable SPI1 */ 
        SPI_Cmd (SPI1, ENABLE);
    
        
    {
        
            /* Set GRAM write direction and BGR = 1 */ 
            /* I/D=00 (Horizontal : decrement, Vertical : decrement) */ 
            /* AM=1 (address is updated in vertical writing direction) */ 
            LCD_WriteReg (LCD_REG_3, 0x1008);
        
    
    
        /* Read bitmap data from SPI Flash and send them to LCD */ 
        for (i = 0; i < size; i++)
        
    {
        
    
    
        
    {
        
    
    
        /* Deselect the FLASH: Chip Select high */ 
        SPI_FLASH_CS_HIGH ();
    
        /* Disable SPI1 */ 
        SPI_Cmd (SPI1, DISABLE);
    
        /* SPI in 8-bit mode */ 
        SPI_DataSizeConfig (SPI1, SPI_DataSize_8b);
    
        /* Enable SPI1 */ 
        SPI_Cmd (SPI1, ENABLE);
    
        
    {
        
            /* Set GRAM write direction and BGR = 1 */ 
            /* I/D = 01 (Horizontal : increment, Vertical : decrement) */ 
            /* AM = 1 (address is updated in vertical writing direction) */ 
            LCD_WriteReg (LCD_REG_3, 0x1018);
    



#endif  /* USE_LCD_DrawBMP */
    
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
  * @brief  Reset LCD control line(/CS) and Send Start-Byte
  * @param  Start_Byte: the Start-Byte to be sent
  * @retval None
  */ 
void LCD_nCS_StartByte (uint8_t Start_Byte) 
{
    
    
    
        
    {
    



/**
  * @brief  Writes index to select the LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */ 
void LCD_WriteRegIndex (uint8_t LCD_Reg) 
{
    
        /* Reset LCD control line(/CS) and Send Start-Byte */ 
        LCD_nCS_StartByte (START_BYTE | SET_INDEX);
    
        /* Write 16-bit Reg Index (High Byte is 0) */ 
        SPI_I2S_SendData (LCD_SPI, 0x00);
    
        
    {
    
    
    
        
    {
    
    



/**
  * @brief  Writes to the selected LCD ILI9320 register.
  * @param  LCD_Reg: address of the selected register.
  * @param  LCD_RegValue: value to write to the selected register.
  * @retval None
  */ 
static void LCD_WriteRegILI9320 (uint8_t LCD_Reg, uint16_t LCD_RegValue) 
{
    
        /* Write 16-bit Index (then Write Reg) */ 
        LCD_WriteRegIndex (LCD_Reg);
    
        /* Write 16-bit Reg */ 
        /* Reset LCD control line(/CS) and Send Start-Byte */ 
        LCD_nCS_StartByte (START_BYTE | LCD_WRITE_REG);
    
    
        
    {
    
    
    
        
    {
    
    



/**
  * @brief  Reads the selected LCD Register.
  * @param  LCD_Reg: address of the selected register.
  * @retval LCD Register Value.
  */ 
    uint16_t LCD_ReadReg (uint8_t LCD_Reg) 
{
    
    
    
        /* LCD_SPI prescaler: 4 */ 
        LCD_SPI->CR1 &= 0xFFC7;
    
    
        /* Write 16-bit Index (then Read Reg) */ 
        LCD_WriteRegIndex (LCD_Reg);
    
        /* Read 16-bit Reg */ 
        /* Reset LCD control line(/CS) and Send Start-Byte */ 
        LCD_nCS_StartByte (START_BYTE | LCD_READ_REG);
    
        
    {
        
        
            
        {
        
        
            /* One byte of invalid dummy data read after the start byte */ 
            while (SPI_I2S_GetFlagStatus (LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
            
        {
        
        
    
    
    
        /* Read upper byte */ 
        while (SPI_I2S_GetFlagStatus (LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
        
    {
    
    
        /* Read lower byte */ 
        while (SPI_I2S_GetFlagStatus (LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
        
    {
    
    
    
    
        
    {
    
    
        /* Read lower byte */ 
        while (SPI_I2S_GetFlagStatus (LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
        
    {
    
    
    
    
        /* LCD_SPI prescaler: 2 */ 
        LCD_SPI->CR1 &= 0xFFC7;
    



/**
  * @brief  Prepare to write to the LCD RAM.
  * @param  None
  * @retval None
  */ 
void LCD_WriteRAM_Prepare (void) 
{
    
    
        /* Reset LCD control line(/CS) and Send Start-Byte */ 
        LCD_nCS_StartByte (START_BYTE | LCD_WRITE_REG);


/**
  * @brief  Writes 1 word to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */ 
void LCD_WriteRAMWord (uint16_t RGB_Code) 
{
    
    
    


/**
  * @brief  Writes to the selected LCD HX8312 register.
  * @param  LCD_Reg: address of the selected register.
  * @param  LCD_RegValue: value to write to the selected register.
  * @retval None
  */ 
static void LCD_WriteRegHX8312 (uint8_t LCD_Reg, uint8_t LCD_RegValue) 
{
    
    
    
    
    
    
    
    
        
    {
    
    



/**
  * @brief  Writes to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @param  LCD_RegValue: value to write to the selected register.
  * @retval None
  */ 
void LCD_WriteReg (uint8_t LCD_Reg, uint16_t LCD_RegValue) 
{
    
        
    {
        
    
    
    else if (LCDType == LCD_HX8312)
        
    {
        
    



/**
  * @brief  Writes to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */ 
void LCD_WriteRAM (uint16_t RGB_Code) 
{
    
        
    {
        
        
            
        {
        
        
        
            
        {
        
    
    
        
    {
        
        
        
        
        
            
        {
        
        
    



/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */ 
void LCD_PowerOn (void) 
{
    
        
    {
        
            /* Power On sequence --------------------------------------------------------- */ 
            LCD_WriteReg (LCD_REG_16, 0x0000);  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        
        
        
        
        
        
        
        
        
        
        
        
        
    
    
    else if (LCDType == LCD_HX8312)
        
    {
        
            /* Power On Set */ 
            LCD_WriteReg (LCD_REG_28, 0x73);
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    



/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */ 
void LCD_DisplayOn (void) 
{
    
        
    {
        
            /* Display On */ 
            LCD_WriteReg (LCD_REG_7, 0x0173);   /* 262K color and display ON */
    
    
    else if (LCDType == LCD_HX8312)
        
    {
        
        
        
            /* Display On */ 
            LCD_WriteReg (LCD_REG_0, 0x80);
        
        
        
    



/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */ 
void LCD_DisplayOff (void) 
{
    
        
    {
        
            /* Display Off */ 
            LCD_WriteReg (LCD_REG_7, 0x0);
    
    
    else if (LCDType == LCD_HX8312)
        
    {
        
            /* Display Off */ 
            LCD_WriteReg (LCD_REG_0, 0xA0);
        
        
    



/**
  * @brief  Configures LCD control lines in Output Push-Pull mode.
  * @param  None
  * @retval None
  */ 
void LCD_CtrlLinesConfig (void) 
{
    
    
        /* Enable GPIO clock */ 
        RCC_APB2PeriphClockCmd (LCD_NCS_GPIO_CLK | LCD_NWR_GPIO_CLK | LCD_RS_GPIO_CLK, ENABLE);
    
        /* Configure NCS in Output Push-Pull mode */ 
        GPIO_InitStructure.GPIO_Pin = LCD_NCS_PIN;
    
    
    
    
        /* Configure NWR(RNW), RS in Output Push-Pull mode */ 
        GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN;
    
    
    
    
    


/**
  * @brief  Sets or reset LCD control lines.
  * @param  GPIOx: where x can be B or D to select the GPIO peripheral.
  * @param  CtrlPins: the Control line.
  *   This parameter can be:
  *     @arg LCD_NCS_PIN: Chip Select pin
  *     @arg LCD_NWR_PIN: Read/Write Selection pin
  *     @arg LCD_RS_PIN: Register/RAM Selection pin
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */ 
void LCD_CtrlLinesWrite (GPIO_TypeDef * GPIOx, uint16_t CtrlPins, BitAction BitVal) 
{
    
        /* Set or Reset the control line */ 
        GPIO_WriteBit (GPIOx, CtrlPins, BitVal);


/**
  * @brief  Configures the LCD_SPI interface.
  * @param  None
  * @retval None
  */ 
void LCD_SPIConfig (void) 
{
    
    
    
        /* Enable GPIO clock */ 
        RCC_APB2PeriphClockCmd (LCD_SPI_SCK_GPIO_CLK | LCD_SPI_MISO_GPIO_CLK | LCD_SPI_MOSI_GPIO_CLK, ENABLE);
    
        /* Enable SPI clock */ 
        RCC_APB1PeriphClockCmd (LCD_SPI_CLK, ENABLE);
    
        /* Configure SPI pins: SCK, MISO and MOSI */ 
        GPIO_InitStructure.GPIO_Pin = LCD_SPI_SCK_PIN;
    
    
    
    
    
    
    
    
    
        /* SPI Config */ 
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    
    
        
    {
        
        
        
    
    
    else if (LCDType == LCD_HX8312)
        
    {
        
        
        
    
    
    
    
    
    
        /* SPI enable */ 
        SPI_Cmd (LCD_SPI, ENABLE);



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