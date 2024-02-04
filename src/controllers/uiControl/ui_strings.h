#ifndef _UI_STRINGS_H
#define _UI_STRINGS_H

#include <Arduino.h>

struct gauge_name_str_single_row
{
    const String coolant_Temp = "Coolant Temp";
    const String oil_Temp = "Oil Temp";
    const String air_Temp = "Air Temp";
    const String oil_Pressure = "Oil Pressure";
    const String fuel_Pressure = "Fuel Pressure";
    const String manifold_Pressure = "Manifold Pressure";
    const String battery_Voltage = "Battery Voltage";
    const String fuel_Level = "Fuel Level";
    const String inj_Duty = "Inj Duty";
    const String afr = "AFR";
};

struct gauge_name_str_double_row
{
    const String coolant_Temp = "Water\nTemp";
    const String oil_Temp = "Oil\nTemp";
    const String air_Temp = "Air\nTemp";
    const String oil_Pressure = "Oil\nPressure";
    const String fuel_Pressure = "Fuel\nPressure";
    const String manifold_Pressure = "Map\nPressure";
    const String battery_Voltage = "Battery\nVoltage";
    const String fuel_Level = "Fuel\nLevel";
    const String inj_Duty = "Inj\nDuty";
    const String afr = "AFR";
};

struct panel_name_str
{
    const String coolant_Temp = "WTEMP";
    const String oil_Temp = "OILT";
    const String air_Temp = "AIRT";
    const String oil_Pressure = "OILP";
    const String fuel_Pressure = "FUELP";
    const String manifold_Pressure = "MAP";
    const String battery_Voltage = "BATT";
    const String fuel_Level = "FL";
    const String inj_Duty = "DUTY";
    const String afr = "AFR";
    const String warning_Count = "WARN";
    const String ing_Timing = "ADV";
    const String inj_PWM = "PWM";
    const String ign_duty = "DUTY";
    const String mcu_temp = "MCUT";
    
};

struct gauge_unit_str
{
    const String coolant_Temp = "°C";
    const String oil_Temp = "°C";
    const String air_Temp = "°C";
    const String oil_Pressure = "kPa";
    const String fuel_Pressure = "kPa";
    const String manifold_Pressure = "kPa";
    const String battery_Voltage = "V";
    const String fuel_Level = "%";
    const String inj_Duty = "%";
    const String afr = "AFR";
};

struct settings_strings
{
    const String RpmsWAText = "Rpms Warning Alert =";
    const String RpmsDAText = "Red Line Alert =";
    const String HWAText = "High Warning Alert =";
    const String HAText = "High Danger Alert =";
    const String LWAText = "Low Warning Alert =";
    const String LDAText = "Low Danger Alert =";
    const String TempLWAText = "Engine Cold Temp =";
    const String WAText = "Warning Alert =";
    const String DAText = "Danger Alert =";
    const String WALevelText = "Warning Alert Level =";
    const String DALevelText = "Danger Alert Level =";
};

const String bar_number_options = "Bar 1\nBar 2\nBar 3\nBar 4";
const String arc_number_options = "Arc 1\nArc 2\nArc 3\nArc 4\nArc 5";
const String bar_options = "Coolant Temp\nOil Temp\nAir Temp\nOil Pressure\nFuel Pressure\nManifold Pressure\nBattery Voltage\nFuel Level\nInj Duty";
const String arc_options = "Coolant Temp\nOil Temp\nAir Temp\nOil Pressure\nFuel Pressure\nManifold Pressure\nBattery Voltage\nFuel Level\nInj Duty\nAFR";
const String panel_options = "Coolant Temp\nOil Temp\nAir Temp\nOil Pressure\nFuel Pressure\nManifold Pressure\nBattery Voltage\nFuel Level\nInj Duty\nAFR\nWarning Count\nIng Timing\nInj PWM\nFuel Trim\nFuel Flow\nFuel Used";
const String panel_number_options = "Panel 1\nPanel 2\nPanel 3\nPanel 4\nPanel 5\nPanel 6";

#endif