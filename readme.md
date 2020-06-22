﻿[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Harmony 3 peripheral library application examples for PIC32MZ W1 family

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices.  Refer to the following links for more information.

- [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)
- [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)
- [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
- [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony)
- [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/)

This repository contains the MPLAB® Harmony 3 peripheral library application examples for PIC32MZ W1 family

- [Release Notes](release_notes.md)
- [MPLAB® Harmony License](mplab_harmony_license.md)

To download or clone these application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1) page and click:

![clone](./docs/images/clone.png)

## Contents Summary

| Folder     | Description                             |
| ---        | ---                                     |
| apps       | Peripheral library example applications |
| docs       | Applications help documentation         |

## Code Examples

The following applications are provided to demonstrate the typical or interesting usage models of one or more peripheral libraries.

| Name | Description|
|:---------|:-----------|
| [ADCHS Interrupt](apps/adchs/adchs_interrupt/readme.md) | This example application shows how to sample an analog input using the ADCHS peripheral and displays the converted samples on a serial terminal |
| [ADCHS polling](apps/adchs/adchs_polled/readme.md) | This example application shows how to sample an analog input using the ADCHS peripheral and displays the converted samples on a serial terminal |
| [CAN FD blocking](apps/can/can_fd_operation_blocking/readme.md) | This example application shows how to use the CAN module to transmit and receive CAN FD messages in polling mode |
| [CAN blocking](apps/can/can_normal_operation_blocking/readme.md) | This example application shows how to use the CAN module to transmit and receive normal CAN messages in polling mode |
| [CAN interrupt](apps/can/can_normal_operation_interrupt_timestamp/readme.md) | This example application shows how to use the CAN module to transmit and receive normal CAN messages in interrupt mode |
| [Clock configuration](apps/clock/clock_config/readme.md) | This example application shows how to configure the clock system to run the device at maximum frequency. It also outputs a prescaled clock signal on a GPIO pin for measurement and verification |
| [CORETIMER periodic interrupt](apps/coretimer/coretimer_periodic_timeout/readme.md) | This example application shows how to use the CoreTimer to generate periodic interrupts |
| [DMAC memory transfer](apps/dmac/dmac_memory_transfer/readme.md) | This example application demonstrates how to use the DMAC peripheral to do a memory to memory transfer |
| [DMT timeout](apps/dmt/dmt_timeout/readme.md) | This example application shows how the deadman timer resets by not clearing the deadman timer counter on switch press |
| [GPIO interrupt](apps/gpio/gpio_led_on_off_interrupt/readme.md) | This example application demonstrate how to generate GPIO interrupt on switch press and release, and indicate the switch status using the LED |
| [I2C EEPROM read write](apps/i2c/master/i2c_eeprom/readme.md) | This example application demonstrates how to use the I2C peripheral to write and read from the I2C serial EEPROM memory |
| [ICAP capture mode](apps/icap/icap_capture_mode/readme.md) | This example application shows how to use the ICAP peripheral to measure the pulse width of the input signal |
| [NVM flash read write](apps/nvm/flash_read_write/readme.md) | This example application demonstrates how to use the NVM to erase and program the internal Flash memory |
| [OCMP compare mode](apps/ocmp/ocmp_compare_mode/readme.md) | This example application shows how to use the OCMP peripheral to generate an active low, active high, and toggle output on compare match |
| [RNG random number](apps/rng/rng_random_number/readme.md) | This example application shows how to use the RNG Peripheral library to generate a pseudo-random number |
| [RTCC alarm interrupt](apps/rtcc/rtcc_alarm/readme.md) | This example application shows how to use the RTCC to configure the time and generate the alarm |
| [SPI SST26 flash write read](apps/spi/spi_sst26_write_read/readme.md) | This example uses the SPI peripheral library to write an array of values to the SST26 Flash and verify the value written by reading the values back and comparing it to the value written. The example application performs the SST26 write only once after a power on reset |
| [TMR periodic interrupt](apps/tmr/tmr_timer_mode/readme.md) | This example demonstrates how to use the TMR module in timer mode to generate periodic interrupt |
| [TMR1 periodic interrupt](apps/tmr1/tmr1_timer_mode/readme.md) | This example demonstrates how to use the TMR1 module in timer mode to generate periodic interrupt |
| [UART echo interrupt](apps/uart/uart_echo_interrupt/readme.md) | This example application demonstrates how to use the UART peripheral to transfer a block of data in a non-blocking manner |
| [UART ring buffer](apps/uart/uart_ring_buffer_interrupt/readme.md) | This example application demonstrates how to use the UART peripheral in ring buffer mode |
| [WDT timeout](apps/wdt/wdt_timeout/readme.md) | This example application shows how the watchdog timer resets by not feeding the watchdog on switch press |
|||
____

[![License](https://img.shields.io/badge/license-Harmony%20license-orange.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1/blob/master/mplab_harmony_license.md)
[![Latest release](https://img.shields.io/github/release/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1/releases/latest)
[![Latest release date](https://img.shields.io/github/release-date/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1/releases/latest)
[![Commit activity](https://img.shields.io/github/commit-activity/y/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1/graphs/commit-activity)
[![Contributors](https://img.shields.io/github/contributors-anon/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1.svg)]()

____

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/)
[![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech)

[![](https://img.shields.io/github/stars/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1.svg?style=social)]()
[![](https://img.shields.io/github/watchers/Microchip-MPLAB-Harmony/csp_apps_pic32mz_w1.svg?style=social)]()
