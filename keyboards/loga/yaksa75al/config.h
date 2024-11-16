// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USB_POWER_EN_PIN                    B1 // USB ENABLE pin
#define LED_POWER_EN_PIN                    A5 // LED ENABLE pin
#define HS_BAT_CABLE_PIN                    A7 // USB insertion detection pin
#define HS_LED_BOOSTING_PIN                 D2 // LED BOOSTING

#define BAT_FULL_PIN                        A15
#define BAT_FULL_STATE                      1

#define HS_RGB_INDICATOR_COUNT              99
#define HS_RGB_BAT_COUNT                    1

#define MM_BT_DEF_PIN                       C14
#define MM_2G4_DEF_PIN                      C15

#define MD_BT1_NAME                         "Yaksa75 AL"
#define MD_BT2_NAME                         "Yaksa75 AL"
#define MD_BT3_NAME                         "Yaksa75 AL"
#define MD_DONGLE_PRODUCT                   "Yaksa75 AL"

/* Device Connection RGB Indicator Light Index And Color */
#define HS_RGB_BLINK_INDEX_BT1              42
#define HS_RGB_BLINK_INDEX_BT2              41
#define HS_RGB_BLINK_INDEX_BT3              40
#define HS_RGB_BLINK_INDEX_2G4              39

#define HS_LBACK_COLOR_BT1                  RGB_BLUE
#define HS_LBACK_COLOR_BT2                  RGB_BLUE
#define HS_LBACK_COLOR_BT3                  RGB_BLUE
#define HS_LBACK_COLOR_2G4                  0x00, 0xFF, 0x00
#define HS_LBACK_COLOR_USB                  RGB_GREEN

#define HS_PAIR_COLOR_BT1                   RGB_BLUE
#define HS_PAIR_COLOR_BT2                   RGB_BLUE
#define HS_PAIR_COLOR_BT3                   RGB_BLUE
#define HS_PAIR_COLOR_2G4                   0x00, 0xFF, 0x00

/* Battery */
#define BATTERY_CAPACITY_LOW                15
#define BATTERY_CAPACITY_STOP               0
#define RGB_MATRIX_BAT_INDEX_MAP            {15, 16, 17, 18, 19, 20, 21, 22, 23, 24}

/* Status Indicator Lamp */
#define HS_MATRIX_BLINK_INDEX_BAT           76
#define HS_RGB_INDEX_CAPS                   0
#define HS_RGB_INDEX_WIN_LOCK               0
#define HS_RGB_BLINK_INDEX_VAI              0
#define HS_RGB_BLINK_INDEX_VAD              1
#define HS_RGB_BLINK_INDEX_SPI              2

#define HS_RGB_BLINK_INDEX_WIN              45
#define HS_RGB_BLINK_INDEX_MAC              46

/* UART */
#define SERIAL_DRIVER                       SD3
#define SD1_TX_PIN                          C10
#define SD1_RX_PIN                          C11

/* Encoder */
#define ENCODER_MAP_KEY_DELAY               1

/* SPI */
#define SPI_DRIVER                          SPIDQ
#define SPI_SCK_PIN                         B3
#define SPI_MOSI_PIN                        B5
#define SPI_MISO_PIN                        B4

/* Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define WEAR_LEVELING_LOGICAL_SIZE          (WEAR_LEVELING_BACKING_SIZE / 2)

/* RGB Matrix */
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

/* RGB Light */
#define RGBLED_NUM 8
#define RGBLIGHT_CUSTOM_DRIVER
#define RGBLIGHT_DISABLE_KEYCODES

#define breathing_val      40
#define rainbow_mood       40
#define LED_TYPE           RGB

/* WS2812 */
#define WS2812_SPI_DRIVER  SPIDM2
#define WS2812_SPI_DIVISOR 32

/* rgb_record */
#define ENABLE_RGB_MATRIX_RGBR_PLAY
#define RGBREC_CHANNEL_NUM         4
#define EECONFIG_CONFINFO_USE_SIZE (4 + 16)
#define EECONFIG_RGBREC_USE_SIZE   (RGBREC_CHANNEL_NUM * MATRIX_ROWS * MATRIX_COLS * 2)
#define EECONFIG_USER_DATA_SIZE    (EECONFIG_RGBREC_USE_SIZE + EECONFIG_CONFINFO_USE_SIZE)
#define RGBREC_EECONFIG_ADDR       (uint8_t *)(EECONFIG_USER_DATABLOCK)
#define CONFINFO_EECONFIG_ADDR     (uint32_t *)((uint32_t)RGBREC_EECONFIG_ADDR + (uint32_t)EECONFIG_RGBREC_USE_SIZE)

#define RGB_MATRIX_BAT_VAL      150

#define IM_BAT_REQ_LEVEL1_VAL   50
#define IM_BAT_REQ_LEVEL1_COLOR 0x00, RGB_MATRIX_BAT_VAL, 0x00

#define IM_BAT_REQ_LEVEL2_VAL   30
#define IM_BAT_REQ_LEVEL2_COLOR 0x00, RGB_MATRIX_BAT_VAL, 0x00

#define IM_BAT_REQ_LEVEL3_COLOR RGB_MATRIX_BAT_VAL, 0x00, 0x00
