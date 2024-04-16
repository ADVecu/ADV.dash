#include "alert_manager.h"

CircularBuffer<byte, ALERTS_BUFFER_SIZE> alertBuffer;

Alert_manager::Alert_manager()
{
    // Initialize the critical panel
    CriticalPanel criticalPanel;

    // Store alerts values from the database
    _mapHighAlert = db.getMAPHighAlertValue();
    _coolantHighAlert = db.getCoolantTempHighAlertValue();
    _oilPressureLowAlert = db.getOilPressureLowAlertValue();
    _batteryVoltageLowAlert = (db.getBatteryVoltageLowAlertValue() / 10);
    _fuelPressureLowAlert = db.getFuelPressureLowAlertValue();
    _fuelLevelLowAlert = db.getFuelLevelLowAlertValue();
    _oilTempHighAlert = db.getOilTempHighAlertValue();

    // Store the alert delay, duration and hide duration
    _alertDelay = db.getAlertDelay();
    _alertDuration = db.getAlertDuration();
    _alertHideDuration = db.getAlertHideDuration();
    _engineONrpms = db.getEngineONrpms();
}

void Alert_manager::alert_manager_data(uint16_t rpms,
                                       uint16_t map,
                                       int8_t coolant_temp,
                                       uint16_t oil_pressure,
                                       uint16_t battery_voltage,
                                       uint16_t fuel_pressure,
                                       uint8_t fuel_level,
                                       int8_t oil_temp)

{
    // Check if the engine is running
    if (rpms > _engineONrpms)
    {
        isEngineRunning = true;
    }
    else
    {
        isEngineRunning = false;
    }

    // Check if the engine has been running for more than 5 seconds and check for all alerts
    if (engineONdelay.delayOn(isEngineRunning, _alertDelay))
    {
        // Check for alerts
        _oilPressureAlert = (oil_pressure * canbus_encode.pressures) < _oilPressureLowAlert ? true : false;
        _coolantTempAlert = (coolant_temp - canbus_encode.temps) > _coolantHighAlert ? true : false;
        _batteryVoltageAlert = (battery_voltage * canbus_encode.battery_voltage) < _batteryVoltageLowAlert ? true : false;
        _fuelPressureAlert = (fuel_pressure * canbus_encode.pressures) < _fuelPressureLowAlert ? true : false;
        _fuelLevelAlert = (fuel_level * canbus_encode.levels_duty) < _fuelLevelLowAlert ? true : false;
        _oilTempAlert = (oil_temp - canbus_encode.temps) > _oilTempHighAlert ? true : false;
        _mapAlert = (map * canbus_encode.pressures) > _mapHighAlert ? true : false;

        // add all alerts to a array
        bool alerts[ALERTS_SIZE] = {_oilPressureAlert, _coolantTempAlert, _batteryVoltageAlert, _fuelPressureAlert, _fuelLevelAlert, _oilTempAlert, _mapAlert};

        // Check if there are any alerts in the array and identify the alert
        for (int i = 0; i < ALERTS_SIZE; i++)
        {
            if (alerts[i])
            {
                if (!alertBuffer.isFull() && alertBuffer[0] != i || alertBuffer.isEmpty())
                {
                    switch (i)
                    {
                    case OIL_PRESSURE_ALERT:
                        alertBuffer.push(OIL_PRESSURE_ALERT);
                        break;
                    case COOLANT_TEMP_ALERT:
                        alertBuffer.push(COOLANT_TEMP_ALERT);
                        break;
                    case BATTERY_VOLTAGE_ALERT:
                        alertBuffer.push(BATTERY_VOLTAGE_ALERT);
                        break;
                    case FUEL_PRESSURE_ALERT:
                        alertBuffer.push(FUEL_PRESSURE_ALERT);
                        break;
                    case FUEL_LEVEL_ALERT:
                        alertBuffer.push(FUEL_LEVEL_ALERT);
                        break;
                    case OIL_TEMP_ALERT:
                        alertBuffer.push(OIL_TEMP_ALERT);
                        break;
                    case MAP_ALERT:
                        alertBuffer.push(MAP_ALERT);
                        break;
                    }

                    // Set the alert active
                    _alertActive = true;
                }
            }
        }

        // Check if there are any alerts in the buffer
        if (!alertBuffer.isEmpty() && !criticalPanel.isPanelOn() && alertHideTimer.delayOn(_alertActive, _alertHideDuration))

        {
            switch (alertBuffer[0])
            {
            case OIL_PRESSURE_ALERT:
                criticalPanel.ShowPanel("OIL PRESSURE\nLOW " + String(oil_pressure * canbus_encode.pressures) + " KPA", LV_PALETTE_RED);
                break;
            case COOLANT_TEMP_ALERT:
                criticalPanel.ShowPanel("COOLANT TEMP\nHIGH " + String(coolant_temp - canbus_encode.temps) + " °C", LV_PALETTE_RED);
                break;
            case BATTERY_VOLTAGE_ALERT:
                criticalPanel.ShowPanel("BATTERY VOLTAGE\nLOW " + String(battery_voltage * canbus_encode.battery_voltage) + "V", LV_PALETTE_RED);
                break;
            case FUEL_PRESSURE_ALERT:
                criticalPanel.ShowPanel("FUEL PRESSURE\nLOW " + String(fuel_pressure * canbus_encode.pressures) + " KPA", LV_PALETTE_RED);
                break;
            case FUEL_LEVEL_ALERT:
                criticalPanel.ShowPanel("FUEL LEVEL\nLOW " + String(fuel_level * canbus_encode.levels_duty) + " %", LV_PALETTE_RED);
                break;
            case OIL_TEMP_ALERT:
                criticalPanel.ShowPanel("OIL TEMP\nHIGH " + String(oil_temp - canbus_encode.temps) + " °C", LV_PALETTE_RED);
                break;
            case MAP_ALERT:
                criticalPanel.ShowPanel("MAP\nHIGH " + String(map * canbus_encode.pressures) + " KPA", LV_PALETTE_RED);
                break;
            }
        }

        // Hide the alert panel if the timer has expired
        if (criticalPanel.isPanelOn() && alertTimer.delayOn(_alertActive, _alertDuration))
        {
            criticalPanel.HidePanel();
            alertBuffer.shift();
            _alertActive = false;
            alertHideTimer.delayReset();
            alertTimer.delayReset();
        }
    }
    else if (_alertActive)
    {

        if (criticalPanel.isPanelOn())
            criticalPanel.HidePanel();

        alertBuffer.clear();
        _alertActive = false;
        alertHideTimer.delayReset();
        alertTimer.delayReset();
    }
}
