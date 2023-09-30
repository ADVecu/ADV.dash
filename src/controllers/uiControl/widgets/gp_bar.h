#ifndef _GP_BAR_H
#define _GP_BAR_H

#include <Arduino.h>
#include "UI/ui.h"
#include "../ui_enums.h"

/**
 * @brief Type of bar background
 */
typedef enum class bar_bg_type
{
    NO_WARNING, // No red or blue indication
    RED_ALERT,  // Red indication at max value
    BLUE_RED    // Red indication at max value and blue indication at min value
} bar_bg_type_t;

/**
 * @brief Generic Bar gauge class
 */
class gp_bar
{

    uint16_t _warningValue;
    uint16_t _alertValue;
    uint16_t _lowWarningValue;
    uint16_t _lowAlertValue;
    uint16_t _maxValue;
    uint16_t _minValue;
    uint16_t _previousValue;
    String _unit;
    String _name;
    lv_img_dsc_t _bgImg;
    lv_obj_t *_bar;
    lv_obj_t *_barUnit;
    lv_obj_t *_barName;
    lv_obj_t *_barBgImg;
    lv_obj_t *_barValue;
    gauge_type _gaugeType;

public:
    // constructor
    /**
     * @brief Construct a new generic bar object
     *
     * @param highWarningValue At which value the bar will change color to yellow at the high end
     * @param highAlertValue At which value the bar will change color to red at the high end
     * @param lowWarningValue At which value the bar will change color at the low end
     * @param lowAlertValue At which value the bar will change color at the low end
     * @param gaugeType Choose between the available gauge types
     * @param bgImg Choose between the 3 available background images for the bar widget
     * @param bar Choose which bar widget to initialize from the 4 available
     */
    gp_bar(uint16_t highWarningValue,
           uint16_t highAlertValue,
           u_int16_t lowWarningValue,
           uint16_t lowAlertValue,
           gauge_type gaugeType,
           bar_number_t bar);

    // methods
    /**
     * @brief Set the value of the bar
     *
     * @param value Value to display
     */
    void setValue(uint16_t value);

    /**
     * @brief Set the warning value of the bar
     *
     * @param warningValue Value to set
     */
    void setHighWarningValue(uint16_t warningValue);

    /**
     * @brief Set the alert value of the bar
     *
     * @param alertValue Value to set
     */
    void setHighAlertValue(uint16_t alertValue);

    /**
     * @brief Set the low warning value of the bar
     *
     * @param lowWarningValue Value to set
     */
    void setLowWarningValue(uint16_t lowWarningValue);

    /**
     * @brief Set the low alert value of the bar
     *
     * @param lowAlertValue Value to set
     */
    void setLowAlertValue(uint16_t lowAlertValue);

    /**
     * @brief Get the bar gauge type
     * 
     */
    gauge_type getGaugeType();
};

#endif // _GP_BAR_H