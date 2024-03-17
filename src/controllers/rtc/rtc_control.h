#ifndef RTC_CONTROL_H
#define RTC_CONTROL_H

#include <Arduino.h>

struct rtc_time
{
    String seconds;
    String minutes;
    String hours;
};

struct rtc_date
{
    String day;
    String month;
    String year;
};

class rtc_control
{

public:
    void init_rtc();
    rtc_date get_date();
    rtc_time get_time();
};

#endif // RTC_CONTROL_H
