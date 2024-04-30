#include "gear_panel.h"

gearPanel::gearPanel()
{
    _previousGear = 0;
}

void gearPanel::setValue(uint8_t value)
{
    String gearValue;

    if (_previousGear != value)
    {
        _previousGear = value;

        // If gear is 0, display N
        if (value == 0)
        {
            gearValue = "N";
        }
        else
        {
            gearValue = String(value);
        }

        _ui_label_set_property(ui_GearValue, _UI_LABEL_PROPERTY_TEXT, gearValue.c_str());
    }
}