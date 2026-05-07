// modules/RFModule.hpp
#pragma once
#include "PentestModule.hpp"

class RFModule : public PentestModule {
public:
  const char* getName() const override { return "SubGHz"; }
  void onEnter() override {
    // Initialize CC1101 on SPI bus (user-supplied pins)
    // RadioLib or ELECHOUSE_CC1101 driver goes here
  }
  void buildUI(lv_obj_t *parent) override {
    auto dd = lv_dropdown_create(parent);
    lv_dropdown_set_options(dd, "Scan 433\nScan 868\nScan 915\nRX Log\nTX Replay");
    lv_obj_set_width(dd, 300);
    lv_obj_center(dd);
    // TX functions are gated behind user confirmation & legal-check flag
  }
};