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
        date.day = rtc.getDate() < 10 ? "0" + String(rtc.getDate()) : String(rtc.getDate());
        date.month = rtc.getMonth() < 10 ? "0" + String(rtc.getMonth()) : String(rtc.getMonth());
        date.year = rtc.getYear() < 10 ? "0" + String(rtc.getYear()) : String(rtc.getYear());
    }

    return date;
}

rtc_time rtc_control::get_time()
{

    rtc_time time;

    if (rtc.updateTime())

    {
        // agregar un 0 a la izquierda si el valor es menor a 10
        time.seconds = rtc.getSeconds() < 10 ? "0" + String(rtc.getSeconds()) : String(rtc.getSeconds());
        time.minutes = rtc.getMinutes() < 10 ? "0" + String(rtc.getMinutes()) : String(rtc.getMinutes());
        time.hours = rtc.getHours() < 10 ? "0" + String(rtc.getHours()) : String(rtc.getHours());
    }

    return time;
}
