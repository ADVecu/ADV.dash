
#include "UI/ui.h"
#include "database/database.h"
#include "ui_control.h"
#include "../canBus/can_bus.h"
#include "ui_enums.h"

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

    // Initialize all the widgets and set the initial values

    // RPMS Bar
    rpmsBar rpmsBar(db.getRpmsRedline(), db.getRpmsWarning());

    // TPS Bar
    tpsBar tpsBar;

    // Bar gauges
    gp_bar gp_Bar_1(db.getBarGaugeHighWarningValue(bar_number_t::BAR_1),
                    db.getBarGaugeHighAlertValue(bar_number_t::BAR_1),
                    db.getBarGaugeLowWarningValue(bar_number_t::BAR_1),
                    db.getBarGaugeLowAlertValue(bar_number_t::BAR_1),
                    db.getBarGaugeType(bar_number_t::BAR_1),
                    bar_number_t::BAR_1);

    gp_bar gp_Bar_2(db.getBarGaugeHighWarningValue(bar_number_t::BAR_2),
                    db.getBarGaugeHighAlertValue(bar_number_t::BAR_2),
                    db.getBarGaugeLowWarningValue(bar_number_t::BAR_2),
                    db.getBarGaugeLowAlertValue(bar_number_t::BAR_2),
                    db.getBarGaugeType(bar_number_t::BAR_2),
                    bar_number_t::BAR_2);

    gp_bar gp_Bar_3(db.getBarGaugeHighWarningValue(bar_number_t::BAR_3),
                    db.getBarGaugeHighAlertValue(bar_number_t::BAR_3),
                    db.getBarGaugeLowWarningValue(bar_number_t::BAR_3),
                    db.getBarGaugeLowAlertValue(bar_number_t::BAR_3),
                    db.getBarGaugeType(bar_number_t::BAR_3),
                    bar_number_t::BAR_3);

    gp_bar gp_Bar_4(db.getBarGaugeHighWarningValue(bar_number_t::BAR_4),
                    db.getBarGaugeHighAlertValue(bar_number_t::BAR_4),
                    db.getBarGaugeLowWarningValue(bar_number_t::BAR_4),
                    db.getBarGaugeLowAlertValue(bar_number_t::BAR_4),
                    db.getBarGaugeType(bar_number_t::BAR_4),
                    bar_number_t::BAR_4);

    gp_bar gp_bar_array[4] = {gp_Bar_1, gp_Bar_2, gp_Bar_3, gp_Bar_4};

    // Arc gauges
    gp_arc gp_Arc_1(db.getArcGaugeHighWarningValue(arc_number_t::ARC_1),
                    db.getArcGaugeHighAlertValue(arc_number_t::ARC_1),
                    db.getArcGaugeLowWarningValue(arc_number_t::ARC_1),
                    db.getArcGaugeLowAlertValue(arc_number_t::ARC_1),
                    db.getArcGaugeType(arc_number_t::ARC_1),
                    arc_number_t::ARC_1);

    gp_arc gp_Arc_2(db.getArcGaugeHighWarningValue(arc_number_t::ARC_2),
                    db.getArcGaugeHighAlertValue(arc_number_t::ARC_2),
                    db.getArcGaugeLowWarningValue(arc_number_t::ARC_2),
                    db.getArcGaugeLowAlertValue(arc_number_t::ARC_2),
                    db.getArcGaugeType(arc_number_t::ARC_2),
                    arc_number_t::ARC_2);

    gp_arc gp_Arc_3(db.getArcGaugeHighWarningValue(arc_number_t::ARC_3),
                    db.getArcGaugeHighAlertValue(arc_number_t::ARC_3),
                    db.getArcGaugeLowWarningValue(arc_number_t::ARC_3),
                    db.getArcGaugeLowAlertValue(arc_number_t::ARC_3),
                    db.getArcGaugeType(arc_number_t::ARC_3),
                    arc_number_t::ARC_3);

    gp_arc gp_Arc_4(db.getArcGaugeHighWarningValue(arc_number_t::ARC_4),
                    db.getArcGaugeHighAlertValue(arc_number_t::ARC_4),
                    db.getArcGaugeLowWarningValue(arc_number_t::ARC_4),
                    db.getArcGaugeLowAlertValue(arc_number_t::ARC_4),
                    db.getArcGaugeType(arc_number_t::ARC_4),
                    arc_number_t::ARC_4);

    gp_arc gp_Arc_5(db.getArcGaugeHighWarningValue(arc_number_t::ARC_5),
                    db.getArcGaugeHighAlertValue(arc_number_t::ARC_5),
                    db.getArcGaugeLowWarningValue(arc_number_t::ARC_5),
                    db.getArcGaugeLowAlertValue(arc_number_t::ARC_5),
                    db.getArcGaugeType(arc_number_t::ARC_5),
                    arc_number_t::ARC_5);

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

    // Infinite loop
    while (1)
    {
        // Read the CAN bus queue
        if (xQueueReceive(canbus_queue, &rx_msg, 1000) == pdTRUE)
        {
            // Update the rpms bar
            rpmsBar.setRPMs(rx_msg.rpms);

            // Update the tps bar
            tpsBar.setValue(rx_msg.tps);

            // iterate through the bar gauges and update the values
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

            // iterate through the panel gauges and update the values
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
                case gauge_type::FUEL_TRIM:
                    gp_panel_array[k].setValue(rx_msg.fuel_trim);
                    break;
                case gauge_type::FUEL_FLOW:
                    gp_panel_array[k].setValue(rx_msg.fuel_flow);
                    break;
                case gauge_type::FUEL_USED:
                    gp_panel_array[k].setValue(rx_msg.fuel_used);
                    break;
                }
            }
        }
    }
}
