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

enum rideMenuOptions
{
    POPSANDBANGS,
    LAUNCH_CONTROL,
    DATALOG,
    QUICKSHIFT,
    RIDING_MODE,
    TRIP_A,
    TRIP_B,
    TRIP_INFO,
    SERVICE,
    SECURITY
};

struct rideMenuOptionsStrings
{
    const char *POPSANDBANGS = "DISABLED\nLEVEL 1\nLEVEL 2\nLEVEL 3";
    const char *LAUNCH_CONTROL = "DISABLED\nLEVEL 1\nLEVEL 2\nLEVEL 3";
    const char *DATALOG = "DISABLED\nSTART DATALOG\nSTOP DATALOG";
    const char *QUICKSHIFT = "DISABLED\nENABLED";
    const char *RIDING_MODE = "ECO\nNORMAL\nSPORT\nRACE";
    const char *TRIP_A = "ACTIVE\nRESET";
    const char *TRIP_B = "ACTIVE\nRESET";
    const char *TRIP_INFO = "TRIP_INFO";
    const char *SERVICE = "SERVICE";
    const char *SECURITY = "LEVEL 1\nLEVEL 2\nLEVEL 3";
};

class Menu_manager
{
private:
    uint8_t _keysArray[6];
    uint8_t _keyPressed;
    rideMenuOptions _selectedMenuOption;

public:
    uint32_t getKeyPressed();
    void rideMenuSetSelectedOptions(rideMenuOptions option);
    rideMenuOptions getSelectedMenuOption();
    void manageMenuActions(rideMenuOptions option, int actionID);
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