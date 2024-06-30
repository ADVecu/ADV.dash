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