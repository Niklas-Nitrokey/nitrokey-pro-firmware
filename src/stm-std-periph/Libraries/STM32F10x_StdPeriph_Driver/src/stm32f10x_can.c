/**
  ******************************************************************************
  * @file    stm32f10x_can.c
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   This file provides all the CAN firmware functions.
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
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"
    
/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */ 
    
/** @defgroup CAN 
  * @brief CAN driver modules
  * @{
  */ 
    
/** @defgroup CAN_Private_TypesDefinitions
  * @{
  */ 
    
/**
  * @}
  */ 
    
/** @defgroup CAN_Private_Defines
  * @{
  */ 
    
    /* CAN Master Control Register bits */ 
#define MCR_INRQ     ((uint32_t)0x00000001) /* Initialization request */
#define MCR_SLEEP    ((uint32_t)0x00000002) /* Sleep mode request */
#define MCR_TXFP     ((uint32_t)0x00000004) /* Transmit FIFO priority */
#define MCR_RFLM     ((uint32_t)0x00000008) /* Receive FIFO locked mode */
#define MCR_NART     ((uint32_t)0x00000010) /* No automatic retransmission */
#define MCR_AWUM     ((uint32_t)0x00000020) /* Automatic wake up mode */
#define MCR_ABOM     ((uint32_t)0x00000040) /* Automatic bus-off management */
#define MCR_TTCM     ((uint32_t)0x00000080) /* time triggered communication */
#define MCR_RESET    ((uint32_t)0x00008000) /* time triggered communication */
#define MCR_DBF      ((uint32_t)0x00010000) /* software master reset */
    
    /* CAN Master Status Register bits */ 
#define MSR_INAK     ((uint32_t)0x00000001)    /* Initialization acknowledge */
#define MSR_WKUI     ((uint32_t)0x00000008)    /* Wake-up interrupt */
#define MSR_SLAKI    ((uint32_t)0x00000010)    /* Sleep acknowledge interrupt */
    
    /* CAN Transmit Status Register bits */ 
#define TSR_RQCP0    ((uint32_t)0x00000001)    /* Request completed mailbox0 */
#define TSR_TXOK0    ((uint32_t)0x00000002)    /* Transmission OK of mailbox0 */
#define TSR_ABRQ0    ((uint32_t)0x00000080)    /* Abort request for mailbox0 */
#define TSR_RQCP1    ((uint32_t)0x00000100)    /* Request completed mailbox1 */
#define TSR_TXOK1    ((uint32_t)0x00000200)    /* Transmission OK of mailbox1 */
#define TSR_ABRQ1    ((uint32_t)0x00008000)    /* Abort request for mailbox1 */
#define TSR_RQCP2    ((uint32_t)0x00010000)    /* Request completed mailbox2 */
#define TSR_TXOK2    ((uint32_t)0x00020000)    /* Transmission OK of mailbox2 */
#define TSR_ABRQ2    ((uint32_t)0x00800000)    /* Abort request for mailbox2 */
#define TSR_TME0     ((uint32_t)0x04000000)    /* Transmit mailbox 0 empty */
#define TSR_TME1     ((uint32_t)0x08000000)    /* Transmit mailbox 1 empty */
#define TSR_TME2     ((uint32_t)0x10000000)    /* Transmit mailbox 2 empty */
    
    /* CAN Receive FIFO 0 Register bits */ 
#define RF0R_FULL0   ((uint32_t)0x00000008)    /* FIFO 0 full */
#define RF0R_FOVR0   ((uint32_t)0x00000010)    /* FIFO 0 overrun */
#define RF0R_RFOM0   ((uint32_t)0x00000020)    /* Release FIFO 0 output mailbox */
    
    /* CAN Receive FIFO 1 Register bits */ 
#define RF1R_FULL1   ((uint32_t)0x00000008)    /* FIFO 1 full */
#define RF1R_FOVR1   ((uint32_t)0x00000010)    /* FIFO 1 overrun */
#define RF1R_RFOM1   ((uint32_t)0x00000020)    /* Release FIFO 1 output mailbox */
    
    /* CAN Error Status Register bits */ 
#define ESR_EWGF     ((uint32_t)0x00000001)    /* Error warning flag */
#define ESR_EPVF     ((uint32_t)0x00000002)    /* Error passive flag */
#define ESR_BOFF     ((uint32_t)0x00000004)    /* Bus-off flag */
    
    /* CAN Mailbox Transmit Request */ 
#define TMIDxR_TXRQ  ((uint32_t)0x00000001) /* Transmit mailbox request */
    
    /* CAN Filter Master Register bits */ 
#define FMR_FINIT    ((uint32_t)0x00000001) /* Filter init mode */
    
    /* Time out for INAK bit */ 
#define INAK_TimeOut        ((uint32_t)0x0000FFFF)
    
    /* Time out for SLAK bit */ 
#define SLAK_TimeOut        ((uint32_t)0x0000FFFF)
    
/**
  * @}
  */ 
    
/** @defgroup CAN_Private_Macros
  * @{
  */ 
    
/**
  * @}
  */ 
    
/** @defgroup CAN_Private_Variables
  * @{
  */ 
    
/**
  * @}
  */ 
    
/** @defgroup CAN_Private_FunctionPrototypes
  * @{
  */ 



/**
  * @}
  */ 
    
/** @defgroup CAN_Private_Functions
  * @{
  */ 
    
/**
  * @brief  Deinitializes the CAN peripheral registers to their default reset values.
  * @param  CANx: where x can be 1 or 2 to select the CAN peripheral.
  * @retval None.
  */ 
void CAN_DeInit (CAN_TypeDef * CANx) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
        
    {
        
            /* Enable CAN1 reset state */ 
            RCC_APB1PeriphResetCmd (RCC_APB1Periph_CAN1, ENABLE);
        
            /* Release CAN1 from reset state */ 
            RCC_APB1PeriphResetCmd (RCC_APB1Periph_CAN1, DISABLE);
    
    
    else
        
    {
        
            /* Enable CAN2 reset state */ 
            RCC_APB1PeriphResetCmd (RCC_APB1Periph_CAN2, ENABLE);
        
            /* Release CAN2 from reset state */ 
            RCC_APB1PeriphResetCmd (RCC_APB1Periph_CAN2, DISABLE);
    



/**
  * @brief  Initializes the CAN peripheral according to the specified
  *   parameters in the CAN_InitStruct.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_InitStruct: pointer to a CAN_InitTypeDef structure that
  *   contains the configuration information for the CAN peripheral.
  * @retval Constant indicates initialization succeed which will be 
  *   CANINITFAILED or CANINITOK.
  */ 
    uint8_t CAN_Init (CAN_TypeDef * CANx, CAN_InitTypeDef * CAN_InitStruct) 
{
    
    
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
    
    
    
    
    
    
    
    
    
    
        /* exit from sleep mode */ 
        CANx->MCR &= ~MCR_SLEEP;
    
        /* Request initialisation */ 
        CANx->MCR |= MCR_INRQ;
    
        /* Wait the acknowledge */ 
        while (((CANx->MSR & MSR_INAK) != MSR_INAK) && (wait_ack != INAK_TimeOut))
        
    {
        
    
    
        /* ...and check acknowledged */ 
        if ((CANx->MSR & MSR_INAK) != MSR_INAK)
        
    {
        
    
    
    else
        
    {
        
            /* Set the time triggered communication mode */ 
            if (CAN_InitStruct->CAN_TTCM == ENABLE)
            
        {
            
        
        
        else
            
        {
            
        
        
            /* Set the automatic bus-off management */ 
            if (CAN_InitStruct->CAN_ABOM == ENABLE)
            
        {
            
        
        
        else
            
        {
            
        
        
            /* Set the automatic wake-up mode */ 
            if (CAN_InitStruct->CAN_AWUM == ENABLE)
            
        {
            
        
        
        else
            
        {
            
        
        
            /* Set the no automatic retransmission */ 
            if (CAN_InitStruct->CAN_NART == ENABLE)
            
        {
            
        
        
        else
            
        {
            
        
        
            /* Set the receive FIFO locked mode */ 
            if (CAN_InitStruct->CAN_RFLM == ENABLE)
            
        {
            
        
        
        else
            
        {
            
        
        
            /* Set the transmit FIFO priority */ 
            if (CAN_InitStruct->CAN_TXFP == ENABLE)
            
        {
            
        
        
        else
            
        {
            
        
        
            /* Set the bit timing register */ 
            CANx->BTR =
            (uint32_t) ((uint32_t) CAN_InitStruct->CAN_Mode << 30) |
            ((uint32_t) CAN_InitStruct->CAN_SJW << 24) | 
                                                           CAN_InitStruct->CAN_BS1
                                                           << 16) |
            ((uint32_t) CAN_InitStruct->CAN_BS2 << 20) | 
        
            /* Request leave initialisation */ 
            CANx->MCR &= ~MCR_INRQ;
        
            /* Wait the acknowledge */ 
            wait_ack = 0x00;
        
            
        {
            
        
        
            /* ...and check acknowledged */ 
            if ((CANx->MSR & MSR_INAK) == MSR_INAK)
            
        {
            
        
        
        else
            
        {
            
        
    
    
        /* At this step, return the status of initialization */ 
        return InitStatus;



/**
  * @brief  Initializes the CAN peripheral according to the specified
  *   parameters in the CAN_FilterInitStruct.
  * @param  CAN_FilterInitStruct: pointer to a CAN_FilterInitTypeDef
  *   structure that contains the configuration information.
  * @retval None.
  */ 
void CAN_FilterInit (CAN_FilterInitTypeDef * CAN_FilterInitStruct) 
{
    
    
        /* Check the parameters */ 
        assert_param (IS_CAN_FILTER_NUMBER (CAN_FilterInitStruct->CAN_FilterNumber));
    
    
    
    
    
    
        /* Initialisation mode for the filter */ 
        CAN1->FMR |= FMR_FINIT;
    
        /* Filter Deactivation */ 
        CAN1->FA1R &= ~(uint32_t) filter_number_bit_pos;
    
        /* Filter Scale */ 
        if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_16bit)
        
    {
        
            /* 16-bit scale for the filter */ 
            CAN1->FS1R &= ~(uint32_t) filter_number_bit_pos;
        
            /* First 16-bit identifier and First 16-bit mask */ 
            /* Or First 16-bit identifier and Second 16-bit identifier */ 
            CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 =
            
               CAN_FilterInitStruct->CAN_FilterMaskIdLow) << 16) | 
        
            /* Second 16-bit identifier and Second 16-bit mask */ 
            /* Or Third 16-bit identifier and Fourth 16-bit identifier */ 
            CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 =
            
               CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) | 
    
    
        
    {
        
            /* 32-bit scale for the filter */ 
            CAN1->FS1R |= filter_number_bit_pos;
        
            /* 32-bit identifier or First 32-bit identifier */ 
            CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 =
            
              << 16) | 
        
            /* 32-bit mask or Second 32-bit identifier */ 
            CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 =
            
               CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) | 
    
    
        /* Filter Mode */ 
        if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
        
    {
        
            /* Id/Mask mode for the filter */ 
            CAN1->FM1R &= ~(uint32_t) filter_number_bit_pos;
    
    
    else    /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
        
    {
        
            /* Identifier list mode for the filter */ 
            CAN1->FM1R |= (uint32_t) filter_number_bit_pos;
    
    
        /* Filter FIFO assignment */ 
        if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_FilterFIFO0)
        
    {
        
            /* FIFO 0 assignation for the filter */ 
            CAN1->FFA1R &= ~(uint32_t) filter_number_bit_pos;
    
    
        
    {
        
            /* FIFO 1 assignation for the filter */ 
            CAN1->FFA1R |= (uint32_t) filter_number_bit_pos;
    
    
        /* Filter activation */ 
        if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE)
        
    {
        
    
    
        /* Leave the initialisation mode for the filter */ 
        CAN1->FMR &= ~FMR_FINIT;



/**
  * @brief  Fills each CAN_InitStruct member with its default value.
  * @param  CAN_InitStruct: pointer to a CAN_InitTypeDef structure which
  *   will be initialized.
  * @retval None.
  */ 
void CAN_StructInit (CAN_InitTypeDef * CAN_InitStruct) 
{
    
        /* Reset CAN init structure parameters values */ 
        /* Initialize the time triggered communication mode */ 
        CAN_InitStruct->CAN_TTCM = DISABLE;
    
        /* Initialize the automatic bus-off management */ 
        CAN_InitStruct->CAN_ABOM = DISABLE;
    
        /* Initialize the automatic wake-up mode */ 
        CAN_InitStruct->CAN_AWUM = DISABLE;
    
        /* Initialize the no automatic retransmission */ 
        CAN_InitStruct->CAN_NART = DISABLE;
    
        /* Initialize the receive FIFO locked mode */ 
        CAN_InitStruct->CAN_RFLM = DISABLE;
    
        /* Initialize the transmit FIFO priority */ 
        CAN_InitStruct->CAN_TXFP = DISABLE;
    
        /* Initialize the CAN_Mode member */ 
        CAN_InitStruct->CAN_Mode = CAN_Mode_Normal;
    
        /* Initialize the CAN_SJW member */ 
        CAN_InitStruct->CAN_SJW = CAN_SJW_1tq;
    
        /* Initialize the CAN_BS1 member */ 
        CAN_InitStruct->CAN_BS1 = CAN_BS1_4tq;
    
        /* Initialize the CAN_BS2 member */ 
        CAN_InitStruct->CAN_BS2 = CAN_BS2_3tq;
    
        /* Initialize the CAN_Prescaler member */ 
        CAN_InitStruct->CAN_Prescaler = 1;


/**
  * @brief  Select the start bank filter for slave CAN.
  * @note   This function applies only to STM32 Connectivity line devices.
  * @param  CAN_BankNumber: Select the start slave bank filter from 1..27.
  * @retval None.
  */ 
void CAN_SlaveStartBank (uint8_t CAN_BankNumber) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_BANKNUMBER (CAN_BankNumber));
    
        /* enter Initialisation mode for the filter */ 
        CAN1->FMR |= FMR_FINIT;
    
        /* Select the start slave bank */ 
        CAN1->FMR &= (uint32_t) 0xFFFFC0F1;
    
    
        /* Leave Initialisation mode for the filter */ 
        CAN1->FMR &= ~FMR_FINIT;


/**
  * @brief  Enables or disables the specified CAN interrupts.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_IT: specifies the CAN interrupt sources to be enabled or disabled.
  *   This parameter can be: CAN_IT_TME, CAN_IT_FMP0, CAN_IT_FF0,
  *   CAN_IT_FOV0, CAN_IT_FMP1, CAN_IT_FF1,
  *   CAN_IT_FOV1, CAN_IT_EWG, CAN_IT_EPV,
  *   CAN_IT_LEC, CAN_IT_ERR, CAN_IT_WKU or
  *   CAN_IT_SLK.
  * @param  NewState: new state of the CAN interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */ 
void CAN_ITConfig (CAN_TypeDef * CANx, uint32_t CAN_IT, FunctionalState NewState) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
    
        
    {
        
            /* Enable the selected CAN interrupt */ 
            CANx->IER |= CAN_IT;
    
    
    else
        
    {
        
            /* Disable the selected CAN interrupt */ 
            CANx->IER &= ~CAN_IT;
    



/**
  * @brief  Initiates the transmission of a message.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  TxMessage: pointer to a structure which contains CAN Id, CAN
  *   DLC and CAN datas.
  * @retval The number of the mailbox that is used for transmission
  *   or CAN_NO_MB if there is no empty mailbox.
  */ 
    uint8_t CAN_Transmit (CAN_TypeDef * CANx, CanTxMsg * TxMessage) 
{
    
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
    
    
        /* Select one empty transmit mailbox */ 
        if ((CANx->TSR & TSR_TME0) == TSR_TME0)
        
    {
        
    
    
    else if ((CANx->TSR & TSR_TME1) == TSR_TME1)
        
    {
        
    
    
    else if ((CANx->TSR & TSR_TME2) == TSR_TME2)
        
    {
        
    
    
    else
        
    {
        
    
    
        
    {
        
            /* Set up the Id */ 
            CANx->sTxMailBox[transmit_mailbox].TIR &= TMIDxR_TXRQ;
        
            
        {
            
            
        
        
        else
            
        {
            
            
        
        
            /* Set up the DLC */ 
            TxMessage->DLC &= (uint8_t) 0x0000000F;
        
        
        
            /* Set up the data field */ 
            CANx->sTxMailBox[transmit_mailbox].TDLR =
            (((uint32_t) TxMessage->Data[3] << 24) | 
             
        
            (((uint32_t) TxMessage->Data[7] << 24) | 
             
        
            /* Request transmission */ 
            CANx->sTxMailBox[transmit_mailbox].TIR |= TMIDxR_TXRQ;
    
    



/**
  * @brief  Checks the transmission of a message.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  TransmitMailbox: the number of the mailbox that is used for transmission.
  * @retval CANTXOK if the CAN driver transmits the message, CANTXFAILED in an other case.
  */ 
    uint8_t CAN_TransmitStatus (CAN_TypeDef * CANx, uint8_t TransmitMailbox) 
{
    
        /* RQCP, TXOK and TME bits */ 
        uint8_t state = 0;
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        
    {
        
            state |= (uint8_t) ((CANx->TSR & TSR_RQCP0) << 2);
            
            
            
        
            state |= (uint8_t) ((CANx->TSR & TSR_RQCP1) >> 6);
            
            
            
        
            state |= (uint8_t) ((CANx->TSR & TSR_RQCP2) >> 14);
            
            
            
        
            
            
    
    
        
    {
            
                /* transmit pending */ 
        case (0x0):
            state = CANTXPENDING;
            
            
                /* transmit failed */ 
        case (0x5):
            state = CANTXFAILED;
            
            
                /* transmit succedeed */ 
        case (0x7):
            state = CANTXOK;
            
        
            
            
    
    



/**
  * @brief  Cancels a transmit request.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral. 
  * @param  Mailbox: Mailbox number.
  * @retval None.
  */ 
void CAN_CancelTransmit (CAN_TypeDef * CANx, uint8_t Mailbox) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        /* abort transmission */ 
        switch (Mailbox)
        
    {
        
            CANx->TSR |= TSR_ABRQ0;
            
        
            CANx->TSR |= TSR_ABRQ1;
            
        
            CANx->TSR |= TSR_ABRQ2;
            
        
            
    



/**
  * @brief  Releases a FIFO.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral. 
  * @param  FIFONumber: FIFO to release, CAN_FIFO0 or CAN_FIFO1.
  * @retval None.
  */ 
void CAN_FIFORelease (CAN_TypeDef * CANx, uint8_t FIFONumber) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        /* Release FIFO0 */ 
        if (FIFONumber == CAN_FIFO0)
        
    {
        
    
    
        /* Release FIFO1 */ 
        else    /* FIFONumber == CAN_FIFO1 */
        
    {
        
    



/**
  * @brief  Returns the number of pending messages.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @retval NbMessage which is the number of pending message.
  */ 
    uint8_t CAN_MessagePending (CAN_TypeDef * CANx, uint8_t FIFONumber) 
{
    
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        
    {
        
    
    
    else if (FIFONumber == CAN_FIFO1)
        
    {
        
    
    
    else
        
    {
        
    
    



/**
  * @brief  Receives a message.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @param  RxMessage: pointer to a structure receive message which 
  *   contains CAN Id, CAN DLC, CAN datas and FMI number.
  * @retval None.
  */ 
void CAN_Receive (CAN_TypeDef * CANx, uint8_t FIFONumber, CanRxMsg * RxMessage) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        /* Get the Id */ 
        RxMessage->IDE = (uint8_t) 0x04 & CANx->sFIFOMailBox[FIFONumber].RIR;
    
        
    {
        
    
    
    else
        
    {
        
    
    
    
        /* Get the DLC */ 
        RxMessage->DLC = (uint8_t) 0x0F & CANx->sFIFOMailBox[FIFONumber].RDTR;
    
        /* Get the FMI */ 
        RxMessage->FMI = (uint8_t) 0xFF & (CANx->sFIFOMailBox[FIFONumber].RDTR >> 8);
    
        /* Get the data field */ 
        RxMessage->Data[0] = (uint8_t) 0xFF & CANx->sFIFOMailBox[FIFONumber].RDLR;
    
    
    
    
    
    
    
    
        /* Release the FIFO */ 
        CAN_FIFORelease (CANx, FIFONumber);



/**
  * @brief  Enables or disables the DBG Freeze for CAN.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  NewState: new state of the CAN peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */ 
void CAN_DBGFreeze (CAN_TypeDef * CANx, FunctionalState NewState) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        
    {
        
            /* Enable Debug Freeze */ 
            CANx->MCR |= MCR_DBF;
    
    
    else
        
    {
        
            /* Disable Debug Freeze */ 
            CANx->MCR &= ~MCR_DBF;
    



/**
  * @brief  Enters the low power mode.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @retval CANSLEEPOK if sleep entered, CANSLEEPFAILED in an other case.
  */ 
    uint8_t CAN_Sleep (CAN_TypeDef * CANx) 
{
    
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
        /* Request Sleep mode */ 
        CANx->MCR = (((CANx->MCR) & (uint32_t) (~MCR_INRQ)) | MCR_SLEEP);
    
        /* Sleep mode status */ 
        if ((CANx->MSR & (CAN_MSR_SLAK | CAN_MSR_INAK)) == CAN_MSR_SLAK)
        
    {
        
            /* Sleep mode not entered */ 
            sleepstatus = CANSLEEPOK;
    
    
        /* At this step, sleep mode status */ 
        return (uint8_t) sleepstatus;



/**
  * @brief  Wakes the CAN up.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @retval CANWAKEUPOK if sleep mode left, CANWAKEUPFAILED in an other case.
  */ 
    uint8_t CAN_WakeUp (CAN_TypeDef * CANx) 
{
    
    
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
        /* Wake up request */ 
        CANx->MCR &= ~MCR_SLEEP;
    
        /* Sleep mode status */ 
        while (((CANx->MSR & CAN_MSR_SLAK) == CAN_MSR_SLAK) && (wait_slak != 0x00))
        
    {
        
    
    
        
    {
        
            /* Sleep mode exited */ 
            wakeupstatus = CANWAKEUPOK;
    
    
        /* At this step, sleep mode status */ 
        return (uint8_t) wakeupstatus;



/**
  * @brief  Checks whether the specified CAN flag is set or not.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_FLAG: specifies the flag to check.
  *   This parameter can be: CAN_FLAG_EWG, CAN_FLAG_EPV or CAN_FLAG_BOF.
  * @retval The new state of CAN_FLAG (SET or RESET).
  */ 
    FlagStatus CAN_GetFlagStatus (CAN_TypeDef * CANx, uint32_t CAN_FLAG) 
{
    
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        /* Check the status of the specified CAN flag */ 
        if ((CANx->ESR & CAN_FLAG) != (uint32_t) RESET)
        
    {
        
            /* CAN_FLAG is set */ 
            bitstatus = SET;
    
    
    else
        
    {
        
            /* CAN_FLAG is reset */ 
            bitstatus = RESET;
    
    
        /* Return the CAN_FLAG status */ 
        return bitstatus;



/**
  * @brief  Clears the CAN's pending flags.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_FLAG: specifies the flag to clear.
  * @retval None.
  */ 
void CAN_ClearFlag (CAN_TypeDef * CANx, uint32_t CAN_FLAG) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        /* Clear the selected CAN flags */ 
        CANx->ESR &= ~CAN_FLAG;


/**
  * @brief  Checks whether the specified CAN interrupt has occurred or not.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_IT: specifies the CAN interrupt source to check.
  *   This parameter can be: CAN_IT_RQCP0, CAN_IT_RQCP1, CAN_IT_RQCP2,
  *   CAN_IT_FF0, CAN_IT_FOV0, CAN_IT_FF1,
  *   CAN_IT_FOV1, CAN_IT_EWG, CAN_IT_EPV, 
  *   CAN_IT_BOF, CAN_IT_WKU or CAN_IT_SLK.
  * @retval The new state of CAN_IT (SET or RESET).
  */ 
    ITStatus CAN_GetITStatus (CAN_TypeDef * CANx, uint32_t CAN_IT) 
{
    
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        
    {
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
    
    
        /* Return the CAN_IT status */ 
        return pendingbitstatus;



/**
  * @brief  Clears the CAN�s interrupt pending bits.
  * @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
  * @param  CAN_IT: specifies the interrupt pending bit to clear.
  * @retval None.
  */ 
void CAN_ClearITPendingBit (CAN_TypeDef * CANx, uint32_t CAN_IT) 
{
    
        /* Check the parameters */ 
        assert_param (IS_CAN_ALL_PERIPH (CANx));
    
    
        
    {
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
            
    



/**
  * @brief  Checks whether the CAN interrupt has occurred or not.
  * @param  CAN_Reg: specifies the CAN interrupt register to check.
  * @param  It_Bit: specifies the interrupt source bit to check.
  * @retval The new state of the CAN Interrupt (SET or RESET).
  */ 
static ITStatus CheckITStatus (uint32_t CAN_Reg, uint32_t It_Bit) 
{
    
    
        
    {
        
            /* CAN_IT is set */ 
            pendingbitstatus = SET;
    
    
    else
        
    {
        
            /* CAN_IT is reset */ 
            pendingbitstatus = RESET;
    
    



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