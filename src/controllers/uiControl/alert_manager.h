#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include <Arduino.h>
#include "widgets/critical_panel.h"
#include "database/database.h"
#include "muTimer.h"
#include "controllers/canBus/can_bus.h"
#include "ui_control.h"
#include "CircularBuffer.hpp"

#define ALERTS_SIZE 7
#define ALERTS_BUFFER_SIZE 5


enum AlertsIndex
{
    OIL_PRESSURE_ALERT,
    COOLANT_TEMP_ALERT,
    BATTERY_VOLTAGE_ALERT,
    FUEL_PRESSURE_ALERT,
    FUEL_LEVEL_ALERT,
    OIL_TEMP_ALERT,
    MAP_ALERT
};

/**
 * @brief Alert manager class
 */
class Alert_manager
{

    CriticalPanel criticalPanel;
    bool isEngineRunning = false;
    muTimer engineONdelay;
    muTimer alertTimer;
    muTimer alertHideTimer;

    uint16_t _coolantHighAlert;
    uint16_t _oilPressureLowAlert;
    uint16_t _batteryVoltageLowAlert;
    uint16_t _fuelPressureLowAlert;
    uint8_t _fuelLevelLowAlert;
    uint16_t _oilTempHighAlert;
    uint16_t _mapHighAlert;

    uint16_t _engineONrpms;
    uint16_t _alertDelay;
    uint16_t _alertDuration;
    uint16_t _alertHideDuration;

    bool _oilPressureAlert = false;
    bool _coolantTempAlert = false;
    bool _batteryVoltageAlert = false;
    bool _fuelPressureAlert = false;
    bool _fuelLevelAlert = false;
    bool _oilTempAlert = false;
    bool _mapAlert = false;

    bool _alertActive = false;

public:
    Alert_manager();

    /**
     * @brief Processes the canbus data and check for alerts
     *
     * @param rpms rpms data to determine if the engine is running
     * @param map
     * @param coolant_temp
     * @param oil_pressure
     * @param battery_voltage
     * @param fuel_pressure
     * @param fuel_level
     * @param oil_temp
     */
    void alert_manager_data(uint16_t rpms,
                            uint16_t map,
                            int8_t coolant_temp,
                            uint16_t oil_pressure,
                            uint16_t battery_voltage,
                            uint16_t fuel_pressure,
                            uint8_t fuel_level,
                            int8_t oil_temp);
};
#endif // ALERT_MANAGER_H