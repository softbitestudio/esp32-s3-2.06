// ui/LVGLConfig.cpp (excerpt)
#include "Display.hpp"
static LGFX lcd;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf1 = nullptr;

void lvgl_init() {
  lcd.init();
  lcd.setBrightness(128);
  lv_init();
  // Allocate in DMA-capable or PSRAM depending on bus width
  buf1 = (lv_color_t*)heap_caps_malloc(466*40*sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
  lv_disp_draw_buf_init(&draw_buf, buf1, nullptr, 466*40);
  
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 466;
  disp_drv.ver_res = 466;
  disp_drv.flush_cb = [](lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
    lcd.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1,
                     (lgfx::rgb565_t*)&color_p->full);
    lv_disp_flush_ready(drv);
  };
  lv_disp_drv_register(&disp_drv);

  // Touch
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = [](lv_indev_drv_t *drv, lv_indev_data_t *data) {
    extern Touch touch; // instantiate elsewhere
    uint16_t x, y; bool p;
    if (touch.read(x, y, p)) {
      data->point.x = x;
      data->point.y = y;
      data->state = p ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    }
  };
  lv_indev_drv_register(&indev_drv);
}