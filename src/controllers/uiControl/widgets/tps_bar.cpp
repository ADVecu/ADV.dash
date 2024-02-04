#include "UI/ui.h"
#include "tps_bar.h"
#include "controllers/canBus/can_bus.h"

tpsBar::tpsBar()
{
    _previousTps = 0;
}

void tpsBar::setValue(uint16_t value)
{
    int tpsValue;

    if (_previousTps != value)
    {
        _previousTps = value;
        tpsValue = (value * canbus_encode.tps);
        _ui_bar_set_property(ui_TpsBar, _UI_BAR_PROPERTY_VALUE, tpsValue);
    }
}