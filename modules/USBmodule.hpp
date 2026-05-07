#pragma once
#include "PentestModule.hpp"
#include "USB.h"
#include "USBHIDKeyboard.h"

class USBModule : public PentestModule {
  USBHIDKeyboard kb;
public:
  const char* getName() const override { return "BadUSB"; }
  const char* getIcon() const override { return LV_SYMBOL_KEYBOARD; }
  void onEnter() override;
  void onExit() override;
  void buildUI(lv_obj_t *parent) override;
private:
  static void onRunClicked(lv_event_t* e);
};