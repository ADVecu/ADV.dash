#include "unit_manager.h"
#include "controllers/uiControl/ui_enums.h"
#include "controllers/uiControl/ui_control.h"

// TODO: Map pressure representation in the traditional way needs Barometric pressure reading

temp_unit tempUNIT;
pressure_unit pressureUNIT;
speed_unit speedUNIT;

void initUnitManager()
{
    tempUNIT = db.getTempUnit();
    pressureUNIT = db.getPressureUnit();
    speedUNIT = db.getSpeedUnit();
};

uint16_t getTemp_Number(uint16_t value)
{
    if (tempUNIT == temp_unit::CELSIUS)
    {
        return value;
    }
    else
    {
        return (value * 9 / 5) + 32;
    }
};

String getTemp_String(uint16_t value)
{
    if (tempUNIT == temp_unit::CELSIUS)
    {
        return String(value);
    }
    else
    {
        return String((value * 9 / 5) + 32);
    }
};

uint16_t getPressure_Number(uint16_t value)
{
    switch (pressureUNIT)
    {
    case pressure_unit::KPA:
        return value;
        break;
    case pressure_unit::PSI:
        return value * 0.145037738;
        break;
    case pressure_unit::BAR:
        return value * 0.01;
        break;
    default:
        return -1;
        break;
    }
};

uint16_t getBatteryVoltage_Number(uint16_t value)
{
    return value * 0.001;
};

String getPressure_String(uint16_t value)
{
    switch (pressureUNIT)
    {
    case pressure_unit::KPA:
        return String(value);
        break;
    case pressure_unit::PSI:
        return String(value * 0.145037738);
        break;
    case pressure_unit::BAR:
        return String(value * 0.01);
        break;
    default:
        return String(-1);
        break;
    }
};

uint16_t getSpeed_Number(uint16_t value)
{
    switch (speedUNIT)
    {
    case speed_unit::KPH:
        return value;
        break;
    case speed_unit::MPH:
        return value * 0.621371192;
        break;
    default:
        return -1;
        break;
    }
};

String getSpeed_String(uint16_t value)
{
    switch (speedUNIT)
    {
    case speed_unit::KPH:
        return String(value);
        break;
    case speed_unit::MPH:
        return String(value * 0.621371192);
        break;
    default:
        return String(-1);
        break;
    }
};

String getBatteryVoltage_String(uint16_t value)
{
    return String(value * 0.001, 1);
};