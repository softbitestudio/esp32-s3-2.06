#include "USBModule.hpp"
#include <lvgl.h>

void USBModule::onEnter() {
  USB.begin();
  kb.begin();
  USB.setManufacturerDescriptor("Generic Corp");
  USB.setProductDescriptor("USB Keyboard");
}

void USBModule::onExit() {
  // Intentionally left empty; USB stays alive
}

void USBModule::buildUI(lv_obj_t *parent) {
  auto ta = lv_textarea_create(parent);
  lv_obj_set_size(ta, 430, 250);
  lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 20);
  lv_textarea_set_placeholder_text(ta, "DuckyScript payload");

  auto btn = lv_btn_create(parent);
  lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -30);
  lv_obj_set_size(btn, 160, 60);
  auto lbl = lv_label_create(btn);
  lv_label_set_text(lbl, "Run Payload");
  lv_obj_center(lbl);
  lv_obj_add_event_cb(btn, onRunClicked, LV_EVENT_CLICKED, &kb);
}

void USBModule::onRunClicked(lv_event_t* e) {
  auto keyboard = (USBHIDKeyboard*)lv_event_get_user_data(e);
  keyboard->println("Hello from ESP32-S3 USBadBunny ");
}