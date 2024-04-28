
/*!
 * @file pcb_definitions.h
 *
 * This is a file that contains the pcb definitions for the different boards
 * that are supported by the firmware.
 *
 * The pcb_def struct is used to define the pinout of the board and the
 * display parameters.
 *
 * The pcb_def struct is passed to the HardwareInit class to initialize the
 * hardware.
 *
 * Just uncomment the board you are using and comment out the rest.
 *
 * Any custom boards can be added here, just copy and paste the struct and
 * change the pinout and display parameters.
 */

#ifndef PCB_DEFINITIONS_H_
#define PCB_DEFINITIONS_H_

#include <Arduino.h>
#include <Arduino_GFX_Library.h>

/*******************************************************************************
 * Select the board you are using
 *******************************************************************************/

// #define ADVdash7inch
#define ADVdash5inch

/*******************************************************************************
 * PCB Definitions
 *******************************************************************************/

#if defined(ADVdash5inch)

#define DISPLAY_DRAW_BUF 800 * 480 / 10

#define RMPS_LEDS true
#define INDICATOR_LEDS true
#define LEDS_NUM 18
#define LEDS_PIN 13
#define LEDS_PIN_CLOCK 12
#define LEDS_RPMS_START 4
#define LEDS_RPMS_END 14
#define LEDS_RPMS_LOW 7
#define LEDS_RPMS_MID 10
#define LEDS_RPMS_MAX 14

// Can Bus Transceiver Pins
// #define CAN_TX_PIN GPIO_NUM_13
// #define CAN_RX_PIN GPIO_NUM_12

#define CAN_TX_PIN GPIO_NUM_44
#define CAN_RX_PIN GPIO_NUM_43

#define BOARD_HAS_SLEEP_CAPABILITY false
#define BOARD_HAS_TOUCH_CAPABILITY true

struct pcb_def
{

    // ESP32RGBPANEL
    int8_t tft_bl = 2;
    int8_t cs = GFX_NOT_DEFINED;
    int8_t sck = GFX_NOT_DEFINED;
    int8_t sda_display = GFX_NOT_DEFINED;
    int8_t de = GPIO_NUM_40;
    int8_t vsync = GPIO_NUM_41;
    int8_t hsync = GPIO_NUM_39;
    int8_t pclk = GPIO_NUM_0;
    int8_t r0 = GPIO_NUM_45;
    int8_t r1 = GPIO_NUM_48;
    int8_t r2 = GPIO_NUM_47;
    int8_t r3 = GPIO_NUM_21;
    int8_t r4 = GPIO_NUM_14;
    int8_t g0 = GPIO_NUM_5;
    int8_t g1 = GPIO_NUM_6;
    int8_t g2 = GPIO_NUM_7;
    int8_t g3 = GPIO_NUM_15;
    int8_t g4 = GPIO_NUM_16;
    int8_t g5 = GPIO_NUM_4;
    int8_t b0 = GPIO_NUM_8;
    int8_t b1 = GPIO_NUM_3;
    int8_t b2 = GPIO_NUM_46;
    int8_t b3 = GPIO_NUM_9;
    int8_t b4 = GPIO_NUM_1;
    uint16_t width = 800;
    uint16_t hsync_polarity = 0;
    uint16_t hsync_front_porch = 8;
    uint16_t hsync_pulse = 4;
    uint16_t hsync_back_porch = 43;
    uint16_t height = 480;
    uint16_t vsync_polarity = 0;
    uint16_t vsync_front_porch = 8;
    uint16_t vsync_pulse = 4;
    uint16_t vsync_back_porch = 12;
    uint16_t pclk_active_neg = 1;
    int32_t prefer_speed = 15000000;
    bool auto_flush = true;

    // GPIO
    gpio_num_t v5Enable = GPIO_NUM_17;
    gpio_num_t sw12v = GPIO_NUM_10;
    gpio_num_t wakeUp = GPIO_NUM_11;

    int sda_touch = 38;
    int scl_touch = 42;
};

enum ledPosition
{
    HIGH_BEAM,
    BATTERY_LIGHT,
    CHECK_ENGINE,
    LEFT_DIR,
    RIGHT_DIR = 14,
    OIL_PRESSURE_LED,
    PARKING_BRAKE,
    FUEL_LED
};

#endif

#if defined(ADVdash7inch)

#define DISPLAY_DRAW_BUF 800 * 480 / 10

#define RMPS_LEDS false
#define INDICATOR_LEDS false
#define LEDS_NUM 18
#define LEDS_PIN 38
#define LEDS_RPMS_START 4
#define LEDS_RPMS_END 14
#define LEDS_RPMS_LOW 7
#define LEDS_RPMS_MID 10
#define LEDS_RPMS_MAX 14

// Can Bus Transceiver Pins
#define CAN_TX_PIN GPIO_NUM_18
#define CAN_RX_PIN GPIO_NUM_17

#define BOARD_HAS_SLEEP_CAPABILITY false
#define BOARD_HAS_TOUCH_CAPABILITY true

struct pcb_def
{

    // ESP32RGBPANEL
    int8_t tft_bl = 2;
    int8_t cs = GFX_NOT_DEFINED;
    int8_t sck = GFX_NOT_DEFINED;
    int8_t sda_display = GFX_NOT_DEFINED;
    int8_t de = 41;
    int8_t vsync = 40;
    int8_t hsync = 39;
    int8_t pclk = 42;
    int8_t r0 = 14;
    int8_t r1 = 21;
    int8_t r2 = 47;
    int8_t r3 = 48;
    int8_t r4 = 45;
    int8_t g0 = 9;
    int8_t g1 = 46;
    int8_t g2 = 3;
    int8_t g3 = 8;
    int8_t g4 = 16;
    int8_t g5 = 1;
    int8_t b0 = 15;
    int8_t b1 = 7;
    int8_t b2 = 6;
    int8_t b3 = 5;
    int8_t b4 = 4;
    uint16_t width = 800;
    uint16_t hsync_polarity = 0;
    uint16_t hsync_front_porch = 210;
    uint16_t hsync_pulse = 30;
    uint16_t hsync_back_porch = 16;
    uint16_t height = 480;
    uint16_t vsync_polarity = 0;
    uint16_t vsync_front_porch = 22;
    uint16_t vsync_pulse = 13;
    uint16_t vsync_back_porch = 10;
    uint16_t pclk_active_neg = 1;
    int32_t prefer_speed = 12000000;
    bool auto_flush = true;

    // GPIO
    gpio_num_t v5Enable = GPIO_NUM_NC;
    gpio_num_t sw12v = GPIO_NUM_NC;
    gpio_num_t wakeUp = GPIO_NUM_NC;
};

enum ledPosition
{
    HIGH_BEAM,
    BATTERY_LIGHT,
    CHECK_ENGINE,
    LEFT_DIR,
    RIGHT_DIR = 14,
    OIL_PRESSURE_LED,
    PARKING_BRAKE,
    FUEL_LED
};

#endif
#endif // PCB_DEFINITIONS_H_