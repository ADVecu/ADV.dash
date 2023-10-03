#include <Preferences.h>
#include <Arduino.h>

#include "database.h"

#define DATABASE_NAME "config"

Preferences preferences;

/*******************************************************************************
 * RPMs Data
 *******************************************************************************/
void Database::saveRpmsRedline(uint16_t redline)
{
    if (redline <= 10000 && redline >= 5000)
    {
        preferences.begin(DATABASE_NAME, false);
        preferences.putUShort("rpmsRedline", redline);
        preferences.end();
    }
}

void Database::saveRpmsWarning(uint16_t warning)
{
    if (warning < 5000 && warning >= 2000)
    {
        preferences.begin(DATABASE_NAME, false);
        preferences.putUShort("rpmsWarning", warning);
        preferences.end();
    }
}

uint16_t Database::getRpmsRedline()
{
    preferences.begin(DATABASE_NAME, true);
    uint16_t redline = preferences.getUShort("rpmsRedline", 8000);
    preferences.end();

    return redline;
}

uint16_t Database::getRpmsWarning()
{
    preferences.begin(DATABASE_NAME, true);
    uint16_t warning = preferences.getUShort("rpmsWarning", 6500);
    preferences.end();

    return warning;
}

/*******************************************************************************
 * Bar Gauges Data
 ********************************************************************************/

void Database::saveBarGaugeType(bar_number_t gaugeNumber, gauge_type gaugeType)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUChar(String("barGaugeType" + String(gaugeNumber)).c_str(), (uint8_t)gaugeType);

    preferences.end();
}

gauge_type Database::getBarGaugeType(bar_number_t gaugeNumber)
{
    gauge_type gaugeType;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case BAR_1:
        gaugeType = (gauge_type)preferences.getUChar("barGaugeType1", (uint8_t)gauge_type::FUEL_LEVEL);
        break;
    case BAR_2:
        gaugeType = (gauge_type)preferences.getUChar("barGaugeType2", (uint8_t)gauge_type::BATTERY_VOLTAGE);
        break;
    case BAR_3:
        gaugeType = (gauge_type)preferences.getUChar("barGaugeType3", (uint8_t)gauge_type::AIR_TEMP);
        break;
    case BAR_4:
        gaugeType = (gauge_type)preferences.getUChar("barGaugeType4", (uint8_t)gauge_type::OIL_TEMP);
        break;
    }

    preferences.end();

    return gaugeType;
}

void Database::saveBarGaugeHighWarningValue(bar_number_t gaugeNumber, uint16_t warningValue)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUShort(String("barGaugeHW" + String(gaugeNumber)).c_str(), warningValue);

    preferences.end();
}

uint16_t Database::getBarGaugeHighWarningValue(bar_number_t gaugeNumber)
{
    uint16_t warningValue;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case BAR_1:
        warningValue = preferences.getUShort("barGaugeHW1", FUEL_LEVEL_HIGH_WARNING_DEFAULT);
        break;
    case BAR_2:
        warningValue = preferences.getUShort("barGaugeHW2", BATTERY_VOLTAGE_HIGH_WARNING_DEFAULT);
        break;
    case BAR_3:
        warningValue = preferences.getUShort("barGaugeHW3", AIR_TEMP_HIGH_WARNING_DEFAULT);
        break;
    case BAR_4:
        warningValue = preferences.getUShort("barGaugeHW4", OIL_TEMP_HIGH_WARNING_DEFAULT);
        break;
    }

    preferences.end();

    return warningValue;
}

void Database::saveBarGaugeHighAlertValue(bar_number_t gaugeNumber, uint16_t alertValue)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUShort(String("barGaugeHA" + String(gaugeNumber)).c_str(), alertValue);

    preferences.end();
}

uint16_t Database::getBarGaugeHighAlertValue(bar_number_t gaugeNumber)
{
    uint16_t alertValue;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case BAR_1:
        alertValue = preferences.getUShort("barGaugeHA1", FUEL_LEVEL_HIGH_ALERT_DEFAULT);
        break;
    case BAR_2:
        alertValue = preferences.getUShort("barGaugeHA2", BATTERY_VOLTAGE_HIGH_ALERT_DEFAULT);
        break;
    case BAR_3:
        alertValue = preferences.getUShort("barGaugeHA3", AIR_TEMP_HIGH_ALERT_DEFAULT);
        break;
    case BAR_4:
        alertValue = preferences.getUShort("barGaugeHA4", OIL_TEMP_HIGH_ALERT_DEFAULT);
        break;
    }

    preferences.end();

    return alertValue;
}

void Database::saveBarGaugeLowWarningValue(bar_number_t gaugeNumber, uint16_t warningValue)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUShort(String("barGaugeLW" + String(gaugeNumber)).c_str(), warningValue);

    preferences.end();
}

uint16_t Database::getBarGaugeLowWarningValue(bar_number_t gaugeNumber)
{
    uint16_t warningValue;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case BAR_1:
        warningValue = preferences.getUShort("barGaugeLW1", FUEL_LEVEL_LOW_WARNING_DEFAULT);
        break;
    case BAR_2:
        warningValue = preferences.getUShort("barGaugeLW2", BATTERY_VOLTAGE_LOW_WARNING_DEFAULT);
        break;
    case BAR_3:
        warningValue = preferences.getUShort("barGaugeLW3", AIR_TEMP_LOW_WARNING_DEFAULT);
        break;
    case BAR_4:
        warningValue = preferences.getUShort("barGaugeLW4", OIL_TEMP_LOW_WARNING_DEFAULT);
        break;
    }

    preferences.end();

    return warningValue;
}

void Database::saveBarGaugeLowAlertValue(bar_number_t gaugeNumber, uint16_t alertValue)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUShort(String("barGaugeLA" + String(gaugeNumber)).c_str(), alertValue);

    preferences.end();
}

uint16_t Database::getBarGaugeLowAlertValue(bar_number_t gaugeNumber)
{
    uint16_t alertValue;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case BAR_1:
        alertValue = preferences.getUShort("barGaugeLA1", FUEL_LEVEL_LOW_ALERT_DEFAULT);
        break;
    case BAR_2:
        alertValue = preferences.getUShort("barGaugeLA2", BATTERY_VOLTAGE_LOW_ALERT_DEFAULT);
        break;
    case BAR_3:
        alertValue = preferences.getUShort("barGaugeLA3", AIR_TEMP_LOW_ALERT_DEFAULT);
        break;
    case BAR_4:
        alertValue = preferences.getUShort("barGaugeLA4", OIL_TEMP_LOW_ALERT_DEFAULT);
        break;
    }

    preferences.end();

    return alertValue;
}

/*******************************************************************************
 * Arc Gauges Data
 ********************************************************************************/

void Database::saveArcGaugeType(arc_number_t gaugeNumber, gauge_type gaugeType)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUChar(String("arcGaugeType" + String(gaugeNumber)).c_str(), (uint8_t)gaugeType);

    preferences.end();
}

gauge_type Database::getArcGaugeType(arc_number_t gaugeNumber)
{
    gauge_type gaugeType;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case ARC_1:
        gaugeType = (gauge_type)preferences.getUChar("arcGaugeType1", (uint8_t)gauge_type::COOLANT_TEMP);
        break;
    case ARC_2:
        gaugeType = (gauge_type)preferences.getUChar("arcGaugeType2", (uint8_t)gauge_type::OIL_PRESSURE);
        break;
    case ARC_3:
        gaugeType = (gauge_type)preferences.getUChar("arcGaugeType3", (uint8_t)gauge_type::FUEL_PRESSURE);
        break;
    case ARC_4:
        gaugeType = (gauge_type)preferences.getUChar("arcGaugeType4", (uint8_t)gauge_type::MANIFOLD_PRESSURE);
        break;
    case ARC_5:
        gaugeType = (gauge_type)preferences.getUChar("arcGaugeType5", (uint8_t)gauge_type::AFR);
        break;
    }

    preferences.end();

    return gaugeType;
}

void Database::saveArcGaugeHighWarningValue(arc_number_t gaugeNumber, uint16_t warningValue)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUShort(String("arcGaugeHW" + String(gaugeNumber)).c_str(), warningValue);

    preferences.end();
}

uint16_t Database::getArcGaugeHighWarningValue(arc_number_t gaugeNumber)
{
    uint16_t warningValue;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case ARC_1:
        warningValue = preferences.getUShort("arcGaugeHW1", COOLANT_TEMP_HIGH_WARNING_DEFAULT);
        break;
    case ARC_2:
        warningValue = preferences.getUShort("arcGaugeHW2", OIL_PRESSURE_HIGH_WARNING_DEFAULT);
        break;
    case ARC_3:
        warningValue = preferences.getUShort("arcGaugeHW3", FUEL_PRESSURE_HIGH_WARNING_DEFAULT);
        break;
    case ARC_4:
        warningValue = preferences.getUShort("arcGaugeHW4", MANIFOLD_PRESSURE_HIGH_WARNING_DEFAULT);
        break;
    case ARC_5:
        warningValue = preferences.getUShort("arcGaugeHW5", AFR_HIGH_WARNING_DEFAULT);
        break;
    }

    preferences.end();

    return warningValue;
}

void Database::saveArcGaugeHighAlertValue(arc_number_t gaugeNumber, uint16_t alertValue)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUShort(String("arcGaugeHA" + String(gaugeNumber)).c_str(), alertValue);

    preferences.end();
}

uint16_t Database::getArcGaugeHighAlertValue(arc_number_t gaugeNumber)
{
    uint16_t alertValue;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case ARC_1:
        alertValue = preferences.getUShort("arcGaugeHA1", COOLANT_TEMP_HIGH_ALERT_DEFAULT);
        break;
    case ARC_2:
        alertValue = preferences.getUShort("arcGaugeHA2", OIL_PRESSURE_HIGH_ALERT_DEFAULT);
        break;
    case ARC_3:
        alertValue = preferences.getUShort("arcGaugeHA3", FUEL_PRESSURE_HIGH_ALERT_DEFAULT);
        break;
    case ARC_4:
        alertValue = preferences.getUShort("arcGaugeHA4", MANIFOLD_PRESSURE_HIGH_ALERT_DEFAULT);
        break;
    case ARC_5:
        alertValue = preferences.getUShort("arcGaugeHA5", AFR_HIGH_ALERT_DEFAULT);
        break;
    }

    preferences.end();

    return alertValue;
}

void Database::saveArcGaugeLowWarningValue(arc_number_t gaugeNumber, uint16_t warningValue)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUShort(String("arcGaugeLW" + String(gaugeNumber)).c_str(), warningValue);

    preferences.end();
}

uint16_t Database::getArcGaugeLowWarningValue(arc_number_t gaugeNumber)
{
    uint16_t warningValue;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case ARC_1:
        warningValue = preferences.getUShort("arcGaugeLW1", COOLANT_TEMP_LOW_WARNING_DEFAULT);
        break;
    case ARC_2:
        warningValue = preferences.getUShort("arcGaugeLW2", OIL_PRESSURE_LOW_WARNING_DEFAULT);
        break;
    case ARC_3:
        warningValue = preferences.getUShort("arcGaugeLW3", FUEL_PRESSURE_LOW_WARNING_DEFAULT);
        break;
    case ARC_4:
        warningValue = preferences.getUShort("arcGaugeLW4", 0);
        break;
    case ARC_5:
        warningValue = preferences.getUShort("arcGaugeLW5", AFR_LOW_WARNING_DEFAULT);
        break;
    }

    preferences.end();

    return warningValue;
}

void Database::saveArcGaugeLowAlertValue(arc_number_t gaugeNumber, uint16_t alertValue)
{
    preferences.begin(DATABASE_NAME, false);

    preferences.putUShort(String("arcGaugeLA" + String(gaugeNumber)).c_str(), alertValue);

    preferences.end();
}

uint16_t Database::getArcGaugeLowAlertValue(arc_number_t gaugeNumber)
{
    uint16_t alertValue;

    preferences.begin(DATABASE_NAME, true);

    switch (gaugeNumber)
    {
    case ARC_1:
        alertValue = preferences.getUShort("arcGaugeLA1", COOLANT_TEMP_LOW_ALERT_DEFAULT);
        break;
    case ARC_2:
        alertValue = preferences.getUShort("arcGaugeLA2", OIL_PRESSURE_LOW_ALERT_DEFAULT);
        break;
    case ARC_3:
        alertValue = preferences.getUShort("arcGaugeLA3", FUEL_PRESSURE_LOW_ALERT_DEFAULT);
        break;
    case ARC_4:
        alertValue = preferences.getUShort("arcGaugeLA4", 0);
        break;
    case ARC_5:
        alertValue = preferences.getUShort("arcGaugeLA5", AFR_LOW_ALERT_DEFAULT);
        break;
    }

    preferences.end();

    return alertValue;
}
