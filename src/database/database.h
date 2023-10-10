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

#define OIL_PRESSURE_HIGH_WARNING_DEFAULT 620
#define OIL_PRESSURE_HIGH_ALERT_DEFAULT 680
#define OIL_PRESSURE_LOW_WARNING_DEFAULT 103
#define OIL_PRESSURE_LOW_ALERT_DEFAULT 68

#define FUEL_PRESSURE_HIGH_WARNING_DEFAULT 413
#define FUEL_PRESSURE_HIGH_ALERT_DEFAULT 482
#define FUEL_PRESSURE_LOW_WARNING_DEFAULT 240
#define FUEL_PRESSURE_LOW_ALERT_DEFAULT 172

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

#define WARNING_COUNT_ALERT_DEFAULT 5
#define INJ_PWM_ALERT_DEFAULT 15
#define ING_TIMING_ALERT_DEFAULT 30
#define FUEL_FLOW_ALERT_DEFAULT 100
#define FUEL_TRIM_ALERT_DEFAULT 150
#define FUEL_USED_ALERT_DEFAULT 100

/**
 * @brief Database class
 * Is used to store user settings in the flash memory
 */
class Database
{
public:
    /*******************************************************************************
     * General Data
     *******************************************************************************/

    /**
     * @brief Save the user settings for temperature unit in the flash memory
     * @param unit Celsius or Fahrenheit
     */
    void saveTempUnit(temp_unit unit);

    /**
     * @brief Get the user settings for temperature unit from the flash memory
     * @return temp_unit Celsius or Fahrenheit
     */
    temp_unit getTempUnit();

    /**
     * @brief Save the user settings for pressure unit in the flash memory
     * @param unit PSI, KPA or BAR
     */
    void savePressureUnit(pressure_unit unit);

    /**
     * @brief Get the user settings for pressure unit from the flash memory
     * @return pressure_unit PSI, KPA or BAR
     */
    pressure_unit getPressureUnit();

    /**
     * @brief Save the user settings for Speed unit in the flash memory
     * @param unit km/h or mph
     */
    void saveSpeedUnit(speed_unit unit);

    /**
     * @brief Get the user settings for Speed unit from the flash memory
     * @return speed_unit km/h or mph
     */
    speed_unit getSpeedUnit();

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

    /*******************************************************************************
     * Arc Gauges Data
     *******************************************************************************/

    /**
     * @brief Saves the arc gauge type
     * @param arcNumber Number of the arc gauge to be saved
     * @param gaugeType Type of gauge to be saved
     */
    void saveArcGaugeType(arc_number_t arcNumber, gauge_type gaugeType);

    /**
     * @brief Gets the arc gauge type
     * @param arcNumber Number of the arc gauge to be retrieved
     * @return gauge_type Type of gauge to be retrieved
     */
    gauge_type getArcGaugeType(arc_number_t arcNumber);

    /**
     * @brief Saves the arc gauge high warning value
     * @param arcNumber Number of the arc gauge to be saved
     * @param warningValue High Warning value of the arc gauge to be saved
     */
    void saveArcGaugeHighWarningValue(arc_number_t arcNumber, uint16_t warningValue);

    /**
     * @brief Gets the arc gauge high warning value
     * @param arcNumber Number of the arc gauge to be retrieved
     * @return High Warning value of the arc gauge to be retrieved
     */
    uint16_t getArcGaugeHighWarningValue(arc_number_t arcNumber);

    /**
     * @brief Saves the arc gauge high alert value
     * @param arcNumber Number of the arc gauge to be saved
     * @param alertValue High alert value of the arc gauge to be saved
     */
    void saveArcGaugeHighAlertValue(arc_number_t arcNumber, uint16_t alertValue);

    /**
     * @brief Gets the arc gauge high alert value
     * @param arcNumber Number of the arc gauge to be retrieved
     * @return High alert value of the arc gauge to be retrieved
     */
    uint16_t getArcGaugeHighAlertValue(arc_number_t arcNumber);

    /**
     * @brief Saves the arc gauge low warning value
     * @param arcNumber Number of the arc gauge to be saved
     * @param warningValue Low warning value of the arc gauge to be saved
     */
    void saveArcGaugeLowWarningValue(arc_number_t arcNumber, uint16_t warningValue);

    /**
     * @brief Gets the arc gauge low warning value
     * @param arcNumber Number of the arc gauge to be retrieved
     * @return Low warning value of the arc gauge to be retrieved
     */
    uint16_t getArcGaugeLowWarningValue(arc_number_t arcNumber);

    /**
     * @brief Saves the arc gauge low alert value
     * @param arcNumber Number of the arc gauge to be saved
     * @param alertValue Low alert value of the arc gauge to be saved
     */
    void saveArcGaugeLowAlertValue(arc_number_t arcNumber, uint16_t alertValue);

    /**
     * @brief Gets the arc gauge low alert value
     * @param arcNumber Number of the arc gauge to be retrieved
     * @return Low alert value of the arc gauge to be retrieved
     */
    uint16_t getArcGaugeLowAlertValue(arc_number_t arcNumber);

    /*******************************************************************************
     * Panel Data
     *******************************************************************************/

    /**
     * @brief Saves the panel gauge type
     * @param panelNumber Number of the panel gauge to be saved
     * @param gaugeType Type of gauge to be saved
     */
    void savePanelGaugeType(panel_number_t panelNumber, gauge_type gaugeType);

    /**
     * @brief Gets the panel gauge type
     * @param panelNumber Number of the panel gauge to be retrieved
     * @return gauge_type Type of gauge to be retrieved
     */
    gauge_type getPanelGaugeType(panel_number_t panelNumber);

    /**
     * @brief Saves the panel gauge alert value
     * @param panelNumber Number of the panel gauge to be saved
     * @param alertValue Alert value of the panel gauge to be saved
     */
    void savePanelGaugeAlertValue(panel_number_t panelNumber, uint16_t alertValue);

    /**
     * @brief Gets the panel gauge alert value
     * @param panelNumber Number of the panel gauge to be retrieved
     * @return Alert value of the panel gauge to be retrieved
     */
    uint16_t getPanelGaugeAlertValue(panel_number_t panelNumber);
};

#endif // __DATABASE__