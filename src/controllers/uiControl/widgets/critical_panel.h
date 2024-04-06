#ifndef CRITICAL_PANEL_H
#define CRITICAL_PANEL_H

// Include necessary libraries here
#include <Arduino.h>
#include "UI/ui.h"
#include "../ui_enums.h"
#include <muTimer.h>

class CriticalPanel
{
public:
    // Constructor
    CriticalPanel();

    /**
     * @brief Show Main Critical Panel
     *
     * @param  message: Message to display
     * @param  bg_color: Background color
     * @param  timeOn: Time to display the panel
     * @return bool: True if panel is on
     */
    bool ShowPanel(
        String message,
        lv_palette_t bg_color,
        uint16_t timeOn);
    
    /**
     * @brief Force hide the panel
     */
    void HidePanel();

private:
    // Member variables
    bool isOn;
};

#endif // CRITICAL_PANEL_H