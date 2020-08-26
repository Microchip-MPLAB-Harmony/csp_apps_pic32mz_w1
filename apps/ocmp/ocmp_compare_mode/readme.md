---
parent: Harmony 3 peripheral library application examples for PIC32MZ W1 family
title: OCMP compare mode 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# OCMP compare mode

This example application shows how to use the OCMP peripheral to generate an active low, active high, and toggle output on compare match.

## Description

In this application, three OCMP modules are used to generate waveforms.

**Active Low Output**: By default output is set as high and it is set as low on the compare match

**Active High Output**: By default output is set as low and it is set as high on the compare match

**Toggled Output**: Compare match toggles the output

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) and then click **Clone** button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/ocmp/ocmp_compare_mode/firmware** .

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
2. Observe active low, active high and toggle output on the oscilloscope

    ![ouptut](images/output_ocmp_compare_mode.png)

3. Refer the following table for pin details:

    | OCMP output | PIC32MZ W1 Curiosity Board pins |
    | ---------- | ------------------ |
    |OC1 output | RB12 (Pin 7 of XPRO header) |
    |OC2 output | RK1 (Red LED) |
    |OC3 output | RA14 (Pin 4 of XPRO header) |
    |||
