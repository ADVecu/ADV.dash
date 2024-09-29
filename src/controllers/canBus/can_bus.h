#pragma once

#ifndef CAN_BUS_H_
#define CAN_BUS_H_

#include <Arduino.h>

extern QueueHandle_t canbus_queue;

typedef struct
{

    uint16_t warning_counter;
    uint16_t last_error;
    bool check_engine_act;
    uint8_t current_gear;
    uint16_t rpms;
    int8_t ignition_timing;
    uint8_t inj_duty;
    uint8_t speed;
    uint16_t tps;
    uint16_t map;
    int8_t coolant_temp;
    int8_t air_temp;
    int8_t aux1_temp;
    int8_t aux2_temp;
    uint16_t oil_pressure;
    uint16_t battery_voltage;
    uint8_t fuel_level;
    uint16_t inj_pwm;
    uint8_t ing_duty;
    uint8_t mcu_temp;
    uint16_t fuel_pressure;
    uint16_t o2_sensor;
    uint16_t oil_temp;
    uint8_t fwPressure;
    int8_t fwTemp;
    uint8_t fwBatteryVoltage;
    uint8_t rwPressure;
    int8_t rwTemp;
    uint8_t rwBatteryVoltage;
    uint8_t ambientTemp;
    uint16_t fuel_trim;
    uint16_t fuel_flow;
    uint16_t fuel_used;
    uint8_t enterBT;
    uint8_t backBT;
    uint8_t upBT;
    uint8_t downBT;
    uint8_t aux1BT;
    uint8_t aux2BT;
    uint8_t aux3BT;
    uint8_t dir_izq;
    uint8_t dir_der;
    uint8_t high_bean;
    uint8_t low_bean;
    uint8_t fog_light;
    uint8_t coolant_level;

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
    float fuel_flow;
    int8_t tyre_temp;
};

extern canbus_encode_msg canbus_encode;

void canbus_init();
void canbus_read(void *pvParameters);
void send_keep_alive_frame();

#endif // CAN_BUS_H_
