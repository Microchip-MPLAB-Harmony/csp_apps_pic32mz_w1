---
parent: Harmony 3 peripheral library application examples for PIC32MZ W1 family
title: GPIO interrupt 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# GPIO interrupt

This example application demonstrate how to generate GPIO interrupt on switch press and release, and indicate the switch status using the LED.

## Description

This application uses the GPIO Peripheral library to generate callback on switch press and release, and drives the GPIO pin connected to the LED to indicate the switch status. The LED is turned ON when the switch is pressed and turned OFF when the switch is released.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) and then click **Clone** button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/gpio/gpio_led_on_off_interrupt/firmware** .

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
2. The LED is turned ON when the switch is pressed and turned OFF when the switch is released

The following table provides the switch and the LED name:

| Board | Switch name | LED name |
| ----- | ----------- | -------- |
| PIC32MZ W1 Curiosity Board | SW1 | RED LED (D202) |
|||