// modules/USBModule.hpp
#pragma once
#include "PentestModule.hpp"
#include "USB.h"
#include "USBHIDKeyboard.h"

class USBModule : public PentestModule {
  USBHIDKeyboard kb;
public:
  const char* getName() const override { return "BadUSB"; }
  void onEnter() override {
    USB.begin();
    kb.begin();
    USB.setManufacturerDescriptor("Generic");
    USB.setProductDescriptor("Keyboard");
  }
  void buildUI(lv_obj_t *parent) override {
    auto ta = lv_textarea_create(parent);
    lv_obj_set_size(ta, 420, 300);
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 10);
    lv_textarea_set_placeholder_text(ta, "DuckyScript payload...");

    auto btn = lv_btn_create(parent);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_event_cb(btn, [](lv_event_t *e){
      auto self = (USBModule*)lv_event_get_user_data(e);
      // Minimal demo: type a test string
      self->kb.println("Hello from ESP32-S3");
    }, LV_EVENT_CLICKED, this);
    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, "Run Payload");
  }
};