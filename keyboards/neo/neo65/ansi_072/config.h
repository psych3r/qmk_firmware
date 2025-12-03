/* 
Copyright 2023 NEO

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//C:\Users\lizhe\qmk_firmware\keyboards\owlab\voice65\hotswap\config.h
//C:\Users\lizhe\qmk_firmware\keyboards\cannonkeys\satisfaction75\config.h
//C:\Users\lizhe\qmk_firmware\keyboards\durgod\dgk6x\config.h
//C:\Users\lizhe\qmk_firmware\keyboards\mechlovin\adelais\rgb_led\rev3\config.h


/* RGB matrix */
#ifdef RGB_MATRIX_ENABLE
// i2c setting


/*
I2Cv2 使用I2CV2的芯片
STM32F0xx
STM32F3xx
STM32F7xx
STM32L4xx

config.h Overrride    Description    Default默认值  I2C1或者2在mcuconf.h中定义，默认是I2C1
I2C_DRIVER    I2C peripheral to use - I2C1 -> I2CD1, I2C2 -> I2CD2 etc.    I2CD1
I2C1_SCL_PIN    The pin definition for SCL    B6
I2C1_SCL_PAL_MODE    The alternate function mode for SCL    4
I2C1_SDA_PIN    The pin definition for SDA    B7
I2C1_SDA_PAL_MODE    The alternate function mode for SDA    4
*/

// #define I2C_DRIVER I2CD1
// #define I2C1_SCL_PIN B6
// #define I2C1_SDA_PIN B7
// #define I2C1_SCL_PAL_MODE 4
// #define I2C1_SDA_PAL_MODE 4

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1
#define I2C1_TIMINGR_PRESC 0x00U
#define I2C1_TIMINGR_SCLDEL 0x03U
#define I2C1_TIMINGR_SDADEL 0x01U
#define I2C1_TIMINGR_SCLH 0x03U
#define I2C1_TIMINGR_SCLL 0x09U


/* 
I2Cv2 configuration structure.

config.h Override    Default
I2C1_TIMINGR_PRESC    0U
I2C1_TIMINGR_SCLDEL    7U
I2C1_TIMINGR_SDADEL    0U
I2C1_TIMINGR_SCLH    38U
I2C1_TIMINGR_SCLL    129U
 */
// #define I2C1_TIMINGR_PRESC   0U
// #define I2C1_TIMINGR_SCLDEL  7U
// #define I2C1_TIMINGR_SDADEL  0U
// #define I2C1_TIMINGR_SCLH   38U
// #define I2C1_TIMINGR_SCLL   129U



// #    define RGB_MATRIX_DISABLE_KEYCODES //禁用默认的RGB_TOGGLE等键值来控制RGB矩阵，而使用其他键和代码来控制
#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES           // reacts to keypresses
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_LED_PROCESS_LIMIT  4
#    define RGB_MATRIX_LED_FLUSH_LIMIT    26
// #    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
#    define RGB_MATRIX_STARTUP_VAL        64
#    define DRIVER_ADDR_1                 0b0110000
//   #define DRIVER_ADDR_2 0b1010011
#    define DRIVER_COUNT                  1  //2
#    define RGB_MATRIX_LED_COUNT          68   //DRIVER_LED_TOTAL              //RGB_MATRIX_LED_COUNT 

#endif