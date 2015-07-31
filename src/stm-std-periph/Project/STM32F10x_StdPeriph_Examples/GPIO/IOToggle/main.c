/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main program body.
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
#include "stm32_eval.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup GPIO_IOToggle
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Private function prototypes ----------------------------------------------- */ 
void Delay (__IO uint32_t nCount);


    /* Private functions --------------------------------------------------------- */ 
    
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */ 
int main (void) 
{
    
        /* !< At this stage the microcontroller clock setting is already configured, 
           from startup
           function, refer to
        
        /* Configure all unused GPIO port pins in Analog Input mode (floating input
           increase the device
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                                
    
    
    
    
    
    
    
    
                              
    
#ifdef USE_STM3210E_EVAL
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);
    
    
    
    
#endif  /* USE_STM3210E_EVAL */
        
        /* Initialize Leds mounted on STM3210X-EVAL board */ 
        STM_EVAL_LEDInit (LED1);
    
    
    
    
        
    {
        
            /* Turn on LD1 */ 
            STM_EVAL_LEDOn (LED1);
        
            /* Insert delay */ 
            Delay (0xAFFFF);
        
            /* Turn on LD2 and LD3 */ 
            STM_EVAL_LEDOn (LED2);
        
        
            /* Turn off LD1 */ 
            STM_EVAL_LEDOff (LED1);
        
            /* Insert delay */ 
            Delay (0xAFFFF);
        
            /* Turn on LD4 */ 
            STM_EVAL_LEDOn (LED4);
        
            /* Turn off LD2 and LD3 */ 
            STM_EVAL_LEDOff (LED2);
        
        
            /* Insert delay */ 
            Delay (0xAFFFF);
        
            /* Turn off LD4 */ 
            STM_EVAL_LEDOff (LED4);
    



/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */ 
void Delay (__IO uint32_t nCount) 
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