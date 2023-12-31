#include "FastLED.h"
#include "Arduino.h"
#include "pcb_definitions.h"
#include "led_control.h"

CRGB strip[LEDS_NUM];

TaskHandle_t ledWelcomeAnimTask;

void led_control::init_leds()
{

    FastLED.addLeds<WS2812B, LEDS_PIN, GRB>(strip, LEDS_NUM);
    FastLED.setBrightness(10);
    FastLED.show();

    xTaskCreatePinnedToCore(this->ledsWelcomeAnimation, "leds_Welcome", 10000, NULL, 1, &ledWelcomeAnimTask, APP_CPU_NUM);
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
            strip[i] = CHSV(hue+=5, 255, 255);
            
            // Show the leds
            FastLED.show();
            // now that we've shown the leds, reset the i'th led to black
             //strip[i] = CRGB::Black;
            for (int i = 0; i < LEDS_NUM; i++)
            {
                strip[i].nscale8(250);
            }
            // Wait a little bit before we loop around and do it again
            delay(50);
        }

        delay(500);

        for (int i = (LEDS_NUM)-1; i >= 0; i--)
        {
            // Set the i'th led to red
            strip[i] = CHSV(hue+=5, 255, 255);
            // Show the leds
            FastLED.show();
            // now that we've shown the leds, reset the i'th led to black
             strip[i] = CRGB::Black;
             for (int i = 0; i < LEDS_NUM; i++)
            {
                strip[i].nscale8(250);
            }
            // Wait a little bit before we loop around and do it again
            delay(25);
        }

        
        FastLED.clear();
        FastLED.show();
        vTaskSuspend(NULL);
    }
}

void led_control::triggerWelcomeAnimation()
{
    vTaskResume(ledWelcomeAnimTask);
}
