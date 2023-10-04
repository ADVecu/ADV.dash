#ifndef _TPS_BAR_H_
#define _TPS_BAR_H_

#include <Arduino.h>

/**
 * @brief TPS bar class
 */
class tpsBar
{

    uint16_t _previousTps;

public:
    // constructor
    /**
     * @brief Construct the TPS Bar object
     */
    tpsBar();

    // methods
    /**
     * @brief sets the TPS value to display.
     * @param value value of the TPS to display
     */
    void setValue(uint16_t value);
};



#endif // _TPS_BAR_H_