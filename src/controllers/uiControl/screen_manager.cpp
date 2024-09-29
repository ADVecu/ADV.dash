#include <Arduino.h>
#include <lvgl.h>
#include "pcb_definitions.h"
#include "UI/ui.h"
#include "muTimer.h"
#include "controllers/canBus/can_bus.h"
#include "controllers/uiControl/screen_manager.h"
#include "controllers/wLed/led_control.h"

bool sw12vState;
bool wakeUpState;
bool swOpen;
bool reset = false;
bool isOn = false;
bool isOff = false;
uint64_t wakeUpMask;
uint64_t wakeUpGPIO;
pcb_def pcb2;

led_control ledControl2;

bool initScreen = true;
bool animScreen = true;
bool mainScreen = true;
bool finalScreen = true;
bool finalOff = true;

muTimer delayOffScreen;
muTimer delayMainScreen;
muTimer delaySleep;
muTimer keepAliveRate;

void screen_manager_init()
{
    xTaskCreatePinnedToCore(
        screen_manager,  /* Task function. */
        "ScreenManager", /* name of task. */
        10000,           /* Stack size of task */
        NULL,            /* parameter of the task */
        1,               /* priority of the task */
        NULL,            /* Task handle to keep track of created task */
        1);

    esp_sleep_enable_ext0_wakeup(pcb2.sw12v,0); //1 = High, 0 = Low
/*
    wakeUpMask = esp_sleep_get_ext1_wakeup_status();
    if (wakeUpMask != 0)
    {
        wakeUpGPIO = log(wakeUpMask) / log(2);
    }
    else
    {
        wakeUpGPIO = 0;
    }
    */
}

void screen_manager(void *pvParameters)
{
    while (1)
    {
        sw12vState = digitalRead(pcb2.sw12v);
        wakeUpState = digitalRead(pcb2.wakeUp);

        lv_obj_t *currentScreen = lv_scr_act();
/*
        Serial.print("12V Switch: ");
        Serial.println(sw12vState);
        Serial.print("WakeUp Switch: ");
        Serial.println(wakeUpState);
*/
        if (sw12vState == HIGH)
        {
            if (delayOffScreen.delayOn(sw12vState, 1000))
            {
                lv_scr_load_anim(ui_FinalScreen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 100, 1000, false);
            }

            if (delaySleep.delayOn(sw12vState, 25000))
            {
                ledControl2.clearLeds();
                analogWrite(pcb2.tft_bl, 0);
                reset = true;
                
            }   
        } else {
            delayOffScreen.cycleResetToOff();
            delaySleep.cycleResetToOff();
        }

        if (sw12vState == LOW)
        {
            if (reset) esp_restart();
            

            if ((currentScreen != ui_MainScreen) && (currentScreen != ui_WelcomeScreen) )
            {
                lv_scr_load_anim(ui_MainScreen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 100, 2000, false);
            } 

            if (keepAliveRate.cycleTrigger(1000))
            {
                send_keep_alive_frame();
            }

            
        }

        vTaskDelay(10);
    }
}