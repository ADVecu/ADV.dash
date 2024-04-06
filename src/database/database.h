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

#define BATTERY_VOLTAGE_HIGH_WARNING_DEFAULT 149
#define BATTERY_VOLTAGE_HIGH_ALERT_DEFAULT 152
#define BATTERY_VOLTAGE_LOW_WARNING_DEFAULT 120
#define BATTERY_VOLTAGE_LOW_ALERT_DEFAULT 115

#define INJ_DUTY_HIGH_WARNING_DEFAULT 80
#define INJ_DUTY_HIGH_ALERT_DEFAULT 90

#define AFR_HIGH_WARNING_DEFAULT 102
#define AFR_HIGH_ALERT_DEFAULT 109
#define AFR_LOW_WARNING_DEFAULT 82
#define AFR_LOW_ALERT_DEFAULT 75

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

    /**
     * @brief Reset to default Settings
     */
    void resetToDefault(void);

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

    /*******************************************************************************
     * MAP Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief  Get MAP Gauge High Warning Value
     */
    uint16_t getMAPHighWarningValue();

    /**
     * @brief  Get MAP Gauge High Alert Value
     */
    uint16_t getMAPHighAlertValue();

    /**
     * @brief  Save MAP Gauge High Warning Value
     * @param  warningValue: MAP Gauge High Warning Value
     */
    void saveMAPHighWarningValue(uint16_t warningValue);

    /**
     * @brief  Save MAP Gauge High Alert Value
     * @param  alertValue: MAP Gauge High Alert Value
     */
    void saveMAPHighAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * Coolant Temp Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief Get Coolant Temp High Warning Value
     */
    uint16_t getCoolantTempHighWarningValue();

    /**
     * @brief Get Coolant Temp High Alert Value
     */
    uint16_t getCoolantTempHighAlertValue();

    /**
     * @brief Get Coolant Temp Low Warning Value
     */
    uint16_t getCoolantTempLowWarningValue();

    /**
     * @brief Get Coolant Temp Low Alert Value
     */
    uint16_t getCoolantTempLowAlertValue();

    /**
     * @brief Save Coolant Temp High Warning Value
     * @param warningValue: Coolant Temp High Warning Value
     */
    void saveCoolantTempHighWarningValue(uint16_t warningValue);

    /**
     * @brief Save Coolant Temp High Alert Value
     * @param alertValue: Coolant Temp High Alert Value
     */
    void saveCoolantTempHighAlertValue(uint16_t alertValue);

    /**
     * @brief Save Coolant Temp Low Warning Value
     * @param warningValue: Coolant Temp Low Warning Value
     */
    void saveCoolantTempLowWarningValue(uint16_t warningValue);

    /**
     * @brief Save Coolant Temp Low Alert Value
     * @param alertValue: Coolant Temp Low Alert Value
     */
    void saveCoolantTempLowAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * Oil Temp Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief Get Oil Temp High Warning Value
     */
    uint16_t getOilTempHighWarningValue();

    /**
     * @brief Get Oil Temp High Alert Value
     */
    uint16_t getOilTempHighAlertValue();

    /**
     * @brief Get Oil Temp Low Warning Value
     */
    uint16_t getOilTempLowWarningValue();

    /**
     * @brief Get Oil Temp Low Alert Value
     */
    uint16_t getOilTempLowAlertValue();

    /**
     * @brief Save Oil Temp High Warning Value
     * @param warningValue: Oil Temp High Warning Value
     */
    void saveOilTempHighWarningValue(uint16_t warningValue);

    /**
     * @brief Save Oil Temp High Alert Value
     * @param alertValue: Oil Temp High Alert Value
     */
    void saveOilTempHighAlertValue(uint16_t alertValue);

    /**
     * @brief Save Oil Temp Low Warning Value
     * @param warningValue: Oil Temp Low Warning Value
     */
    void saveOilTempLowWarningValue(uint16_t warningValue);

    /**
     * @brief Save Oil Temp Low Alert Value
     * @param alertValue: Oil Temp Low Alert Value
     */
    void saveOilTempLowAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * Air Temp Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief Get Air Temp High Warning Value
     */
    uint16_t getAirTempHighWarningValue();

    /**
     * @brief Get Air Temp High Alert Value
     */
    uint16_t getAirTempHighAlertValue();

    /**
     * @brief Get Air Temp Low Warning Value
     */
    uint16_t getAirTempLowWarningValue();

    /**
     * @brief Get Air Temp Low Alert Value
     */
    uint16_t getAirTempLowAlertValue();

    /**
     * @brief Save Air Temp High Warning Value
     * @param warningValue: Air Temp High Warning Value
     */
    void saveAirTempHighWarningValue(uint16_t warningValue);

    /**
     * @brief Save Air Temp High Alert Value
     * @param alertValue: Air Temp High Alert Value
     */
    void saveAirTempHighAlertValue(uint16_t alertValue);

    /**
     * @brief Save Air Temp Low Warning Value
     * @param warningValue: Air Temp Low Warning Value
     */
    void saveAirTempLowWarningValue(uint16_t warningValue);

    /**
     * @brief Save Air Temp Low Alert Value
     * @param alertValue: Air Temp Low Alert Value
     */
    void saveAirTempLowAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * Oil Pressure Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief get Oil Pressure High Warning Value
     */
    uint16_t getOilPressureHighWarningValue();

    /**
     * @brief get Oil Pressure High Alert Value
     */
    uint16_t getOilPressureHighAlertValue();

    /**
     * @brief get Oil Pressure Low Warning Value
     */
    uint16_t getOilPressureLowWarningValue();

    /**
     * @brief get Oil Pressure Low Alert Value
     */
    uint16_t getOilPressureLowAlertValue();

    /**
     * @brief Save Oil Pressure High Warning Value
     * @param warningValue: Oil Pressure High Warning Value
     */
    void saveOilPressureHighWarningValue(uint16_t warningValue);

    /**
     * @brief Save Oil Pressure High Alert Value
     * @param alertValue: Oil Pressure High Alert Value
     */
    void saveOilPressureHighAlertValue(uint16_t alertValue);

    /**
     * @brief Save Oil Pressure Low Warning Value
     * @param warningValue: Oil Pressure Low Warning Value
     */
    void saveOilPressureLowWarningValue(uint16_t warningValue);

    /**
     * @brief Save Oil Pressure Low Alert Value
     * @param alertValue: Oil Pressure Low Alert Value
     */
    void saveOilPressureLowAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * Fuel Pressure Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief Get Fuel Pressure High Warning Value
     */
    uint16_t getFuelPressureHighWarningValue();

    /**
     * @brief Get Fuel Pressure High Alert Value
     */
    uint16_t getFuelPressureHighAlertValue();

    /**
     * @brief Get Fuel Pressure Low Warning Value
     */
    uint16_t getFuelPressureLowWarningValue();

    /**
     * @brief Get Fuel Pressure Low Alert Value
     */
    uint16_t getFuelPressureLowAlertValue();

    /**
     * @brief Save Fuel Pressure High Warning Value
     * @param warningValue: Fuel Pressure High Warning Value
     */
    void saveFuelPressureHighWarningValue(uint16_t warningValue);

    /**
     * @brief Save Fuel Pressure High Alert Value
     * @param alertValue: Fuel Pressure High Alert Value
     */
    void saveFuelPressureHighAlertValue(uint16_t alertValue);

    /**
     * @brief Save Fuel Pressure Low Warning Value
     * @param warningValue: Fuel Pressure Low Warning Value
     */
    void saveFuelPressureLowWarningValue(uint16_t warningValue);

    /**
     * @brief Save Fuel Pressure Low Alert Value
     * @param alertValue: Fuel Pressure Low Alert Value
     */
    void saveFuelPressureLowAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * Battery voltage Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief Get Battery Voltage High Warning Value
     */
    uint16_t getBatteryVoltageHighWarningValue();

    /**
     * @brief Get Battery Voltage High Alert Value
     */
    uint16_t getBatteryVoltageHighAlertValue();

    /**
     * @brief Get Battery Voltage Low Warning Value
     */
    uint16_t getBatteryVoltageLowWarningValue();

    /**
     * @brief Get Battery Voltage Low Alert Value
     */
    uint16_t getBatteryVoltageLowAlertValue();

    /**
     * @brief Save Battery Voltage High Warning Value
     * @param warningValue: Battery Voltage High Warning Value
     */
    void saveBatteryVoltageHighWarningValue(uint16_t warningValue);

    /**
     * @brief Save Battery Voltage High Alert Value
     * @param alertValue: Battery Voltage High Alert Value
     */
    void saveBatteryVoltageHighAlertValue(uint16_t alertValue);

    /**
     * @brief Save Battery Voltage Low Warning Value
     * @param warningValue: Battery Voltage Low Warning Value
     */
    void saveBatteryVoltageLowWarningValue(uint16_t warningValue);

    /**
     * @brief Save Battery Voltage Low Alert Value
     * @param alertValue: Battery Voltage Low Alert Value
     */
    void saveBatteryVoltageLowAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * Fuel Level Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief  Get Fuel Level High Warning Value
     */
    uint16_t getFuelLevelHighWarningValue();

    /**
     * @brief  Get Fuel Level High Alert Value
     */
    uint16_t getFuelLevelHighAlertValue();

    /**
     * @brief  Get Fuel Level Low Warning Value
     */
    uint16_t getFuelLevelLowWarningValue();

    /**
     * @brief  Get Fuel Level Low Alert Value
     */
    uint16_t getFuelLevelLowAlertValue();

    /**
     * @brief  Save Fuel Level High Warning Value
     * @param  warningValue: Fuel Level High Warning Value
     */
    void saveFuelLevelHighWarningValue(uint16_t warningValue);

    /**
     * @brief  Save Fuel Level High Alert Value
     * @param  alertValue: Fuel Level High Alert Value
     */
    void saveFuelLevelHighAlertValue(uint16_t alertValue);

    /**
     * @brief  Save Fuel Level Low Warning Value
     * @param  warningValue: Fuel Level Low Warning Value
     */
    void saveFuelLevelLowWarningValue(uint16_t warningValue);

    /**
     * @brief  Save Fuel Level Low Alert Value
     * @param  alertValue: Fuel Level Low Alert Value
     */
    void saveFuelLevelLowAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * AFR Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief Get AFR High Warning Value
     */
    uint16_t getAFRHighWarningValue();

    /**
     * @brief Get AFR High Alert Value
     */
    uint16_t getAFRHighAlertValue();

    /**
     * @brief Get AFR Low Warning Value
     */
    uint16_t getAFRLowWarningValue();

    /**
     * @brief Get AFR Low Alert Value
     */
    uint16_t getAFRLowAlertValue();

    /**
     * @brief Save AFR High Warning Value
     * @param warningValue: AFR High Warning Value
     */
    void saveAFRHighWarningValue(uint16_t warningValue);

    /**
     * @brief Save AFR High Alert Value
     * @param alertValue: AFR High Alert Value
     */
    void saveAFRHighAlertValue(uint16_t alertValue);

    /**
     * @brief Save AFR Low Warning Value
     * @param warningValue: AFR Low Warning Value
     */
    void saveAFRLowWarningValue(uint16_t warningValue);

    /**
     * @brief Save AFR Low Alert Value
     * @param alertValue: AFR Low Alert Value
     */
    void saveAFRLowAlertValue(uint16_t alertValue);

    /*******************************************************************************
     * Inj Duty Warnings/Alerts
     ********************************************************************************/

    /**
     * @brief get Inj Duty High Warning Value
     */
    uint16_t getInjDutyHighWarningValue();

    /**
     * @brief get Inj Duty High Alert Value
     */
    uint16_t getInjDutyHighAlertValue();

    /**
     * @brief Save Inj Duty High Warning Value
     * @param warningValue: Inj Duty High Warning Value
     */
    void saveInjDutyHighWarningValue(uint16_t warningValue);

    /**
     * @brief Save Inj Duty High Alert Value
     * @param alertValue: Inj Duty High Alert Value
     */
    void saveInjDutyHighAlertValue(uint16_t alertValue);
};

#endif // __DATABASE__