#include "critical_panel.h"

muTimer offTimer;
muTimer delayAlertTimer;

CriticalPanel::CriticalPanel()
{
    // Constructor
    lv_obj_add_flag(ui_CriticalAlertPanel, LV_OBJ_FLAG_HIDDEN);
    isOn = false;
}

void CriticalPanel::ShowPanel(
    String message,
    lv_palette_t bg_color)
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
}

void CriticalPanel::HidePanel()
{
    // Hide the panel
    lv_obj_add_flag(ui_CriticalAlertPanel, LV_OBJ_FLAG_HIDDEN);

    // Reset the flag
    isOn = false;
}

bool CriticalPanel::isPanelOn()
{
    return isOn;
}