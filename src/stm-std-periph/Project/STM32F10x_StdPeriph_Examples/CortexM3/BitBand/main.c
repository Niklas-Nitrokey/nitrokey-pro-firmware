/**
  ******************************************************************************
  * @file    CortexM3/BitBand/main.c 
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
    
/** @addtogroup CortexM3_BitBand
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
#define RAM_BASE       0x20000000
#define RAM_BB_BASE    0x22000000
    
    /* Private macro ------------------------------------------------------------- */ 
#define  Var_ResetBit_BB(VarAddr, BitNumber)    \
    (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0) 
#define Var_SetBit_BB(VarAddr, BitNumber)       \
    (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1) 
#define Var_GetBit_BB(VarAddr, BitNumber)       \
    (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2))) 
    /* Private variables --------------------------------------------------------- */ 
    

    /* Private function prototypes ----------------------------------------------- */ 
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
        
    
        /* A mapping formula shows how to reference each word in the alias region to a 
           formula is:
           in the alias memory region that 
           the number of the byte in the bit-band region that contains 
        
        /* Get the variable address -------------------------------------------------- */ 
        VarAddr = (uint32_t) & Var;
    
        /* Modify variable bit using bit-band access --------------------------------- */ 
        /* Modify Var variable bit 0 ----------------------------------------------- */ 
        Var_ResetBit_BB (VarAddr, 0);   /* Var = 0x00005AA4 */
    
    
        /* Modify Var variable bit 11 ---------------------------------------------- */ 
        Var_ResetBit_BB (VarAddr, 11);  /* Var = 0x000052A5 */
    
        /* Get Var variable bit 11 value */ 
        VarBitValue = Var_GetBit_BB (VarAddr, 11);  /* VarBitValue = 0x00000000 */
    
    
        /* Get Var variable bit 11 value */ 
        VarBitValue = Var_GetBit_BB (VarAddr, 11);  /* VarBitValue = 0x00000001 */
    
        /* Modify Var variable bit 31 ---------------------------------------------- */ 
        Var_SetBit_BB (VarAddr, 31);    /* Var = 0x80005AA5 */
    
        /* Get Var variable bit 31 value */ 
        VarBitValue = Var_GetBit_BB (VarAddr, 31);  /* VarBitValue = 0x00000001 */
    
    
        /* Get Var variable bit 31 value */ 
        VarBitValue = Var_GetBit_BB (VarAddr, 31);  /* VarBitValue = 0x00000000 */
    
        
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