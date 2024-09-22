#include "menu_manager.h"

void Menu_manager::Menu_manager_buttons_data(uint8_t enter,
                                             uint8_t back,
                                             uint8_t up,
                                             uint8_t down,
                                             uint8_t aux1,
                                             uint8_t aux2,
                                             uint8_t aux3)
{
    _keysArray[0] = enter;
    _keysArray[1] = back;
    _keysArray[2] = up;
    _keysArray[3] = down;
    _keysArray[4] = aux1;
    _keysArray[5] = aux2;
    _keysArray[6] = aux3;
}

uint32_t Menu_manager::getKeyPressed()
{
    _keyPressed = 0;

    for (uint8_t i = 0; i < 6; i++)
    {
        if (_keysArray[i] == 100)
        {
            _keyPressed = i + 1;
            Serial.print("Key pressed: ");
            Serial.println(_keyPressed);
        }
    }

    return _keyPressed;
}

void Menu_manager::rideMenuSetSelectedOptions(rideMenuOptions option)
{
    rideMenuOptionsStrings MenuOptions;

    _selectedMenuOption = option;

    switch (option)
    {
    case POPSANDBANGS:
        lv_roller_set_options(ui_Menu2, MenuOptions.POPSANDBANGS, LV_ROLLER_MODE_NORMAL);
        break;
    case LAUNCH_CONTROL:
        lv_roller_set_options(ui_Menu2, MenuOptions.LAUNCH_CONTROL, LV_ROLLER_MODE_NORMAL);
        break;
    case DATALOG:
        lv_roller_set_options(ui_Menu2, MenuOptions.DATALOG, LV_ROLLER_MODE_NORMAL);
        break;
    case QUICKSHIFT:
        lv_roller_set_options(ui_Menu2, MenuOptions.QUICKSHIFT, LV_ROLLER_MODE_NORMAL);
        break;
    case RIDING_MODE:
        lv_roller_set_options(ui_Menu2, MenuOptions.RIDING_MODE, LV_ROLLER_MODE_NORMAL);
        break;
    case TRIP_A:
        lv_roller_set_options(ui_Menu2, MenuOptions.TRIP_A, LV_ROLLER_MODE_NORMAL);
        break;
    case TRIP_B:
        lv_roller_set_options(ui_Menu2, MenuOptions.TRIP_B, LV_ROLLER_MODE_NORMAL);
        break;
    case TRIP_INFO:
        lv_obj_clear_flag(ui_Menu2, LV_OBJ_FLAG_HIDDEN);
        break;
    case SERVICE:

        break;
    case SECURITY:
        lv_roller_set_options(ui_Menu2, MenuOptions.SECURITY, LV_ROLLER_MODE_NORMAL);
        break;
    default:
        break;
    }
}

void Menu_manager::manageMenuActions(rideMenuOptions option, int actionID)
{
    switch (option)
    {
    case POPSANDBANGS:
        break;
    case LAUNCH_CONTROL:
        break;
    case DATALOG:
        switch (actionID)
        {
        case 0:
            /* code */
            break;
        
        default:
            break;
        }
        break;
    case QUICKSHIFT:
        break;
    case RIDING_MODE:
        break;
    case TRIP_A:
        break;
    case TRIP_B:
        break;
    case TRIP_INFO:
        break;
    case SERVICE:
        break;
    case SECURITY:
        break;
    default:
        break;
    }
}

rideMenuOptions Menu_manager::getSelectedMenuOption()
{
    return _selectedMenuOption;
}