/**
  ******************************************************************************
  * @file    DMA/FLASH_RAM/main.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main program body
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
#include "stm32f10x.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup DMA_FLASH_RAM
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define BufferSize  32
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    DMA_InitTypeDef DMA_InitStructure;



    0x15161718, 0x191A1B1C, 0x1D1E1F20, 
    0x2D2E2F30, 
    0x393A3B3C, 0x3D3E3F40, 
    
    0x5D5E5F60, 
    0x75767778, 0x797A7B7C, 0x7D7E7F80
};



    /* Private function prototypes ----------------------------------------------- */ 
void RCC_Configuration (void);





    /* Private functions --------------------------------------------------------- */ 
    
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */ 
int main (void) 
{
    
        /* !< At this stage the microcontroller clock setting is already configured, 
           from startup
           function, refer to
        
        /* System Clocks Configuration */ 
        RCC_Configuration ();
    
        /* NVIC configuration */ 
        NVIC_Configuration ();
    
        /* DMA1 channel6 configuration */ 
        DMA_DeInit (DMA1_Channel6);
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* Enable DMA1 Channel6 Transfer Complete interrupt */ 
        DMA_ITConfig (DMA1_Channel6, DMA_IT_TC, ENABLE);
    
        /* Get Current Data Counter value before transfer begins */ 
        CurrDataCounterBegin = DMA_GetCurrDataCounter (DMA1_Channel6);
    
        /* Enable DMA1 Channel6 transfer */ 
        DMA_Cmd (DMA1_Channel6, ENABLE);
    
        /* Wait the end of transmission */ 
        while (CurrDataCounterEnd != 0)
        
    {
    
    
        /* Check if the transmitted and received data are equal */ 
        TransferStatus = Buffercmp (SRC_Const_Buffer, DST_Buffer, BufferSize);
    
        /* TransferStatus = PASSED, if the transmitted and received data 
        /* TransferStatus = FAILED, if the transmitted and received data 
        
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* Enable peripheral clocks ------------------------------------------------ */ 
        /* Enable DMA1 clock */ 
        RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1, ENABLE);


/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Enable DMA1 channel6 IRQ Channel */ 
        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
    
    
    
    


/**
  * @brief  Compares two buffers.
  * @param  pBuffer, pBuffer1: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer identical to pBuffer1
  *   FAILED: pBuffer differs from pBuffer1
  */ 
    TestStatus Buffercmp (const uint32_t * pBuffer, uint32_t * pBuffer1, uint16_t BufferLength) 
{
    
        
    {
        
            
        {
            
        
        
        
    
    



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */ 
void assert_failed (uint8_t * file, uint32_t line) 
{
    
        /* User can add his own implementation to report the file name and line number,
           file, line) */ 
        
        /* Infinite loop */ 
        while (1)
        
    {
    



#endif /* 
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 