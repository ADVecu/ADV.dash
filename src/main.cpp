
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <driver/twai.h>
#include <driver/gpio.h>
#include <Wire.h>
#include "UI/ui.h"
#include "muTimer.h"
#include "controllers/canBus/can_bus.h"
#include "controllers/uiControl/ui_control.h"
#include "pcb_definitions.h"
#include "controllers/wLed/led_control.h"
#include "soc/gpio_periph.h"
#include "hal/gpio_hal.h"
#include "controllers/uiControl/screen_manager.h"
#include "controllers/rtc/rtc_control.h"
#include "controllers/sensors/bmp280.h"
#include "controllers/uiControl/unit_manager.h"
#include "controllers/comms/comms.h"
//  #include "SparkFun_External_EEPROM.h"

#define TFT_BL 2
#define GFX_BL DF_GFX_BL // default backlight pin
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

pcb_def pcb;                // pcb definitions struct
rtc_control rtc_controller; // rtc control class
bmp280 bmp280_controller;   // bmp280 control class

bool pse;
bool entry = true;
int count = 0;

// create a task handler for the leds
TaskHandle_t test_leds_task;

/*******************************************************************************
 * Screen Driver Configuration
 *******************************************************************************/

class LGFX : public lgfx::LGFX_Device
{
public:
  lgfx::Bus_RGB _bus_instance;
  lgfx::Panel_RGB _panel_instance;
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;
      cfg.pin_d0 = pcb.b0;  // B0
      cfg.pin_d1 = pcb.b1;  // B1
      cfg.pin_d2 = pcb.b2;  // B2
      cfg.pin_d3 = pcb.b3;  // B3
      cfg.pin_d4 = pcb.b4;  // B4
      cfg.pin_d5 = pcb.g0;  // G0
      cfg.pin_d6 = pcb.g1;  // G1
      cfg.pin_d7 = pcb.g2;  // G2
      cfg.pin_d8 = pcb.g3;  // G3
      cfg.pin_d9 = pcb.g4;  // G4
      cfg.pin_d10 = pcb.g5; // G5
      cfg.pin_d11 = pcb.r0; // R0
      cfg.pin_d12 = pcb.r1; // R1
      cfg.pin_d13 = pcb.r2; // R2
      cfg.pin_d14 = pcb.r3; // R3
      cfg.pin_d15 = pcb.r4; // R4
      cfg.pin_henable = pcb.de;
      cfg.pin_vsync = pcb.vsync;
      cfg.pin_hsync = pcb.hsync;
      cfg.pin_pclk = pcb.pclk;
      cfg.freq_write = pcb.prefer_speed;
      cfg.hsync_polarity = pcb.hsync_polarity;
      cfg.hsync_front_porch = pcb.hsync_front_porch;
      cfg.hsync_pulse_width = pcb.hsync_pulse;
      cfg.hsync_back_porch = pcb.hsync_back_porch;
      cfg.vsync_polarity = pcb.vsync_polarity;
      cfg.vsync_front_porch = pcb.vsync_front_porch;
      cfg.vsync_pulse_width = pcb.vsync_pulse;
      cfg.vsync_back_porch = pcb.vsync_back_porch;
      cfg.pclk_active_neg = pcb.pclk_active_neg;
      cfg.de_idle_high = 0;
      cfg.pclk_idle_high = 0;
      _bus_instance.config(cfg);
    }
    {
      auto cfg = _panel_instance.config();
      cfg.memory_width = 800;
      cfg.memory_height = 480;
      cfg.panel_width = 800;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      _panel_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);
    setPanel(&_panel_instance);
  }
};

LGFX lcd;

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
  lcd.pushImageDMA(area->x1, area->y1, w, h, (lgfx::rgb565_t *)&color_p->full);
#else
  lcd.pushImageDMA(area->x1, area->y1, w, h, (lgfx::rgb565_t *)&color_p->full);
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
  Serial.begin(115200); // Init Display

  delay(200);

  lv_init();
  touch_init();

  lcd.begin();
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextSize(2);
  delay(200);

  screenWidth = lcd.width();
  screenHeight = lcd.height();

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
  if (BOARD_HAS_TOUCH_CAPABILITY)
  {
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
  }

  if (BOARD_HAS_SLEEP_CAPABILITY)
  {
    gpio_hold_dis(pcb.v5Enable);
    pinMode(pcb.v5Enable, OUTPUT);    // Enable 5V
    digitalWrite(pcb.v5Enable, HIGH); // Enable 5V
  }

  initUnitManager(); // Unit Manager Init

  rtc_controller.init_rtc(); // RTC Init

  bmp280_controller.init_bmp280(); // BMP280 Init

  // CAN BUS Init
  canbus_init();

  /* Main UI init Function*/
  ui_init(); // ui from Squareline or GUI Guider

  // UI Initial Configurations
  ui_init_config();

  // Screen Manager Init
  if (BOARD_HAS_SLEEP_CAPABILITY)
  {
    screen_manager_init();
  }

  if (RMPS_LEDS)
  {
    leds.init_leds();
  }

  if (!BOARD_HAS_SLEEP_CAPABILITY)
  {
    _ui_screen_change(&ui_MainScreen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 100, 2000, ui_MainScreen_screen_init);
  }

  SerialCommsInit();

#ifdef TFT_BL
  pinMode((gpio_num_t)pcb.tft_bl, OUTPUT);
  analogWrite(pcb.tft_bl, 255);
#endif
}

/*******************************************************************************
 * Main Loop
 *******************************************************************************/
void loop()
{

  lv_timer_handler();

  delay(5);
}