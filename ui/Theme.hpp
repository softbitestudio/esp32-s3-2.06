#pragma once
#include <lvgl.h>

namespace Theme {
  inline lv_color_t bg()      { return lv_color_hex(0x050505); }
  inline lv_color_t surface() { return lv_color_hex(0x1a1a1a); }
  inline lv_color_t accent()  { return lv_color_hex(0x00e676); }
  inline lv_color_t text()    { return lv_color_hex(0xffffff); }
  inline lv_color_t danger()  { return lv_color_hex(0xff5252); }
}