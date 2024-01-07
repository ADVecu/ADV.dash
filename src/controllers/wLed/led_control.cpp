
#include "NeoPixelBusLg.h"
#include "Arduino.h"
#include "pcb_definitions.h"
#include "led_control.h"
#include "../canBus/can_bus.h"
#include "muTimer.h"

xSemaphoreHandle semaphore = NULL;

NeoPixelBusLg<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod> strip(LEDS_NUM, LEDS_PIN);

TaskHandle_t ledWelcomeAnimTask;
TaskHandle_t commit_task;

muTimer FlashTimer;

indicatorLedState indicatorLedST;
indicatorLedStatePrevious indicatorLedStateP;

bool initAnimationComplete = false;

void led_control::init_leds()
{

    strip.Begin();
    strip.SetLuminance(50);
    strip.Show();

    xTaskCreatePinnedToCore(this->ledsWelcomeAnimation, "leds_Welcome", 10000, NULL, 1, &ledWelcomeAnimTask, 1);
    xTaskCreatePinnedToCore(ledControlTask, "ledControlTask", 10000, NULL, 10, NULL, 0);

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
            strip.SetPixelColor(i, HsbColor(hue += 0.1f, 1.0f, 1.0f));

            // Show the leds
            strip.Show();
            // now that we've shown the leds, reset the i'th led to black
            // strip[i] = CRGB::Black;
            // Wait a little bit before we loop around and do it again
            delay(50);
        }

        delay(500);

        for (int i = (LEDS_NUM)-1; i >= 0; i--)
        {
            // Set the i'th led to red
            strip.SetPixelColor(i, HsbColor(hue += 0.1f, 1.0f, 1.0f));
            // Show the leds
            strip.Show();
            // now that we've shown the leds, reset the i'th led to black
            strip.SetPixelColor(i, 0);

            // Wait a little bit before we loop around and do it again
            delay(25);
        }

        strip.ClearTo(0);
        strip.Show();
        initAnimationComplete = true;
        vTaskSuspend(NULL);
    }
}

void led_control::triggerWelcomeAnimation()
{
    initAnimationComplete = false;
    vTaskResume(ledWelcomeAnimTask);
}


void ledControlTask(void *pvParameters)
{
    canbus_data_t canbus_data;
    int ledsOn = 0;
    int ledsOnPrev = 0;

    while (1)
    {
        if (xQueueReceive(canbus_queue, &canbus_data, portMAX_DELAY) == pdTRUE && initAnimationComplete)
        {
            ledsOn = map(canbus_data.rpms, 3000, 6000, LEDS_RPMS_START, LEDS_RPMS_END);

            if (ledsOn != ledsOnPrev && canbus_data.rpms < 6000)
            {
                for (int i = LEDS_RPMS_START; i < LEDS_RPMS_END; i++)
                {
                    strip.SetPixelColor(i, 0);
                }

                if (canbus_data.rpms < 6000)
                {

                    for (int i = LEDS_RPMS_START; i < ledsOn; i++)
                    {
                        if (i >= LEDS_RPMS_LOW && i <= LEDS_RPMS_MID)
                        {
                            strip.SetPixelColor(i, RgbColor(0, 255, 0));
                        }
                        else if (i >= LEDS_RPMS_MID && i <= LEDS_RPMS_MAX)
                        {
                            strip.SetPixelColor(i, RgbColor(255, 0, 0));
                        }
                        else
                        {
                            strip.SetPixelColor(i, RgbColor(0, 0, 255));
                        }
                    }
                    commit();
                }
            }
            else if (canbus_data.rpms >= 6000)
            {
                if (FlashTimer.cycleOnOff(100, 100))
                {
                    static boolean ps0; // stores the pixel state
                    ps0 = !ps0;         // toggle on/off state
                    if (ps0 == 1)
                    {
                        for (int i = LEDS_RPMS_START; i < LEDS_RPMS_END; i++)
                        {
                            strip.SetPixelColor(i, RgbColor(255, 0, 0));
                        }
                    }
                    else
                    {
                        for (int i = LEDS_RPMS_START; i < LEDS_RPMS_END; i++)
                        {
                            strip.SetPixelColor(i, 0);
                        }
                    }

                    commit();
                } // reset
            }

            if (canbus_data.fuel_level <= 20 && indicatorLedST.FuelST != indicatorLedStateP.FuelST)
            {
                indicatorLedStateP.FuelST = indicatorLedST.FuelST;
                indicatorLedST.FuelST = true;
                strip.SetPixelColor(FUEL_LED, RgbColor(255, 255, 0));
                commit();
            }
            else if (canbus_data.fuel_level > 20 && indicatorLedST.FuelST != indicatorLedStateP.FuelST)
            {
                indicatorLedStateP.FuelST = indicatorLedST.FuelST;
                indicatorLedST.FuelST = false;
                strip.SetPixelColor(FUEL_LED, 0);
                commit();
            }

            if (canbus_data.battery_voltage <= 1200 && indicatorLedST.BatteryST != indicatorLedStateP.BatteryST)
            {
                indicatorLedStateP.BatteryST = indicatorLedST.BatteryST;
                indicatorLedST.BatteryST = true;
                strip.SetPixelColor(BATTERY_LIGHT, RgbColor(255, 0, 0));
                commit();
            }
            else if (canbus_data.battery_voltage > 1200 && indicatorLedST.BatteryST != indicatorLedStateP.BatteryST)
            {
                indicatorLedStateP.BatteryST = indicatorLedST.BatteryST;
                indicatorLedST.BatteryST = false;
                strip.SetPixelColor(BATTERY_LIGHT, 0);
                commit();
            }

            ledsOnPrev = ledsOn;

            delay(10);
        }
    }
}

void commitTaskProcedure(void *arg)
{
    while (true)
    {
        while (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 1)
            ;
        strip.Show();
        while (!strip.CanShow())
            ;
        xSemaphoreGive(semaphore);
    }
}

void commit()
{
    xTaskNotifyGive(commit_task);
    while (xSemaphoreTake(semaphore, portMAX_DELAY) != pdTRUE)
        ;
}