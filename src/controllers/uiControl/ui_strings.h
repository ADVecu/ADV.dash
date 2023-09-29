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
    const String coolant_Temp = "Coolant\nTemp";
    const String oil_Temp = "Oil\nTemp";
    const String air_Temp = "Air\nTemp";
    const String oil_Pressure = "Oil\nPressure";
    const String fuel_Pressure = "Fuel\nPressure";
    const String manifold_Pressure = "Manifold\nPressure";
    const String battery_Voltage = "Battery\nVoltage";
    const String fuel_Level = "Fuel\nLevel";
    const String inj_Duty = "Inj\nDuty";
    const String afr = "AFR";
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
