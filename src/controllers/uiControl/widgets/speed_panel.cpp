#include "speed_panel.h"

speedPanel::speedPanel()
{
    _previousSpeed = 0;
}

void speedPanel::setValue(uint16_t value)
{
    String speedValue;

    if (_previousSpeed != value)
    {
        _previousSpeed = value;

        // Add 2 ceros to the speed value
        if (value < 10)
        {
            speedValue = "00" + String(value);
        }
        else if (value < 100)
        {
            speedValue = "0" + String(value);
        }
        else
        {
            speedValue = String(value);
        }

        _ui_label_set_property(ui_SpeedValue, _UI_LABEL_PROPERTY_TEXT, speedValue.c_str());
    }
}