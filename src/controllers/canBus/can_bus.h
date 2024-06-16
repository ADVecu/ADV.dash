#pragma once

#ifndef CAN_BUS_H_
#define CAN_BUS_H_

#include <Arduino.h>

extern QueueHandle_t canbus_queue;


typedef struct
{

    uint16_t warning_counter = 0;
    uint16_t last_error = 0;
    bool check_engine_act = 0;
    uint8_t current_gear = 0;
    uint16_t rpms = 0;
    int8_t ignition_timing = 0;
    uint8_t inj_duty = 0;
    uint8_t speed = 0;
    uint16_t tps = 0;
    uint16_t map = 0;
    int8_t coolant_temp = 0;
    int8_t air_temp = 0;
    int8_t aux1_temp = 0;
    int8_t aux2_temp = 0;
    uint16_t oil_pressure = 0;
    uint16_t battery_voltage = 0;
    uint8_t fuel_level = 0;
    uint16_t inj_pwm = 0;
    uint8_t ing_duty = 0;
    uint8_t mcu_temp = 0;
    uint16_t fuel_pressure = 0;
    uint16_t o2_sensor = 0;

} canbus_data_t;

struct canbus_encode_msg
{
    float levels_duty;
    float battery_voltage;
    int8_t temps;
    float pressures;
    float ign_advance;
    float pwm;
    float lambda;
    float afr;
    float tps;
    
};

extern canbus_encode_msg canbus_encode;

void canbus_init();
void canbus_read(void *pvParameters);

#endif // CAN_BUS_H_
