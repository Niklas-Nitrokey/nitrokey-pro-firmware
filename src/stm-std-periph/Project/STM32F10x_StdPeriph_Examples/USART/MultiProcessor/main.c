/**
  ******************************************************************************
  * @file    USART/MultiProcessor/main.c 
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
    
/** @addtogroup USART_MultiProcessor
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
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
    
        /* Configure the GPIO ports */ 
        GPIO_Configuration ();
    
        /* Initialize Leds, Wakeup and Key Buttons mounted on STM3210X-EVAL board */ 
        STM_EVAL_LEDInit (LED1);
    
    
    
    
    
    
        /* USARTy and USARTz configuration ------------------------------------------- */ 
        /* USARTy and USARTz configured as follow:
           control disabled (RTS and CTS signals)
        USART_InitStructure.USART_BaudRate = 9600;
    
    
    
    
    
    
        /* Configure USARTy */ 
        USART_Init (USARTy, &USART_InitStructure);
    
        /* Configure USARTz */ 
        USART_Init (USARTz, &USART_InitStructure);
    
        /* Enable the USARTy */ 
        USART_Cmd (USARTy, ENABLE);
    
        /* Enable the USARTz */ 
        USART_Cmd (USARTz, ENABLE);
    
        /* Set the USARTy Address */ 
        USART_SetAddress (USARTy, 0x1);
    
        /* Set the USARTz Address */ 
        USART_SetAddress (USARTz, 0x2);
    
        /* Select the USARTz WakeUp Method */ 
        USART_WakeUpConfig (USARTz, USART_WakeUp_AddressMark);
    
        
    {
        
            /* Send one byte from USARTy to USARTz */ 
            USART_SendData (USARTy, 0x33);
        
            /* Wait while USART1 TXE = 0 */ 
            while (USART_GetFlagStatus (USARTz, USART_FLAG_TXE) == RESET)
            
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
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */ 
void Delay (__IO uint32_t nCount) 
{
    
        /* Decrement nCount value */ 
        for (; nCount != 0; nCount--);



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