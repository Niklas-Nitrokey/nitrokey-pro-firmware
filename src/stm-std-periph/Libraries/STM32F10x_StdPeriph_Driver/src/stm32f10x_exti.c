/**
  ******************************************************************************
  * @file    stm32f10x_exti.c
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   This file provides all the EXTI firmware functions.
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
#include "stm32f10x_exti.h"
    
/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */ 
    
/** @defgroup EXTI 
  * @brief EXTI driver modules
  * @{
  */ 
    
/** @defgroup EXTI_Private_TypesDefinitions
  * @{
  */ 
    
/**
  * @}
  */ 
    
/** @defgroup EXTI_Private_Defines
  * @{
  */ 
    
#define EXTI_LineNone    ((uint32_t)0x00000)  /* No interrupt selected */
    
/**
  * @}
  */ 
    
/** @defgroup EXTI_Private_Macros
  * @{
  */ 
    
/**
  * @}
  */ 
    
/** @defgroup EXTI_Private_Variables
  * @{
  */ 
    
/**
  * @}
  */ 
    
/** @defgroup EXTI_Private_FunctionPrototypes
  * @{
  */ 
    
/**
  * @}
  */ 
    
/** @defgroup EXTI_Private_Functions
  * @{
  */ 
    
/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */ 
void EXTI_DeInit (void) 
{
    
    
    
    
    


/**
  * @brief  Initializes the EXTI peripheral according to the specified
  *   parameters in the EXTI_InitStruct.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
  *   that contains the configuration information for the EXTI peripheral.
  * @retval None
  */ 
void EXTI_Init (EXTI_InitTypeDef * EXTI_InitStruct) 
{
    
    
        /* Check the parameters */ 
        assert_param (IS_EXTI_MODE (EXTI_InitStruct->EXTI_Mode));
    
    
    
    
    
        
    {
        
            /* Clear EXTI line configuration */ 
            EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
        
        
        
        
            /* Clear Rising Falling edge configuration */ 
            EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
        
        
            /* Select the trigger for the selected external interrupts */ 
            if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
            
        {
            
                /* Rising Falling edge */ 
                EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
            
        
        
        else
            
        {
            
            
            
        
    
    
    else
        
    {
        
        
            /* Disable the selected external lines */ 
            *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
    



/**
  * @brief  Fills each EXTI_InitStruct member with its reset value.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
  *   be initialized.
  * @retval None
  */ 
void EXTI_StructInit (EXTI_InitTypeDef * EXTI_InitStruct) 
{
    
    
    
    


/**
  * @brief  Generates a Software interrupt.
  * @param  EXTI_Line: specifies the EXTI lines to be enabled or disabled.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
  * @retval None
  */ 
void EXTI_GenerateSWInterrupt (uint32_t EXTI_Line) 
{
    
        /* Check the parameters */ 
        assert_param (IS_EXTI_LINE (EXTI_Line));
    


/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  EXTI_Line: specifies the EXTI line flag to check.
  *   This parameter can be:
  *     @arg EXTI_Linex: External interrupt line x where x(0..19)
  * @retval The new state of EXTI_Line (SET or RESET).
  */ 
    FlagStatus EXTI_GetFlagStatus (uint32_t EXTI_Line) 
{
    
    
        /* Check the parameters */ 
        assert_param (IS_GET_EXTI_LINE (EXTI_Line));
    
        
    {
        
    
    
    else
        
    {
        
    
    



/**
  * @brief  Clears the EXTI�s line pending flags.
  * @param  EXTI_Line: specifies the EXTI lines flags to clear.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
  * @retval None
  */ 
void EXTI_ClearFlag (uint32_t EXTI_Line) 
{
    
        /* Check the parameters */ 
        assert_param (IS_EXTI_LINE (EXTI_Line));
    


/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  EXTI_Line: specifies the EXTI line to check.
  *   This parameter can be:
  *     @arg EXTI_Linex: External interrupt line x where x(0..19)
  * @retval The new state of EXTI_Line (SET or RESET).
  */ 
    ITStatus EXTI_GetITStatus (uint32_t EXTI_Line) 
{
    
    
    
        /* Check the parameters */ 
        assert_param (IS_GET_EXTI_LINE (EXTI_Line));
    
    
        
    {
        
    
    
    else
        
    {
        
    
    



/**
  * @brief  Clears the EXTI�s line pending bits.
  * @param  EXTI_Line: specifies the EXTI lines to clear.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
  * @retval None
  */ 
void EXTI_ClearITPendingBit (uint32_t EXTI_Line) 
{
    
        /* Check the parameters */ 
        assert_param (IS_EXTI_LINE (EXTI_Line));
    


/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 