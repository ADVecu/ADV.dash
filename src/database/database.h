#ifndef __DATABASE__
#define __DATABASE__

#include <Arduino.h>
#include "./controllers/uiControl/ui_enums.h"

#define FUEL_LEVEL_HIGH_WARNING_DEFAULT 0
#define FUEL_LEVEL_HIGH_ALERT_DEFAULT 0
#define FUEL_LEVEL_LOW_WARNING_DEFAULT 25
#define FUEL_LEVEL_LOW_ALERT_DEFAULT 10

#define COOLANT_TEMP_HIGH_WARNING_DEFAULT 95
#define COOLANT_TEMP_HIGH_ALERT_DEFAULT 105
#define COOLANT_TEMP_LOW_WARNING_DEFAULT 50
#define COOLANT_TEMP_LOW_ALERT_DEFAULT 50

#define OIL_TEMP_HIGH_WARNING_DEFAULT 95
#define OIL_TEMP_HIGH_ALERT_DEFAULT 105
#define OIL_TEMP_LOW_WARNING_DEFAULT 50
#define OIL_TEMP_LOW_ALERT_DEFAULT 50

#define AIR_TEMP_HIGH_WARNING_DEFAULT 60
#define AIR_TEMP_HIGH_ALERT_DEFAULT 70
#define AIR_TEMP_LOW_WARNING_DEFAULT 0
#define AIR_TEMP_LOW_ALERT_DEFAULT 0

#define OIL_PRESSURE_HIGH_WARNING_DEFAULT 90
#define OIL_PRESSURE_HIGH_ALERT_DEFAULT 100
#define OIL_PRESSURE_LOW_WARNING_DEFAULT 15
#define OIL_PRESSURE_LOW_ALERT_DEFAULT 10

#define FUEL_PRESSURE_HIGH_WARNING_DEFAULT 60
#define FUEL_PRESSURE_HIGH_ALERT_DEFAULT 70
#define FUEL_PRESSURE_LOW_WARNING_DEFAULT 35
#define FUEL_PRESSURE_LOW_ALERT_DEFAULT 25

#define MANIFOLD_PRESSURE_HIGH_WARNING_DEFAULT 180
#define MANIFOLD_PRESSURE_HIGH_ALERT_DEFAULT 210

#define BATTERY_VOLTAGE_HIGH_WARNING_DEFAULT 14900
#define BATTERY_VOLTAGE_HIGH_ALERT_DEFAULT 15200
#define BATTERY_VOLTAGE_LOW_WARNING_DEFAULT 12000
#define BATTERY_VOLTAGE_LOW_ALERT_DEFAULT 11500

#define INJ_DUTY_HIGH_WARNING_DEFAULT 80
#define INJ_DUTY_HIGH_ALERT_DEFAULT 90

#define AFR_HIGH_WARNING_DEFAULT 150
#define AFR_HIGH_ALERT_DEFAULT 160
#define AFR_LOW_WARNING_DEFAULT 100
#define AFR_LOW_ALERT_DEFAULT 90

/**
 * @brief Database class
 * Is used to store user settings in the flash memory
 */
class Database
{
public:
    /*******************************************************************************
     * RPMS Data
     *******************************************************************************/
    /**
     * @brief Saves the redline rpms setting in the flash memory
     * @param redline Rpms at which the redline should be set, Range: 5000 - 10000
     */
    void saveRpmsRedline(uint16_t redline);

    /**
     * @brief Saves the warning rpms setting in the flash memory
     * @param warning Rpms at which the warning should be set, Range: 2000 - RedLine setting
     */
    void saveRpmsWarning(uint16_t warning);

    /**
     * @brief Gets the redline rpms setting from the flash memory
     * @return uint16_t Rpms at which the redline is set, Range: 5000 - 10000
     */
    uint16_t getRpmsRedline();

    /**
     * @brief Gets the warning rpms setting from the flash memory
     * @return uint16_t Rpms at which the warning is set, Range: 2000 - RedLine setting
     */
    uint16_t getRpmsWarning();

    /*******************************************************************************
     * Bar Gauges Data
     *******************************************************************************/
    /**
     * @brief Saves the bar gauge type
     * @param gaugeNumber Number of the bar gauge to be saved
     * @param gaugeType Type of gauge to be saved
     */
    void saveBarGaugeType(bar_number_t gaugeNumber, gauge_type gaugeType);

    /**
     * @brief Gets the bar gauge type
     * @param gaugeNumber Number of the bar gauge to be retrieved
     * @return gauge_type Type of gauge to be retrieved
     */
    gauge_type getBarGaugeType(bar_number_t gaugeNumber);

    /**
     * @brief Saves the bar gauge high warning value
     * @param gaugeNumber Number of the bar gauge to be saved
     * @param warningValue High Warning value of the bar gauge to be saved
     */
    void saveBarGaugeHighWarningValue(bar_number_t gaugeNumber, uint16_t warningValue);

    /**
     * @brief Gets the bar gauge high warning value
     * @param gaugeNumber Number of the bar gauge to be retrieved
     * @return High Warning value of the bar gauge to be retrieved
     */
    uint16_t getBarGaugeHighWarningValue(bar_number_t gaugeNumber);

    /**
     * @brief Saves the bar gauge high alert value
     * @param gaugeNumber Number of the bar gauge to be saved
     * @param alertValue High alert value of the bar gauge to be saved
     */
    void saveBarGaugeHighAlertValue(bar_number_t gaugeNumber, uint16_t alertValue);

    /**
     * @brief Gets the bar gauge high alert value
     * @param gaugeNumber Number of the bar gauge to be retrieved
     * @return High alert value of the bar gauge to be retrieved
     */
    uint16_t getBarGaugeHighAlertValue(bar_number_t gaugeNumber);

    /**
     * @brief Saves the bar gauge low warning value
     * @param gaugeNumber Number of the bar gauge to be saved
     * @param warningValue Low warning value of the bar gauge to be saved
     */
    void saveBarGaugeLowWarningValue(bar_number_t gaugeNumber, uint16_t warningValue);

    /**
     * @brief Gets the bar gauge low warning value
     * @param gaugeNumber Number of the bar gauge to be retrieved
     * @return Low warning value of the bar gauge to be retrieved
     */
    uint16_t getBarGaugeLowWarningValue(bar_number_t gaugeNumber);

    /**
     * @brief Saves the bar gauge low alert value
     * @param gaugeNumber Number of the bar gauge to be saved
     * @param alertValue Low alert value of the bar gauge to be saved
     */
    void saveBarGaugeLowAlertValue(bar_number_t gaugeNumber, uint16_t alertValue);

    /**
     * @brief Gets the bar gauge low alert value
     * @param gaugeNumber Number of the bar gauge to be retrieved
     * @return Low alert value of the bar gauge to be retrieved
     */
    uint16_t getBarGaugeLowAlertValue(bar_number_t gaugeNumber);
};

#endif // __DATABASE__