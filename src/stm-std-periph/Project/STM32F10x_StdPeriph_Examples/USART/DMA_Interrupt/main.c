/**
  ******************************************************************************
  * @file    USART/DMA_Interrupt/main.c 
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
#include "platform_config.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup USART_DMA_Interrupt
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define TxBufferSize2   (countof(TxBuffer2) - 1)
    
    /* Private macro ------------------------------------------------------------- */ 
#define countof(a)   (sizeof(a) / sizeof(*(a)))
    
    /* Private variables --------------------------------------------------------- */ 
    USART_InitTypeDef USART_InitStructure;









    /* Private function prototypes ----------------------------------------------- */ 
void RCC_Configuration (void);









    /* Private functions --------------------------------------------------------- */ 
    
/**
  * @brief   Main program
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
    
        /* Configure the GPIO ports */ 
        GPIO_Configuration ();
    
        /* Configure the DMA */ 
        DMA_Configuration ();
    
        /* USARTy and USARTz configuration ------------------------------------------- */ 
        /* USARTy and USARTz configured as follow:
           control disabled (RTS and CTS signals)
        
    
    
    
    
    
    
        /* Configure USARTy */ 
        USART_Init (USARTy, &USART_InitStructure);
    
        /* Configure USARTz */ 
        USART_Init (USARTz, &USART_InitStructure);
    
        /* Enable USARTy DMA TX request */ 
        USART_DMACmd (USARTy, USART_DMAReq_Tx, ENABLE);
    
        /* Enable USARTz DMA TX request */ 
        USART_DMACmd (USARTz, USART_DMAReq_Tx, ENABLE);
    
        /* Enable the USARTz Receive Interrupt */ 
        USART_ITConfig (USARTz, USART_IT_RXNE, ENABLE);
    
        /* Enable USARTy */ 
        USART_Cmd (USARTy, ENABLE);
    
        /* Enable USARTz */ 
        USART_Cmd (USARTz, ENABLE);
    
        /* Enable USARTy DMA TX Channel */ 
        DMA_Cmd (USARTy_Tx_DMA_Channel, ENABLE);
    
        /* Enable USARTz DMA TX Channel */ 
        DMA_Cmd (USARTz_Tx_DMA_Channel, ENABLE);
    
        /* Receive the TxBuffer2 */ 
        while (index < TxBufferSize2)
        
    {
        
            
        {
        
        
    
    
        /* Wait until USARTy TX DMA1 Channel Transfer Complete */ 
        while (DMA_GetFlagStatus (USARTy_Tx_DMA_FLAG) == RESET)
        
    {
    
    
        /* Wait until USARTz TX DMA1 Channel Transfer Complete */ 
        while (DMA_GetFlagStatus (USARTz_Tx_DMA_FLAG) == RESET)
        
    {
    
    
        /* Check the received data with the send ones */ 
        TransferStatus1 = Buffercmp (TxBuffer2, RxBuffer1, TxBufferSize2);
    
        /* TransferStatus1 = PASSED, if the data transmitted from USARTz and 
        /* TransferStatus1 = FAILED, if the data transmitted from USARTz and 
        TransferStatus2 = Buffercmp (TxBuffer1, RxBuffer2, TxBufferSize1);
    
        /* TransferStatus2 = PASSED, if the data transmitted from USARTy and 
        /* TransferStatus2 = FAILED, if the data transmitted from USARTy and 
        
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* DMA clock enable */ 
        RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1, ENABLE);
    
        /* Enable GPIO clock */ 
        RCC_APB2PeriphClockCmd (USARTy_GPIO_CLK | USARTz_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
    
#ifndef USE_STM3210C_EVAL
        /* Enable USARTy Clock */ 
        RCC_APB2PeriphClockCmd (USARTy_CLK, ENABLE);
    
#else /* 
        /* Enable USARTy Clock */ 
        RCC_APB1PeriphClockCmd (USARTy_CLK, ENABLE);
    
#endif /* 
        /* Enable USARTz Clock */ 
        RCC_APB1PeriphClockCmd (USARTz_CLK, ENABLE);


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
#ifdef USE_STM3210C_EVAL
        /* Enable the USART3 Pins Software Remapping */ 
        GPIO_PinRemapConfig (GPIO_PartialRemap_USART3, ENABLE);
    
        /* Enable the USART2 Pins Software Remapping */ 
        GPIO_PinRemapConfig (GPIO_Remap_USART2, ENABLE);
    
#elif defined(USE_STM3210B_EVAL) || defined(USE_STM32100B_EVAL)
        /* Enable the USART2 Pins Software Remapping */ 
        GPIO_PinRemapConfig (GPIO_Remap_USART2, ENABLE);
    
#endif /* 
        
        /* Configure USARTy Rx as input floating */ 
        GPIO_InitStructure.GPIO_Pin = USARTy_RxPin;
    
    
    
        /* Configure USARTz Rx as input floating */ 
        GPIO_InitStructure.GPIO_Pin = USARTz_RxPin;
    
    
        /* Configure USARTy Tx as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = USARTy_TxPin;
    
    
    
    
        /* Configure USARTz Tx as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = USARTz_TxPin;
    


/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Enable the USARTz Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = USARTz_IRQn;
    
    
    
    


/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */ 
void DMA_Configuration (void) 
{
    
    
        /* USARTy_Tx_DMA_Channel (triggered by USARTy Tx event) Config */ 
        DMA_DeInit (USARTy_Tx_DMA_Channel);
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* USARTz_Tx_DMA_Channel (triggered by USARTz Tx event) Config */ 
        DMA_DeInit (USARTz_Tx_DMA_Channel);
    
    
    
    
    


/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */ 
    TestStatus Buffercmp (uint8_t * pBuffer1, uint8_t * pBuffer2, uint16_t BufferLength) 
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