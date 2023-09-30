
#include "UI/ui.h"
#include "database/database.h"
#include "ui_control.h"
#include "../canBus/can_bus.h"
#include "ui_enums.h"

// Widgets
#include "widgets/rpms_bar.h"
#include "widgets/gp_bar.h"

// Database instance
Database db;

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
    uint16_t _battVoltage = 0;

    // Initialize all the widgets and set the initial values
    rpmsBar rpmsBar(db.getRpmsRedline(), db.getRpmsWarning());

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
    
    while (1)
    {

        // Read the CAN bus queue
        if (xQueueReceive(canbus_queue, &rx_msg, 1000) == pdTRUE)
        {
            // Update the rpms bar
            rpmsBar.setRPMs(rx_msg.rpms);
            
            // Update the bar gauge 1
            switch(gp_Bar_1.getGaugeType()){
                case gauge_type::COOLANT_TEMP:
                    gp_Bar_1.setValue(rx_msg.coolant_temp);
                    break;
                case gauge_type::OIL_TEMP:
                    gp_Bar_1.setValue(rx_msg.aux1_temp);
                    break;
                case gauge_type::AIR_TEMP:
                    gp_Bar_1.setValue(rx_msg.air_temp);
                    break;
                case gauge_type::OIL_PRESSURE:
                    gp_Bar_1.setValue(rx_msg.oil_pressure);
                    break;
                case gauge_type::FUEL_PRESSURE:
                    gp_Bar_1.setValue(rx_msg.fuel_pressure); 
                    break;
                case gauge_type::BATTERY_VOLTAGE:
                    gp_Bar_1.setValue(rx_msg.battery_voltage);
                    break;
                case gauge_type::FUEL_LEVEL:
                    gp_Bar_1.setValue(rx_msg.fuel_level);
                    break;
                case gauge_type::INJ_DUTY:
                    gp_Bar_1.setValue(rx_msg.inj_duty);
                    break;
                case gauge_type::MANIFOLD_PRESSURE:
                    gp_Bar_1.setValue(rx_msg.map);
                    break;
            }

            // Update the bar gauge 2
            switch (gp_Bar_2.getGaugeType())
            {
            case gauge_type::COOLANT_TEMP:
                gp_Bar_2.setValue(rx_msg.coolant_temp);
                break;
            case gauge_type::OIL_TEMP:
                gp_Bar_2.setValue(rx_msg.aux1_temp);
                break;
            case gauge_type::AIR_TEMP:
                gp_Bar_2.setValue(rx_msg.air_temp);
                break;
            case gauge_type::OIL_PRESSURE:
                gp_Bar_2.setValue(rx_msg.oil_pressure);
                break;
            case gauge_type::FUEL_PRESSURE:
                gp_Bar_2.setValue(rx_msg.fuel_pressure);
                break;
            case gauge_type::BATTERY_VOLTAGE:
                gp_Bar_2.setValue(rx_msg.battery_voltage);
                break;
            case gauge_type::FUEL_LEVEL:
                gp_Bar_2.setValue(rx_msg.fuel_level);
                break;
            case gauge_type::INJ_DUTY:
                gp_Bar_2.setValue(rx_msg.inj_duty);
                break;
            case gauge_type::MANIFOLD_PRESSURE:
                gp_Bar_2.setValue(rx_msg.map);
                break;
            }
                
            }
        }
    }
