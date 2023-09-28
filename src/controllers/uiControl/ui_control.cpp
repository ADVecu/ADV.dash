#include <Arduino.h>
#include "UI/ui.h"
#include "database/database.h"

// Widgets
#include "widgets/rpms_bar.h"

//Database instance
Database db;

/**
 * @brief Initialize the UI configuration
 */
void ui_init_config()
{
    rpmsBar rpmsBar(db.getRpmsRedline(), db.getRpmsWarning());

   
}