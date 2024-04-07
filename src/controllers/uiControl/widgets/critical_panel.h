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
     */
    void ShowPanel(
        String message,
        lv_palette_t bg_color);

    /**
     * @brief Force hide the panel
     */
    void HidePanel();

    /**
     * @brief Check if the panel is on
     * @return bool: True if panel is on
     */
    bool isPanelOn();

private:
    // Member variables
    bool isOn;
};

#endif // CRITICAL_PANEL_H