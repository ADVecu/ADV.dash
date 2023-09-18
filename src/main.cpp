
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
// #include <demos/lv_demos.h>
#include "UI/ui.h"
#include "muTimer.h"

#define TFT_BL 2
#define GFX_BL DF_GFX_BL // default backlight pin

muTimer testTimer;
muTimer testTimer2;
muTimer testTimer3;

bool entry = true;
int count = 0;

/*******************************************************************************
 * Display Selection
 *******************************************************************************/

// #define Display_43   // 4.3 inch 480x272
#define Display_50 // 5.0 inch 800x480
// #define Display_70   // 7.0 inch 800x480

/*******************************************************************************
 * Screen Driver Configuration
 *******************************************************************************/
#if defined(Display_43) // 4.3INCH 480x272
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
    bus,
    480 /* width */, 0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 43 /* hsync_back_porch */,
    272 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 12 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 7000000 /* prefer_speed */, true /* auto_flush */);

#elif defined(Display_50) // 5.0INCH 800x480
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 0 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
    bus,
    800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 43 /* hsync_back_porch */,
    480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 12 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);

#elif defined(Display_70) // 7.0INCH 800x480
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 0 /* PCLK */,
    14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
    9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
    15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
    bus,
    800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 1 /* hsync_pulse_width */, 46 /* hsync_back_porch */,
    480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 1 /* vsync_pulse_width */, 23 /* vsync_back_porch */,
    0 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);
#endif

/*******************************************************************************
 * Display Driver Configuration
 *******************************************************************************/
#include "touch.h"

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[800 * 480 / 10]; // 5,7inch: lv_color_t disp_draw_buf[800*480/10]            4.3inch: lv_color_t disp_draw_buf[480*272/10]
// static lv_color_t disp_draw_buf;
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
  pinMode(TFT_BL, OUTPUT);
  analogWrite(TFT_BL, 255);
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

  /* LVGL Demos*/
  // lv_demo_widgets();

  /* Main UI init Function*/
  ui_init(); // ui from Squareline or GUI Guider
}

/*******************************************************************************
 * Main Loop
 *******************************************************************************/
void loop()
{
  lv_timer_handler();

  if (lv_scr_act() == ui_Screen1 && true)
  {
    lv_bar_set_value(ui_RpmsBar, random(8, 9), LV_ANIM_OFF);
    lv_label_set_text_fmt(ui_RpmsValue, "%d", random(800, 900));

    if (lv_bar_get_value(ui_RpmsBar) >= 50 && entry)
    {
      lv_obj_set_style_bg_color(ui_RpmsBar, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      entry = false;
    }

    if (lv_bar_get_value(ui_RpmsBar) >= 100)
    {
      lv_obj_set_style_bg_color(ui_RpmsBar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
      entry = true;
      lv_bar_set_value(ui_RpmsBar, 0, LV_ANIM_OFF);
    }

    lv_arc_set_value(ui_Arc1, random(45, 48));
    lv_label_set_text_fmt(ui_ArcValue1, "%d", random(45, 48));

    lv_arc_set_value(ui_Arc2, random(10, 15));
    lv_label_set_text_fmt(ui_ArcValue2, "%d", random(10, 15));
    lv_arc_set_value(ui_Arc4, random(50, 60));
    lv_label_set_text_fmt(ui_ArcValue4, "%d", random(50, 60));

    lv_arc_set_value(ui_MainArc, random(30, 90));
    lv_label_set_text_fmt(ui_MainArcValue, "%d", random(30, 90));

    lv_label_set_text_fmt(ui_PanelValue1, "%d", random(100));

    lv_label_set_text_fmt(ui_PanelValue2, "%d", random(100));
    lv_label_set_text_fmt(ui_PanelValue4, "%d", random(100));
    lv_label_set_text_fmt(ui_PanelValue5, "%d", random(100));

    lv_label_set_text_fmt(ui_SpeedValue, "%d", random(80, 85));

    lv_bar_set_value(ui_TpsBar, random(50, 60), LV_ANIM_OFF);

    if (testTimer.cycleTrigger(500))
    {

      lv_label_set_text_fmt(ui_PanelValue6, "%d", random(90, 98));

      lv_bar_set_value(ui_Bar2, random(50, 52), LV_ANIM_OFF);
      lv_label_set_text_fmt(ui_BarValue2, "%d", random(100));

      lv_label_set_text_fmt(ui_GearValue, "%d", random(7));
    }

    if (testTimer2.cycleTrigger(1000))
    {

      lv_bar_set_value(ui_Bar1, random(80, 82), LV_ANIM_OFF);
      lv_label_set_text_fmt(ui_BarValue1, "%d", random(80, 82));

      lv_bar_set_value(ui_Bar3, random(40, 50), LV_ANIM_OFF);
      lv_label_set_text_fmt(ui_BarValue2, "%d", random(40, 50));

      lv_bar_set_value(ui_Bar4, random(70, 75), LV_ANIM_OFF);
      lv_label_set_text_fmt(ui_BarValue4, "%d", random(70, 75));

      lv_arc_set_value(ui_Arc3, random(95, 105));
      lv_label_set_text_fmt(ui_ArcValue3, "%d", random(95, 105));

      lv_label_set_text_fmt(ui_PanelValue3, "%d", random(85, 87));
    }
  }

  if (lv_scr_act() == ui_Screen2 && true)
  {
    if (testTimer3.delayOn(true, 1000))

    {
      lv_chart_series_t *serie = lv_chart_get_series_next(ui_Chart1, NULL);
      lv_chart_set_next_value(ui_Chart1, serie, lv_rand(80, 90));
    }
  }
  delay(5);
}