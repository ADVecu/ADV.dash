#include <Arduino.h>

#define TEMP_MAX_VALUE 120
#define TEMP_MIN_VALUE 0
#define PRESSURE_MAX_VALUE 100
#define PRESSURE_MIN_VALUE 0
#define VOLTAGE_MAX_VALUE 16
#define VOLTAGE_MIN_VALUE 8
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
enum class gauge_type
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