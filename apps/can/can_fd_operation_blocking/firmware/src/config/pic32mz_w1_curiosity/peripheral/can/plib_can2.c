/*******************************************************************************
  Controller Area Network (CAN) Peripheral Library Source File

  Company:
    Microchip Technology Inc.

  File Name:
    plib_can2.c

  Summary:
    CAN peripheral library interface.

  Description:
    This file defines the interface to the CAN peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
//DOM-IGNORE-END
// *****************************************************************************
// *****************************************************************************
// Header Includes
// *****************************************************************************
// *****************************************************************************
#include <sys/kmem.h>
#include "plib_can2.h"


// *****************************************************************************
// *****************************************************************************
// Global Data
// *****************************************************************************
// *****************************************************************************
/* CAN2 Message memory size */
#define CAN_MESSAGE_RAM_CONFIG_SIZE 224
/* Number of configured FIFO */
#define CAN_NUM_OF_FIFO             2
/* Maximum number of CAN Message buffers in each FIFO */
#define CAN_FIFO_MESSAGE_BUFFER_MAX 32

#define CAN_CONFIGURATION_MODE      0x4
#define CAN_OPERATION_MODE          0x0
#define CAN_NUM_OF_FILTER           1
/* FIFO Offset in word (4 bytes) */
#define CAN_FIFO_OFFSET             0x3
/* Filter Offset in word (4 bytes) */
#define CAN_FILTER_OFFSET           0x1
#define CAN_FILTER_OBJ_OFFSET       0x2
/* Acceptance Mask Offset in word (4 bytes) */
#define CAN_ACCEPTANCE_MASK_OFFSET  0x2
#define CAN_MSG_SID_MASK            0x7FF
#define CAN_MSG_EID_MASK            0x1FFFFFFF
#define CAN_MSG_DLC_MASK            0x0000000F
#define CAN_MSG_IDE_MASK            0x00000010
#define CAN_MSG_RTR_MASK            0x00000020
#define CAN_MSG_BRS_MASK            0x00000040
#define CAN_MSG_FDF_MASK            0x00000080
#define CAN_MSG_SEQ_MASK            0xFFFFFE00
#define CAN_MSG_TX_EXT_SID_MASK     0x1FFC0000
#define CAN_MSG_TX_EXT_EID_MASK     0x0003FFFF
#define CAN_MSG_RX_EXT_SID_MASK     0x000007FF
#define CAN_MSG_RX_EXT_EID_MASK     0x1FFFF800
#define CAN_MSG_FLT_EXT_SID_MASK    0x1FFC0000
#define CAN_MSG_FLT_EXT_EID_MASK    0x0003FFFF

static uint8_t __attribute__((coherent, aligned(16))) can_message_buffer[CAN_MESSAGE_RAM_CONFIG_SIZE];
static const uint8_t dlcToLength[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

/******************************************************************************
Local Functions
******************************************************************************/
static void CANLengthToDlcGet(uint8_t length, uint8_t *dlc)
{
    if (length <= 8)
    {
        *dlc = length;
    }
    else if (length <= 12)
    {
        *dlc = 0x9;
    }
    else if (length <= 16)
    {
        *dlc = 0xA;
    }
    else if (length <= 20)
    {
        *dlc = 0xB;
    }
    else if (length <= 24)
    {
        *dlc = 0xC;
    }
    else if (length <= 32)
    {
        *dlc = 0xD;
    }
    else if (length <= 48)
    {
        *dlc = 0xE;
    }
    else
    {
        *dlc = 0xF;
    }
}

// *****************************************************************************
// *****************************************************************************
// CAN2 PLib Interface Routines
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Function:
    void CAN2_Initialize(void)

   Summary:
    Initializes given instance of the CAN peripheral.

   Precondition:
    None.

   Parameters:
    None.

   Returns:
    None
*/
void CAN2_Initialize(void)
{
    /* Switch the CAN module ON */
    CFD2CON |= _CFD2CON_ON_MASK;

    /* Switch the CAN module to Configuration mode. Wait until the switch is complete */
    CFD2CON = (CFD2CON & ~_CFD2CON_REQOP_MASK) | ((CAN_CONFIGURATION_MODE << _CFD2CON_REQOP_POSITION) & _CFD2CON_REQOP_MASK);
    while(((CFD2CON & _CFD2CON_OPMOD_MASK) >> _CFD2CON_OPMOD_POSITION) != CAN_CONFIGURATION_MODE);

    /* Set the Data bitrate to 2000 Kbps */
    CFD2DBTCFG = ((1 << _CFD2DBTCFG_BRP_POSITION) & _CFD2DBTCFG_BRP_MASK)
               | ((16 << _CFD2DBTCFG_TSEG1_POSITION) & _CFD2DBTCFG_TSEG1_MASK)
               | ((6 << _CFD2DBTCFG_TSEG2_POSITION) & _CFD2DBTCFG_TSEG2_MASK)
               | ((6 << _CFD2DBTCFG_SJW_POSITION) & _CFD2DBTCFG_SJW_MASK);

    /* Set the Nominal bitrate to 500 Kbps */
    CFD2NBTCFG = ((9 << _CFD2NBTCFG_BRP_POSITION) & _CFD2NBTCFG_BRP_MASK)
               | ((13 << _CFD2NBTCFG_TSEG1_POSITION) & _CFD2NBTCFG_TSEG1_MASK)
               | ((4 << _CFD2NBTCFG_TSEG2_POSITION) & _CFD2NBTCFG_TSEG2_MASK)
               | ((4 << _CFD2NBTCFG_SJW_POSITION) & _CFD2NBTCFG_SJW_MASK);

    /* Set Message memory base address for all FIFOs/Queue */
    CFD2FIFOBA = (uint32_t)KVA_TO_PA(can_message_buffer);

    /* Tx Event FIFO Configuration */
    CFD2TEFCON = (((1 - 1) << _CFD2TEFCON_FSIZE_POSITION) & _CFD2TEFCON_FSIZE_MASK);
    CFD2CON |= _CFD2CON_STEF_MASK;

    /* Tx Queue Configuration */
    CFD2TXQCON = (((1 - 1) << _CFD2TXQCON_FSIZE_POSITION) & _CFD2TXQCON_FSIZE_MASK)
               | ((0x7 << _CFD2TXQCON_PLSIZE_POSITION) & _CFD2TXQCON_PLSIZE_MASK)
               | ((0x0 << _CFD2TXQCON_TXPRI_POSITION) & _CFD2TXQCON_TXPRI_MASK);
    CFD2CON |= _CFD2CON_TXQEN_MASK;


    /* Configure CAN FIFOs */
    CFD2FIFOCON1 = (((1 - 1) << _CFD2FIFOCON1_FSIZE_POSITION) & _CFD2FIFOCON1_FSIZE_MASK) | _CFD2FIFOCON1_TXEN_MASK | ((0x0 << _CFD2FIFOCON1_TXPRI_POSITION) & _CFD2FIFOCON1_TXPRI_MASK) | ((0x0 << _CFD2FIFOCON1_RTREN_POSITION) & _CFD2FIFOCON1_RTREN_MASK) | ((0x7 << _CFD2FIFOCON1_PLSIZE_POSITION) & _CFD2FIFOCON1_PLSIZE_MASK);
    CFD2FIFOCON2 = (((1 - 1) << _CFD2FIFOCON2_FSIZE_POSITION) & _CFD2FIFOCON2_FSIZE_MASK) | ((0x7 << _CFD2FIFOCON2_PLSIZE_POSITION) & _CFD2FIFOCON2_PLSIZE_MASK);

    /* Configure CAN Filters */
    /* Filter 0 configuration */
    CFD2FLTOBJ0 = (0 & CAN_MSG_SID_MASK);
    CFD2MASK0 = (0 & CAN_MSG_SID_MASK);
    CFD2FLTCON0 |= (((0x2 << _CFD2FLTCON0_F0BP_POSITION) & _CFD2FLTCON0_F0BP_MASK)| _CFD2FLTCON0_FLTEN0_MASK);

    /* Switch the CAN module to CAN_OPERATION_MODE. Wait until the switch is complete */
    CFD2CON = (CFD2CON & ~_CFD2CON_REQOP_MASK) | ((CAN_OPERATION_MODE << _CFD2CON_REQOP_POSITION) & _CFD2CON_REQOP_MASK);
    while(((CFD2CON & _CFD2CON_OPMOD_MASK) >> _CFD2CON_OPMOD_POSITION) != CAN_OPERATION_MODE);
}

// *****************************************************************************
/* Function:
    bool CAN2_MessageTransmit(uint32_t id, uint8_t length, uint8_t* data, uint8_t fifoQueueNum, CAN_MODE mode, CAN_MSG_TX_ATTRIBUTE msgAttr)

   Summary:
    Transmits a message into CAN bus.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    id           - 11-bit / 29-bit identifier (ID).
    length       - Length of data buffer in number of bytes.
    data         - Pointer to source data buffer
    fifoQueueNum - If fifoQueueNum is 0 then Transmit Queue otherwise FIFO
    mode         - CAN mode Classic CAN or CAN FD without BRS or CAN FD with BRS
    msgAttr      - Data frame or Remote frame to be transmitted

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool CAN2_MessageTransmit(uint32_t id, uint8_t length, uint8_t* data, uint8_t fifoQueueNum, CAN_MODE mode, CAN_MSG_TX_ATTRIBUTE msgAttr)
{
    CAN_TX_MSG_OBJECT *txMessage = NULL;
    static uint32_t sequence = 0;
    uint8_t count = 0;
    uint8_t dlc = 0;
    bool status = false;

    if (fifoQueueNum == 0)
    {
        if ((CFD2TXQSTA & _CFD2TXQSTA_TXQNIF_MASK) == _CFD2TXQSTA_TXQNIF_MASK)
        {
            txMessage = (CAN_TX_MSG_OBJECT *)PA_TO_KVA1(CFD2TXQUA);
            status = true;
        }
    }
    else if (fifoQueueNum <= CAN_NUM_OF_FIFO)
    {
        if ((*(volatile uint32_t *)(&CFD2FIFOSTA1 + ((fifoQueueNum - 1) * CAN_FIFO_OFFSET)) & _CFD2FIFOSTA1_TFNRFNIF_MASK) == _CFD2FIFOSTA1_TFNRFNIF_MASK)
        {
            txMessage = (CAN_TX_MSG_OBJECT *)PA_TO_KVA1(*(volatile uint32_t *)(&CFD2FIFOUA1 + ((fifoQueueNum - 1) * CAN_FIFO_OFFSET)));
            status = true;
        }
    }

    if (status)
    {
        /* Check the id whether it falls under SID or EID,
         * SID max limit is 0x7FF, so anything beyond that is EID */
        if (id > CAN_MSG_SID_MASK)
        {
            txMessage->t0 = (((id & CAN_MSG_TX_EXT_SID_MASK) >> 18) | ((id & CAN_MSG_TX_EXT_EID_MASK) << 11)) & CAN_MSG_EID_MASK;
            txMessage->t1 = CAN_MSG_IDE_MASK;
        }
        else
        {
            txMessage->t0 = id;
            txMessage->t1 = 0;
        }
        if (length > 64)
            length = 64;

        CANLengthToDlcGet(length, &dlc);

        txMessage->t1 |= (dlc & CAN_MSG_DLC_MASK);

        if(mode == CAN_MODE_FD_WITH_BRS)
        {
            txMessage->t1 |= CAN_MSG_FDF_MASK | CAN_MSG_BRS_MASK;
        }
        else if (mode == CAN_MODE_FD_WITHOUT_BRS)
        {
            txMessage->t1 |= CAN_MSG_FDF_MASK;
        }
        if (msgAttr == CAN_MSG_TX_REMOTE_FRAME)
        {
            txMessage->t1 |= CAN_MSG_RTR_MASK;
        }
        else
        {
            while(count < length)
            {
                txMessage->data[count++] = *data++;
            }
        }

        txMessage->t1 |= ((++sequence << 9) & CAN_MSG_SEQ_MASK);

        if (fifoQueueNum == 0)
        {
            /* Request the transmit */
            CFD2TXQCON |= _CFD2TXQCON_UINC_MASK;
            CFD2TXQCON |= _CFD2TXQCON_TXREQ_MASK;
        }
        else
        {
            /* Request the transmit */
            *(volatile uint32_t *)(&CFD2FIFOCON1 + ((fifoQueueNum - 1) * CAN_FIFO_OFFSET)) |= _CFD2FIFOCON1_UINC_MASK;
            *(volatile uint32_t *)(&CFD2FIFOCON1 + ((fifoQueueNum - 1) * CAN_FIFO_OFFSET)) |= _CFD2FIFOCON1_TXREQ_MASK;
        }
    }
    return status;
}

// *****************************************************************************
/* Function:
    bool CAN2_MessageReceive(uint32_t *id, uint8_t *length, uint8_t *data, uint32_t *timestamp, uint8_t fifoNum, CAN_MSG_RX_ATTRIBUTE *msgAttr)

   Summary:
    Receives a message from CAN bus.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    id          - Pointer to 11-bit / 29-bit identifier (ID) to be received.
    length      - Pointer to data length in number of bytes to be received.
    data        - Pointer to destination data buffer
    timestamp   - Pointer to Rx message timestamp, timestamp value is 0 if Timestamp is disabled in CFD2TSCON
    fifoNum     - FIFO number
    msgAttr     - Data frame or Remote frame to be received

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool CAN2_MessageReceive(uint32_t *id, uint8_t *length, uint8_t *data, uint32_t *timestamp, uint8_t fifoNum, CAN_MSG_RX_ATTRIBUTE *msgAttr)
{
    CAN_RX_MSG_OBJECT *rxMessage = NULL;
    uint8_t count = 0;
    bool status = false;

    if ((fifoNum > CAN_NUM_OF_FIFO) || (id == NULL))
    {
        return status;
    }

    /* Check if there is a message available in FIFO */
    if ((*(volatile uint32_t *)(&CFD2FIFOSTA1 + ((fifoNum - 1) * CAN_FIFO_OFFSET)) & _CFD2FIFOSTA1_TFNRFNIF_MASK) == _CFD2FIFOSTA1_TFNRFNIF_MASK)
    {
        /* Get a pointer to RX message buffer */
        rxMessage = (CAN_RX_MSG_OBJECT *)PA_TO_KVA1(*(volatile uint32_t *)(&CFD2FIFOUA1 + ((fifoNum - 1) * CAN_FIFO_OFFSET)));

        /* Check if it's a extended message type */
        if (rxMessage->r1 & CAN_MSG_IDE_MASK)
        {
            *id = (((rxMessage->r0 & CAN_MSG_RX_EXT_SID_MASK) << 18) | ((rxMessage->r0 & CAN_MSG_RX_EXT_EID_MASK) >> 11)) & CAN_MSG_EID_MASK;
        }
        else
        {
            *id = rxMessage->r0 & CAN_MSG_SID_MASK;
        }

        if ((rxMessage->r1 & CAN_MSG_RTR_MASK) && ((rxMessage->r1 & CAN_MSG_FDF_MASK) == 0))
        {
            *msgAttr = CAN_MSG_RX_REMOTE_FRAME;
        }
        else
        {
            *msgAttr = CAN_MSG_RX_DATA_FRAME;
        }

        *length = dlcToLength[(rxMessage->r1 & CAN_MSG_DLC_MASK)];

        if (timestamp != NULL)
        {
        }

        /* Copy the data into the payload */
        while (count < *length)
        {
            *data++ = rxMessage->data[count++];
        }

        /* Message processing is done, update the message buffer pointer. */
        *(volatile uint32_t *)(&CFD2FIFOCON1 + ((fifoNum - 1) * CAN_FIFO_OFFSET)) |= _CFD2FIFOCON1_UINC_MASK;

        /* Message is processed successfully, so return true */
        status = true;
    }

    return status;
}

// *****************************************************************************
/* Function:
    void CAN2_MessageAbort(uint8_t fifoQueueNum)

   Summary:
    Abort request for a Queue/FIFO.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    fifoQueueNum - If fifoQueueNum is 0 then Transmit Queue otherwise FIFO

   Returns:
    None.
*/
void CAN2_MessageAbort(uint8_t fifoQueueNum)
{
    if (fifoQueueNum == 0)
    {
        CFD2TXQCON &= ~_CFD2TXQCON_TXREQ_MASK;
    }
    else if (fifoQueueNum <= CAN_NUM_OF_FIFO)
    {
        *(volatile uint32_t *)(&CFD2FIFOCON1 + ((fifoQueueNum - 1) * CAN_FIFO_OFFSET)) &= ~_CFD2FIFOCON1_TXREQ_MASK;
    }
}

// *****************************************************************************
/* Function:
    void CAN2_MessageAcceptanceFilterSet(uint8_t filterNum, uint32_t id)

   Summary:
    Set Message acceptance filter configuration.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    filterNum - Filter number
    id        - 11-bit or 29-bit identifier

   Returns:
    None.
*/
void CAN2_MessageAcceptanceFilterSet(uint8_t filterNum, uint32_t id)
{
    uint32_t filterEnableBit = 0;
    uint8_t filterRegIndex = 0;

    if (filterNum < CAN_NUM_OF_FILTER)
    {
        filterRegIndex = filterNum >> 2;
        filterEnableBit = (filterNum % 4 == 0)? _CFD2FLTCON0_FLTEN0_MASK : 1 << ((((filterNum % 4) + 1) * 8) - 1);

        *(volatile uint32_t *)(&CFD2FLTCON0 + (filterRegIndex * CAN_FILTER_OFFSET)) &= ~filterEnableBit;

        if (id > CAN_MSG_SID_MASK)
        {
            *(volatile uint32_t *)(&CFD2FLTOBJ0 + (filterNum * CAN_FILTER_OBJ_OFFSET)) = ((((id & CAN_MSG_FLT_EXT_SID_MASK) >> 18) | ((id & CAN_MSG_FLT_EXT_EID_MASK) << 11)) & CAN_MSG_EID_MASK) | _CFD2FLTOBJ0_EXIDE_MASK;
        }
        else
        {
            *(volatile uint32_t *)(&CFD2FLTOBJ0 + (filterNum * CAN_FILTER_OBJ_OFFSET)) = id & CAN_MSG_SID_MASK;
        }
        *(volatile uint32_t *)(&CFD2FLTCON0 + (filterRegIndex * CAN_FILTER_OFFSET)) |= filterEnableBit;
    }
}

// *****************************************************************************
/* Function:
    uint32_t CAN2_MessageAcceptanceFilterGet(uint8_t filterNum)

   Summary:
    Get Message acceptance filter configuration.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    filterNum - Filter number

   Returns:
    Returns Message acceptance filter identifier
*/
uint32_t CAN2_MessageAcceptanceFilterGet(uint8_t filterNum)
{
    uint32_t id = 0;

    if (filterNum < CAN_NUM_OF_FILTER)
    {
        if (*(volatile uint32_t *)(&CFD2FLTOBJ0 + (filterNum * CAN_FILTER_OBJ_OFFSET)) & _CFD2FLTOBJ0_EXIDE_MASK)
        {
            id = (((*(volatile uint32_t *)(&CFD2FLTOBJ0 + (filterNum * CAN_FILTER_OBJ_OFFSET)) & CAN_MSG_RX_EXT_SID_MASK) << 18)
               | ((*(volatile uint32_t *)(&CFD2FLTOBJ0 + (filterNum * CAN_FILTER_OBJ_OFFSET)) & CAN_MSG_RX_EXT_EID_MASK) >> 11))
               & CAN_MSG_EID_MASK;
        }
        else
        {
            id = (*(volatile uint32_t *)(&CFD2FLTOBJ0 + (filterNum * CAN_FILTER_OBJ_OFFSET)) & CAN_MSG_SID_MASK);
        }
    }
    return id;
}

// *****************************************************************************
/* Function:
    void CAN2_MessageAcceptanceFilterMaskSet(uint8_t acceptanceFilterMaskNum, uint32_t id)

   Summary:
    Set Message acceptance filter mask configuration.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    acceptanceFilterMaskNum - Acceptance Filter Mask number
    id                      - 11-bit or 29-bit identifier

   Returns:
    None.
*/
void CAN2_MessageAcceptanceFilterMaskSet(uint8_t acceptanceFilterMaskNum, uint32_t id)
{
    /* Switch the CAN module to Configuration mode. Wait until the switch is complete */
    CFD2CON = (CFD2CON & ~_CFD2CON_REQOP_MASK) | ((CAN_CONFIGURATION_MODE << _CFD2CON_REQOP_POSITION) & _CFD2CON_REQOP_MASK);
    while(((CFD2CON & _CFD2CON_OPMOD_MASK) >> _CFD2CON_OPMOD_POSITION) != CAN_CONFIGURATION_MODE);

    if (id > CAN_MSG_SID_MASK)
    {
        *(volatile uint32_t *)(&CFD2MASK0 + (acceptanceFilterMaskNum * CAN_ACCEPTANCE_MASK_OFFSET)) = ((((id & CAN_MSG_FLT_EXT_SID_MASK) >> 18) | ((id & CAN_MSG_FLT_EXT_EID_MASK) << 11)) & CAN_MSG_EID_MASK) | _CFD2MASK0_MIDE_MASK;
    }
    else
    {
        *(volatile uint32_t *)(&CFD2MASK0 + (acceptanceFilterMaskNum * CAN_ACCEPTANCE_MASK_OFFSET)) = id & CAN_MSG_SID_MASK;
    }

    /* Switch the CAN module to CAN_OPERATION_MODE. Wait until the switch is complete */
    CFD2CON = (CFD2CON & ~_CFD2CON_REQOP_MASK) | ((CAN_OPERATION_MODE << _CFD2CON_REQOP_POSITION) & _CFD2CON_REQOP_MASK);
    while(((CFD2CON & _CFD2CON_OPMOD_MASK) >> _CFD2CON_OPMOD_POSITION) != CAN_OPERATION_MODE);
}

// *****************************************************************************
/* Function:
    uint32_t CAN2_MessageAcceptanceFilterMaskGet(uint8_t acceptanceFilterMaskNum)

   Summary:
    Get Message acceptance filter mask configuration.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    acceptanceFilterMaskNum - Acceptance Filter Mask number

   Returns:
    Returns Message acceptance filter mask.
*/
uint32_t CAN2_MessageAcceptanceFilterMaskGet(uint8_t acceptanceFilterMaskNum)
{
    uint32_t id = 0;

    if (*(volatile uint32_t *)(&CFD2MASK0 + (acceptanceFilterMaskNum * CAN_ACCEPTANCE_MASK_OFFSET)) & _CFD2MASK0_MIDE_MASK)
    {
        id = (((*(volatile uint32_t *)(&CFD2MASK0 + (acceptanceFilterMaskNum * CAN_ACCEPTANCE_MASK_OFFSET)) & CAN_MSG_RX_EXT_SID_MASK) << 18)
           | ((*(volatile uint32_t *)(&CFD2MASK0 + (acceptanceFilterMaskNum * CAN_ACCEPTANCE_MASK_OFFSET)) & CAN_MSG_RX_EXT_EID_MASK) >> 11))
           & CAN_MSG_EID_MASK;
    }
    else
    {
        id = (*(volatile uint32_t *)(&CFD2MASK0 + (acceptanceFilterMaskNum * CAN_ACCEPTANCE_MASK_OFFSET)) & CAN_MSG_SID_MASK);
    }
    return id;
}

// *****************************************************************************
/* Function:
    bool CAN2_TransmitEventFIFOElementGet(uint32_t *id, uint32_t *sequence, uint32_t *timestamp)

   Summary:
    Get the Transmit Event FIFO Element for the transmitted message.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    id          - Pointer to 11-bit / 29-bit identifier (ID) to be received.
    sequence    - Pointer to Tx message sequence number to be received
    timestamp   - Pointer to Tx message timestamp to be received, timestamp value is 0 if Timestamp is disabled in CFD2TSCON

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool CAN2_TransmitEventFIFOElementGet(uint32_t *id, uint32_t *sequence, uint32_t *timestamp)
{
    CAN_TX_EVENT_FIFO_ELEMENT *txEventFIFOElement = NULL;
    bool status = false;

    /* Check if there is a message available in Tx Event FIFO */
    if ((CFD2TEFSTA & _CFD2TEFSTA_TEFNEIF_MASK) == _CFD2TEFSTA_TEFNEIF_MASK)
    {
        /* Get a pointer to Tx Event FIFO Element */
        txEventFIFOElement = (CAN_TX_EVENT_FIFO_ELEMENT *)PA_TO_KVA1(CFD2TEFUA);

        /* Check if it's a extended message type */
        if (txEventFIFOElement->te1 & CAN_MSG_IDE_MASK)
        {
            *id = txEventFIFOElement->te0 & CAN_MSG_EID_MASK;
        }
        else
        {
            *id = txEventFIFOElement->te0 & CAN_MSG_SID_MASK;
        }

        *sequence = ((txEventFIFOElement->te1 & CAN_MSG_SEQ_MASK) >> 9);

        if (timestamp != NULL)
        {
        }

        /* Tx Event FIFO Element read done, update the Tx Event FIFO tail */
        CFD2TEFCON |= _CFD2TEFCON_UINC_MASK;

        /* Tx Event FIFO Element read successfully, so return true */
        status = true;
    }
    return status;
}

// *****************************************************************************
/* Function:
    CAN_ERROR CAN2_ErrorGet(void)

   Summary:
    Returns the error during transfer.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    None.

   Returns:
    Error during transfer.
*/
CAN_ERROR CAN2_ErrorGet(void)
{
    CAN_ERROR error = CAN_ERROR_NONE;
    uint32_t errorStatus = CFD2TREC;

    /* Check if error occurred */
    error = (CAN_ERROR)((errorStatus & _CFD2TREC_EWARN_MASK) |
                        (errorStatus & _CFD2TREC_RXWARN_MASK) |
                        (errorStatus & _CFD2TREC_TXWARN_MASK) |
                        (errorStatus & _CFD2TREC_RXBP_MASK) |
                        (errorStatus & _CFD2TREC_TXBP_MASK) |
                        (errorStatus & _CFD2TREC_TXBO_MASK));

    return error;
}

// *****************************************************************************
/* Function:
    void CAN2_ErrorCountGet(uint8_t *txErrorCount, uint8_t *rxErrorCount)

   Summary:
    Returns the transmit and receive error count during transfer.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    txErrorCount - Transmit Error Count to be received
    rxErrorCount - Receive Error Count to be received

   Returns:
    None.
*/
void CAN2_ErrorCountGet(uint8_t *txErrorCount, uint8_t *rxErrorCount)
{
    *txErrorCount = (uint8_t)((CFD2TREC & _CFD2TREC_TERRCNT_MASK) >> _CFD2TREC_TERRCNT_POSITION);
    *rxErrorCount = (uint8_t)(CFD2TREC & _CFD2TREC_RERRCNT_MASK);
}

// *****************************************************************************
/* Function:
    bool CAN2_InterruptGet(uint8_t fifoQueueNum, CAN_FIFO_INTERRUPT_FLAG_MASK fifoInterruptFlagMask)

   Summary:
    Returns the FIFO Interrupt status.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    fifoQueueNum          - FIFO number
    fifoInterruptFlagMask - FIFO interrupt flag mask

   Returns:
    true - Requested fifo interrupt is occurred.
    false - Requested fifo interrupt is not occurred.
*/
bool CAN2_InterruptGet(uint8_t fifoQueueNum, CAN_FIFO_INTERRUPT_FLAG_MASK fifoInterruptFlagMask)
{
    if (fifoQueueNum == 0)
    {
        return ((CFD2TXQSTA & fifoInterruptFlagMask) != 0x0);
    }
    else
    {
        return ((*(volatile uint32_t *)(&CFD2FIFOSTA1 + ((fifoQueueNum - 1) * CAN_FIFO_OFFSET)) & fifoInterruptFlagMask) != 0x0);
    }
}

// *****************************************************************************
/* Function:
    bool CAN2_TxFIFOQueueIsFull(uint8_t fifoQueueNum)

   Summary:
    Returns true if Tx FIFO/Queue is full otherwise false.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.

   Parameters:
    fifoQueueNum - FIFO/Queue number

   Returns:
    true  - Tx FIFO/Queue is full.
    false - Tx FIFO/Queue is not full.
*/
bool CAN2_TxFIFOQueueIsFull(uint8_t fifoQueueNum)
{
    if (fifoQueueNum == 0)
    {
        return ((CFD2TXQSTA & _CFD2TXQSTA_TXQNIF_MASK) != _CFD2TXQSTA_TXQNIF_MASK);
    }
    else
    {
        return ((*(volatile uint32_t *)(&CFD2FIFOSTA1 + ((fifoQueueNum - 1) * CAN_FIFO_OFFSET)) & _CFD2FIFOSTA1_TFNRFNIF_MASK) != _CFD2FIFOSTA1_TFNRFNIF_MASK);
    }
}

// *****************************************************************************
/* Function:
    bool CAN2_AutoRTRResponseSet(uint32_t id, uint8_t length, uint8_t* data, uint8_t fifoNum)

   Summary:
    Set the Auto RTR response for remote transmit request.

   Precondition:
    CAN2_Initialize must have been called for the associated CAN instance.
    Auto RTR Enable must be set to 0x1 for the requested Transmit FIFO in MHC configuration.

   Parameters:
    id           - 11-bit / 29-bit identifier (ID).
    length       - Length of data buffer in number of bytes.
    data         - Pointer to source data buffer
    fifoNum      - FIFO Number

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool CAN2_AutoRTRResponseSet(uint32_t id, uint8_t length, uint8_t* data, uint8_t fifoNum)
{
    CAN_TX_MSG_OBJECT *txMessage = NULL;
    uint8_t count = 0;
    bool status = false;

    if (fifoNum <= CAN_NUM_OF_FIFO)
    {
        if ((*(volatile uint32_t *)(&CFD2FIFOSTA1 + ((fifoNum - 1) * CAN_FIFO_OFFSET)) & _CFD2FIFOSTA1_TFNRFNIF_MASK) == _CFD2FIFOSTA1_TFNRFNIF_MASK)
        {
            txMessage = (CAN_TX_MSG_OBJECT *)PA_TO_KVA1(*(volatile uint32_t *)(&CFD2FIFOUA1 + ((fifoNum - 1) * CAN_FIFO_OFFSET)));
            status = true;
        }
    }

    if (status)
    {
        /* Check the id whether it falls under SID or EID,
         * SID max limit is 0x7FF, so anything beyond that is EID */
        if (id > CAN_MSG_SID_MASK)
        {
            txMessage->t0 = (((id & CAN_MSG_TX_EXT_SID_MASK) >> 18) | ((id & CAN_MSG_TX_EXT_EID_MASK) << 11)) & CAN_MSG_EID_MASK;
            txMessage->t1 = CAN_MSG_IDE_MASK;
        }
        else
        {
            txMessage->t0 = id;
            txMessage->t1 = 0;
        }

        /* Limit length */
        if (length > 8)
            length = 8;
        txMessage->t1 |= length;

        while(count < length)
        {
            txMessage->data[count++] = *data++;
        }

        /* Set UINC to respond to RTR */
        *(volatile uint32_t *)(&CFD2FIFOCON1 + ((fifoNum - 1) * CAN_FIFO_OFFSET)) |= _CFD2FIFOCON1_UINC_MASK;
    }
    return status;
}

