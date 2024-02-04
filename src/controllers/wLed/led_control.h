#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "pcb_definitions.h"

enum ledState
{
    LED_OFF,
    LED_ON,
    LED_BLINK
};

enum ledColor
{
    LED_RED = 0xff0000,
    LED_GREEN = 0x00ff00,
    LED_BLUE = 0x0000ff,
    LED_YELLOW = 0xffff00,
    LED_PURPLE = 0xff00ff,
    LED_CYAN = 0x00ffff,
    LED_WHITE = 0xffffff
};

struct indicatorLedState
{
    bool HighBeamST = false;
    bool LeftTurnST = false;
    bool RightTurnST = false;
    bool ParkingST = false;
    bool BatteryST = false;
    bool OilPressureST = false;
    bool CheckEngineST = false;
    bool FuelST = false;

};

struct indicatorLedStatePrevious
{
    bool HighBeamST = true;
    bool LeftTurnST = true;
    bool RightTurnST = true;
    bool ParkingST = true;
    bool BatteryST = true;
    bool OilPressureST = true;
    bool CheckEngineST = true;
    bool FuelST = true;

};

void ledControlTask(void *pvParameters);
void commitTaskProcedure(void *arg);
void commit();

class led_control
{

public:
    void init_leds();
    static void ledsWelcomeAnimation(void *pvParameters);
    void triggerWelcomeAnimation();
    void clearLeds();
    
    // void setIndicatorLeds(ledState state, ledPosition position ,ledColor color);
};

#endif // LED_CONTROL_H
