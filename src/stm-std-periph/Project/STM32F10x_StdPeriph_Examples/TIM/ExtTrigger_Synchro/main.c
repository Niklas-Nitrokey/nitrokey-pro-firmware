/**
  ******************************************************************************
  * @file TIM/ExtTrigger_Synchro/main.c 
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
    
/** @addtogroup TIM_ExtTrigger_Synchro
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
    
        /* Configure the GPIO ports */ 
        GPIO_Configuration ();
    
        /* Timers synchronisation in cascade mode with an external trigger -----
           TIM1 Enable event is used as Trigger Output 
           (TIM1 CH2 configured as input pin):
           Mode.
           used, so start and stop of slave counter
           is used as Trigger Output. 
           used, so start and stop of slave counter
           Medium-density, High-density and Connectivity line devices:
           counter is equal to 24 MHz.
           For Low-Density Value line and Medium-Density Value line devices:
           clock 
           counters are controlled by the 
           are controlled by the TIM3.  
        
        /* Time base configuration */ 
        TIM_TimeBaseStructure.TIM_Period = 73;
    
    
    
    
    
    
    
    
    
        /* Master Configuration in Toggle Mode */ 
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    
    
    
    
    
        /* TIM1 Input Capture Configuration */ 
        TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    
    
    
    
    
    
        /* TIM1 Input trigger configuration: External Trigger connected to TI2 */ 
        TIM_SelectInputTrigger (TIM1, TIM_TS_TI2FP2);
    
    
        /* Select the Master Slave Mode */ 
        TIM_SelectMasterSlaveMode (TIM1, TIM_MasterSlaveMode_Enable);
    
        /* Master Mode selection: TIM1 */ 
        TIM_SelectOutputTrigger (TIM1, TIM_TRGOSource_Enable);
    
        /* Slaves Configuration: Toggle Mode */ 
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    
    
    
    
        /* Slave Mode selection: TIM3 */ 
        TIM_SelectInputTrigger (TIM3, TIM_TS_ITR0);
    
    
        /* Select the Master Slave Mode */ 
        TIM_SelectMasterSlaveMode (TIM3, TIM_MasterSlaveMode_Enable);
    
        /* Master Mode selection: TIM3 */ 
        TIM_SelectOutputTrigger (TIM3, TIM_TRGOSource_Enable);
    
        /* Slave Mode selection: TIM4 */ 
        TIM_SelectInputTrigger (TIM4, TIM_TS_ITR2);
    
    
        /* TIM1 Main Output Enable */ 
        TIM_CtrlPWMOutputs (TIM1, ENABLE);
    
        /* TIM enable counter */ 
        TIM_Cmd (TIM1, ENABLE);
    
    
    
        
    {
    }



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* TIM1, TIM3 and TIM4 clock enable */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3 | 
    
        /* TIM1, GPIOA, GPIOE, GPIOC and GPIOB clocks enable */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA |
                                RCC_APB2Periph_GPIOB | 


/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
#ifdef STM32F10X_CL
        /* GPIOE Configuration: Channel 1 as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    
    
    
    
        /* GPIOE Configuration: Channel 2 as Input floating */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    
    
    
        /* TIM1 Full remapping pins */ 
        GPIO_PinRemapConfig (GPIO_FullRemap_TIM1, ENABLE);
    
        /* GPIOB Configuration: TIM3 channel1, 2, 3 and 4 */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    
    
    
    
    
        /* GPIOB Configuration: PB.06(TIM4 CH1) as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    
    
#else /* 
        /* GPIOA Configuration: PA.08(TIM1 CH1) and PA.06(TIM3 CH1) as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_6;
    
    
    
    
        /* GPIOB Configuration: PB.06(TIM4 CH1) as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    
    
        /* GPIOA Configuration: PA.09(TIM1 CH2) */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    
    
    
#endif /* 


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