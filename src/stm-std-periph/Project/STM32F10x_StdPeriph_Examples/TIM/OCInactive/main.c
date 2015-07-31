/**
  ******************************************************************************
  * @file TIM/OCInactive/main.c 
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
    
/** @addtogroup TIM_OCInactive
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;







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
    
        /* NVIC Configuration */ 
        NVIC_Configuration ();
    
        /* GPIO Configuration */ 
        GPIO_Configuration ();
    
        /* ---------------------------------------------------------------
           get TIM2 counter clock at 1 KHz:
           TIM2_CH1 delay = CCR1_Val/TIM2 counter clock = 1000 ms
           CCR3_Val/TIM2 counter clock = 250 ms
           Low-density, Medium-density, High-density
           line devices
        /* Compute the prescaler value */ 
        PrescalerValue = (uint16_t) (SystemCoreClock / 2000) - 1;
    
        /* Time base configuration */ 
        TIM_TimeBaseStructure.TIM_Period = 65535;
    
    
    
    
    
        /* Output Compare Active Mode configuration: Channel1 */ 
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
    
    
    
    
    
    
        /* Output Compare Active Mode configuration: Channel2 */ 
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    
    
    
    
        /* Output Compare Active Mode configuration: Channel3 */ 
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    
    
    
    
        /* Output Compare Active Mode configuration: Channel4 */ 
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    
    
    
    
    
        /* TIM IT enable */ 
        TIM_ITConfig (TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
    
        /* Set PC.06, PC.07, PC.08 and PC.09 pins */ 
        GPIO_SetBits (GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
    
        /* TIM2 enable counter */ 
        TIM_Cmd (TIM2, ENABLE);
    
        
    {
    }



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* PCLK1 = HCLK/4 */ 
        RCC_PCLK1Config (RCC_HCLK_Div4);
    
        /* TIM2 clock enable */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE);
    
        /* GPIOC clock enable */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);


/**
  * @brief  Configure the GPIOD Pins.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
        /* GPIOC Configuration: Pin6, 7, 8 and 9 as output push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    
    
    


/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Enable the TIM2 Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    
    
    
    


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