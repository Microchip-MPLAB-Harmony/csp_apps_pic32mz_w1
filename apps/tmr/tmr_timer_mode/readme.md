[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# TMR periodic interrupt

This example demonstrates how to use the TMR module in timer mode to generate periodic interrupt.

## Description

The TMR module generates periodic interrupt on 1 second period match. The LED is toggled in the interrupt handler to indicate periodic callback. Two TMR modules are used to form a 32-bit timer.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) and click

![clone](../../../docs/images/clone.png)

Path of the application within the repository is **apps/tmr/tmr_timer_mode/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| pic32mz_w1_curiosity.X | MPLABX project for PIC32MZ W1 Curiosity Board |
|||

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| pic32mz_w1_curiosity.X | PIC32MZ W1 Curiosity Board |
|||

### Setting up PIC32MZ W1 Curiosity Board

- Connect the Debug USB port on the board to the computer using a micro USB cable

## Running the Application

1. Build and program the application project using its IDE
2. On successful execution, LED starts blinking

Following table provides the LED names:

| Board | LED name |
| ----- | -------- |
| PIC32MZ W1 Curiosity Board | RED LED (D202) |
|||