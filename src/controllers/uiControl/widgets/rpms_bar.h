#include "Arduino.h"

/**
 * @brief Main RPMS Bar class
 * Top bar of the display, shows the rpms, warning advice and redline
 */
class rpmsBar
{
    uint16_t _rpmsRedline;
    uint16_t _rpmsWarning;
    uint16_t _previousRpm;

public:
    // constructor
    /**
     * @brief Construct the rpms Bar object
     *
     * @param rpmsRedline initial value of the redline
     * @param rpmsWarning initial value of the warning
     */
    rpmsBar(uint16_t rpmsRedline, uint16_t rpmsWarning);

    // methods
    /**
     * @brief sets the rpms value to display.
     * This method also checks if the rpms are above the redline or warning values and change the bar color accordingly
     * @param rpm value of the rpms to display
     */
    void setRPMs(uint16_t rpm);

    /**
     * @brief sets the redline value of the rpms bar
     * @param redline value of the redline to set
     */
    void setRedline(uint16_t redline);

    /**
     * @brief Set the Warning value of the rpms bar
     * @param warning value of the warning to set
     */
    void setWarning(uint16_t warning);
};
