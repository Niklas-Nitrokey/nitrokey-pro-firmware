/**
  ******************************************************************************
  * @file    CAN/LoopBack/main.c 
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
#include "stm32_eval.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup CAN_LoopBack
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    __IO uint32_t ret = 0;  /* for return of the interrupt handling */



    /* Private function prototypes ----------------------------------------------- */ 
void NVIC_Configuration (void);






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
        
        /* CAN1 Periph clock enable */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_CAN1, ENABLE);
    
        /* NVIC Configuration */ 
        NVIC_Configuration ();
    
        /* Configures LED 1..4 */ 
        STM_EVAL_LEDInit (LED1);
    
    
    
    
        /* Turns selected LED Off */ 
        STM_EVAL_LEDOff (LED1);
    
    
    
    
        /* CAN transmit at 100Kb/s and receive by polling in loopback mode */ 
        TestRx = CAN_Polling ();
    
        
    {
        
            /* Turn on led LD3 */ 
            STM_EVAL_LEDOn (LED3);
    
    
    else
        
    {
        
            /* Turn on led LD1 */ 
            STM_EVAL_LEDOn (LED1);
    
    
        /* CAN transmit at 500Kb/s and receive by interrupt in loopback mode */ 
        TestRx = CAN_Interrupt ();
    
        
    {
        
            /* Turn on led LD4 */ 
            STM_EVAL_LEDOn (LED4);
    
    
    else
        
    {
        
            /* Turn on led LD2 */ 
            STM_EVAL_LEDOn (LED2);
    
    
        /* Infinite loop */ 
        while (1)
        
    {
    



/**
  * @brief  Configures the CAN, transmit and receive by polling
  * @param  None
  * @retval PASSED if the reception is well done, FAILED in other case
  */ 
    TestStatus CAN_Polling (void) 
{
    
    
    
    
    
    
    
        /* CAN register init */ 
        CAN_DeInit (CAN1);
    
    
        /* CAN cell init */ 
        CAN_InitStructure.CAN_TTCM = DISABLE;
    
    
    
    
    
    
    
    
    
    
    
    
        /* CAN filter init */ 
        CAN_FilterInitStructure.CAN_FilterNumber = 0;
    
    
    
    
    
    
    
    
    
    
        /* transmit */ 
        TxMessage.StdId = 0x11;
    
    
    
    
    
    
    
    
        
    {
        
    
    
    
        
    {
        
    
    
        /* receive */ 
        RxMessage.StdId = 0x00;
    
    
    
    
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    



/**
  * @brief  Configures the CAN, transmit and receive using interrupt.
  * @param  None
  * @retval PASSED if the reception is well done, FAILED in other case
  */ 
    TestStatus CAN_Interrupt (void) 
{
    
    
    
    
    
        /* CAN register init */ 
        CAN_DeInit (CAN1);
    
    
        /* CAN cell init */ 
        CAN_InitStructure.CAN_TTCM = DISABLE;
    
    
    
    
    
    
    
    
    
    
    
    
        /* CAN filter init */ 
        CAN_FilterInitStructure.CAN_FilterNumber = 1;
    
    
    
    
    
    
    
    
    
    
        /* CAN FIFO0 message pending interrupt enable */ 
        CAN_ITConfig (CAN1, CAN_IT_FMP0, ENABLE);
    
        /* transmit 1 message */ 
        TxMessage.StdId = 0x00;
    
    
    
    
    
    
    
    
        /* initialize the value that will be returned */ 
        ret = 0xFF;
    
        /* receive message with interrupt handling */ 
        i = 0;
    
        
    {
        
    
    
        
    {
        
    
    
        /* disable interrupt handling */ 
        CAN_ITConfig (CAN1, CAN_IT_FMP0, DISABLE);
    



/**
  * @brief  Configures the NVIC and Vector Table base address.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Enable CAN1 RX0 interrupt IRQ channel */ 
#ifndef STM32F10X_CL
        NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    
#else /* 
        NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    
#endif  /* STM32F10X_CL*/
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    
    
    


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