#ifndef _UI_ENUMS_H
#define _UI_ENUMS_H

#include <Arduino.h>

#define TEMP_MAX_VALUE 120
#define TEMP_MIN_VALUE 0
#define PRESSURE_MAX_VALUE 700
#define PRESSURE_MIN_VALUE 0
#define VOLTAGE_MAX_VALUE 16000
#define VOLTAGE_MIN_VALUE 8000
#define FUEL_MAX_VALUE 100
#define FUEL_MIN_VALUE 0
#define DUTY_MAX_VALUE 100
#define DUTY_MIN_VALUE 0
#define AFR_MAX_VALUE 136
#define AFR_MIN_VALUE 68
#define MANIFOLD_MAX_VALUE 250
#define MANIFOLD_MIN_VALUE 0
#define LEVEL_MAX_VALUE 100
#define LEVEL_MIN_VALUE 0

/**
 * @brief Define the type of gauge to display
 *
 */
enum gauge_type
{
    COOLANT_TEMP,
    OIL_TEMP,
    AIR_TEMP,
    OIL_PRESSURE,
    FUEL_PRESSURE,
    MANIFOLD_PRESSURE,
    BATTERY_VOLTAGE,
    FUEL_LEVEL,
    INJ_DUTY,
    AFR,
    WARNING_COUNT,
    ING_TIMING,
    INJ_PWM,
    IGN_DUTY,
    MCU_TEMP,
    AMBIENT_TEMP,

};

/**
 * @brief Bar widget number
 */
enum bar_number_t
{
    BAR_1 = 1, // Top Left bar
    BAR_2,     // Top Right bar
    BAR_3,     // Bottom Left bar
    BAR_4      // Bottom Right bar
};

/**
 * @brief Arc widget number
 */
typedef enum arc_number
{
    ARC_1 = 1, // Left left arc
    ARC_2,     // left right arc
    ARC_3,     // Right left arc
    ARC_4,     // Right Right arc
    ARC_5,     // Bottom center arc
} arc_number_t;

/**
 * @brief Panel widget number
 */
typedef enum panel_number
{
    PANEL_1 = 1, // Left 1 panel
    PANEL_2,     // left 2 panel
    PANEL_3,     // Left 3 panel
    PANEL_4,     // Right 1 panel
    PANEL_5,     // Right 2 panel
    PANEL_6,     // Right 3 panel
} panel_number_t;

/**
 * @brief Define temperature unit of measure
 */
enum temp_unit
{
    CELSIUS,
    FAHRENHEIT
};

/**
 * @brief Define pressure unit of measure
 */
enum pressure_unit
{
    KPA,
    PSI,
    BAR
};

/**
 * @brief Define speed unit of measure
 */
enum speed_unit
{
    KPH,
    MPH
};

enum widget_type
{
    BARW,
    ARCW,
    PANELW
};

#endif // _UI_ENUMS_H