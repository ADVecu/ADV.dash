#include "UI/ui.h"
#include "gp_bar.h"
#include "../ui_strings.h"

gp_bar::gp_bar(uint16_t warningValue, uint16_t alertValue, gauge_type gaugeType, bar_bg_type_t bgImg, bar_number_t bar)
{
    _warningValue = warningValue;
    _alertValue = alertValue;
    _previousValue = 0;

    gauge_name_str_single_row gauge_name_strings;
    gauge_unit_str gauge_unit_strings;

    // Assign the background image corresponding to the bar type
    switch (bgImg)
    {
    case bar_bg_type::NO_WARNING:
        _bgImg = ui_img_barscale_png;
        break;
    case bar_bg_type::RED_ALERT:
        _bgImg = ui_img_barscalered_png;
        break;
    case bar_bg_type::BLUE_RED:
        // TODO: Create a blue red bar
        _bgImg = ui_img_barscalered_png;
        break;
    }

    // Assign the bar widget, bar name and bar unit
    switch (bar)
    {
    case bar_number::BAR_1:
        _bar = ui_Bar1;
        _barUnit = ui_BarUnit1;
        _barName = ui_BarName1;
        _barBgImg = ui_BarBG1;
        break;
    case bar_number::BAR_2:
        _bar = ui_Bar2;
        _barUnit = ui_BarUnit2;
        _barName = ui_BarName2;
        _barBgImg = ui_BarBG2;
        break;
    case bar_number::BAR_3:
        _bar = ui_Bar3;
        _barUnit = ui_BarUnit3;
        _barName = ui_BarName3;
        _barBgImg = ui_BarBG3;
        break;
    case bar_number::BAR_4:
        _bar = ui_Bar4;
        _barUnit = ui_BarUnit4;
        _barName = ui_BarName4;
        _barBgImg = ui_BarBG4;
        break;
    }

    // Set the name, unit and range of the bar
    switch (gaugeType)
    {
    case gauge_type::COOLANT_TEMP:
        _name = gauge_name_strings.coolant_Temp;
        _unit = gauge_unit_strings.coolant_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        break;

    case gauge_type::OIL_TEMP:
        _name = gauge_name_strings.oil_Temp;
        _unit = gauge_unit_strings.oil_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        break;

    case gauge_type::AIR_TEMP:
        _name = gauge_name_strings.air_Temp;
        _unit = gauge_unit_strings.air_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        break;

    case gauge_type::OIL_PRESSURE:
        _name = gauge_name_strings.oil_Pressure;
        _unit = gauge_unit_strings.oil_Pressure;
        _maxValue = PRESSURE_MAX_VALUE;
        _minValue = PRESSURE_MIN_VALUE;
        break;

    case gauge_type::FUEL_PRESSURE:
        _name = gauge_name_strings.fuel_Pressure;
        _unit = gauge_unit_strings.fuel_Pressure;
        _maxValue = PRESSURE_MAX_VALUE;
        _minValue = PRESSURE_MIN_VALUE;
        break;

    case gauge_type::MANIFOLD_PRESSURE:
        _name = gauge_name_strings.manifold_Pressure;
        _unit = gauge_unit_strings.manifold_Pressure;
        _maxValue = MANIFOLD_MAX_VALUE;
        _minValue = MANIFOLD_MIN_VALUE;
        break;

    case gauge_type::BATTERY_VOLTAGE:
        _name = gauge_name_strings.battery_Voltage;
        _unit = gauge_unit_strings.battery_Voltage;
        _maxValue = VOLTAGE_MAX_VALUE;
        _minValue = VOLTAGE_MIN_VALUE;
        break;

    case gauge_type::FUEL_LEVEL:
        _name = gauge_name_strings.fuel_Level;
        _unit = gauge_unit_strings.fuel_Level;
        _maxValue = FUEL_MAX_VALUE;
        _minValue = FUEL_MIN_VALUE;
        break;

    case gauge_type::INJ_DUTY:
        _name = gauge_name_strings.inj_Duty;
        _unit = gauge_unit_strings.inj_Duty;
        _maxValue = DUTY_MAX_VALUE;
        _minValue = DUTY_MIN_VALUE;
        break;

    case gauge_type::AFR:
        _name = gauge_name_strings.afr;
        _unit = gauge_unit_strings.afr;
        _maxValue = AFR_MAX_VALUE;
        _minValue = AFR_MIN_VALUE;
        break;
    }

    // Set the bar Name
    _ui_label_set_property(_barName, _UI_LABEL_PROPERTY_TEXT, _name.c_str());

    // Set the bar Unit
    _ui_label_set_property(_barUnit, _UI_LABEL_PROPERTY_TEXT, _unit.c_str());

    // Set the bar background image
    lv_img_set_src(_barBgImg, &_bgImg);
}

void gp_bar::setValue(uint16_t value)
{
    if (_previousValue != value)
    {
        _previousValue = value;
        // Map the value to the bar length
        _ui_bar_set_property(_bar, _UI_BAR_PROPERTY_VALUE, map(value, _minValue, _maxValue, 0, 100));

        // Set the value label
        _ui_label_set_property(_barUnit, _UI_LABEL_PROPERTY_TEXT, String(value).c_str());

        // Set the bar color
        if (value >= _alertValue)
        {
            lv_obj_set_style_bg_color(_bar, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        else if (value >= _warningValue && value < _alertValue)
        {
            lv_obj_set_style_bg_color(_bar, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        else
        {
            lv_obj_set_style_bg_color(_bar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
    }
}