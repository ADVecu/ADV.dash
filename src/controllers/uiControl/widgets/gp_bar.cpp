#include "UI/ui.h"
#include "gp_bar.h"
#include "../ui_strings.h"
#include <muTimer.h>
#include "controllers/canBus/can_bus.h"

muTimer batteryTimer;

gp_bar::gp_bar(uint16_t highWarningValue,
               uint16_t highAlertValue,
               uint16_t lowWarningValue,
               uint16_t lowAlertValue,
               gauge_type gaugeType,
               bar_number_t bar)
{
    _warningValue = highWarningValue;
    _alertValue = highAlertValue;
    _lowWarningValue = lowWarningValue;
    _lowAlertValue = lowAlertValue;
    _previousValue = 0;
    _gaugeType = gaugeType;

    gauge_name_str_single_row gauge_name_strings;
    gauge_unit_str gauge_unit_strings;

    // Assign the bar widget, bar name and bar unit
    switch (bar)
    {
    case bar_number_t::BAR_1:
        _bar = ui_Bar1;
        _barUnit = ui_BarUnit1;
        _barName = ui_BarName1;
        _barBgImg = ui_BarBG1;
        _barValue = ui_BarValue1;
        break;
    case bar_number_t::BAR_2:
        _bar = ui_Bar2;
        _barUnit = ui_BarUnit2;
        _barName = ui_BarName2;
        _barBgImg = ui_BarBG2;
        _barValue = ui_BarValue2;
        break;
    case bar_number_t::BAR_3:
        _bar = ui_Bar3;
        _barUnit = ui_BarUnit3;
        _barName = ui_BarName3;
        _barBgImg = ui_BarBG3;
        _barValue = ui_BarValue3;
        break;
    case bar_number_t::BAR_4:
        _bar = ui_Bar4;
        _barUnit = ui_BarUnit4;
        _barName = ui_BarName4;
        _barBgImg = ui_BarBG4;
        _barValue = ui_BarValue4;
        break;
    }

    // Set the name, unit and range of the bar
    switch (_gaugeType)
    {
    case gauge_type::COOLANT_TEMP:
        _name = gauge_name_strings.coolant_Temp;
        _unit = gauge_unit_strings.coolant_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        _bgImg = ui_img_barscalerb_png;
        break;

    case gauge_type::OIL_TEMP:
        _name = gauge_name_strings.oil_Temp;
        _unit = gauge_unit_strings.oil_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        _bgImg = ui_img_barscalerb_png;
        break;

    case gauge_type::AIR_TEMP:
        _name = gauge_name_strings.air_Temp;
        _unit = gauge_unit_strings.air_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        _bgImg = ui_img_barscalerb_png;
        break;

    case gauge_type::OIL_PRESSURE:
        _name = gauge_name_strings.oil_Pressure;
        _unit = gauge_unit_strings.oil_Pressure;
        _maxValue = PRESSURE_MAX_VALUE;
        _minValue = PRESSURE_MIN_VALUE;
        _bgImg = ui_img_barscalered_png;
        break;

    case gauge_type::FUEL_PRESSURE:
        _name = gauge_name_strings.fuel_Pressure;
        _unit = gauge_unit_strings.fuel_Pressure;
        _maxValue = PRESSURE_MAX_VALUE;
        _minValue = PRESSURE_MIN_VALUE;
        _bgImg = ui_img_barscalered_png;
        break;

    case gauge_type::MANIFOLD_PRESSURE:
        _name = gauge_name_strings.manifold_Pressure;
        _unit = gauge_unit_strings.manifold_Pressure;
        _maxValue = MANIFOLD_MAX_VALUE;
        _minValue = MANIFOLD_MIN_VALUE;
        _bgImg = ui_img_barscalered_png;
        break;

    case gauge_type::BATTERY_VOLTAGE:
        _name = gauge_name_strings.battery_Voltage;
        _unit = gauge_unit_strings.battery_Voltage;
        _maxValue = VOLTAGE_MAX_VALUE;
        _minValue = VOLTAGE_MIN_VALUE;
        _bgImg = ui_img_barscalered_png;
        break;

    case gauge_type::FUEL_LEVEL:
        _name = gauge_name_strings.fuel_Level;
        _unit = gauge_unit_strings.fuel_Level;
        _maxValue = FUEL_MAX_VALUE;
        _minValue = FUEL_MIN_VALUE;
        _bgImg = ui_img_barscale_png;
        break;

    case gauge_type::INJ_DUTY:
        _name = gauge_name_strings.inj_Duty;
        _unit = gauge_unit_strings.inj_Duty;
        _maxValue = DUTY_MAX_VALUE;
        _minValue = DUTY_MIN_VALUE;
        _bgImg = ui_img_barscalered_png;
        break;

    case gauge_type::AFR:
        _name = gauge_name_strings.afr;
        _unit = gauge_unit_strings.afr;
        _maxValue = AFR_MAX_VALUE;
        _minValue = AFR_MIN_VALUE;
        _bgImg = ui_img_barscalered_png;
        break;
    }

    // Set the bar Name
    _ui_label_set_property(_barName, _UI_LABEL_PROPERTY_TEXT, _name.c_str());

    // Set the bar Unit
    _ui_label_set_property(_barUnit, _UI_LABEL_PROPERTY_TEXT, _unit.c_str());

    // Set the bar background image
    lv_img_set_src(_barBgImg, &_bgImg);
}

void gp_bar::setValue(int16_t value)
{
    float barValue;

    if (_previousValue != value)
    {
        _previousValue = value;

        // Set the value label
        switch (_gaugeType)
        {
        case gauge_type::BATTERY_VOLTAGE:

            if (batteryTimer.cycleTrigger(1000))
            {   
                barValue = (value * canbus_encode.battery_voltage);
                _ui_bar_set_property(_bar, _UI_BAR_PROPERTY_VALUE, map(value, _minValue, _maxValue, 0, 100));
                _ui_label_set_property(_barValue, _UI_LABEL_PROPERTY_TEXT, String(barValue, 1).c_str());
                barValue * 10;
            }
            break;

        case gauge_type::MANIFOLD_PRESSURE:
        case gauge_type::OIL_PRESSURE:
        case gauge_type::FUEL_PRESSURE:
            barValue = (value * canbus_encode.pressures);
            _ui_bar_set_property(_bar, _UI_BAR_PROPERTY_VALUE, map(barValue, _minValue, _maxValue, 0, 100));
            _ui_label_set_property(_barValue, _UI_LABEL_PROPERTY_TEXT, String(barValue, 0).c_str());
            break;

        case gauge_type::FUEL_LEVEL:
        case gauge_type::INJ_DUTY:
            barValue = (value * canbus_encode.levels_duty);
            _ui_bar_set_property(_bar, _UI_BAR_PROPERTY_VALUE, map(barValue, _minValue, _maxValue, 0, 100));
            _ui_label_set_property(_barValue, _UI_LABEL_PROPERTY_TEXT, String(barValue, 0).c_str());
            break;

        case gauge_type::COOLANT_TEMP:
        case gauge_type::OIL_TEMP:
        case gauge_type::AIR_TEMP:
            barValue = (value - canbus_encode.temps);
            _ui_bar_set_property(_bar, _UI_BAR_PROPERTY_VALUE, map(barValue, _minValue, _maxValue, 0, 100));
            _ui_label_set_property(_barValue, _UI_LABEL_PROPERTY_TEXT, String(barValue, 0).c_str());
            break;

        default:
            _ui_bar_set_property(_bar, _UI_BAR_PROPERTY_VALUE, map(value, _minValue, _maxValue, 0, 100));
            _ui_label_set_property(_barValue, _UI_LABEL_PROPERTY_TEXT, String(value, 0).c_str());
            break;
        }

        // Set the the high warning color change except for the fuel level gauge
        if (barValue >= _warningValue && barValue < _alertValue && _gaugeType != gauge_type::FUEL_LEVEL)
        {
            lv_obj_set_style_bg_color(_bar, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }

        // Set the the high alert color change except for the fuel level gauge
        else if (barValue >= _alertValue && _gaugeType != gauge_type::FUEL_LEVEL)
        {
            lv_obj_set_style_bg_color(_bar, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }

        // Set the low warning alert color change except for the duty cycle and manifold pressure gauges
        else if (barValue <= _lowWarningValue && barValue > _lowAlertValue && _gaugeType != gauge_type::INJ_DUTY && _gaugeType != gauge_type::MANIFOLD_PRESSURE)
        {
            switch (_gaugeType)
            {
            case gauge_type::AIR_TEMP:
            case gauge_type::COOLANT_TEMP:
            case gauge_type::OIL_TEMP:
                lv_obj_set_style_bg_color(_bar, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;

            default:
                lv_obj_set_style_bg_color(_bar, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;
            }
        }

        // Set the low alert color change except for the duty cycle and manifold pressure gauges
        else if (barValue <= _lowAlertValue && _gaugeType != gauge_type::INJ_DUTY && _gaugeType != gauge_type::MANIFOLD_PRESSURE)
        {
            switch (_gaugeType)
            {
            case gauge_type::AIR_TEMP:
            case gauge_type::COOLANT_TEMP:
            case gauge_type::OIL_TEMP:
                lv_obj_set_style_bg_color(_bar, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;

            default:
                lv_obj_set_style_bg_color(_bar, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;
            }
        }
        else // Set the default color
        {
            lv_obj_set_style_bg_color(_bar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
    }
}

void gp_bar::setHighWarningValue(uint16_t warningValue)
{
    if (warningValue != _warningValue)
    {
        _warningValue = warningValue;
    }
}

void gp_bar::setHighAlertValue(uint16_t alertValue)
{
    if (alertValue != _alertValue)
    {
        _alertValue = alertValue;
    }
}

void gp_bar::setLowWarningValue(uint16_t lowWarningValue)
{
    if (lowWarningValue != _lowWarningValue)
    {
        _lowWarningValue = lowWarningValue;
    }
}

void gp_bar::setLowAlertValue(uint16_t lowAlertValue)
{
    if (lowAlertValue != _lowAlertValue)
    {
        _lowAlertValue = lowAlertValue;
    }
}

gauge_type gp_bar::getGaugeType()
{
    return _gaugeType;
}
