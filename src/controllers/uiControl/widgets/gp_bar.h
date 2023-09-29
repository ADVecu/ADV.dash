#include <Arduino.h>
#include "UI/ui.h"
#include "../ui_enums.h"

/**
 * @brief Bar widget number
 */
typedef enum class bar_number
{
    BAR_1, // Top Left bar
    BAR_2, // Top Right bar
    BAR_3, // Bottom Left bar
    BAR_4  // Bottom Right bar
} bar_number_t;

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

public:
    // constructor
    /**
     * @brief Construct a new generic bar object
     *
     * @param warningValue At which value the bar will change color to yellow
     * @param alertValue At which value the bar will change color to red
     * @param gaugeType Choose between the available gauge types
     * @param bgImg Choose between the 3 available background images for the bar widget
     * @param bar Choose which bar widget to initialize from the 4 available
     */
    gp_bar(uint16_t warningValue, uint16_t alertValue, gauge_type gaugeType, bar_bg_type_t bgImg, bar_number_t bar);

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
    void setWarningValue(uint16_t warningValue);

    /**
     * @brief Set the alert value of the bar
     *
     * @param alertValue Value to set
     */
    void setAlertValue(uint16_t alertValue);

    /**
     * @brief Set the max value of the bar
     *
     * @param maxValue Value to set
     */
    void setMaxValue(uint16_t maxValue);

    /**
     * @brief Set the min value of the bar
     *
     * @param minValue Value to set
     */
    void setMinValue(uint16_t minValue);

    /**
     * @brief Set the unit of the bar
     *
     * @param unit Value to set
     */
    void setUnit(String unit);

    /**
     * @brief Set the name of the bar
     *
     * @param name Name to set
     */
    void setName(String name);

    /**
     * @brief Set the background image of the bar
     *
     * @param bgImg Image to set
     */
    void setBgImg(lv_img_dsc_t bgImg);
};