/**
  ******************************************************************************
  * @file    stm3210e_eval_fsmc_nand.c
  * @author  MCD Application Team
  * @version V4.2.0
  * @date    04/16/2010
  * @brief   This file provides a set of functions needed to drive the
  *          NAND512W3A2 memory mounted on STM3210E-EVAL board.
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
#include "stm3210e_eval_fsmc_nand.h"
    
/** @addtogroup Utilities
  * @{
  */ 
    
/** @addtogroup STM32_EVAL
  * @{
  */ 
    
/** @addtogroup STM3210E_EVAL
  * @{
  */ 
    
/** @addtogroup STM3210E_EVAL_FSMC_NAND
  * @brief      This file provides a set of functions needed to drive the
  *             NAND512W3A2 memory mounted on STM3210E-EVAL board.
  * @{
  */ 
    
/** @defgroup STM3210E_EVAL_FSMC_NAND_Private_Types
  * @{
  */ 
/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_FSMC_NAND_Private_Defines
  * @{
  */ 
/** 
  * @brief  FSMC Bank 2 
  */ 
#define FSMC_Bank_NAND     FSMC_Bank2_NAND
#define Bank_NAND_ADDR     Bank2_NAND_ADDR 
#define Bank2_NAND_ADDR    ((uint32_t)0x70000000)     
/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_FSMC_NAND_Private_Macros
  * @{
  */ 
#define ROW_ADDRESS (Address.Page + (Address.Block + (Address.Zone * NAND_ZONE_SIZE)) * NAND_BLOCK_SIZE)  
/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_FSMC_NAND_Private_Variables
  * @{
  */ 
/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_FSMC_NAND_Private_Function_Prototypes
  * @{
  */ 
/**
  * @}
  */ 
    
/** @defgroup STM3210E_EVAL_FSMC_NAND_Private_Functions
  * @{
  */ 
    
/**
  * @brief  Configures the FSMC and GPIOs to interface with the NAND memory.
  *         This function must be called before any write/read operation on the 
  *         NAND.
  * @param  None
  * @retval None
  */ 
void NAND_Init (void) 
{
    
    
    
    
    
/*-- GPIO Configuration ------------------------------------------------------*/ 
        /* !< CLE, ALE, D0->D3, NOE, NWE and NCE2 NAND pin configuration */ 
        GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15 | 
    
    
    
    
        /* !< D4->D7 NAND pin configuration */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    
    
        /* !< NWAIT NAND pin configuration */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    
    
    
    
        /* !< INT2 NAND pin configuration */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    
    
  /*-- FSMC Configuration ------------------------------------------------------*/ 
        p.FSMC_SetupTime = 0x1;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* !< FSMC NAND Bank Cmd Test */ 
        FSMC_NANDCmd (FSMC_Bank2_NAND, ENABLE);


/**
  * @brief  Reads NAND memory's ID.
  * @param  NAND_ID: pointer to a NAND_IDTypeDef structure which will hold
  *         the Manufacturer and Device ID.  
  * @retval None
  */ 
void NAND_ReadID (NAND_IDTypeDef * NAND_ID) 
{
    
    
        /* !< Send Command to the command area */ 
        *(__IO uint8_t *) (Bank_NAND_ADDR | CMD_AREA) = 0x90;
    
    
        /* !< Sequence to read ID from NAND flash */ 
        data = *(__IO uint32_t *) (Bank_NAND_ADDR | DATA_AREA);
    
    
    
    


/**
  * @brief  This routine is for writing one or several 512 Bytes Page size.
  * @param  pBuffer: pointer on the Buffer containing data to be written 
  * @param  Address: First page address
  * @param  NumPageToWrite: Number of page to write  
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate 
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation 
  *                And the new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address  
  */ 
    uint32_t NAND_WriteSmallPage (uint8_t * pBuffer, NAND_ADDRESS Address, uint32_t NumPageToWrite) 
{
    
    
    
        
    {
        
            /* !< Page write command and address */ 
            *(__IO uint8_t *) (Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_A;
        
        
        
        
        
        
            /* !< Calculate the size */ 
            size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpagewritten);
        
            /* !< Write data */ 
            for (; index < size; index++)
            
        {
            
        
        
        
            /* !< Check status for successful operation */ 
            status = NAND_GetStatus ();
        
            
        {
            
            
            
                /* !< Calculate Next small page Address */ 
                addressstatus = NAND_AddressIncrement (&Address);
        
    
    



/**
  * @brief  This routine is for sequential read from one or several 512 Bytes Page size.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  Address: First page address
  * @param  NumPageToRead: Number of page to read  
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate 
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation 
  *                And the new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address
  */ 
    uint32_t NAND_ReadSmallPage (uint8_t * pBuffer, NAND_ADDRESS Address, uint32_t NumPageToRead) 
{
    
    
    
        
    {
        
            /* !< Page Read command and page address */ 
            *(__IO uint8_t *) (Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_A;
        
        
        
        
        
        
            /* !< Calculate the size */ 
            size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpageread);
        
            /* !< Get Data into Buffer */ 
            for (; index < size; index++)
            
        {
            
        
        
        
        
            /* !< Calculate page address */ 
            addressstatus = NAND_AddressIncrement (&Address);
    
    
    



/**
  * @brief  This routine write the spare area information for the specified
  *         pages addresses.  
  * @param  pBuffer: pointer on the Buffer containing data to be written 
  * @param  Address: First page address
  * @param  NumSpareAreaTowrite: Number of Spare Area to write
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate 
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation 
  *                And the new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address
  */ 
    uint32_t NAND_WriteSpareArea (uint8_t * pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaTowrite) 
{
    
    
    
        
    {
        
            /* !< Page write Spare area command and address */ 
            *(__IO uint8_t *) (Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_C;
        
        
        
        
        
        
            /* !< Calculate the size */ 
            size = NAND_SPARE_AREA_SIZE + (NAND_SPARE_AREA_SIZE * numsparesreawritten);
        
            /* !< Write the data */ 
            for (; index < size; index++)
            
        {
            
        
        
        
            /* !< Check status for successful operation */ 
            status = NAND_GetStatus ();
        
            
        {
            
            
            
                /* !< Calculate Next page Address */ 
                addressstatus = NAND_AddressIncrement (&Address);
        
    
    



/**
  * @brief  This routine read the spare area information from the specified
  *         pages addresses.  
  * @param  pBuffer: pointer on the Buffer to fill 
  * @param  Address: First page address
  * @param  NumSpareAreaToRead: Number of Spare Area to read
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate 
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation 
  *                And the new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address
  */ 
    uint32_t NAND_ReadSpareArea (uint8_t * pBuffer, NAND_ADDRESS Address, uint32_t NumSpareAreaToRead) 
{
    
    
    
        
    {
        
            /* !< Page Read command and page address */ 
            *(__IO uint8_t *) (Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_C;
        
        
        
        
        
        
            /* !< Data Read */ 
            size = NAND_SPARE_AREA_SIZE + (NAND_SPARE_AREA_SIZE * numsparearearead);
        
            /* !< Get Data into Buffer */ 
            for (; index < size; index++)
            
        {
            
        
        
        
        
            /* !< Calculate page address */ 
            addressstatus = NAND_AddressIncrement (&Address);
    
    
    



/**
  * @brief  This routine erase complete block from NAND FLASH
  * @param  Address: Any address into block to be erased
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate 
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation 
  */ 
    uint32_t NAND_EraseBlock (NAND_ADDRESS Address) 
{
    
    
    
    
    
    



/**
  * @brief  This routine reset the NAND FLASH.
  * @param  None
  * @retval NAND_READY
  */ 
    uint32_t NAND_Reset (void) 
{
    
    



/**
  * @brief  Get the NAND operation status.
  * @param  None
  * @retval New status of the NAND operation. This parameter can be:
  *              - NAND_TIMEOUT_ERROR: when the previous operation generate
  *                a Timeout error
  *              - NAND_READY: when memory is ready for the next operation
  */ 
    uint32_t NAND_GetStatus (void) 
{
    
    
    
        /* !< Wait for a NAND operation to complete or a TIMEOUT to occur */ 
        while ((status != NAND_READY) && (timeout != 0x00))
        
    {
        
        
    
    
        
    {
        
    
    
        /* !< Return the operation status */ 
        return (status);



/**
  * @brief  Reads the NAND memory status using the Read status command. 
  * @param  None
  * @retval The status of the NAND memory. This parameter can be:
  *              - NAND_BUSY: when memory is busy
  *              - NAND_READY: when memory is ready for the next operation
  *              - NAND_ERROR: when the previous operation gererates error
  */ 
    uint32_t NAND_ReadStatus (void) 
{
    
    
        /* !< Read status operation ------------------------------------ */ 
        *(__IO uint8_t *) (Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_STATUS;
    
    
        
    {
        
    
    
    else if ((data & NAND_READY) == NAND_READY)
        
    {
        
    
    
    else
        
    {
        
    
    



/**
  * @brief  Increment the NAND memory address. 
  * @param  Address: address to be incremented.
  * @retval The new status of the increment address operation. It can be:
  *              - NAND_VALID_ADDRESS: When the new address is valid address
  *              - NAND_INVALID_ADDRESS: When the new address is invalid address   
  */ 
    uint32_t NAND_AddressIncrement (NAND_ADDRESS * Address) 
{
    
    
    
        
    {
        
        
        
            
        {
            
            
            
                
            {
                
            
        
    
    



/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
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