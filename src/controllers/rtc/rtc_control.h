#ifndef RTC_CONTROL_H
#define RTC_CONTROL_H

#include <Arduino.h>

struct rtc_time
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
};

struct rtc_date
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

class rtc_control
{

public:
    void init_rtc();
    rtc_date get_date();
    rtc_time get_time();

};

#endif // RTC_CONTROL_H
