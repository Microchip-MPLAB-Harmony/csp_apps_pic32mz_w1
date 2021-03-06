---
parent: Harmony 3 peripheral library application examples for PIC32MZ W1 family
title: SPI slave write read 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# SPI slave write read

This example application demonstrates how to use the SPI peripheral in slave mode

## Description

This example uses the SPI peripheral library in slave mode and allows reading and writing data from/to its internal buffer by a SPI master. 

The SPI master writes data by sending a write command followed by two bytes of memory address followed by the data to be written.

< WR_CMD > < ADDR_MSB > < ADDR_LSB > < DATA0 > ... < DATA n >

The SPI slave asserts the Busy line to indicate to the SPI master that it is busy. Once ready, the SPI slave de-asserts the Busy line. Once the SPI slave is ready, the SPI master reads the data by sending read command followed by two bytes of memory address and the number of bytes to read.

< RD_CMD > < ADDR_MSB > < ADDR_LSB > < NUM_BYTES >

The SPI slave responds by sending the data at the requested memory address. The SPI master compares the sent data with the received data and repeats the test if it matches.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) and then click **Clone** button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/spi/slave/spi_write_read/firmware** .

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

- To run this demo two PIC32MZ W1 Curiosity Boards are required. One will be progammed as SPI master and other will be programmed as SPI slave.
- Connect Pin 15, 16, 17, 18 on XPRO Header of SPI slave to Pin 15, 17, 16, 18 respectively on XPRO Header of SPI master 
    - Pin 15 - SPI Chip Select
    - Pin 16 - SDO
    - Pin 17 - SDI
    - Pin 18 - SCK
- Connect Pin 5 on XPRO Header of SPI slave to Pin 5 on XPRO Header of SPI master. Pin 5 is configured as GPIO and serves as the slave busy pin.
- Connect the Debug USB port on the board to the computer using a micro USB cable

## Running the Application

1. Build and Program the SPI master application project using its IDE. Path of the SPI master application within the repository is **apps/spi/master/spi_write_read_test_app**.
2. Build and Program the SPI slave application project using its IDE
3. On the SPI master board, press switch to start reading and writing data
2. LED on SPI master board indicates the success or failure:
    - LED is turned ON when the data read from the SPI slave matches with the data written
    - LED is turned OFF when the data read from the SPI slave does not match with the data written

Following table provides the Switch and LED name:

| Board | Switch name | LED name |
| ----- | ----------- | -------- |
| PIC32MZ W1 Curiosity Board | SW1 | RED LED (D202) |
|||