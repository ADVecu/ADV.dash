#ifndef __DATABASE__
#define __DATABASE__

#include <Arduino.h>

class Database
{
public:
    // RPMs Data
    void saveRpmsRedline(uint16_t redline);
    void saveRpmsWarning(uint16_t warning);
    uint16_t getRpmsRedline();
    uint16_t getRpmsWarning();
};

#endif // __DATABASE__