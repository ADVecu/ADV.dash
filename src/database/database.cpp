#include <Preferences.h>
#include <Arduino.h>

#include "database.h"

#define DATABASE_NAME "config"

Preferences preferences;

/*******************************************************************************
 * RPMs Data
 *******************************************************************************/
void Database::saveRpmsRedline(uint16_t redline)
{
    if (redline <= 10000 && redline >= 5000)
    {
        preferences.begin(DATABASE_NAME, false);
        preferences.putUShort("rpmsRedline", redline);
        preferences.end();
    }
}

void Database::saveRpmsWarning(uint16_t warning)
{
    if (warning < 5000 && warning >= 2000)
    {
        preferences.begin(DATABASE_NAME, false);
        preferences.putUShort("rpmsWarning", warning);
        preferences.end();
    }
}

uint16_t Database::getRpmsRedline()
{
    preferences.begin(DATABASE_NAME, true);
    uint16_t redline = preferences.getUShort("rpmsRedline", 8000);
    preferences.end();

    return redline;
}

uint16_t Database::getRpmsWarning()
{
    preferences.begin(DATABASE_NAME, true);
    uint16_t warning = preferences.getUShort("rpmsWarning", 6500);
    preferences.end();

    return warning;
}

/*******************************************************************************
 * RPMs Data
 *******************************************************************************/