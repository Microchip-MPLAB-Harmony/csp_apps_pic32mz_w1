---
parent: Harmony 3 peripheral library application examples for PIC32MZ W1 family
title: SPI SST26 flash write read 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# SPI SST26 flash write read

This example demonstrates read and writing to SPI based SST26 flash

## Description

This example uses the SPI peripheral library to write an array of values to the SST26 Flash and verify the value written by reading the values back and comparing it to the value written. The example application performs the SST26 write only once after a power on reset.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) and click

![clone](../../../docs/images/clone.png)

Path of the application within the repository is **apps/spi/spi_sst26_write_read/firmware** .

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

1. Build and program the application project using its respective IDE
2. LED indicates the success or failure:
    - LED is turned ON when the value read from the Flash matched with the written value

Following table provides the LED name:

| Board | LED name |
| ----- | -------- |
| PIC32MZ W1 Curiosity Board | RED LED (D202) |
|||