/**
  ******************************************************************************
  * @file TIM/PWM_Input/main.c 
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
    
/** @addtogroup TIM_PWM_Input
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    TIM_ICInitTypeDef TIM_ICInitStructure;

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
    
        /* TIM3 configuration: PWM Input mode ------------------------
           is used as active edge,
           ------------------------------------------------------------ */ 
        
    
    
    
    
    
    
        /* Select the TIM3 Input Trigger: TI2FP2 */ 
        TIM_SelectInputTrigger (TIM3, TIM_TS_TI2FP2);
    
        /* Select the slave Mode: Reset Mode */ 
        TIM_SelectSlaveMode (TIM3, TIM_SlaveMode_Reset);
    
        /* Enable the Master/Slave Mode */ 
        TIM_SelectMasterSlaveMode (TIM3, TIM_MasterSlaveMode_Enable);
    
        /* TIM enable counter */ 
        TIM_Cmd (TIM3, ENABLE);
    
        /* Enable the CC2 Interrupt Request */ 
        TIM_ITConfig (TIM3, TIM_IT_CC2, ENABLE);
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* TIM3 clock enable */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE);
    
        /* GPIOA clock enable */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);


/**
  * @brief  Configure the GPIOD Pins.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
        /* TIM3 channel 2 pin (PA.07) configuration */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    
    
    


/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Enable the TIM3 global Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    
    
    
    


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
        
        
    {
    }



#endif /* 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 