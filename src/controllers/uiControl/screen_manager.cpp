#include <Arduino.h>
#include <lvgl.h>
#include "pcb_definitions.h"
#include "UI/ui.h"
#include "muTimer.h"
#include "controllers/uiControl/screen_manager.h"
#include "controllers/wLed/led_control.h"

bool sw12vState;
bool wakeUpState;
bool swOpen;
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

muTimer testTimer4;
muTimer testTimer5;
muTimer testTimer6;
muTimer testTimer7;
muTimer testTimer8;

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

    esp_sleep_enable_ext1_wakeup(0xC00, ESP_EXT1_WAKEUP_ANY_LOW); // 1 = High, 0 = Low

    wakeUpMask = esp_sleep_get_ext1_wakeup_status();
    if (wakeUpMask != 0)
    {
        wakeUpGPIO = log(wakeUpMask) / log(2);
    }
    else
    {
        wakeUpGPIO = 0;
    }
}

void screen_manager(void *pvParameters)
{
    while (1)
    {
        sw12vState = digitalRead(pcb2.sw12v);
        wakeUpState = digitalRead(pcb2.wakeUp);

        if (sw12vState == HIGH && wakeUpState == HIGH && wakeUpGPIO == 0)
        {
            delay(2000);
            ledControl2.clearLeds();
            digitalWrite(pcb2.v5Enable, LOW);
            gpio_hold_en(pcb2.v5Enable);
            esp_deep_sleep_start();
        }

        if (!isOn && sw12vState == HIGH && wakeUpState == LOW || wakeUpGPIO == pcb2.wakeUp)
        {
            if (testTimer4.delayOn(animScreen, 1000))
            {
                lv_obj_set_style_opa(ui_proIMG, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

                titleAnim_Animation(ui_welcomeLabel, 0);
                carAnim_Animation(ui_carIMG, 2000);
                bannerAnim_Animation(ui_bannerTextA, 2500);
                proAnim_Animation(ui_proBannerIMG, 2500);

                animScreen = false;
            }

            if (testTimer6.delayOn(sw12vState, 60000))
            {
                ledControl2.clearLeds();
                digitalWrite(pcb2.v5Enable, LOW);
                gpio_hold_en(pcb2.v5Enable);
                esp_deep_sleep_start();
            }
        }

        if (!sw12vState && mainScreen)
        {

            ui_MainScreen_screen_init();
            lv_scr_load_anim(ui_MainScreen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 100, 1000, false);

            mainScreen = false;
            isOn = true;
            sw12vState = false;
            Serial.println("Main Screen");
        }

        if (isOn && sw12vState == HIGH)
        {
            if (testTimer7.delayOn(finalScreen, 1000))
            {
                _ui_screen_change(&ui_FinalScreen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 100, 0, ui_FinalScreen_screen_init);

                finalScreen = false;
                mainScreen = true;
                isOn = false;
                isOff = true;
            }
        }

        if (isOff && sw12vState == HIGH)
        {
            if (testTimer8.delayOn(finalOff, 30000))
            {
                ledControl2.clearLeds();
                digitalWrite(pcb2.v5Enable, LOW);
                gpio_hold_en(pcb2.v5Enable);
                esp_deep_sleep_start();
            }
        }

        vTaskDelay(10);
    }
}