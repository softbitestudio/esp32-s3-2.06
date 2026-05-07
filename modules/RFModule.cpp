#include "RFModule.hpp"
#include <lvgl.h>

void RFModule::onEnter() {
  // TODO: RadioLib init CC1101 on Board SPI pins
}

void RFModule::buildUI(lv_obj_t *parent) {
  auto dd = lv_dropdown_create(parent);
  lv_dropdown_set_options(dd,
    "RX Log 433 MHz\n"
    "RX Log 868 MHz\n"
    "RX Log 915 MHz\n"
    "TX Replay (AUTH REQ)"
  );
  lv_obj_set_width(dd, 360);
  lv_obj_align(dd, LV_ALIGN_TOP_MID, 0, 40);
  lv_obj_add_event_cb(dd, onDDEvent, LV_EVENT_VALUE_CHANGED, this);

  auto lbl = lv_label_create(parent);
  lv_label_set_text(lbl, "External CC1101 / C1101 required");
  lv_obj_align(lbl, LV_ALIGN_BOTTOM_MID, 0, -40);
}

void RFModule::onDDEvent(lv_event_t* e) {
  // Route to RadioLib abstraction here
}