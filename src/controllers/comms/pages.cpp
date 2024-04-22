#include "pages.h"

uint16_t getPageSize(byte pageNum)
{
    // return pgm_read_word(&(ini_page_sizes[pageNum]));
}

void writeConfig(uint8_t pageNum)
{
}

uint32_t calculatePageCRC32(byte pageNum)
{
}

/** Retrieves and returns the 4 byte CRC32 checksum for a given calibration page from EEPROM.
@param calibrationPageNum - Config page number
*/
uint32_t readCalibrationCRC32(uint8_t calibrationPageNum)
{
}