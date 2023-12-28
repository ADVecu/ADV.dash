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

#ifdef ADVdash5inch

#define DISPLAY_DRAW_BUF 800 * 480 / 10

struct pcb_def
{

    // ESP32RGBPANEL
    int8_t tft_bl = 2;
    int8_t cs = GFX_NOT_DEFINED;
    int8_t sck = GFX_NOT_DEFINED;
    int8_t sda_display = GFX_NOT_DEFINED;
    int8_t de = 40;
    int8_t vsync = 41;
    int8_t hsync = 39;
    int8_t pclk = 0;
    int8_t r0 = 45;
    int8_t r1 = 48;
    int8_t r2 = 47;
    int8_t r3 = 21;
    int8_t r4 = 14;
    int8_t g0 = 5;
    int8_t g1 = 6;
    int8_t g2 = 7;
    int8_t g3 = 15;
    int8_t g4 = 16;
    int8_t g5 = 4;
    int8_t b0 = 8;
    int8_t b1 = 3;
    int8_t b2 = 46;
    int8_t b3 = 9;
    int8_t b4 = 1;
    uint16_t width = 800;
    uint16_t hsync_polarity = 0;
    uint16_t hsync_front_porch = 210;
    uint16_t hsync_pulse = 4;
    uint16_t hsync_back_porch = 43;
    uint16_t height = 480;
    uint16_t vsync_polarity = 0;
    uint16_t vsync_front_porch = 22;
    uint16_t vsync_pulse = 4;
    uint16_t vsync_back_porch = 12;
    uint16_t pclk_active_neg = 1;
    int32_t prefer_speed = 16000000;
    bool auto_flush = true;

    // RGB LEDS
    uint16_t led_count = 18;
    uint16_t led_pin = 38;

    // GPIO
    gpio_num_t v5Enable = GPIO_NUM_17;
};

#endif
