#include "alert_manager.h"

// CriticalPanel criticalPanel;

Alert_manager::Alert_manager()
{
    // Initialize the critical panel
    CriticalPanel criticalPanel;

    // Store alerts values from the database
    _mapHighAlert = db.getMAPHighAlertValue();
    _coolantHighAlert = db.getCoolantTempHighAlertValue();
    _oilPressureLowAlert = db.getOilPressureLowAlertValue();
    _batteryVoltageLowAlert = db.getBatteryVoltageLowAlertValue();
    _fuelPressureLowAlert = db.getFuelPressureLowAlertValue();
    _fuelLevelLowAlert = db.getFuelLevelLowAlertValue();
    _oilTempHighAlert = db.getOilTempHighAlertValue();
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
    if (rpms > 0)
    {
        isEngineRunning = true;
    }
    else
    {
        isEngineRunning = false;
    }

    // Check if the engine has been running for more than 5 seconds and check for all alerts
    if (engineONdelay.delayOn(isEngineRunning, 5000))
    {
        // Check for low oil pressure
        if ((oil_pressure * canbus_encode.pressures) < _oilPressureLowAlert)
        {
            switch (alertTimer.cycleOnOffTrigger(5000, 2000))
            {
            case 0:
                criticalPanel.HidePanel();
                break;
            case 1:
                criticalPanel.ShowPanel("Oil Pressure\nLow ", LV_PALETTE_RED);
                break;
            }
        }
        else
        {
            criticalPanel.HidePanel();
            alertTimer.cycleResetToOff();
        }
    }
}
