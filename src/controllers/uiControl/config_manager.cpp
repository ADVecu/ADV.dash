#include "config_manager.h"

String panel_name;
byte widgetID[2];
gauge_type arc_type;

void textConfigArc(arc_number_t arc, bool setDropdown)
{

    if (setDropdown)
    {
        arc_type = db.getArcGaugeType(arc);
        lv_dropdown_clear_options(ui_GaugeType);
        lv_dropdown_set_options(ui_GaugeType, arc_options.c_str());
    }
    else
    {
         arc_type = (gauge_type)lv_dropdown_get_selected(ui_GaugeType);
    }

    panel_name = arc_config_name + arc;
    lv_textarea_set_text(ui_ConfigName, panel_name.c_str());

    widgetID[0] = widget_type::ARCW;
    widgetID[1] = arc;

    switch (arc_type)
    {
    case gauge_type::COOLANT_TEMP:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, noLow_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::COOLANT_TEMP);
        break;

    case gauge_type::OIL_TEMP:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, noLow_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::OIL_TEMP);
        break;

    case gauge_type::AIR_TEMP:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, noLow_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::AIR_TEMP);
        break;

    case gauge_type::OIL_PRESSURE:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, full_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::OIL_PRESSURE);

        break;

    case gauge_type::FUEL_PRESSURE:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, full_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::FUEL_PRESSURE);
        break;

    case gauge_type::MANIFOLD_PRESSURE:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, noLow_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::MANIFOLD_PRESSURE);
        break;

    case gauge_type::BATTERY_VOLTAGE:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, full_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::BATTERY_VOLTAGE);
        break;

    case gauge_type::FUEL_LEVEL:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, noHigh_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::FUEL_LEVEL);
        break;

    case gauge_type::INJ_DUTY:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, noLow_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::INJ_DUTY);
        break;

    case gauge_type::AFR:
        _ui_label_set_property(ui_ConfigText, _UI_LABEL_PROPERTY_TEXT, afr_settings.c_str());
        lv_dropdown_set_selected(ui_GaugeType, gauge_type::AFR);
        break;
    }
}

void dropDownChange()
{
    switch (widgetID[0])
    {
    case widget_type::ARCW:
        textConfigArc((arc_number_t)widgetID[1], false);
        break;
    }
}
