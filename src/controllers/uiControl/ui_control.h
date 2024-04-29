#ifndef _UI_CONTROL_H
#define _UI_CONTROL_H

#include "database/database.h"
#include <Arduino.h>

extern Database db;
extern TaskHandle_t ui_task_handle;

// UI task
void ui_task(void *pvParameters);

void ui_init_config();

#endif