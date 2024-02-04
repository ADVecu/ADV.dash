#ifndef BMP280_H
#define BMP280_H

#include <Arduino.h>

struct atmospheric_data
{
    float pressure;
    float temperature;
    float altitude;
};

class bmp280
{

public:
    void init_bmp280();
    float get_pressure();
    float get_temperature();
    float get_altitude();
    atmospheric_data get_atmospheric_data();

};

#endif // BMP280_H
