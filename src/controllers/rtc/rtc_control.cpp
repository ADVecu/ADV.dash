#include <Arduino.h>
#include <SparkFun_RV8803.h>
#include "rtc_control.h"

RV8803 rtc;

void rtc_control::init_rtc()
{

    if (rtc.begin() == false)
    {
        Serial.println("RTC failed to initialize!");
    }
    else
    {
        Serial.println("RTC initialized successfully.");
    }
    /*
    if (rtc.setToCompilerTime() == false)
        Serial.println("Something went wrong setting the time");
    else
        Serial.println("New time set!");
        */
} 

rtc_date rtc_control::get_date()
{

    rtc_date date;

    if (rtc.updateTime())
    {
        date.day = rtc.getDate();
        date.month = rtc.getMonth();
        date.year = rtc.getYear();
    }

    return date;
}

rtc_time rtc_control::get_time()
{

    rtc_time time;

    if (rtc.updateTime())
    {
        time.seconds = rtc.getSeconds();
        time.minutes = rtc.getMinutes();
        time.hours = rtc.getHours();
    }

    return time;
}
