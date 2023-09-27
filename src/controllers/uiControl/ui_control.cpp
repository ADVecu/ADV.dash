#include "UI/ui.h"
#include "ui_control.h"
#include "database/database.h"

Database db;

rpmsBar::rpmsBar()
{
    // Get from database the redline and warning values saved by the user
    _rpmsRedline = db.getRpmsRedline();
    _rpmsWarning = db.getRpmsWarning();

    Serial.println("Redline: " + String(_rpmsRedline));
    uint8_t redlineBarValue = map(_rpmsRedline, 5000, 10000, 0, 100);
    Serial.println("Redline: " + String(_rpmsRedline) + " Bar Value: " + String(redlineBarValue));

    // Map the redline value to the bar length
    lv_bar_set_start_value(ui_RedLineBar, 50, LV_ANIM_OFF);
}

void rpmsBar::setRPMs(uint16_t rpm)
{
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
        db.saveRpmsRedline(redline);
        lv_bar_set_start_value(ui_RedLineBar, map(_rpmsRedline, 5000, 10000, 0, 100), LV_ANIM_OFF);
    }
}

void rpmsBar::setWarning(uint16_t warning)
{
    if (warning != _rpmsWarning)
    {
        _rpmsWarning = warning;
        db.saveRpmsWarning(warning);
    }
}

void ui_init_config(void)
{
    rpmsBar rpmsBar;
    rpmsBar.setRPMs(2500);
    rpmsBar.setRedline(7000);
};