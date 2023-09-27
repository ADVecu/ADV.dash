#ifndef __DATABASE__
#define __DATABASE__

#include <Arduino.h>

/**
 * @brief Database class
 * Is used to store user settings in the flash memory
 */
class Database
{
public:
    /*******************************************************************************
     * RPMS Data
     *******************************************************************************/
    /**
     * @brief Saves the redline rpms setting in the flash memory
     * @param redline Rpms at which the redline should be set, Range: 5000 - 10000
     */
    void saveRpmsRedline(uint16_t redline);

    /**
     * @brief Saves the warning rpms setting in the flash memory
     * @param warning Rpms at which the warning should be set, Range: 2000 - RedLine setting
     */
    void saveRpmsWarning(uint16_t warning);

    /**
     * @brief Gets the redline rpms setting from the flash memory
     * @return uint16_t Rpms at which the redline is set, Range: 5000 - 10000
     */
    uint16_t getRpmsRedline();

    /**
     * @brief Gets the warning rpms setting from the flash memory
     * @return uint16_t Rpms at which the warning is set, Range: 2000 - RedLine setting
     */
    uint16_t getRpmsWarning();
};

#endif // __DATABASE__