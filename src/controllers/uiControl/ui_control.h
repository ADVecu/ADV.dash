#include "Arduino.h"

class rpmsBar
{
    uint16_t _rpmsRedline;
    uint16_t _rpmsWarning;
    uint16_t _previousRpm;

public:
    // constructor
    rpmsBar();

    // methods
    void setRPMs(uint16_t rpm);
    void setRedline(uint16_t redline);
    void setWarning(uint16_t warning);
};

void ui_init_config(void);