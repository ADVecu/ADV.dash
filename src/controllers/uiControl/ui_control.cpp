
#include "UI/ui.h"
#include "database/database.h"
#include "ui_control.h"
#include "../canBus/can_bus.h"

// Widgets
#include "widgets/rpms_bar.h"

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

    rpmsBar rpmsBar(db.getRpmsRedline(), db.getRpmsWarning());

    while (1)
    {

        // Read the CAN bus queue
        if (xQueueReceive(canbus_queue, &rx_msg, 1000) == pdTRUE)
        {
            // Update the rpms bar
            rpmsBar.setRPMs(rx_msg.rpms);
        }
    }
}