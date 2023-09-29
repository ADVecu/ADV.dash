#include "UI/ui.h"
#include "rpms_bar.h"

rpmsBar::rpmsBar(uint16_t rpmsRedline, uint16_t rpmsWarning)
{
    _rpmsRedline = rpmsRedline;
    _rpmsWarning = rpmsWarning;
    _previousRpm = 0;

    // Set the range mode and map the redline value to the bar length
    lv_bar_set_mode(ui_RedLineBar, LV_BAR_MODE_RANGE);
    lv_bar_set_start_value(ui_RedLineBar, map(_rpmsRedline, 5000, 10000, 0, 100), LV_ANIM_OFF);
}

void rpmsBar::setRPMs(uint16_t rpm)
{

    // TODO: Test Warning color change
    if (_previousRpm != rpm)
    {
        _previousRpm = rpm;
        // Map the rpm value to the bar length
        _ui_bar_set_property(ui_RpmsBar, _UI_BAR_PROPERTY_VALUE, map(rpm, 0, 10000, 0, 100));
        _ui_label_set_property(ui_RpmsValue, _UI_LABEL_PROPERTY_TEXT, String(rpm).c_str());

        if (rpm >= _rpmsRedline)
        {
            lv_obj_set_style_bg_color(ui_RpmsBar, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        else if (rpm >= _rpmsWarning && rpm < _rpmsRedline)
        {
            lv_obj_set_style_bg_color(ui_RpmsBar, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        else
        {
            lv_obj_set_style_bg_color(ui_RpmsBar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
    }
}

void rpmsBar::setRedline(uint16_t redline)
{
    if (redline != _rpmsRedline)
    {
        _rpmsRedline = redline;
        lv_bar_set_start_value(ui_RedLineBar, map(_rpmsRedline, 5000, 10000, 0, 100), LV_ANIM_OFF);
    }
}

void rpmsBar::setWarning(uint16_t warning)
{
    if (warning != _rpmsWarning)
    {
        _rpmsWarning = warning;
    }
}
