#include "dash_icons.h"

muTimer turnSignalTimer;


DashIcons::DashIcons()
{
    // Constructor
    lv_obj_add_flag(ui_LeftArrow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_RightArrow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_CoolantLvl, LV_OBJ_FLAG_HIDDEN);
    
}

void DashIcons::TurnSignalsManager(bool left, bool right)
{
    if (left & turnSignalTimer.cycleOnOff(TURN_SIGNAL_ON_TIME, TURN_SIGNAL_OFF_TIME)) 
    {
        lv_obj_clear_flag(ui_LeftArrow, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(ui_LeftArrow, LV_OBJ_FLAG_HIDDEN);
    }

    if (right & turnSignalTimer.cycleOnOff(TURN_SIGNAL_ON_TIME, TURN_SIGNAL_OFF_TIME))
    {
        lv_obj_clear_flag(ui_RightArrow, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(ui_RightArrow, LV_OBJ_FLAG_HIDDEN);
    }
}

void DashIcons::CoolantLevelManager(bool status)
{
    if (status)
    {
        lv_obj_clear_flag(ui_CoolantLvl, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(ui_CoolantLvl, LV_OBJ_FLAG_HIDDEN);
    }
}

void DashIcons::LightsManager(bool highBeam, bool lowBeam, bool fogLights)
{
    if (highBeam)
    {
        lv_obj_set_style_img_recolor(ui_HighBean, lv_color_hex(HIGH_BEAN_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
        lv_obj_set_style_img_recolor(ui_HighBean, lv_color_hex(ICONS_OFF_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (lowBeam)
    {
        lv_obj_set_style_img_recolor(ui_LowBean, lv_color_hex(LOW_BEAN_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
        lv_obj_set_style_img_recolor(ui_LowBean, lv_color_hex(ICONS_OFF_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (fogLights)
    {
        lv_obj_set_style_img_recolor(ui_FogLight, lv_color_hex(FOG_LIGHT_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
        lv_obj_set_style_img_recolor(ui_FogLight, lv_color_hex(ICONS_OFF_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    
}


