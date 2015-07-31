/**
  ******************************************************************************
  * @file    BKP/Tamper/main.c 
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
#include "main.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup BKP_Tamper
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
#if defined USE_STM3210B_EVAL || defined USE_STM32100B_EVAL
#define BKP_DR_NUMBER              10   
#else /* 
#define BKP_DR_NUMBER              42
#endif  /* USE_STM3210B_EVAL or USE_STM32100B_EVAL */
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
#if defined USE_STM3210B_EVAL || defined USE_STM32100B_EVAL
    uint16_t BKPDataReg[BKP_DR_NUMBER] = 
{



#else /* 
    uint16_t BKPDataReg[BKP_DR_NUMBER] = 
{

        
        BKP_DR15, BKP_DR16, 
        BKP_DR21, BKP_DR22, BKP_DR23, BKP_DR24, 
        BKP_DR27, BKP_DR28, BKP_DR29, BKP_DR30, BKP_DR31, BKP_DR32,
        

#endif  /* USE_STM3210B_EVAL or USE_STM32100B_EVAL */
    
    /* Private function prototypes ----------------------------------------------- */ 
void GPIO_Configuration (void);







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
        
        /* NVIC configuration */ 
        NVIC_Configuration ();
    
        /* Initialize Leds mounted on STM3210X-EVAL board */ 
        STM_EVAL_LEDInit (LED1);
    
    
    
    
        /* Enable PWR and BKP clock */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    
        /* Enable write access to Backup domain */ 
        PWR_BackupAccessCmd (ENABLE);
    
        /* Disable Tamper pin */ 
        BKP_TamperPinCmd (DISABLE);
    
        /* Disable Tamper interrupt */ 
        BKP_ITConfig (DISABLE);
    
        /* Tamper pin active on low level */ 
        BKP_TamperPinLevelConfig (BKP_TamperPinLevel_Low);
    
        /* Clear Tamper pin Event(TE) pending flag */ 
        BKP_ClearFlag ();
    
        /* Enable Tamper interrupt */ 
        BKP_ITConfig (ENABLE);
    
        /* Enable Tamper pin */ 
        BKP_TamperPinCmd (ENABLE);
    
        /* Write data to Backup DRx registers */ 
        WriteToBackupReg (0xA53C);
    
        /* Check if the written data are correct */ 
        if (CheckBackupReg (0xA53C) == 0x00)
        
    {
        
            /* Turn on LED1 */ 
            STM_EVAL_LEDOn (LED1);
    
    
    else
        
    {
        
            /* Turn on LED2 */ 
            STM_EVAL_LEDOn (LED2);
    
    
        
    {
    



/**
  * @brief  Configures NVIC and Vector Table base location.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Enable TAMPER IRQChannel */ 
        NVIC_InitStructure.NVIC_IRQChannel = TAMPER_IRQn;
    
    
    
    


/**
  * @brief  Writes data Backup DRx registers.
  * @param  FirstBackupData: data to be written to Backup data registers.
  * @retval None
  */ 
void WriteToBackupReg (uint16_t FirstBackupData) 
{
    
    
        
    {
        
    



/**
  * @brief  Checks if the Backup DRx registers values are correct or not.
  * @param  FirstBackupData: data to be compared with Backup data registers.
  * @retval 
  *         - 0: All Backup DRx registers values are correct
  *         - Value different from 0: Number of the first Backup register
  *           which value is not correct
  */ 
    uint32_t CheckBackupReg (uint16_t FirstBackupData) 
{
    
    
        
    {
        
            
        {
            
        
    
    



/**
  * @brief  Checks if the Backup DRx registers are reset or not.
  * @param  None
  * @retval 
  *          - 0: All Backup DRx registers are reset
  *          - Value different from 0: Number of the first Backup register
  *            not reset
  */ 
    uint32_t IsBackupRegReset (void) 
{
    
    
        
    {
        
            
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