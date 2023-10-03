#include "UI/ui.h"
#include "gp_arc.h"
#include "../ui_strings.h"
#include <muTimer.h>

muTimer batteryTimerARC;

gp_arc::gp_arc(uint16_t highWarningValue,
               uint16_t highAlertValue,
               uint16_t lowWarningValue,
               uint16_t lowAlertValue,
               gauge_type gaugeType,
               arc_number_t arc)
{
    _warningValue = highWarningValue;
    _alertValue = highAlertValue;
    _lowWarningValue = lowWarningValue;
    _lowAlertValue = lowAlertValue;
    _previousValue = 0;
    _gaugeType = gaugeType;

    gauge_name_str_double_row gauge_name_strings;
    gauge_unit_str gauge_unit_strings;

    // Assign the arc widget, arc name and arc unit
    switch (arc)
    {
    case arc_number::ARC_1:
        _arc = ui_Arc1;
        _arcUnit = ui_ArcUnit1;
        _arcName = ui_ArcName1;
        _arcBgImg = ui_ArcBG1;
        _arcValue = ui_ArcValue1;
        break;
    case arc_number::ARC_2:
        _arc = ui_Arc2;
        _arcUnit = ui_ArcUnit2;
        _arcName = ui_ArcName2;
        _arcBgImg = ui_ArcBG2;
        _arcValue = ui_ArcValue2;
        break;
    case arc_number::ARC_3:
        _arc = ui_Arc3;
        _arcUnit = ui_ArcUnit3;
        _arcName = ui_ArcName3;
        _arcBgImg = ui_ArcBG3;
        _arcValue = ui_ArcValue3;
        break;
    case arc_number::ARC_4:
        _arc = ui_Arc4;
        _arcUnit = ui_ArcUnit4;
        _arcName = ui_ArcName4;
        _arcBgImg = ui_ArcBG4;
        _arcValue = ui_ArcValue4;
        break;
    case arc_number::ARC_5:
        _arc = ui_Arc5;
        _arcUnit = ui_ArcUnit5;
        _arcName = ui_ArcName5;
        _arcBgImg = ui_ArcBG5;
        _arcValue = ui_ArcValue5;
        break;
    }

    // Set the name, unit and range of the arc
    switch (_gaugeType)
    {
    case gauge_type::COOLANT_TEMP:
        _unit = gauge_unit_strings.coolant_Temp;
        _name = gauge_name_strings.coolant_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::OIL_TEMP:
        _unit = gauge_unit_strings.oil_Temp;
        _name = gauge_name_strings.oil_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::AIR_TEMP:
        _unit = gauge_unit_strings.air_Temp;
        _name = gauge_name_strings.air_Temp;
        _maxValue = TEMP_MAX_VALUE;
        _minValue = TEMP_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::OIL_PRESSURE:
        _unit = gauge_unit_strings.oil_Pressure;
        _name = gauge_name_strings.oil_Pressure;
        _maxValue = PRESSURE_MAX_VALUE;
        _minValue = PRESSURE_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::FUEL_PRESSURE:
        _unit = gauge_unit_strings.fuel_Pressure;
        _name = gauge_name_strings.fuel_Pressure;
        _maxValue = PRESSURE_MAX_VALUE;
        _minValue = PRESSURE_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::MANIFOLD_PRESSURE:
        _unit = gauge_unit_strings.manifold_Pressure;
        _name = gauge_name_strings.manifold_Pressure;
        _maxValue = MANIFOLD_MAX_VALUE;
        _minValue = MANIFOLD_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::BATTERY_VOLTAGE:
        _unit = gauge_unit_strings.battery_Voltage;
        _name = gauge_name_strings.battery_Voltage;
        _maxValue = VOLTAGE_MAX_VALUE;
        _minValue = VOLTAGE_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::FUEL_LEVEL:
        _unit = gauge_unit_strings.fuel_Level;
        _name = gauge_name_strings.fuel_Level;
        _maxValue = FUEL_MAX_VALUE;
        _minValue = FUEL_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::INJ_DUTY:
        _unit = gauge_unit_strings.inj_Duty;
        _name = gauge_name_strings.inj_Duty;
        _maxValue = DUTY_MAX_VALUE;
        _minValue = DUTY_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;

    case gauge_type::AFR:
        _unit = gauge_unit_strings.afr;
        _name = gauge_name_strings.afr;
        _maxValue = AFR_MAX_VALUE;
        _minValue = AFR_MIN_VALUE;
        _bgImg = ui_img_arcscalenored_png;
        break;
    }

    // Set the arc name
    _ui_label_set_property(_arcName, _UI_LABEL_PROPERTY_TEXT, _name.c_str());

    // Set the arc unit
    _ui_label_set_property(_arcUnit, _UI_LABEL_PROPERTY_TEXT, _unit.c_str());

    // Set the arc background image
    lv_img_set_src(_arcBgImg, &_bgImg);
}

void gp_arc::setValue(uint16_t value)
{

    if (_previousValue != value)
    {
        _previousValue = value;
        switch (_gaugeType)
        {
        case gauge_type::BATTERY_VOLTAGE:
            if (batteryTimerARC.cycleTrigger(1000))
            {
                lv_arc_set_value(_arc, map(value, _minValue, _maxValue, 0, 100));
                _ui_label_set_property(_arcValue, _UI_LABEL_PROPERTY_TEXT, String((float)value / 1000.0, 1).c_str());
            }
            break;

        default:
            lv_arc_set_value(_arc, map(value, _minValue, _maxValue, 0, 100));
            _ui_label_set_property(_arcValue, _UI_LABEL_PROPERTY_TEXT, String(value).c_str());
            break;
        }

        // Set the the high warning color change except for the fuel level gauge
        if (value >= _warningValue && value < _alertValue && _gaugeType != gauge_type::FUEL_LEVEL)
        {
            lv_obj_set_style_arc_color(_arc, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }

        // Set the the high alert color change except for the fuel level gauge
        else if (value >= _alertValue && _gaugeType != gauge_type::FUEL_LEVEL)
        {
            lv_obj_set_style_arc_color(_arc, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }

        // Set the low warning alert color change except for the duty cycle and manifold pressure gauges
        else if (value <= _lowWarningValue && value > _lowAlertValue && _gaugeType != gauge_type::INJ_DUTY && _gaugeType != gauge_type::MANIFOLD_PRESSURE)
        {
            switch (_gaugeType)
            {
            case gauge_type::AIR_TEMP:
            case gauge_type::COOLANT_TEMP:
            case gauge_type::OIL_TEMP:
                lv_obj_set_style_arc_color(_arc, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;

            default:
                lv_obj_set_style_arc_color(_arc, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;
            }
        }

        // Set the low alert color change except for the duty cycle and manifold pressure gauges
        else if (value <= _lowAlertValue && _gaugeType != gauge_type::INJ_DUTY && _gaugeType != gauge_type::MANIFOLD_PRESSURE)
        {
            switch (_gaugeType)
            {
            case gauge_type::AIR_TEMP:
            case gauge_type::COOLANT_TEMP:
            case gauge_type::OIL_TEMP:
                lv_obj_set_style_arc_color(_arc, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;

            default:
                lv_obj_set_style_arc_color(_arc, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;
            }
        }
        else // Set the default color
        {
            lv_obj_set_style_arc_color(_arc, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
    }
}

void gp_arc::setHighWarningValue(uint16_t warningValue)
{
    if (warningValue != _warningValue)
    {
        _warningValue = warningValue;
    }
}

void gp_arc::setHighAlertValue(uint16_t alertValue)
{
    if (alertValue != _alertValue)
    {
        _alertValue = alertValue;
    }
}

void gp_arc::setLowWarningValue(uint16_t lowWarningValue)
{
    if (lowWarningValue != _lowWarningValue)
    {
        _lowWarningValue = lowWarningValue;
    }
}

void gp_arc::setLowAlertValue(uint16_t lowAlertValue)
{
    if (lowAlertValue != _lowAlertValue)
    {
        _lowAlertValue = lowAlertValue;
    }
}

gauge_type gp_arc::getGaugeType()
{
    return _gaugeType;
}
