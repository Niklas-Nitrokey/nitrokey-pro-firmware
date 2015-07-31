/**
  ******************************************************************************
  * @file    USART/IrDA/Transmit/main.c 
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
    
/** @addtogroup USART_IrDA_Transmit
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
    
#ifndef USE_STM3210C_EVAL
        /* Initialize JoyStick Button mounted on STM3210X-EVAL board */ 
        STM_EVAL_PBInit (BUTTON_UP, BUTTON_MODE_GPIO);
    
    
    
    
    
#else /* 
        /* Configure the IO Expander */ 
        if (IOE_Config ())
        
    {
        
            /* IO Expander config error */ 
            while (1);
    
    
#endif /* 
        
        /* USARTy configuration ------------------------------------------------------ */ 
        /* USARTy configured as follow:
           disabled (RTS and CTS signals)
        USART_InitStructure.USART_BaudRate = 115200;
    
    
    
    
    
    
        /* Configure the USARTy */ 
        USART_Init (USARTy, &USART_InitStructure);
    
        /* Enable the USARTy */ 
        USART_Cmd (USARTy, ENABLE);
    
        /* Set the USARTy prescaler */ 
        USART_SetPrescaler (USARTy, 0x1);
    
        /* Configure the USARTy IrDA mode */ 
        USART_IrDAConfig (USARTy, USART_IrDAMode_Normal);
    
        /* Enable the USARTy IrDA mode */ 
        USART_IrDACmd (USARTy, ENABLE);
    
        
    {
        
            /* Read Key */ 
            MyKey = ReadKey ();
        
            
        {
            
                
                
                    
                {
                
                
            
                
                
                    
                {
                
                
            
                
                
                    
                {
                
                
            
                
                
                    
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
        RCC_APB2PeriphClockCmd (USARTy_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
    
        /* Enable USARTy clocks */ 
        RCC_APB1PeriphClockCmd (USARTy_CLK, ENABLE);


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
#ifndef USE_STM3210C_EVAL
        /* Enable the USART3 Pins Partial Software Remapping */ 
        GPIO_PinRemapConfig (GPIO_PartialRemap_USART3, ENABLE);
    
#else /* 
        /* Enable the USART2 Pins Software Remapping */ 
        GPIO_PinRemapConfig (GPIO_Remap_USART2, ENABLE);
    
#endif /* 
        
        /* Configure USARTy Tx as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = USARTy_TxPin;
    
    
    
    
        /* Configure USARTy Rx as input floating */ 
        GPIO_InitStructure.GPIO_Pin = USARTy_RxPin;
    
    


/**
  * @brief  Reads key from demoboard.
  * @param  None
  * @retval Return JOY_RIGHT, JOY_LEFT, JOY_SEL, JOY_UP, JOY_DOWN or JOY_NONE
  */ 
    JOYState_TypeDef ReadKey (void) 
{
    
#ifndef USE_STM3210C_EVAL
        /* "right" key is pressed */ 
        if (!STM_EVAL_PBGetState (BUTTON_RIGHT))
        
    {
        
        
    
    
        /* "left" key is pressed */ 
        if (!STM_EVAL_PBGetState (BUTTON_LEFT))
        
    {
        
        
    
    
        /* "up" key is pressed */ 
        if (!STM_EVAL_PBGetState (BUTTON_UP))
        
    {
        
        
    
    
        /* "down" key is pressed */ 
        if (!STM_EVAL_PBGetState (BUTTON_DOWN))
        
    {
        
        
    
    
        /* "sel" key is pressed */ 
        if (!STM_EVAL_PBGetState (BUTTON_SEL))
        
    {
        
        
    
    
        /* No key is pressed */ 
        else
        
    {
        
    
    
#else /* 
        return IOE_JoyStickGetState ();
    
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