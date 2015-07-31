/**
  ******************************************************************************
  * @file    DAC/TwoChannels_TriangleWave/main.c 
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
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup DAC_TwoChannels_TriangleWave
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
    /* Init Structure definition */ 
    DAC_InitTypeDef DAC_InitStructure;


    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    /* Private function prototypes ----------------------------------------------- */ 
void RCC_Configuration (void);






    /* Private functions --------------------------------------------------------- */ 
    
/**
  * @brief   Main program.
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
    
        /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically 
           consumption, 
        GPIO_Configuration ();
    
        /* TIM2 Configuration */ 
        TIM_TimeBaseStructInit (&TIM_TimeBaseStructure);
    
    
    
    
    
    
        /* TIM2 TRGO selection */ 
        TIM_SelectOutputTrigger (TIM2, TIM_TRGOSource_Update);
    
        /* DAC channel1 Configuration */ 
        DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
    
    
    
    
    
        /* DAC channel2 Configuration */ 
        DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;
    
    
        /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is 
        DAC_Cmd (DAC_Channel_1, ENABLE);
    
        /* Enable DAC Channel2: Once the DAC channel2 is enabled, PA.05 is 
        DAC_Cmd (DAC_Channel_2, ENABLE);
    
        /* Set DAC dual channel DHR12RD register */ 
        DAC_SetDualChannelData (DAC_Align_12b_R, 0x100, 0x100);
    
        /* TIM2 enable counter */ 
        TIM_Cmd (TIM2, ENABLE);
    
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* Enable peripheral clocks ------------------------------------------------ */ 
        /* GPIOA Periph clock enable */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);
    
        /* DAC Periph clock enable */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_DAC, ENABLE);
    
        /* TIM2 Periph clock enable */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE);


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
        /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically 
           consumption, 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    
    


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