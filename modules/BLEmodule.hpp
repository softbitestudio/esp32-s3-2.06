// modules/BLEModule.hpp
#pragma once
#include "PentestModule.hpp"
#include <NimBLEDevice.h>

class BLEModule : public PentestModule, public NimBLEAdvertisedDeviceCallbacks {
  lv_obj_t *list = nullptr;
  int deviceCount = 0;
public:
  const char* getName() const override { return "BLE"; }
  const char* getIcon() const override { return LV_SYMBOL_BLUETOOTH; }

  void onEnter() override {
    NimBLEDevice::init("PEN-TOOL");
    auto pScan = NimBLEDevice::getScan();
    pScan->setAdvertisedDeviceCallbacks(this);
    pScan->setInterval(100);
    pScan->setWindow(99);
    pScan->setActiveScan(true);
    pScan->start(0, nullptr, false); // scan forever
  }
  void onExit() override {
    NimBLEDevice::getScan()->stop();
  }
  void buildUI(lv_obj_t *parent) override {
    list = lv_list_create(parent);
    lv_obj_set_size(list, 440, 400);
    lv_obj_center(list);
    lv_list_add_btn(list, LV_SYMBOL_SAVE, "Save Log"); // TODO: SD logger
  }
  // NimBLE callback
  void onResult(NimBLEAdvertisedDevice *adv) override {
    if (!list) return;
    char buf[96];
    snprintf(buf, sizeof(buf), "%s | RSSI:%d", adv->getName().c_str(), adv->getRSSI());
    lv_list_add_btn(list, LV_SYMBOL_BLUETOOTH, buf);
    deviceCount++;
  }
};