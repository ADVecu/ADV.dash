
#include "UI/ui.h"
#include "database/database.h"
#include "ui_control.h"
#include "../canBus/can_bus.h"
#include "ui_enums.h"
#include "ui_strings.h"
#include "unit_manager.h"
#include "../wLed/led_control.h"
#include "pcb_definitions.h"
#include "controllers/rtc/rtc_control.h"
#include "controllers/sensors/bmp280.h"
#include <muTimer.h>
#include "controllers/canBus/rus_efi_can_verbose.h"

// Widgets
#include "widgets/rpms_bar.h"
#include "widgets/gp_bar.h"
#include "widgets/gp_arc.h"
#include "widgets/gp_panel.h"
#include "widgets/tps_bar.h"

// Database instance
Database db;

// CAN bus data queue
QueueSetHandle_t canbus_queue;

muTimer welcomeInfoTimer;
muTimer mainScreenClockTimer;
muTimer panelDataRate;
muTimer barDataRate;
muTimer DataRate;

rtc_date dateUI;
rtc_time timeUI;

rtc_control rtc_UI;

bmp280 atmosphericSensor;
atmospheric_data atmosphericData;

/**
 * @brief Initialize the UI configuration
 */
void ui_init_config()
{
    // create the task to handle the UI values refresh
    xTaskCreatePinnedToCore(
        ui_task,      /* Function to implement the task */
        "ui_task",    /* Name of the task */
        10000,        /* Stack size in words */
        NULL,         /* Task input parameter */
        0,            /* Priority of the task */
        NULL,         /* Task handle. */
        APP_CPU_NUM); /* Core where the task should run */
}

/**
 * @brief UI task
 *
 * @param pvParameters
 */
void ui_task(void *pvParameters)
{
    // Initialize the CAN message struct
    canbus_data_t rx_msg;

    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;
    bool firstTimeRpms = true;
    bool firstTimeBars = true;
    bool firstTimeArcs = true;
    bool firstTimePanels = true;
    bool barChanged = true;
    bool barTypeChanged = true;
    bool arcChanged = true;
    bool arcTypeChanged = true;
    bool panelChanged = true;
    bool panelTypeChanged = true;
    uint8_t previousBarNumber = 20;
    uint8_t previousBarType = 20;
    uint8_t previousArcNumber = 20;
    uint8_t previousArcType = 20;
    uint8_t previousPanelNumber = 20;
    uint8_t previousPanelType = 20;
    settings_strings settings_strings;

    // Initialize all the widgets and set the initial values

    // RPMS Bar
    rpmsBar rpmsBar(db.getRpmsRedline(), db.getRpmsWarning());

    // TPS Bar
    tpsBar tpsBar;

    // Bar gauges
    gp_bar gp_Bar_1(bar_number_t::BAR_1);

    gp_bar gp_Bar_2(bar_number_t::BAR_2);

    gp_bar gp_Bar_3(bar_number_t::BAR_3);

    gp_bar gp_Bar_4(bar_number_t::BAR_4);

    gp_bar gp_bar_array[4] = {gp_Bar_1, gp_Bar_2, gp_Bar_3, gp_Bar_4};

    // Arc gauges
    gp_arc gp_Arc_1(arc_number_t::ARC_1);

    gp_arc gp_Arc_2(arc_number_t::ARC_2);

    gp_arc gp_Arc_3(arc_number_t::ARC_3);

    gp_arc gp_Arc_4(arc_number_t::ARC_4);

    gp_arc gp_Arc_5(arc_number_t::ARC_5);

    gp_arc gp_arc_array[5] = {gp_Arc_1, gp_Arc_2, gp_Arc_3, gp_Arc_4, gp_Arc_5};

    // Panel gauges
    gp_panel gp_Panel_1(db.getPanelGaugeAlertValue(panel_number_t::PANEL_1),
                        db.getPanelGaugeType(panel_number_t::PANEL_1),
                        panel_number_t::PANEL_1);

    gp_panel gp_Panel_2(db.getPanelGaugeAlertValue(panel_number_t::PANEL_2),
                        db.getPanelGaugeType(panel_number_t::PANEL_2),
                        panel_number_t::PANEL_2);

    gp_panel gp_Panel_3(db.getPanelGaugeAlertValue(panel_number_t::PANEL_3),
                        db.getPanelGaugeType(panel_number_t::PANEL_3),
                        panel_number_t::PANEL_3);

    gp_panel gp_Panel_4(db.getPanelGaugeAlertValue(panel_number_t::PANEL_4),
                        db.getPanelGaugeType(panel_number_t::PANEL_4),
                        panel_number_t::PANEL_4);

    gp_panel gp_Panel_5(db.getPanelGaugeAlertValue(panel_number_t::PANEL_5),
                        db.getPanelGaugeType(panel_number_t::PANEL_5),
                        panel_number_t::PANEL_5);

    gp_panel gp_Panel_6(db.getPanelGaugeAlertValue(panel_number_t::PANEL_6),
                        db.getPanelGaugeType(panel_number_t::PANEL_6),
                        panel_number_t::PANEL_6);

    gp_panel gp_panel_array[6] = {gp_Panel_1, gp_Panel_2, gp_Panel_3, gp_Panel_4, gp_Panel_5, gp_Panel_6};

    // Leds control
    led_control leds;

    bool canReady = false;

    // Serial.println(db.getRpmsRedline());
    //  Infinite loop
    while (1)
    {

        // Read the CAN bus queue
        if (xQueueReceive(canbus_queue, &rx_msg, 1000) == pdTRUE && lv_scr_act() == ui_MainScreen)
        {
            // Set the flag to true
            canReady = true;

            if (DataRate.cycleTrigger(50))
            {
                // Update the rpms bar
                rpmsBar.setRPMs(rx_msg.rpms);

                // Update the tps bar
                tpsBar.setValue(rx_msg.tps);

                // iterate through the arc gauges and update the values
                for (j = 0; j < 5; j++)
                {
                    switch (gp_arc_array[j].getGaugeType())
                    {
                    case gauge_type::COOLANT_TEMP:
                        gp_arc_array[j].setValue(rx_msg.coolant_temp);
                        break;
                    case gauge_type::OIL_TEMP:
                        gp_arc_array[j].setValue(rx_msg.aux1_temp);
                        break;
                    case gauge_type::AIR_TEMP:
                        gp_arc_array[j].setValue(rx_msg.air_temp);
                        break;
                    case gauge_type::OIL_PRESSURE:
                        gp_arc_array[j].setValue(rx_msg.oil_pressure);
                        break;
                    case gauge_type::FUEL_PRESSURE:
                        gp_arc_array[j].setValue(rx_msg.fuel_pressure);
                        break;
                    case gauge_type::BATTERY_VOLTAGE:
                        gp_arc_array[j].setValue(rx_msg.battery_voltage);
                        break;
                    case gauge_type::FUEL_LEVEL:
                        gp_arc_array[j].setValue(rx_msg.fuel_level);
                        break;
                    case gauge_type::INJ_DUTY:
                        gp_arc_array[j].setValue(rx_msg.inj_duty);
                        break;
                    case gauge_type::MANIFOLD_PRESSURE:
                        gp_arc_array[j].setValue(rx_msg.map);
                        break;
                    case gauge_type::AFR:
                        gp_arc_array[j].setValue(rx_msg.o2_sensor);
                        break;
                    }
                }
            }

            // iterate through the bar gauges and update the values
            if (barDataRate.cycleTrigger(200))
            {
                for (i = 0; i < 4; i++)
                {
                    switch (gp_bar_array[i].getGaugeType())
                    {
                    case gauge_type::COOLANT_TEMP:
                        gp_bar_array[i].setValue(rx_msg.coolant_temp);
                        break;
                    case gauge_type::OIL_TEMP:
                        gp_bar_array[i].setValue(rx_msg.aux1_temp);
                        break;
                    case gauge_type::AIR_TEMP:
                        gp_bar_array[i].setValue(rx_msg.air_temp);
                        break;
                    case gauge_type::OIL_PRESSURE:
                        gp_bar_array[i].setValue(rx_msg.oil_pressure);
                        break;
                    case gauge_type::FUEL_PRESSURE:
                        gp_bar_array[i].setValue(rx_msg.fuel_pressure);
                        break;
                    case gauge_type::BATTERY_VOLTAGE:
                        gp_bar_array[i].setValue(rx_msg.battery_voltage);
                        break;
                    case gauge_type::FUEL_LEVEL:
                        gp_bar_array[i].setValue(rx_msg.fuel_level);
                        break;
                    case gauge_type::INJ_DUTY:
                        gp_bar_array[i].setValue(rx_msg.inj_duty);
                        break;
                    case gauge_type::MANIFOLD_PRESSURE:
                        gp_bar_array[i].setValue(rx_msg.map);
                        break;
                    }
                }
            }

            // iterate through the panel gauges and update the values
            if (panelDataRate.cycleTrigger(200))
            {
                for (k = 0; k < 6; k++)
                {
                    switch (gp_panel_array[k].getGaugeType())
                    {
                    case gauge_type::COOLANT_TEMP:
                        gp_panel_array[k].setValue(rx_msg.coolant_temp);
                        break;
                    case gauge_type::OIL_TEMP:
                        gp_panel_array[k].setValue(rx_msg.aux1_temp);
                        break;
                    case gauge_type::AIR_TEMP:
                        gp_panel_array[k].setValue(rx_msg.air_temp);
                        break;
                    case gauge_type::OIL_PRESSURE:
                        gp_panel_array[k].setValue(rx_msg.oil_pressure);
                        break;
                    case gauge_type::FUEL_PRESSURE:
                        gp_panel_array[k].setValue(rx_msg.fuel_pressure);
                        break;
                    case gauge_type::BATTERY_VOLTAGE:
                        gp_panel_array[k].setValue(rx_msg.battery_voltage);
                        break;
                    case gauge_type::FUEL_LEVEL:
                        gp_panel_array[k].setValue(rx_msg.fuel_level);
                        break;
                    case gauge_type::INJ_DUTY:
                        gp_panel_array[k].setValue(rx_msg.inj_duty);
                        break;
                    case gauge_type::MANIFOLD_PRESSURE:
                        gp_panel_array[k].setValue(rx_msg.map);
                        break;
                    case gauge_type::AFR:
                        gp_panel_array[k].setValue(rx_msg.o2_sensor);
                        break;
                    case gauge_type::WARNING_COUNT:
                        gp_panel_array[k].setValue(rx_msg.warning_counter);
                        break;
                    case gauge_type::ING_TIMING:
                        gp_panel_array[k].setValue(rx_msg.ignition_timing);
                        break;
                    case gauge_type::INJ_PWM:
                        gp_panel_array[k].setValue(rx_msg.inj_pwm);
                        break;
                    case gauge_type::IGN_DUTY:
                        gp_panel_array[k].setValue(rx_msg.ing_duty);
                        break;
                    case gauge_type::MCU_TEMP:
                        gp_panel_array[k].setValue(rx_msg.mcu_temp);
                        break;
                    }
                }
            }
        }
        else
        {
            canReady = false;
        }

        // If the settins screen is active
        if (lv_scr_act() == ui_SettingsScreen)
        {
            // Get the roller active item
            switch (lv_roller_get_selected(ui_Roller))
            {
            case 0: // Rpms settings
                if (firstTimeRpms)
                {
                    _ui_flag_modify(ui_SelectPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                    _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                    _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                    _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.RpmsWAText.c_str());
                    _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.RpmsDAText.c_str());
                    lv_slider_set_range(ui_HWASlider, 0, 10000);
                    lv_slider_set_range(ui_HDASlider, 5000, 10000);
                    _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, db.getRpmsWarning());
                    _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, db.getRpmsRedline());
                    _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getRpmsWarning()).c_str());
                    _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getRpmsRedline()).c_str());
                    firstTimeRpms = false;
                    firstTimeArcs = true;
                    firstTimeBars = true;
                    firstTimePanels = true;
                }
                break;
            case 1:
            { // Bars

                if (firstTimeBars)
                {
                    // Show the select panel
                    _ui_flag_modify(ui_SelectPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                    _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                    _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                    // Setup the dropdowns
                    lv_dropdown_clear_options(ui_GaugeNumberD);
                    lv_dropdown_set_options(ui_GaugeNumberD, bar_number_options.c_str());
                    lv_dropdown_set_selected(ui_GaugeNumberD, 0);
                    lv_dropdown_clear_options(ui_GaugeTypeD);
                    lv_dropdown_set_options(ui_GaugeTypeD, bar_options.c_str());
                    lv_dropdown_set_selected(ui_GaugeTypeD, (int)(db.getBarGaugeType(bar_number_t::BAR_1)));
                }

                uint8_t rawBarNumber = (uint8_t)(lv_dropdown_get_selected(ui_GaugeNumberD) + 1);
                bar_number_t selectedGaugeNum = (bar_number_t)rawBarNumber;
                gauge_type selectedGaugeType = (gauge_type)lv_dropdown_get_selected(ui_GaugeTypeD);

                if (previousBarNumber != lv_dropdown_get_selected(ui_GaugeNumberD))
                {
                    barChanged = true;
                    previousBarNumber = lv_dropdown_get_selected(ui_GaugeNumberD);
                    lv_dropdown_set_selected(ui_GaugeTypeD, (int)(db.getBarGaugeType(selectedGaugeNum)));
                }

                if (previousBarType != lv_dropdown_get_selected(ui_GaugeTypeD) || barChanged)
                {
                    barTypeChanged = true;
                    previousBarType = lv_dropdown_get_selected(ui_GaugeTypeD);
                    selectedGaugeType = (gauge_type)lv_dropdown_get_selected(ui_GaugeTypeD);
                }

                // Set the options for each gauge type possible for BAR 1
                if (barChanged || barTypeChanged)
                {
                    switch (selectedGaugeType)
                    {
                    case gauge_type::COOLANT_TEMP:
                    case gauge_type::OIL_TEMP:
                    case gauge_type::AIR_TEMP:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HWAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HAText.c_str());
                        _ui_label_set_property(ui_LWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.TempLWAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x050154), LV_PART_MAIN | LV_STATE_DEFAULT);

                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0x0000FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0x0000FF), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, getTemp_Number(TEMP_MIN_VALUE), getTemp_Number(TEMP_MAX_VALUE));
                        lv_slider_set_range(ui_HDASlider, getTemp_Number(TEMP_MIN_VALUE), getTemp_Number(TEMP_MAX_VALUE));
                        lv_slider_set_range(ui_LWASlider, getTemp_Number(TEMP_MIN_VALUE), getTemp_Number(TEMP_MAX_VALUE));

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, getTemp_Number(db.getBarGaugeHighWarningValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, getTemp_Number(db.getBarGaugeHighAlertValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_LWASlider, _UI_SLIDER_PROPERTY_VALUE, getTemp_Number(db.getBarGaugeLowWarningValue(selectedGaugeNum)));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, getTemp_String(db.getBarGaugeHighWarningValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, getTemp_String(db.getBarGaugeHighAlertValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_LWALabel, _UI_LABEL_PROPERTY_TEXT, getTemp_String(db.getBarGaugeLowWarningValue(selectedGaugeNum)).c_str());

                        break;

                    case gauge_type::OIL_PRESSURE:
                    case gauge_type::FUEL_PRESSURE:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HWAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HAText.c_str());
                        _ui_label_set_property(ui_LWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.LWAText.c_str());
                        _ui_label_set_property(ui_LDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.LDAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x262700), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, getPressure_Number(PRESSURE_MIN_VALUE), getPressure_Number(PRESSURE_MAX_VALUE));
                        lv_slider_set_range(ui_HDASlider, getPressure_Number(PRESSURE_MIN_VALUE), getPressure_Number(PRESSURE_MAX_VALUE));
                        lv_slider_set_range(ui_LWASlider, getPressure_Number(PRESSURE_MIN_VALUE), getPressure_Number(PRESSURE_MAX_VALUE));
                        lv_slider_set_range(ui_LDASlider, getPressure_Number(PRESSURE_MIN_VALUE), getPressure_Number(PRESSURE_MAX_VALUE));

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getBarGaugeHighWarningValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getBarGaugeHighAlertValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_LWASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getBarGaugeLowWarningValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_LDASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getBarGaugeLowAlertValue(selectedGaugeNum)));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getBarGaugeHighWarningValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getBarGaugeHighAlertValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_LWALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getBarGaugeLowWarningValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_LDALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getBarGaugeLowAlertValue(selectedGaugeNum)).c_str());

                        break;

                    case gauge_type::MANIFOLD_PRESSURE:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.WAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.DAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x262700), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, getPressure_Number(MANIFOLD_MIN_VALUE), getPressure_Number(MANIFOLD_MAX_VALUE));
                        lv_slider_set_range(ui_HDASlider, getPressure_Number(MANIFOLD_MIN_VALUE), getPressure_Number(MANIFOLD_MAX_VALUE));

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getBarGaugeHighWarningValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getBarGaugeHighAlertValue(selectedGaugeNum)));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getBarGaugeHighWarningValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getBarGaugeHighAlertValue(selectedGaugeNum)).c_str());

                        break;

                    case gauge_type::BATTERY_VOLTAGE:

                        // TODO: add different callback fuctions to set the values for the sliders as voltage whit decimals

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HWAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HAText.c_str());
                        _ui_label_set_property(ui_LWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.LWAText.c_str());
                        _ui_label_set_property(ui_LDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.LDAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x262700), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, getBatteryVoltage_Number(VOLTAGE_MIN_VALUE), getBatteryVoltage_Number(VOLTAGE_MAX_VALUE));
                        lv_slider_set_range(ui_HDASlider, getBatteryVoltage_Number(VOLTAGE_MIN_VALUE), getBatteryVoltage_Number(VOLTAGE_MAX_VALUE));
                        lv_slider_set_range(ui_LWASlider, getBatteryVoltage_Number(VOLTAGE_MIN_VALUE), getBatteryVoltage_Number(VOLTAGE_MAX_VALUE));
                        lv_slider_set_range(ui_LDASlider, getBatteryVoltage_Number(VOLTAGE_MIN_VALUE), getBatteryVoltage_Number(VOLTAGE_MAX_VALUE));

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, getBatteryVoltage_Number(db.getBarGaugeHighWarningValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, getBatteryVoltage_Number(db.getBarGaugeHighAlertValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_LWASlider, _UI_SLIDER_PROPERTY_VALUE, getBatteryVoltage_Number(db.getBarGaugeLowWarningValue(selectedGaugeNum)));
                        _ui_slider_set_property(ui_LDASlider, _UI_SLIDER_PROPERTY_VALUE, getBatteryVoltage_Number(db.getBarGaugeLowAlertValue(selectedGaugeNum)));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, getBatteryVoltage_String(db.getBarGaugeHighWarningValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, getBatteryVoltage_String(db.getBarGaugeHighAlertValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_LWALabel, _UI_LABEL_PROPERTY_TEXT, getBatteryVoltage_String(db.getBarGaugeLowWarningValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_LDALabel, _UI_LABEL_PROPERTY_TEXT, getBatteryVoltage_String(db.getBarGaugeLowAlertValue(selectedGaugeNum)).c_str());

                        break;

                    case gauge_type::FUEL_LEVEL:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_LWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.WALevelText.c_str());
                        _ui_label_set_property(ui_LDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.DALevelText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x262700), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_LWASlider, LEVEL_MIN_VALUE, LEVEL_MAX_VALUE);
                        lv_slider_set_range(ui_LDASlider, LEVEL_MIN_VALUE, LEVEL_MAX_VALUE);

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_LWASlider, _UI_SLIDER_PROPERTY_VALUE, db.getBarGaugeLowWarningValue(selectedGaugeNum));
                        _ui_slider_set_property(ui_LDASlider, _UI_SLIDER_PROPERTY_VALUE, db.getBarGaugeLowAlertValue(selectedGaugeNum));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_LWALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getBarGaugeLowWarningValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_LDALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getBarGaugeLowAlertValue(selectedGaugeNum)).c_str());

                        break;

                    case gauge_type::INJ_DUTY:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.WAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.DAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, VOLTAGE_MIN_VALUE, VOLTAGE_MAX_VALUE);
                        lv_slider_set_range(ui_HDASlider, VOLTAGE_MIN_VALUE, VOLTAGE_MAX_VALUE);

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, db.getBarGaugeHighWarningValue(selectedGaugeNum));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, db.getBarGaugeHighAlertValue(selectedGaugeNum));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getBarGaugeHighWarningValue(selectedGaugeNum)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getBarGaugeHighAlertValue(selectedGaugeNum)).c_str());

                        break;
                    }
                }

                firstTimeBars = false;
                firstTimeArcs = true;
                firstTimeRpms = true;
                firstTimePanels = true;
                barChanged = false;
                barTypeChanged = false;
                arcChanged = true;
                arcTypeChanged = true;
                panelChanged = true;
                panelTypeChanged = true;
            }
            break;

            case 2:
            { // Arcs

                if (firstTimeArcs)
                {
                    // Show the select panel
                    _ui_flag_modify(ui_SelectPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                    _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                    _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                    // Setup the dropdowns
                    lv_dropdown_clear_options(ui_GaugeNumberD);
                    lv_dropdown_set_options(ui_GaugeNumberD, arc_number_options.c_str());
                    lv_dropdown_set_selected(ui_GaugeNumberD, 0);
                    lv_dropdown_clear_options(ui_GaugeTypeD);
                    lv_dropdown_set_options(ui_GaugeTypeD, arc_options.c_str());
                    lv_dropdown_set_selected(ui_GaugeTypeD, (int)(db.getArcGaugeType(arc_number::ARC_1)));
                }

                uint8_t rawArcNumber = (uint8_t)(lv_dropdown_get_selected(ui_GaugeNumberD) + 1);
                arc_number selectedGaugeNumArc = (arc_number)rawArcNumber;
                gauge_type selectedGaugeTypeArc = (gauge_type)lv_dropdown_get_selected(ui_GaugeTypeD);

                if (previousArcNumber != lv_dropdown_get_selected(ui_GaugeNumberD))
                {
                    arcChanged = true;
                    previousArcNumber = lv_dropdown_get_selected(ui_GaugeNumberD);
                    lv_dropdown_set_selected(ui_GaugeTypeD, (int)(db.getArcGaugeType(selectedGaugeNumArc)));
                }

                if (previousArcType != lv_dropdown_get_selected(ui_GaugeTypeD) || arcChanged)
                {
                    arcTypeChanged = true;
                    previousArcType = lv_dropdown_get_selected(ui_GaugeTypeD);
                    selectedGaugeTypeArc = (gauge_type)lv_dropdown_get_selected(ui_GaugeTypeD);
                }

                // Set the options for each gauge type possible for BAR 1
                if (arcChanged || arcTypeChanged)
                {
                    switch (selectedGaugeTypeArc)
                    {
                    case gauge_type::COOLANT_TEMP:
                    case gauge_type::OIL_TEMP:
                    case gauge_type::AIR_TEMP:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HWAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HAText.c_str());
                        _ui_label_set_property(ui_LWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.TempLWAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x050154), LV_PART_MAIN | LV_STATE_DEFAULT);

                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0x0000FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0x0000FF), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, getTemp_Number(TEMP_MIN_VALUE), getTemp_Number(TEMP_MAX_VALUE));
                        lv_slider_set_range(ui_HDASlider, getTemp_Number(TEMP_MIN_VALUE), getTemp_Number(TEMP_MAX_VALUE));
                        lv_slider_set_range(ui_LWASlider, getTemp_Number(TEMP_MIN_VALUE), getTemp_Number(TEMP_MAX_VALUE));

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, getTemp_Number(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, getTemp_Number(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_LWASlider, _UI_SLIDER_PROPERTY_VALUE, getTemp_Number(db.getArcGaugeLowWarningValue(selectedGaugeNumArc)));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, getTemp_String(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, getTemp_String(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_LWALabel, _UI_LABEL_PROPERTY_TEXT, getTemp_String(db.getArcGaugeLowWarningValue(selectedGaugeNumArc)).c_str());

                        break;

                    case gauge_type::OIL_PRESSURE:
                    case gauge_type::FUEL_PRESSURE:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HWAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HAText.c_str());
                        _ui_label_set_property(ui_LWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.LWAText.c_str());
                        _ui_label_set_property(ui_LDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.LDAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x262700), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, getPressure_Number(PRESSURE_MIN_VALUE), getPressure_Number(PRESSURE_MAX_VALUE));
                        lv_slider_set_range(ui_HDASlider, getPressure_Number(PRESSURE_MIN_VALUE), getPressure_Number(PRESSURE_MAX_VALUE));
                        lv_slider_set_range(ui_LWASlider, getPressure_Number(PRESSURE_MIN_VALUE), getPressure_Number(PRESSURE_MAX_VALUE));
                        lv_slider_set_range(ui_LDASlider, getPressure_Number(PRESSURE_MIN_VALUE), getPressure_Number(PRESSURE_MAX_VALUE));

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_LWASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getArcGaugeLowWarningValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_LDASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getArcGaugeLowAlertValue(selectedGaugeNumArc)));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_LWALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getArcGaugeLowWarningValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_LDALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getArcGaugeLowAlertValue(selectedGaugeNumArc)).c_str());

                        break;

                    case gauge_type::MANIFOLD_PRESSURE:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.WAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.DAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x262700), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, getPressure_Number(MANIFOLD_MIN_VALUE), getPressure_Number(MANIFOLD_MAX_VALUE));
                        lv_slider_set_range(ui_HDASlider, getPressure_Number(MANIFOLD_MIN_VALUE), getPressure_Number(MANIFOLD_MAX_VALUE));

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, getPressure_Number(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, getPressure_String(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)).c_str());

                        break;

                    case gauge_type::BATTERY_VOLTAGE:

                        // TODO: add different callback fuctions to set the values for the sliders as voltage whit decimals

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HWAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.HAText.c_str());
                        _ui_label_set_property(ui_LWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.LWAText.c_str());
                        _ui_label_set_property(ui_LDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.LDAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x262700), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, getBatteryVoltage_Number(VOLTAGE_MIN_VALUE), getBatteryVoltage_Number(VOLTAGE_MAX_VALUE));
                        lv_slider_set_range(ui_HDASlider, getBatteryVoltage_Number(VOLTAGE_MIN_VALUE), getBatteryVoltage_Number(VOLTAGE_MAX_VALUE));
                        lv_slider_set_range(ui_LWASlider, getBatteryVoltage_Number(VOLTAGE_MIN_VALUE), getBatteryVoltage_Number(VOLTAGE_MAX_VALUE));
                        lv_slider_set_range(ui_LDASlider, getBatteryVoltage_Number(VOLTAGE_MIN_VALUE), getBatteryVoltage_Number(VOLTAGE_MAX_VALUE));

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, getBatteryVoltage_Number(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, getBatteryVoltage_Number(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_LWASlider, _UI_SLIDER_PROPERTY_VALUE, getBatteryVoltage_Number(db.getArcGaugeLowWarningValue(selectedGaugeNumArc)));
                        _ui_slider_set_property(ui_LDASlider, _UI_SLIDER_PROPERTY_VALUE, getBatteryVoltage_Number(db.getArcGaugeLowAlertValue(selectedGaugeNumArc)));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, getBatteryVoltage_String(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, getBatteryVoltage_String(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_LWALabel, _UI_LABEL_PROPERTY_TEXT, getBatteryVoltage_String(db.getArcGaugeLowWarningValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_LDALabel, _UI_LABEL_PROPERTY_TEXT, getBatteryVoltage_String(db.getArcGaugeLowAlertValue(selectedGaugeNumArc)).c_str());

                        break;

                    case gauge_type::FUEL_LEVEL:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_LWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.WALevelText.c_str());
                        _ui_label_set_property(ui_LDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.DALevelText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue
                        lv_obj_set_style_bg_color(ui_LWAPanel, lv_color_hex(0x262700), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(ui_LWASlider, lv_color_hex(0xFFFF00), LV_PART_KNOB | LV_STATE_DEFAULT);

                        // Set the range for the sliders
                        lv_slider_set_range(ui_LWASlider, LEVEL_MIN_VALUE, LEVEL_MAX_VALUE);
                        lv_slider_set_range(ui_LDASlider, LEVEL_MIN_VALUE, LEVEL_MAX_VALUE);

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_LWASlider, _UI_SLIDER_PROPERTY_VALUE, db.getArcGaugeLowWarningValue(selectedGaugeNumArc));
                        _ui_slider_set_property(ui_LDASlider, _UI_SLIDER_PROPERTY_VALUE, db.getArcGaugeLowAlertValue(selectedGaugeNumArc));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_LWALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getArcGaugeLowWarningValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_LDALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getArcGaugeLowAlertValue(selectedGaugeNumArc)).c_str());

                        break;

                    case gauge_type::INJ_DUTY:

                        // Set the flags
                        _ui_flag_modify(ui_LDAPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LDASlider, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                        _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                        _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

                        // Set the titles for the alerts and warnings
                        _ui_label_set_property(ui_HWATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.WAText.c_str());
                        _ui_label_set_property(ui_HDATittle, _UI_LABEL_PROPERTY_TEXT, settings_strings.DAText.c_str());

                        // Change the color of the Low Warning Alerts in this case to blue

                        // Set the range for the sliders
                        lv_slider_set_range(ui_HWASlider, DUTY_MIN_VALUE, DUTY_MAX_VALUE);
                        lv_slider_set_range(ui_HDASlider, DUTY_MIN_VALUE, DUTY_MAX_VALUE);

                        // Set the values for the sliders from the database
                        _ui_slider_set_property(ui_HWASlider, _UI_SLIDER_PROPERTY_VALUE, db.getArcGaugeHighWarningValue(selectedGaugeNumArc));
                        _ui_slider_set_property(ui_HDASlider, _UI_SLIDER_PROPERTY_VALUE, db.getArcGaugeHighAlertValue(selectedGaugeNumArc));

                        // Set the labels for the sliders
                        _ui_label_set_property(ui_HWALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getArcGaugeHighWarningValue(selectedGaugeNumArc)).c_str());
                        _ui_label_set_property(ui_HDALabel, _UI_LABEL_PROPERTY_TEXT, String(db.getArcGaugeHighAlertValue(selectedGaugeNumArc)).c_str());

                        break;
                    }
                }
                firstTimeBars = true;
                firstTimeArcs = false;
                firstTimeRpms = true;
                firstTimePanels = true;
                barChanged = true;
                barTypeChanged = true;
                arcChanged = false;
                arcTypeChanged = false;
                panelChanged = true;
                panelTypeChanged = true;
            }
            break;

            case 3: // Panels
            {
                if (firstTimePanels)
                {
                    // Show the select panel
                    _ui_flag_modify(ui_SelectPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                    _ui_flag_modify(ui_LowAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
                    _ui_flag_modify(ui_HighAlertPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

                    // Setup the dropdowns
                    lv_dropdown_clear_options(ui_GaugeNumberD);
                    lv_dropdown_set_options(ui_GaugeNumberD, panel_number_options.c_str());
                    lv_dropdown_set_selected(ui_GaugeNumberD, 0);
                    lv_dropdown_clear_options(ui_GaugeTypeD);
                    lv_dropdown_set_options(ui_GaugeTypeD, panel_options.c_str());
                    lv_dropdown_set_selected(ui_GaugeTypeD, (int)(db.getPanelGaugeType(panel_number::PANEL_1)));
                }

                uint8_t rawPanelNumber = (uint8_t)(lv_dropdown_get_selected(ui_GaugeNumberD) + 1);
                panel_number selectedGaugeNumPanel = (panel_number)rawPanelNumber;
                gauge_type selectedGaugeTypePanel = (gauge_type)lv_dropdown_get_selected(ui_GaugeTypeD);

                if (previousPanelNumber != lv_dropdown_get_selected(ui_GaugeNumberD))
                {
                    panelChanged = true;
                    previousPanelNumber = lv_dropdown_get_selected(ui_GaugeNumberD);
                    lv_dropdown_set_selected(ui_GaugeTypeD, (int)(db.getPanelGaugeType(selectedGaugeNumPanel)));
                }

                if (previousPanelType != lv_dropdown_get_selected(ui_GaugeTypeD) || panelChanged)
                {
                    panelTypeChanged = true;
                    previousPanelType = lv_dropdown_get_selected(ui_GaugeTypeD);
                    selectedGaugeTypePanel = (gauge_type)lv_dropdown_get_selected(ui_GaugeTypeD);
                }

                firstTimeBars = true;
                firstTimeArcs = true;
                firstTimeRpms = true;
                firstTimePanels = false;
                barChanged = true;
                barTypeChanged = true;
                arcChanged = true;
                arcTypeChanged = true;
                panelChanged = false;
                panelTypeChanged = false;
            }
            break;
            }
        }
        if (lv_scr_act() == ui_WelcomeScreen || lv_scr_act() == ui_FinalScreen)
        {
            if (welcomeInfoTimer.cycleTrigger(1000))
            {
                String welcomeInfo;

                dateUI = rtc_UI.get_date();
                timeUI = rtc_UI.get_time();
                atmosphericData = atmosphericSensor.get_atmospheric_data();

                welcomeInfo =
                    String(atmosphericData.temperature, 1) + " °C" + " | " + String(atmosphericData.pressure, 1) + " kPa" + " | " + String(dateUI.day) + "/" + String(dateUI.month) + "/" + String(dateUI.year) + " | " + String(timeUI.hours) + ":" + String(timeUI.minutes) + " | " + String(atmosphericData.altitude, 0) + " MSNM";

                if (lv_scr_act() == ui_WelcomeScreen)
                {
                    lv_textarea_set_text(ui_bannerTextA, welcomeInfo.c_str());
                }
                else
                {
                    lv_textarea_set_text(ui_bannerTextA2, welcomeInfo.c_str());
                }
            }
        }

        if (lv_scr_act() == ui_MainScreen)
        {
            if (mainScreenClockTimer.cycleTrigger(1000))
            {
                String clockInfo;

                // Get the data from the sensors
                dateUI = rtc_UI.get_date();
                timeUI = rtc_UI.get_time();
                atmosphericData = atmosphericSensor.get_atmospheric_data();

                // Set the clock info
                clockInfo = timeUI.hours + ":" + timeUI.minutes + " | " + dateUI.day + "/" + String(dateUI.month) + "/" + String(dateUI.year) + " | " + String(atmosphericData.temperature, 1) + "°C";

                _ui_label_set_property(ui_ClockLabel, _UI_LABEL_PROPERTY_TEXT, clockInfo.c_str());
            }
        }
    }
}
