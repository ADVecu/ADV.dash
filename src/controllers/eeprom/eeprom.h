#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include <SparkFun_External_EEPROM.h>

class EEPROM_manager
{
private:
    ExternalEEPROM eeprom;
    uint8_t _eepromAddress;
    uint8_t _eepromData;

public:
    EEPROM_manager();
    void writeEEPROM(uint8_t address, uint8_t data);
    uint8_t readEEPROM(uint8_t address);
};

#endif // EEPROM_H