#include "eeprom.h"

EEPROM_manager::EEPROM_manager()
{
    eeprom.setMemoryType(512);

    if (eeprom.begin() == false)
    {
        Serial.println(F("No memory detected. Freezing."));
    }
    else
    {
        Serial.println(F("Memory detected!"));
    }
}