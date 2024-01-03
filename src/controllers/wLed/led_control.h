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

class led_control
{

public:
    void init_leds();
    static void ledsWelcomeAnimation(void *pvParameters);
    void triggerWelcomeAnimation();
    void setRmpsLeds(int rpms, int minRpms, int maxRpms);
    void setIndicatorLeds(ledState state, ledPosition position ,ledColor color);
};

#endif // LED_CONTROL_H
