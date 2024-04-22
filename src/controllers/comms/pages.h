#ifndef PAGES_H
#define PAGES_H

#include "Arduino.h"

uint16_t getPageSize(byte pageNum);

/** Write a table or map to EEPROM storage.
Takes the current configuration (config pages and maps)
and writes them to EEPROM as per the layout defined in storage.h.
*/
void writeConfig(uint8_t pageNum);

uint32_t calculatePageCRC32(byte pageNum);

/** Retrieves and returns the 4 byte CRC32 checksum for a given calibration page from EEPROM.
@param calibrationPageNum - Config page number
*/
uint32_t readCalibrationCRC32(uint8_t calibrationPageNum);

#endif // PAGES_H