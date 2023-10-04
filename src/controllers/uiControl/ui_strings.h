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
    const String fuel_Trim = "TRIM";
    const String fuel_Flow = "FLOW";
    const String fuel_Used = "USED";
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
