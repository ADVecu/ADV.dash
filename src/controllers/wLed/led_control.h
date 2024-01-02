#ifndef LED_CONTROL_H
#define LED_CONTROL_H


class led_control
{

public:
    void init_leds();
    static void ledsWelcomeAnimation(void *pvParameters);
    void triggerWelcomeAnimation();
    void setRmpsLeds(int rpms, int minRpms, int maxRpms);
};

#endif // LED_CONTROL_H
