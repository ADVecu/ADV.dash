#ifndef SPEED_PANEL_H
#define SPEED_PANEL_H

#include <Arduino.h>
#include "UI/ui.h"

class speedPanel
{
    uint16_t _previousSpeed;

public:
    // constructor
    speedPanel();

    // methods
    void setValue(uint16_t value);
};

#endif // SPEED_PANEL_H