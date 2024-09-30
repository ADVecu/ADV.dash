#include "UI/ui.h"
#include "gp_panel.h"
#include <muTimer.h>
#include "controllers/canBus/can_bus.h"


muTimer batteryTimerPanel;

gp_panel::gp_panel(uint16_t alertValue,
                   gauge_type gaugeType,
                   panel_number_t panel)
{
    _alertValue = alertValue;
    _previousValue = 0;
    _gaugeType = gaugeType;

    panel_name_str panel_name_strings;
    gauge_unit_str unit_name_strings;

    // Assign the panel widget, panel name and panel unit
    switch (panel)
    {
    case panel_number::PANEL_1:
        _panel = ui_Panel1;
        _panelName = ui_PanelName1;
        _panelValue = ui_PanelValue1;
        break;
    case panel_number::PANEL_2:
        _panel = ui_Panel2;
        _panelName = ui_PanelName2;
        _panelValue = ui_PanelValue2;
        break;
    case panel_number::PANEL_3:
        _panel = ui_Panel3;
        _panelName = ui_PanelName3;
        _panelValue = ui_PanelValue3;
        break;
    case panel_number::PANEL_4:
        _panel = ui_Panel4;
        _panelName = ui_PanelName4;
        _panelValue = ui_PanelValue4;
        break;
    case panel_number::PANEL_5:
        _panel = ui_Panel5;
        _panelName = ui_PanelName5;
        _panelValue = ui_PanelValue5;
        break;
    case panel_number::PANEL_6:
        _panel = ui_Panel6;
        _panelName = ui_PanelName6;
        _panelValue = ui_PanelValue6;
        break;
    }

    // Set the name of the panel
    switch (_gaugeType)
    {
    case gauge_type::COOLANT_TEMP:
        _name = panel_name_strings.coolant_Temp;
        break;
    case gauge_type::OIL_TEMP:
        _name = panel_name_strings.oil_Temp;
        break;
    case gauge_type::AIR_TEMP:
        _name = panel_name_strings.air_Temp;
        break;
    case gauge_type::OIL_PRESSURE:
        _name = panel_name_strings.oil_Pressure;
        break;
    case gauge_type::FUEL_PRESSURE:
        _name = panel_name_strings.fuel_Pressure;
        break;
    case gauge_type::MANIFOLD_PRESSURE:
        _name = panel_name_strings.manifold_Pressure;
        break;
    case gauge_type::BATTERY_VOLTAGE:
        _name = panel_name_strings.battery_Voltage;
        break;
    case gauge_type::FUEL_LEVEL:
        _name = panel_name_strings.fuel_Level;
        break;
    case gauge_type::INJ_DUTY:
        _name = panel_name_strings.inj_Duty;
        break;
    case gauge_type::AFR:
        _name = panel_name_strings.afr;
        break;
    case gauge_type::WARNING_COUNT:
        _name = panel_name_strings.warning_Count;
        break;
    case gauge_type::ING_TIMING:
        _name = panel_name_strings.ing_Timing;
        break;
    case gauge_type::INJ_PWM:
        _name = panel_name_strings.inj_PWM;
        break;
    case gauge_type::IGN_DUTY:
        _name = panel_name_strings.ign_duty;
        break;
    case gauge_type::MCU_TEMP:
        _name = panel_name_strings.mcu_temp;
        break;
    case gauge_type::AMBIENT_TEMP:
        _name = panel_name_strings.ambient_Temp;
        break;
    case gauge_type::FW_PRESS:
        _name = panel_name_strings.fw_Press;
        break;
    case gauge_type::FW_TEMP:
        _name = panel_name_strings.fw_Temp;
        break;
    case gauge_type::RW_PRESS:
        _name = panel_name_strings.rw_Press;
        break;
    case gauge_type::RW_TEMP:
        _name = panel_name_strings.rw_Temp;
        break;
    case gauge_type::FUEL_TRIM:
        _name = panel_name_strings.fuel_Trim;
        break;
    case gauge_type::FUEL_FLOW:
        _name = panel_name_strings.fuel_Flow;
        break;
    case gauge_type::FUEL_USED:
        _name = panel_name_strings.fuel_Used;
        break;

    }

    // Set the panel name
    _ui_label_set_property(_panelName, _UI_LABEL_PROPERTY_TEXT, _name.c_str());
}

void gp_panel::setValue(int16_t value)
{

    float panelValue;

    if (_previousValue != value )
    {
        _previousValue = value;

        // Set the panel value
        switch (_gaugeType)
        {
        case gauge_type::BATTERY_VOLTAGE:


            if (batteryTimerPanel.cycleTrigger(1000))
            {
                panelValue = (value * canbus_encode.battery_voltage);
                _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 1).c_str());
                panelValue * 10;
            }
            break;

        case gauge_type::AFR:
            panelValue = (value * canbus_encode.afr);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 1).c_str());
            panelValue * 10;
            break;
        
        case gauge_type::INJ_DUTY:
        case gauge_type::IGN_DUTY:
            panelValue = (value * canbus_encode.levels_duty);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 0).c_str());
            break;
        
        case gauge_type::ING_TIMING:
            panelValue = (value * canbus_encode.ign_advance);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 1).c_str());
            break;
    
        case gauge_type::INJ_PWM:
            panelValue = (value * canbus_encode.pwm);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 1).c_str());
            break;
        
        case gauge_type::COOLANT_TEMP:
        case gauge_type::OIL_TEMP:
        case gauge_type::MCU_TEMP:
        case gauge_type::AIR_TEMP:
            panelValue = (value - canbus_encode.temps);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 0).c_str());
            break;
        
        case gauge_type::FW_PRESS:
        case gauge_type::RW_PRESS:
            panelValue = (value * canbus_encode.tyre_press);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 1).c_str());
            break;
        
        case gauge_type::FUEL_TRIM:
            panelValue = (value * canbus_encode.tps);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 2).c_str());
            break;

        case gauge_type::FUEL_FLOW:
            panelValue = (value * canbus_encode.fuel_flow);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 2).c_str());
            break;

        case gauge_type::FW_TEMP:
        case gauge_type::RW_TEMP:
            panelValue = (value - canbus_encode.tyre_temp);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 0).c_str());
            break;

        case gauge_type::FUEL_USED:
            panelValue = (value / 730);
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(panelValue, 2).c_str());
            break;

        default:
            _ui_label_set_property(_panelValue, _UI_LABEL_PROPERTY_TEXT, String(value).c_str());
            break;
        }

        // Set the panel color
        if (panelValue >= _alertValue && _gaugeType != gauge_type::FUEL_LEVEL)
        {
            lv_obj_set_style_border_color(_panel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else
        {
            lv_obj_set_style_border_color(_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        
    }
}

void gp_panel::setAlert(uint16_t alertValue)
{
    if (alertValue != _alertValue)
    {
        _alertValue = alertValue;
    }
}

gauge_type gp_panel::getGaugeType()
{
    return _gaugeType;
}