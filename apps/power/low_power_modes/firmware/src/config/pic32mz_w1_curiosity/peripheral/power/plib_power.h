/*******************************************************************************
  Power PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_power.h

  Summary
    Power PLIB Header File.

  Description
    This file defines the interface to the DSCTRL peripheral library.
    This library provides access to and control of the associated Resets.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef PLIB_POWER_H      // Guards against multiple inclusion
#define PLIB_POWER_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdbool.h>
#include <stddef.h>
#include "device.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

typedef enum {

    LOW_POWER_IDLE_MODE,
    LOW_POWER_SLEEP_MODE,
    LOW_POWER_DEEP_SLEEP_MODE,
} POWER_LOW_POWER_MODE;

typedef enum
{
    POWER_DS_WAKEUP_SOURCE_ICD = _DSWAKE_ICD_MASK,

    POWER_DS_WAKEUP_SOURCE_MCLR = _DSWAKE_MCLR_MASK,

    POWER_DS_WAKEUP_SOURCE_RTCC = _DSWAKE_RTCC_MASK,

    POWER_DS_WAKEUP_SOURCE_DSWDT = _DSWAKE_DSWDT_MASK,

    POWER_DS_WAKEUP_SOURCE_EXT = _DSWAKE_EXT_MASK,

    POWER_DS_WAKEUP_SOURCE_FAULT = _DSWAKE_FAULT_MASK,

    POWER_DS_WAKEUP_SOURCE_INT0 = _DSWAKE_INT0_MASK,

} POWER_DS_WAKEUP_SOURCE;

typedef enum
{
    POWER_DS_EXTENDED_SEMAPHORE_1,
    POWER_DS_EXTENDED_SEMAPHORE_2,
    POWER_DS_EXTENDED_SEMAPHORE_3,
    POWER_DS_EXTENDED_SEMAPHORE_4,
    POWER_DS_EXTENDED_SEMAPHORE_5,
    POWER_DS_EXTENDED_SEMAPHORE_6,
    POWER_DS_EXTENDED_SEMAPHORE_7,
    POWER_DS_EXTENDED_SEMAPHORE_8,
    POWER_DS_EXTENDED_SEMAPHORE_9,
    POWER_DS_EXTENDED_SEMAPHORE_10,
    POWER_DS_EXTENDED_SEMAPHORE_11,
    POWER_DS_EXTENDED_SEMAPHORE_12,
    POWER_DS_EXTENDED_SEMAPHORE_13,
    POWER_DS_EXTENDED_SEMAPHORE_14,
    POWER_DS_EXTENDED_SEMAPHORE_15,
    POWER_DS_EXTENDED_SEMAPHORE_16,
    POWER_DS_EXTENDED_SEMAPHORE_17,
    POWER_DS_EXTENDED_SEMAPHORE_18,
    POWER_DS_EXTENDED_SEMAPHORE_19,
    POWER_DS_EXTENDED_SEMAPHORE_20,
    POWER_DS_EXTENDED_SEMAPHORE_21,
    POWER_DS_EXTENDED_SEMAPHORE_22,
    POWER_DS_EXTENDED_SEMAPHORE_23,
    POWER_DS_EXTENDED_SEMAPHORE_24,
    POWER_DS_EXTENDED_SEMAPHORE_25,
    POWER_DS_EXTENDED_SEMAPHORE_26,
    POWER_DS_EXTENDED_SEMAPHORE_27,
    POWER_DS_EXTENDED_SEMAPHORE_28,
    POWER_DS_EXTENDED_SEMAPHORE_29,
    POWER_DS_EXTENDED_SEMAPHORE_30,
    POWER_DS_EXTENDED_SEMAPHORE_31,
    POWER_DS_EXTENDED_SEMAPHORE_32,
} POWER_DS_EXTENDED_SEMAPHORE;
// *****************************************************************************
// *****************************************************************************
// Section: Interface
// *****************************************************************************
// *****************************************************************************

void POWER_LowPowerModeEnter( POWER_LOW_POWER_MODE mode );
void POWER_Initialize( void );
POWER_DS_WAKEUP_SOURCE POWER_DS_WakeupSourceGet( void );
void POWER_DS_SoftwareRestore(void);
void POWER_DS_WakeupSourceClear( POWER_DS_WAKEUP_SOURCE wakeupSource );
void POWER_DS_SemaphoreWrite(uint32_t sema1Value);
uint32_t POWER_DS_SemaphoreRead(void);
void POWER_DS_ExtendedSemaphoreWrite(POWER_DS_EXTENDED_SEMAPHORE xsema, uint32_t xsemaValue);
uint32_t POWER_DS_ExtendedSemaphoreRead(POWER_DS_EXTENDED_SEMAPHORE xsema);
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif /* PLIB_POWER_H */
