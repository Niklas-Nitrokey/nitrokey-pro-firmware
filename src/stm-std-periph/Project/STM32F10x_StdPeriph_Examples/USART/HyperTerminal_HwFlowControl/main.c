/**
  ******************************************************************************
  * @file    USART/HyperTerminal_HwFlowControl/main.c 
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
    
/** @addtogroup USART_HyperTerminal_HwFlowControl
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
#define TxBufferSize   (countof(TxBuffer) - 1)
#define RxBufferSize   0xFF
    
    /* Private macro ------------------------------------------------------------- */ 
#define countof(a)   (sizeof(a) / sizeof(*(a)))
    
    /* Private variables --------------------------------------------------------- */ 
    USART_InitTypeDef USART_InitStructure;

Hyperterminal communication using hardware flow control\n\r";





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
    
        /* Configure the GPIO ports */ 
        GPIO_Configuration ();
    
        /* USART2 configuration ------------------------------------------------------ */ 
        /* USART2 configured as follow:
           enabled (RTS and CTS signals)
        USART_InitStructure.USART_BaudRate = 115200;
    
    
    
    
    
    
    
        /* Enable the USART2 */ 
        USART_Cmd (USART2, ENABLE);
    
        /* Communication hyperterminal-USART2 using hardware flow control ------------- */ 
        /* Send a buffer from USART to hyperterminal */ 
        while (NbrOfDataToTransfer--)
        
    {
        
        
    
    
        /* Receive a string (Max RxBufferSize bytes) from the Hyperterminal ended by '\r' (Enter key) */ 
        do
        
    {
        
            
        {
            
            
        
    
    
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* Enable GPIOx and AFIO clocks */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOx | RCC_APB2Periph_AFIO, ENABLE);
    
        /* Enable USART2 clocks */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_USART2, ENABLE);


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
#if defined(USE_STM3210B_EVAL) || defined(USE_STM32100B_EVAL)
        /* Enable the USART2 Pins Software Remapping */ 
        GPIO_PinRemapConfig (GPIO_Remap_USART2, ENABLE);
    
#endif /* 
        
        /* Configure USART2 RTS and USART2 Tx as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_RTSPin | GPIO_TxPin;
    
    
    
    
        /* Configure USART2 CTS and USART2 Rx as input floating */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_CTSPin | GPIO_RxPin;
    
    


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