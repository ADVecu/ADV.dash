#ifndef _UI_ENUMS_H
#define _UI_ENUMS_H

#include <Arduino.h>

#define TEMP_MAX_VALUE 120
#define TEMP_MIN_VALUE 0
#define PRESSURE_MAX_VALUE 100
#define PRESSURE_MIN_VALUE 0
#define VOLTAGE_MAX_VALUE 16000
#define VOLTAGE_MIN_VALUE 8000
#define FUEL_MAX_VALUE 100
#define FUEL_MIN_VALUE 0
#define DUTY_MAX_VALUE 100
#define DUTY_MIN_VALUE 0
#define AFR_MAX_VALUE 200
#define AFR_MIN_VALUE 100
#define MANIFOLD_MAX_VALUE 250
#define MANIFOLD_MIN_VALUE 0

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
    AFR

};

/**
 * @brief Bar widget number
 */
typedef enum bar_number
{
    BAR_1 = 1, // Top Left bar
    BAR_2,     // Top Right bar
    BAR_3,     // Bottom Left bar
    BAR_4      // Bottom Right bar
} bar_number_t;

/**
 * @brief Arc widget number
 */
typedef enum arc_number
{
    ARC_1 = 1, // Left left arc
    ARC_2,     // left right arc
    ARC_3,     // Right left arc
    ARC_4,      // Right Right arc
    ARC_5,      // Bottom center arc
} arc_number_t;

#endif // _UI_ENUMS_H