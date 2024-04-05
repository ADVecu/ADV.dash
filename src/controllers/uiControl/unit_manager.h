#ifndef _UNIT_MANAGER_H
#define _UNIT_MANAGER_H

#include <Arduino.h>

/**
 * @brief Get the Temperature reading in the correct unit
 * @param value temperature reding raw from canbus
 * @return Temperature in the unit set by the user
 */
uint16_t getTemp_Number(uint16_t value);

/**
 * @brief Get the Pressure reading in the correct unit
 * @param value pressure reding raw from canbus
 * @return Pressure in the unit set by the user
 */
uint16_t getPressure_Number(uint16_t value);

/**
 * @brief Get the Speed reading in the correct unit
 * @param value speed reding raw from canbus
 * @return Speed in the unit set by the user
 */
uint16_t getSpeed_Number(uint16_t value);

/**
 * @brief Get the Battery Voltage reading in the correct unit
 * @param value battery voltage reding raw from canbus
 * @return Battery Voltage in Volts
 */
uint16_t getBatteryVoltage_Number(uint16_t value);

/**
 * @brief Get the Temperature reading in the correct unit formatted as a string
 * @param value temperature reding raw from canbus
 * @return Temperature in the unit set by the user formatted as a string
 */
String getTemp_String(uint16_t value);

/**
 * @brief Get the Pressure reading in the correct unit formatted as a string
 * @param value pressure reding raw from canbus
 * @return Pressure in the unit set by the user formatted as a string
 */
String getPressure_String(uint16_t value);

/**
 * @brief Get the Speed reading in the correct unit formatted as a string
 * @param value speed reding raw from canbus
 * @return Speed in the unit set by the user formatted as a string
 */
String getSpeed_String(uint16_t value);

/**
 * @brief Get the Battery Voltage reading in the correct unit formatted as a string
 * @param value battery voltage reding raw from canbus
 * @return Battery Voltage in Volts formatted as a string
 */
String getBatteryVoltage_String(uint16_t value);

/**
 * @brief Get the database data for the units and store them in RAM
 */
void initUnitManager();

#endif