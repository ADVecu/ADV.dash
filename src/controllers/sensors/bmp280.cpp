#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include "bmp280.h"



Adafruit_BMP280 bmp;


void bmp280::init_bmp280()
{
    if (!bmp.begin())
    {
        Serial.println("Could not find a valid BMP280 sensor");
    }

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

float bmp280::get_pressure()
{
    return bmp.readPressure() / 100.0F;
}

float bmp280::get_temperature()
{
    return bmp.readTemperature();
}

float bmp280::get_altitude()
{
    return bmp.readAltitude(1013.25);
}

atmospheric_data bmp280::get_atmospheric_data()
{
    atmospheric_data data;

    data.pressure = bmp.readPressure() / 1000.0F;
    data.temperature = bmp.readTemperature();
    data.altitude = bmp.readAltitude(1017.25);

    return data;
}