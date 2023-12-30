#include "Adafruit_NeoPixel.h"
#include "Arduino.h"
#include "pcb_definitions.h"
#include "led_control.h"

Adafruit_NeoPixel strip(LEDS_NUM, LEDS_PIN, NEO_GRB + NEO_KHZ800);

void led_control::init_leds()
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strip.setBrightness(10);

    xTaskCreatePinnedToCore(this->ledsWelcomeAnimation, "leds_Welcome", 10000, NULL, 1, NULL, APP_CPU_NUM);
}

void led_control::ledsWelcomeAnimation(void *pvParameters)
{
    while (1)
    {
        int firstPixelHue = 0; // First pixel starts at red (hue 0)
        for (int a = 0; a < 10; a++)
        { // Repeat 30 times...
            for (int b = 0; b < 3; b++)
            {                  //  'b' counts from 0 to 2...
                strip.clear(); //   Set all pixels in RAM to 0 (off)
                // 'c' counts up from 'b' to end of strip in increments of 3...
                for (int c = b; c < strip.numPixels(); c += 3)
                {
                    // hue of pixel 'c' is offset by an amount to make one full
                    // revolution of the color wheel (range 65536) along the length
                    // of the strip (strip.numPixels() steps):
                    int hue = firstPixelHue + c * 65536L / strip.numPixels();
                    uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
                    strip.setPixelColor(c, color);                       // Set pixel 'c' to value 'color'
                }
                strip.show();                // Update strip with new contents
                delay(50);                 // Pause for a moment
                firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
            }
        }

        strip.clear();
        strip.show();
        vTaskDelete(NULL);
    }
}
