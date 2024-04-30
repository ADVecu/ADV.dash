#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <Arduino.h>
#include "ui_enums.h"
#include "ui_strings.h"
#include "ui_control.h"
#include "UI/ui.h"

void textConfigArc(arc_number_t arc, bool setDropdown);
void dropDownChange();

#endif // CONFIG_MANAGER_H