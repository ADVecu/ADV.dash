#include "UI/ui.h"
#include "tps_bar.h"

tpsBar::tpsBar()
{
    _previousTps = 0;
}

void tpsBar::setValue(uint16_t value)
{
    if (_previousTps != value)
    {
        _previousTps = value;
        _ui_bar_set_property(ui_TpsBar, _UI_BAR_PROPERTY_VALUE, map(value, 0, 10000, 0, 100));
    }
}