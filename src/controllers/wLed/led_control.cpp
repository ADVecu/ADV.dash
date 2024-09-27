
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "Arduino.h"
#include "pcb_definitions.h"
#include "led_control.h"
#include "../canBus/can_bus.h"
#include "muTimer.h"

xSemaphoreHandle semaphore = NULL;
CRGB strip[LEDS_NUM];  

TaskHandle_t ledWelcomeAnimTask;
TaskHandle_t commit_task;

muTimer FlashTimer;

indicatorLedState indicatorLedST;
indicatorLedStatePrevious indicatorLedStateP;

bool initAnimationComplete = false;

void led_control::init_leds()
{

    FastLED.addLeds<APA102, LEDS_PIN, LEDS_PIN_CLOCK, RGB>(strip, LEDS_NUM);  
    FastLED.setBrightness(50);
    FastLED.show();

    xTaskCreatePinnedToCore(this->ledsWelcomeAnimation, "leds_Welcome", 10000, NULL, 1, &ledWelcomeAnimTask, 0);
    xTaskCreatePinnedToCore(ledControlTask, "ledControlTask", 10000, NULL, 4, NULL, 0);

    commit_task = NULL;
    semaphore = xSemaphoreCreateBinary();

    xTaskCreatePinnedToCore(
        commitTaskProcedure, /* Task function. */
        "ShowRunnerTask",    /* name of task. */
        10000,               /* Stack size of task */
        NULL,                /* parameter of the task */
        10,                  /* priority of the task */
        &commit_task,        /* Task handle to keep track of created task */
        0);
}

void led_control::ledsWelcomeAnimation(void *pvParameters)
{
    while (1)
    {
        static uint8_t hue = 0;

        // First slide the led in one direction
        for (int i = 0; i < LEDS_NUM; i++)
        {
            // Set the i'th led to red
            strip[i] = CHSV(hue++, 255, 255);

            // Show the leds
            FastLED.show();
            // now that we've shown the leds, reset the i'th led to black
            // strip[i] = CRGB::Black;
            // Wait a little bit before we loop around and do it again
            delay(50);
        }

        delay(500);

        for (int i = (LEDS_NUM)-1; i >= 0; i--)
        {
            // Set the i'th led to red
            strip[i] = CHSV(hue++, 255, 255);
            // Show the leds
            FastLED.show();
            // now that we've shown the leds, reset the i'th led to black
            strip[i] = CRGB::Black;

            // Wait a little bit before we loop around and do it again
            delay(25);
        }

        FastLED.clear();
        FastLED.show();
        initAnimationComplete = true;
        vTaskSuspend(NULL);
    }
}

void led_control::triggerWelcomeAnimation()
{
    initAnimationComplete = false;
    vTaskResume(ledWelcomeAnimTask);
}

void led_control::clearLeds()
{
    FastLED.clear();
    FastLED.show();
}

void ledControlTask(void *pvParameters)
{
    canbus_data_t canbus_data;
    int ledsOn = 0;
    int ledsOnPrev = 0;

    while (1)
    {
        if (xQueuePeek(canbus_queue, &canbus_data, portMAX_DELAY) == pdTRUE && initAnimationComplete)
        {
            //TODO: Change Hardcoded values for rpms leds activation
            ledsOn = map(canbus_data.rpms, 6000, 9000, LEDS_RPMS_START, LEDS_RPMS_END);

            if (ledsOn != ledsOnPrev && canbus_data.rpms < 9000)
            {
                for (int i = LEDS_RPMS_START; i < LEDS_RPMS_END; i++)
                {
                    strip[i] = 0;
                }

                if (canbus_data.rpms < 6000)
                {

                    for (int i = LEDS_RPMS_START; i < ledsOn; i++)
                    {
                        if (i >= LEDS_RPMS_LOW && i <= LEDS_RPMS_MID)
                        {
                            strip[i].setRGB(0, 255, 0);
                        }
                        else if (i >= LEDS_RPMS_MID && i <= LEDS_RPMS_MAX)
                        {
                            strip[i].setRGB(255, 0, 0);
                        }
                        else
                        {
                            strip[i].setRGB(0, 0, 255);
                        }
                    }
                    commit();
                }
            }
            else if (canbus_data.rpms >= 9000)
            {
                if (FlashTimer.cycleOnOff(300, 300))
                {
                    static boolean ps0; // stores the pixel state
                    ps0 = !ps0;         // toggle on/off state
                    if (ps0 == 1)
                    {
                        for (int i = LEDS_RPMS_START; i < LEDS_RPMS_END; i++)
                        {
                            strip[i].setRGB(255, 0, 0);
                        }
                    }
                    else
                    {
                        for (int i = LEDS_RPMS_START; i < LEDS_RPMS_END; i++)
                        {
                            strip[i].setRGB(0, 0, 0);
                        }
                    }

                    commit();
                } // reset
            }

            if (canbus_data.fuel_level <= 20 && indicatorLedST.FuelST != indicatorLedStateP.FuelST)
            {
                indicatorLedStateP.FuelST = indicatorLedST.FuelST;
                indicatorLedST.FuelST = true;
                strip[FUEL_LED].setRGB(255, 0, 0);
                commit();
            }
            else if (canbus_data.fuel_level > 20 && indicatorLedST.FuelST != indicatorLedStateP.FuelST)
            {
                indicatorLedStateP.FuelST = indicatorLedST.FuelST;
                indicatorLedST.FuelST = false;
                strip[FUEL_LED].setRGB(0, 0, 0);
                commit();
            }

            if (canbus_data.battery_voltage <= 12000 && indicatorLedST.BatteryST != indicatorLedStateP.BatteryST)
            {
                indicatorLedStateP.BatteryST = indicatorLedST.BatteryST;
                indicatorLedST.BatteryST = true;
                strip[BATTERY_LIGHT].setRGB(255, 0, 0);
                commit();
            }
            else if (canbus_data.battery_voltage > 12000 && indicatorLedST.BatteryST != indicatorLedStateP.BatteryST)
            {
                indicatorLedStateP.BatteryST = indicatorLedST.BatteryST;
                indicatorLedST.BatteryST = false;
                strip[BATTERY_LIGHT].setRGB(0, 0, 0);
                commit();
            }

            if (canbus_data.dir_der == 1 && indicatorLedST.RightTurnST != indicatorLedStateP.RightTurnST)
            {
                indicatorLedStateP.RightTurnST = indicatorLedST.RightTurnST;
                indicatorLedST.RightTurnST = true;
                strip[RIGHT_DIR].setRGB(0, 255, 0);
                commit();
            }
            else if (canbus_data.dir_der == 0 && indicatorLedST.RightTurnST != indicatorLedStateP.RightTurnST)
            {
                indicatorLedStateP.RightTurnST = indicatorLedST.RightTurnST;
                indicatorLedST.RightTurnST = false;
                strip[RIGHT_DIR].setRGB(0, 0, 0);
                commit();
            }

            if (canbus_data.dir_izq == 1 && indicatorLedST.LeftTurnST != indicatorLedStateP.LeftTurnST)
            {
                indicatorLedStateP.LeftTurnST = indicatorLedST.LeftTurnST;
                indicatorLedST.LeftTurnST = true;
                strip[LEFT_DIR].setRGB(0, 255, 0);
                commit();
            }
            else if (canbus_data.dir_izq == 0 && indicatorLedST.LeftTurnST != indicatorLedStateP.LeftTurnST)
            {
                indicatorLedStateP.LeftTurnST = indicatorLedST.LeftTurnST;
                indicatorLedST.LeftTurnST = false;
                strip[LEFT_DIR].setRGB(0, 0, 0);
                commit();
            }

            if (canbus_data.high_bean == 1 && indicatorLedST.HighBeamST != indicatorLedStateP.HighBeamST)
            {
                indicatorLedStateP.HighBeamST = indicatorLedST.HighBeamST;
                indicatorLedST.HighBeamST = true;
                strip[HIGH_BEAM].setRGB(0, 0, 255);
                commit();
            }
            else if (canbus_data.high_bean == 0 && indicatorLedST.HighBeamST != indicatorLedStateP.HighBeamST)
            {
                indicatorLedStateP.HighBeamST = indicatorLedST.HighBeamST;
                indicatorLedST.HighBeamST = false;
                strip[HIGH_BEAM].setRGB(0, 0, 0);
                commit();
            }

            ledsOnPrev = ledsOn;

            vTaskDelay( 10 / portTICK_PERIOD_MS );
        }
    }
}

void commitTaskProcedure(void *arg)
{
    while (true)
    {
        while (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 1)
            ;
        FastLED.show();
        xSemaphoreGive(semaphore);
    }
}

void commit()
{
    xTaskNotifyGive(commit_task);
    while (xSemaphoreTake(semaphore, portMAX_DELAY) != pdTRUE)
        ;
}