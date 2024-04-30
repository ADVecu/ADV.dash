#ifndef GEAR_PANEL_H
#define GEAR_PANEL_H

#include <Arduino.h>
#include "UI/ui.h"

class gearPanel
{

    uint8_t _previousGear;

public:
    gearPanel();
    void setValue(uint8_t value);
};

#endif // GEAR_PANEL_H