/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

enum
{
  IDLE_MODE = 'a',
  SLEEP_MODE = 'b',
  DEEP_SLEEP_MODE ='c',
}LOW_POWER_MODES;

uint8_t cmd = 0;

void timeout (uint32_t status, uintptr_t context)
{
    LED_Toggle();   
}

void display_menu (void)
{
    printf("\n\n\n\rSelect the low power mode to enter");
    printf("\n\ra) Idle Mode");
    printf("\n\rb) Sleep Mode"); 
    printf("\n\rc) Deep Sleep Mode");
    printf("\n\rEnter your choice");    
    scanf("%c", &cmd);
}
int main ( void )
{
    RCON_RESET_CAUSE resetCause;
    char typedChar[4];
    char savedChar[4]="init";
    
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    resetCause = RCON_ResetCauseGet();
    
    POWER_ReleaseGPIO();

    /* Check if RESET was after deep sleep wakeup */
    if (((resetCause & RCON_RESET_CAUSE_DPSLP) == RCON_RESET_CAUSE_DPSLP))
    {
        RCON_ResetCauseClear(RCON_RESET_CAUSE_DPSLP);
        
        /* Recollect the saved characters */
        savedChar[0]= POWER_DSGPR_Read(POWER_DSGPR0);
        savedChar[1]= POWER_DSGPR_Read(POWER_DSGPR1);
        savedChar[2]= POWER_DSGPR_Read(POWER_DSGPR2);
        savedChar[3]= POWER_DSGPR_Read(POWER_DSGPR3);

        printf("\r\n\r\nDevice woke up after deep sleep mode due to INT0 interrupt reset.\r\n");
        printf("Four letters which were typed before entering into deep sleep state are:\r\n");
        UART1_Write((uint8_t*)&savedChar[0],sizeof(savedChar));
    }
    
    printf("\n\n\r----------------------------------------------");
    printf("\n\r                 LOW power demo"               );
    printf("\n\r----------------------------------------------"); 
    
    TMR1_CallbackRegister(&timeout, (uintptr_t) NULL);
    TMR1_Start();
    /* INT0 interrupt is used to wake up from Deep Sleep */
    EVIC_ExternalInterruptEnable(EXTERNAL_INT_0);
    /* CN interrupt is used to wake up from Idle or Sleep mode */
    GPIO_PinInterruptEnable(CN_INT_PIN);
    
    display_menu();
    
    while(1)
    {
        switch(cmd)
        {
            case IDLE_MODE:
            {
                printf("\n\rEntering IDLE Mode");
                printf("\n\rPress Switch SW1 to wakeup the device");
                TMR1_Stop();
                POWER_LowPowerModeEnter(LOW_POWER_IDLE_MODE);
                printf("\n\rChange Notice Interrupt came, exiting IDLE mode......");
                TMR1_Start();
                display_menu();
                break;
            }
            case SLEEP_MODE:
            {
                printf("\n\rEntering SLEEP Mode");
                printf("\n\rPress Switch SW1 to wakeup the device         ");
                TMR1_Stop();
                POWER_LowPowerModeEnter(LOW_POWER_SLEEP_MODE);
                printf("\n\rChange Notice Interrupt came, exiting SLEEP mode......");
                TMR1_Start();
                display_menu();
                break;
            }
            case DEEP_SLEEP_MODE:
            {
                printf("\r\n\r\n#### Type four letters which you want to save in deep sleep state ####\r\n");
                UART1_Read(&typedChar[0], 4);

                /* Save the typed characters in DSGPR registers which will retain during deep sleep */
                POWER_DSGPR_Write(POWER_DSGPR0, typedChar[0]);
                POWER_DSGPR_Write(POWER_DSGPR1, typedChar[1]);
                POWER_DSGPR_Write(POWER_DSGPR2, typedChar[2]);
                POWER_DSGPR_Write(POWER_DSGPR3, typedChar[3]);

                printf("Letters which were typed are:\r\n");
                UART1_Write((uint8_t*)&typedChar[0],sizeof(typedChar));
                printf("\r\n#### Now entering deep sleep mode...\r\n");
                printf("\n\rPress Switch SW1 to wakeup the device         ");
               
                POWER_LowPowerModeEnter(LOW_POWER_DEEP_SLEEP_MODE);
                break;
            }
            default:
            {
                printf("\n\rInvalid choice");
                display_menu();
                break;
            }
        } 
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

