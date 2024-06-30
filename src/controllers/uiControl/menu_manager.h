#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

// Include any necessary headers here
#include <Arduino.h>
#include <lvgl.h>
#include "UI/ui.h"

// Define any necessary structs or classes here
enum keysID
{
    ENTER = 1,
    BACK,
    UP,
    DOWN,
    AUX1,
    AUX2,
    AUX3
};

class Menu_manager
{
private:
    uint8_t _keysArray[6];
    uint8_t _keyPressed;

public:
    uint32_t getKeyPressed();
    void Menu_manager_buttons_data(uint8_t enter,
                                   uint8_t back,
                                   uint8_t up,
                                   uint8_t down,
                                   uint8_t aux1,
                                   uint8_t aux2,
                                   uint8_t aux3);
};

extern Menu_manager menu_manager;


// Declare any necessary functions here

#endif // MENU_MANAGER_H