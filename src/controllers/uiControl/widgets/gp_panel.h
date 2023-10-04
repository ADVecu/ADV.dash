#ifndef _GP_PANEL_H_
#define _GP_PANEL_H_

#include <Arduino.h>

#include "../ui_enums.h"
#include "../ui_strings.h"
#include "UI/ui.h"

/**
 * @brief Generic Panel gauge class
 */
class gp_panel
{
    uint16_t _alertValue;
    uint16_t _previousValue;
    String _unit;
    String _name;
    lv_img_dsc_t _bgImg;
    lv_obj_t *_panel;
    lv_obj_t *_panelName;
    lv_obj_t *_panelValue;
    gauge_type _gaugeType;

public:
    // constructor
    /**
     * @brief Construct a new generic panel object
     *
     * @param alertValue At which value the panel will change color to red
     * @param gaugeType Choose between the available gauge types
     * @param panel Choose which panel widget to initialize from the 4 available
     */
    gp_panel(uint16_t alertValue,
             gauge_type gaugeType,
             panel_number_t panel);

    // methods
    /**
     * @brief sets the value to display.
     * This method also checks if the value is above the alert value and change the panel color accordingly
     * @param value value to display
     */
    void setValue(uint16_t value);

    /**
     * @brief sets the alert value of the panel
     * @param alertValue value of the alert to set
     */
    void setAlert(uint16_t alertValue);

    /**
     * @brief gets the gauge type of the panel
     * @return gauge_type value of the gauge type
     */
    gauge_type getGaugeType();

};
#endif