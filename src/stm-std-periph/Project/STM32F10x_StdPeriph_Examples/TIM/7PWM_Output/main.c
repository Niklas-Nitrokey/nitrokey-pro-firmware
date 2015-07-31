/**
  ******************************************************************************
  * @file TIM/7PWM_Output/main.c 
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
    
/** @addtogroup TIM_7PWM_Output
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
    
        /* GPIO Configuration */ 
        GPIO_Configuration ();
    
        /* TIM1 Configuration ---------------------------------------------------
           SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
           High-density
           objective is to generate 7 PWM signal at 17.57 KHz:
           cycle is set to 50%
           channel 4 duty cycle is set to 12.5%
           ----------------------------------------------------------------------- */ 
        /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */ 
        TimerPeriod = (SystemCoreClock / 17570) - 1;
    
        /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */ 
        Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
    
        /* Compute CCR2 value to generate a duty cycle at 37.5% for channel 2 and 2N */ 
        Channel2Pulse = (uint16_t) (((uint32_t) 375 * (TimerPeriod - 1)) / 1000);
    
        /* Compute CCR3 value to generate a duty cycle at 25% for channel 3 and 3N */ 
        Channel3Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);
    
        /* Compute CCR4 value to generate a duty cycle at 12.5% for channel 4 */ 
        Channel4Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod - 1)) / 1000);
    
        /* Time Base configuration */ 
        TIM_TimeBaseStructure.TIM_Prescaler = 0;
    
    
    
    
    
    
        /* Channel 1, 2,3 and 4 Configuration in PWM mode */ 
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* TIM1 counter enable */ 
        TIM_Cmd (TIM1, ENABLE);
    
        /* TIM1 Main Output Enable */ 
        TIM_CtrlPWMOutputs (TIM1, ENABLE);
    
        
    {
    }



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* TIM1, GPIOA, GPIOB, GPIOE and AFIO clocks enable */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA |
                                RCC_APB2Periph_GPIOE | 


/**
  * @brief  Configure the TIM1 Pins.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
#ifdef STM32F10X_CL
        /* GPIOE Configuration: Channel 1/1N, 2/2N, 3/3N and 4 as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14 | 
    
    
    
    
        /* TIM1 Full remapping pins */ 
        GPIO_PinRemapConfig (GPIO_FullRemap_TIM1, ENABLE);
    
#else /* 
        /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    
    
    
    
        /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    
    
#endif /* 
} 

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