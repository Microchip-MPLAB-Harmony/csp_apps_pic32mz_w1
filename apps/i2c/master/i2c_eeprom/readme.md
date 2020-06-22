[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# I2C EEPROM read write

This example application demonstrates how to use the I2C peripheral to write and read from the I2C serial EEPROM memory.

## Description

This example uses the I2C peripheral library to write an array of values to the I2C Serial EEPROM and verify the value written by reading the values back and comparing it to the value written.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) and click

![clone](../../../../docs/images/clone.png)

Path of the application within the repository is **apps/i2c/master/i2c_eeprom/firmware** .

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

- To run the application, following additional hardware are required:
  - [EEPROM 3 click board](https://www.mikroe.com/eeprom-3-click)

- Install an [EEPROM 3 click board](https://www.mikroe.com/eeprom-3-click) on to the mikroBUS socket (J200)
- Connect the Debug USB port on the board to the computer using a micro USB cable

## Running the Application

- Build and program the application using its IDE
-LED indicates the success or failure:
  - LED is turned ON when the value read from the EEPROM matched with the written value
  - LED is turned OFF when the value read from the EEPROM did not match with the written value

Following table provides LED names:

| Board | LED name |
| ----- | -------- |
| PIC32MZ W1 Curiosity Board | RED LED (D202) |
|||