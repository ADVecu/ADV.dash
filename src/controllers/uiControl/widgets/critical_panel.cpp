#include "critical_panel.h"

muTimer offTimer;

CriticalPanel::CriticalPanel()
{
    // Constructor
    lv_obj_add_flag(ui_CriticalAlertPanel, LV_OBJ_FLAG_HIDDEN);
    isOn = false;
}

bool CriticalPanel::ShowPanel(
    String message,
    lv_palette_t bg_color,
    uint16_t timeOn)
{
    if (!isOn)
    {
        // Set the message
        lv_label_set_text(ui_CriticalAlertText, message.c_str());

        // Set the background color
        lv_obj_set_style_bg_color(ui_CriticalAlertPanel, lv_palette_main(bg_color), 0);

        // Show the panel
        lv_obj_clear_flag(ui_CriticalAlertPanel, LV_OBJ_FLAG_HIDDEN);

        // Set the flag
        isOn = true;
    }
    else if (offTimer.delayOn(isOn, timeOn))
    {
        // Hide the panel
        lv_obj_add_flag(ui_CriticalAlertPanel, LV_OBJ_FLAG_HIDDEN);

        // Reset the flag
        isOn = false;
    }

    return isOn;
}

void CriticalPanel::HidePanel()
{
    // Hide the panel
    lv_obj_add_flag(ui_CriticalAlertPanel, LV_OBJ_FLAG_HIDDEN);

    // Reset the flag
    isOn = false;
}