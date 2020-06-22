[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# CAN interrupt

This example application shows how to use the CAN module to transmit and receive normal CAN messages in interrupt mode.

## Description

This application transmits CAN message to CAN Bus and receives CAN message from CAN Bus. To run this application, an evaluation board and [Microchip CAN Bus Analyzer](http://www.microchip.com/Developmenttools/ProductDetails/APGDT002) is required . They act as different nodes on the CAN bus. While running the application, user can send and receive CAN messages between the board and the analyzer.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) and click

![clone](../../../docs/images/clone.png)

Path of the application within the repository is **apps/can/can_normal_operation_interrupt_timestamp/firmware** .

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

- To run the demo, the following additional hardware are required:
  - [Microchip CAN Bus Analyzer](http://www.microchip.com/Developmenttools/ProductDetails/APGDT002)
  - [ATA6563 click board](https://www.mikroe.com/ata6563-click)
  - [USB UART click board](https://www.mikroe.com/usb-uart-click)

- Install [Microchip CAN Bus Analyzer](http://www.microchip.com/Developmenttools/ProductDetails/APGDT002) software on PC
- Connect [Microchip CAN Bus Analyzer](http://www.microchip.com/Developmenttools/ProductDetails/APGDT002) to [ATA6563 click board](https://www.mikroe.com/ata6563-click) using female to female DB9 serial cable
- Connect [ATA6563 click board](https://www.mikroe.com/ata6563-click) to the PIC32MZ W1 Curiosity Board as per the Pin connections shown below

    | PIC32MZ W1 Curiosity Board | ATA6563 click board  |
    | -------------------------- | -------------------- |
    | PWM(RPB12), mikroBUS Connector | RX (PIN 14)  |
    | AN(RPA14), mikroBUS Connector  | TX (PIN 13)  |
    | +3.3V, mikroBUS Connector | 3V3 (PIN 7)  |
    | +5V, mikroBUS Connector   | 5V (PIN 10) |
    | GND, mikroBUS Connector   | GND (PIN 9)  |

- Connect [Microchip CAN Bus Analyzer](http://www.microchip.com/Developmenttools/ProductDetails/APGDT002) to PC using USB Male-A to Male Mini-B cable
- Connect the USB to TTL serial ([USB UART click board](https://www.mikroe.com/usb-uart-click)) to U1TX pin (pin 23) and U1RX pin (pin 13) of J207 header
- Connect the Debug USB port on the board to the computer using a mini USB cable
- Connect mini USB cable to [USB UART click board](https://www.mikroe.com/usb-uart-click) to the computer. This will enumerate the USB to UART port.

## Running the Application

1. Build and program the application project using its respective IDE
2. Open [Microchip CAN Bus Analyzer](http://www.microchip.com/Developmenttools/ProductDetails/APGDT002) software and make the following configurations:

    |Description | Settings  |
    | ---------- | --------- |
    | CAN Bitrate Control | 500 Kbps |
    | CAN Mode Control | Normal Mode |
    | Bus Termination Control | ON  |
    |||

3. Connect to the DEBUG UART Virtual COM port and configure the serial settings as follows:
    - Baud : 115200
    - Data : 8 Bits
    - Parity : None
    - Stop : 1 Bit
    - Flow Control : None
4. Press '1' to transmit message to CAN Bus on console window of the board
5. "Transmitting Message:Success" will be displayed in the console window of PIC32MK GP DB board board
6. CAN message will be displayed in the CAN analyzer software
7. Press '2' to receive message from CAN Bus on console window of the board
8. Send following CAN message from CAN analyzer software
    - ID : 0x469, DLC : 8, Data: 1, 2, 3, 4, 5, 6, 7, 8
9. CAN message will be displayed in the terminal window of PIC32MK GP DB board

   ![output](images/output_can_normal_operation_blocking.png)

10. LED toggles at each message transmission or reception

   | Board | LED name |
   |------ | -------- |
   | PIC32MZ W1 Curiosity Board | RED, D202 |
   |||
