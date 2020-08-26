---
parent: Harmony 3 peripheral library application examples for PIC32MZ W1 family
title: NVM flash read write 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# NVM flash read write

This example application demonstrates how to use the NVM to erase and program the internal Flash memory.

## Description

This example uses the NVM peripheral library to erase a page and write an array of values to the internal Flash memory. It verifies the value written by reading the values back and comparing it to the value written.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) and then click **Clone** button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/nvm/flash_read_write/firmware** .

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
