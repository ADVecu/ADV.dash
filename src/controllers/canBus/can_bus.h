#pragma once

#ifndef CAN_BUS_H_
#define CAN_BUS_H_

#include <Arduino.h>

extern QueueHandle_t canbus_queue;

typedef struct{

    uint16_t warning_counter;
    uint16_t last_error;
    uint8_t main_relay_act;
    uint8_t fuel_pump_act;
    uint8_t check_engine_act;
    uint8_t current_gear;
    uint16_t rpms;
    uint16_t ignition_timing;
    uint8_t inj_duty;
    uint8_t speed;
    int16_t tps;
    uint16_t map;
    uint8_t coolant_temp;
    uint8_t air_temp;
    uint8_t aux1_temp;
    uint8_t aux2_temp;
    uint16_t oil_pressure;
    uint16_t battery_voltage;
    uint8_t fuel_level;
    uint16_t inj_pwm;
    uint16_t fuel_used;
    uint16_t fuel_flow;
    uint16_t fuel_trim;
    uint16_t fuel_pressure;
    uint16_t o2_sensor;
     
} canbus_data_t;

void canbus_init();
void canbus_read(void *pvParameters);

#endif // CAN_BUS_H_
