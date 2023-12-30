
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <driver/twai.h>
#include <driver/gpio.h>
#include "UI/ui.h"
#include "muTimer.h"
#include "controllers/canBus/can_bus.h"
#include "controllers/uiControl/ui_control.h"
#include "pcb_definitions.h"
#include "controllers/wLed/led_control.h"

/*
#include <SparkFun_RV8803.h>
#include <Adafruit_BMP280.h>
#include "SparkFun_External_EEPROM.h"
*/

#define TFT_BL 2
#define GFX_BL DF_GFX_BL // default backlight pin

pcb_def pcb; // pcb definitions struct

muTimer testTimer4;

bool pse;
bool entry = true;
int count = 0;
bool initScreen = true;

// create a task handler for the leds
TaskHandle_t test_leds_task;

/*******************************************************************************
 * Screen Driver Configuration
 *******************************************************************************/

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    pcb.cs /* CS */, pcb.sck /* SCK */, pcb.sda_display /* SDA */,
    pcb.de /* DE */, pcb.vsync /* VSYNC */, pcb.hsync /* HSYNC */, pcb.pclk /* PCLK */,
    pcb.r0 /* R0 */, pcb.r1 /* R1 */, pcb.r2 /* R2 */, pcb.r3 /* R3 */, pcb.r4 /* R4 */,
    pcb.g0 /* G0 */, pcb.g1 /* G1 */, pcb.g2 /* G2 */, pcb.g3 /* G3 */, pcb.g4 /* G4 */, pcb.g5 /* G5 */,
    pcb.b0 /* B0 */, pcb.b1 /* B1 */, pcb.b2 /* B2 */, pcb.b3 /* B3 */, pcb.b4 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
    bus,
    pcb.width /* width */, pcb.hsync_polarity /* hsync_polarity */, pcb.hsync_front_porch /* hsync_front_porch */, pcb.hsync_pulse /* hsync_pulse_width */, pcb.hsync_back_porch /* hsync_back_porch */,
    pcb.height /* height */, pcb.vsync_polarity /* vsync_polarity */, pcb.vsync_front_porch /* vsync_front_porch */, pcb.vsync_pulse /* vsync_pulse_width */, pcb.vsync_back_porch /* vsync_back_porch */,
    pcb.pclk /* pclk_active_neg */, pcb.prefer_speed /* prefer_speed */, pcb.auto_flush /* auto_flush */);

/*******************************************************************************
 * Display Driver Configuration
 *******************************************************************************/
#include "touch.h"

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[DISPLAY_DRAW_BUF];
static lv_disp_drv_t disp_drv;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  lcd->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  lcd->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      Serial.print("Data x :");
      Serial.println(touch_last_x);

      Serial.print("Data y :");
      Serial.println(touch_last_y);
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

led_control leds; // led control class

/*******************************************************************************
 * Setup Function
 *******************************************************************************/
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600); // Init Display

  lcd->begin();
  lcd->fillScreen(BLACK);
  lcd->setTextSize(2);
  delay(200);
#ifdef TFT_BL
  pinMode((gpio_num_t)pcb.tft_bl, OUTPUT);
  analogWrite(pcb.tft_bl, 255);
#endif
  lv_init();
  touch_init();
  screenWidth = lcd->width();
  screenHeight = lcd->height();

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 10);
  //  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, 480 * 272 / 10);

  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);

  /* Display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  gpio_hold_dis(pcb.v5Enable);
  pinMode(pcb.v5Enable, OUTPUT);    // Enable 5V
  digitalWrite(pcb.v5Enable, HIGH); // Enable 5V

  /* Main UI init Function*/
  ui_init(); // ui from Squareline or GUI Guider

  // CAN BUS Init
  canbus_init();

  // UI Initial Configurations
  ui_init_config();

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_10, 0); // 1 = High, 0 = Low
  // xTaskCreatePinnedToCore(light_sleep, "light_sleep", 10000, NULL, 1, NULL, APP_CPU_NUM);

  leds.init_leds();
}

/*******************************************************************************
 * Main Loop
 *******************************************************************************/
void loop()
{
  lv_timer_handler();

  // TODO: Create a xTask for this function and move to ui_control.cpp
  if (testTimer4.delayOn(initScreen, 1000))
  {
    _ui_screen_change(&ui_MainScreen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 100, 0, ui_MainScreen_screen_init);

    if (lv_scr_act() == ui_WelcomeScreen)
    {
      initScreen = false;
      _ui_screen_delete(&ui_WelcomeScreen);
    }
  }

  delay(5);
}