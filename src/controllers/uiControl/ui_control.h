#ifndef _UI_CONTROL_H
#define _UI_CONTROL_H

#include "database/database.h"
#include <Arduino.h>

// UI task
void ui_task(void *pvParameters);

void ui_init_config();

#endif