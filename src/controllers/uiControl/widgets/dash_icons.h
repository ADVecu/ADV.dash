#ifndef DASH_ICONS_H
#define DASH_ICONS_H

#include <Arduino.h>
#include "UI/ui.h"
#include "../ui_enums.h"
#include <muTimer.h>

#define TURN_SIGNAL_ON_TIME 1000
#define TURN_SIGNAL_OFF_TIME 1000

#define LOW_BEAN_COLOR 0x09A803
#define HIGH_BEAN_COLOR 0x1103A8
#define FOG_LIGHT_COLOR 0xA87F03

#define ICONS_OFF_COLOR 0x292929

class DashIcons
{
public:
    // Constructor
    DashIcons();

    /**
     * @brief Manage the turn signals
     *
     * @param  left: Left turn signal
     * @param  right: Right turn signal
     */
    void TurnSignalsManager(bool left, bool right);

    /**
     * @brief Manage the coolant level icon
     *
     * @param  status: Coolant level status
     */
    void CoolantLevelManager(bool status);

    /**
     * @brief Manage the lights icons
     *
     * @param  highBeam: High beam status
     * @param  lowBeam: Low beam status
     * @param  fogLights: Fog lights status
     */
    void LightsManager(bool highBeam, bool lowBeam, bool fogLights);
};


#endif // DASH_ICONS_H