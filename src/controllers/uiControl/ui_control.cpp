
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
#include "alert_manager.h"
#include "menu_manager.h"
#include "controllers/eeprom/eeprom.h"

// Widgets
#include "widgets/rpms_bar.h"
#include "widgets/gp_bar.h"
#include "widgets/gp_arc.h"
#include "widgets/gp_panel.h"
#include "widgets/tps_bar.h"
#include "widgets/speed_panel.h"
#include "widgets/gear_panel.h"
#include "widgets/dash_icons.h"

// Database instance
Database db;

// CAN bus data queue
QueueSetHandle_t canbus_queue;

// ui task handeler
TaskHandle_t ui_task_handle;

muTimer welcomeInfoTimer;
muTimer mainScreenClockTimer;
muTimer panelDataRate;
muTimer barDataRate;
muTimer DataRate;
muTimer IconsDataRate;

rtc_date dateUI;
rtc_time timeUI;

rtc_control rtc_UI;

bmp280 atmosphericSensor;
atmospheric_data atmosphericData;

EEPROM_manager eeprom_manager;

/**
 * @brief Initialize the UI configuration
 */
void ui_init_config()
{
    // create the task to handle the UI values refresh
    xTaskCreatePinnedToCore(
        ui_task,         /* Function to implement the task */
        "ui_task",       /* Name of the task */
        10000,           /* Stack size in words */
        NULL,            /* Task input parameter */
        0,               /* Priority of the task */
        &ui_task_handle, /* Task handle. */
        APP_CPU_NUM);    /* Core where the task should run */
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
    // TODO - Change the way rpms and panels widgets are initialized

    // RPMS Bar
    rpmsBar rpmsBar(db.getRpmsRedline(), db.getRpmsWarning());

    // TPS Bar
    tpsBar tpsBar;

    // Speed Panel
    speedPanel speedPanel;

    // Gear Panel
    gearPanel gearPanel;

    // Arc gauges
    gp_arc gp_Arc_1(arc_number_t::ARC_1);

    gp_arc gp_Arc_2(arc_number_t::ARC_2);

    gp_arc gp_Arc_3(arc_number_t::ARC_3);

    gp_arc gp_Arc_4(arc_number_t::ARC_4);

    gp_arc gp_Arc_5(arc_number_t::ARC_5);

    gp_arc gp_arc_array[5] = {gp_Arc_1, gp_Arc_2, gp_Arc_3, gp_Arc_4, gp_Arc_5};

    // Bar gauges
    gp_bar gp_Bar_1(bar_number_t::BAR_1);

    gp_bar gp_Bar_2(bar_number_t::BAR_2);

    gp_bar gp_Bar_3(bar_number_t::BAR_3);

    gp_bar gp_Bar_4(bar_number_t::BAR_4);

    gp_bar gp_bar_array[4] = {gp_Bar_1, gp_Bar_2, gp_Bar_3, gp_Bar_4};

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

    // Alert Manager
    Alert_manager alert_manager;

    // Dash Icons Manager
    DashIcons dash_icons;

    bool canReady = false;

    // Serial.println(db.getRpmsRedline());
    //  Infinite loop
    while (1)
    {

        // Read the CAN bus queue
        if (xQueueReceive(canbus_queue, &rx_msg, 0) == pdTRUE && lv_scr_act() == ui_MainScreen)
        {
            // Set the flag to true
            canReady = true;

            if (DataRate.cycleTrigger(100))
            {
                // Update the rpms bar
                rpmsBar.setRPMs(rx_msg.rpms);

                // Update the tps bar
                tpsBar.setValue(rx_msg.tps);

                // Update the speed panel
                speedPanel.setValue(rx_msg.speed);

                // Update Current gear
                gearPanel.setValue(rx_msg.current_gear);

                // Send data to the alert manager
                alert_manager.alert_manager_data(rx_msg.rpms,
                                                 rx_msg.map,
                                                 rx_msg.coolant_temp,
                                                 rx_msg.oil_pressure,
                                                 rx_msg.battery_voltage,
                                                 rx_msg.fuel_pressure,
                                                 rx_msg.fuel_level,
                                                 rx_msg.aux1_temp);

                // Send buttons data to the menu manager
                menu_manager.Menu_manager_buttons_data(rx_msg.enterBT,
                                                       rx_msg.backBT,
                                                       rx_msg.upBT,
                                                       rx_msg.downBT,
                                                       rx_msg.aux1BT,
                                                       rx_msg.aux2BT,
                                                       rx_msg.aux3BT);

                // iterate through the arc gauges and update the values
                for (j = 0; j < 5; j++)
                {
                    switch (gp_arc_array[j].getGaugeType())
                    {
                    case gauge_type::COOLANT_TEMP:
                        gp_arc_array[j].setValue(rx_msg.coolant_temp);
                        break;
                    case gauge_type::OIL_TEMP:
                        gp_arc_array[j].setValue(rx_msg.oil_temp);
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
            if (barDataRate.cycleTrigger(500))
            {
                for (i = 0; i < 4; i++)
                {
                    switch (gp_bar_array[i].getGaugeType())
                    {
                    case gauge_type::COOLANT_TEMP:
                        gp_bar_array[i].setValue(rx_msg.coolant_temp);
                        break;
                    case gauge_type::OIL_TEMP:
                        gp_bar_array[i].setValue(rx_msg.oil_temp);
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
            if (panelDataRate.cycleTrigger(500))
            {
                for (k = 0; k < 6; k++)
                {
                    switch (gp_panel_array[k].getGaugeType())
                    {
                    case gauge_type::COOLANT_TEMP:
                        gp_panel_array[k].setValue(rx_msg.coolant_temp);
                        break;
                    case gauge_type::OIL_TEMP:
                        gp_panel_array[k].setValue(rx_msg.oil_temp);
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
                    case gauge_type::AMBIENT_TEMP:
                        gp_panel_array[k].setValue(rx_msg.ambientTemp);
                        break;
                    case gauge_type::FW_PRESS:
                        gp_panel_array[k].setValue(rx_msg.fwPressure);
                        break;
                    case gauge_type::FW_TEMP:
                        gp_panel_array[k].setValue(rx_msg.fwTemp);
                        break;
                    case gauge_type::RW_PRESS:
                        gp_panel_array[k].setValue(rx_msg.rwPressure);
                        break;
                    case gauge_type::RW_TEMP:
                        gp_panel_array[k].setValue(rx_msg.rwTemp);
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

            // Update the dash icons
            if(IconsDataRate.cycleTrigger(500))
            {
            dash_icons.TurnSignalsManager(rx_msg.dir_izq, rx_msg.dir_der);  // Turn signals
            dash_icons.LightsManager(rx_msg.high_bean, rx_msg.low_bean, rx_msg.fog_light); // Lights
            dash_icons.CoolantLevelManager(rx_msg.coolant_level); // Coolant level
            }
        }
        else
        {
            canReady = false;
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
                // clockInfo = timeUI.hours + ":" + timeUI.minutes + " | " + dateUI.day + "/" + String(dateUI.month) + "/" + String(dateUI.year) + " | " + String(atmosphericData.temperature, 1) + "°C";
                clockInfo = timeUI.hours + ":" + timeUI.minutes + " | "
                                                                  "56.326 KM" +
                            " | " + String(atmosphericData.altitude, 0) + " MSNM";

                _ui_label_set_property(ui_ClockLabel, _UI_LABEL_PROPERTY_TEXT, clockInfo.c_str());
            }
        }
        uint32_t notificationValue = 0;

        // check task notification
        if (xTaskNotifyWait(0, 0, &notificationValue, 0) == pdTRUE)
        {
            Serial.print("Task notification received ");
            Serial.println(notificationValue);
        }
    }
}

void refresh_arc_gauges(arc_number_t arc_number)
{
}
