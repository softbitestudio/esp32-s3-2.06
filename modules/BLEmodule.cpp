#include "BLEModule.hpp"
#include <lvgl.h>

void BLEModule::onEnter() {
  NimBLEDevice::init("PENTEST");
  auto scan = NimBLEDevice::getScan();
  scan->setAdvertisedDeviceCallbacks(this, false);
  scan->setInterval(100);
  scan->setWindow(99);
  scan->setActiveScan(true);
  scan->start(0, nullptr, false);
}

void BLEModule::onExit() {
  NimBLEDevice::getScan()->stop();
}

void BLEModule::onLoop() {
  if (dirty && uiList) {
    flushPending();
    dirty = false;
  }
}

void BLEModule::buildUI(lv_obj_t *parent) {
  uiList = lv_list_create(parent);
  lv_obj_set_size(uiList, 440, 400);
  lv_obj_center(uiList);
  auto btn = lv_list_add_btn(uiList, LV_SYMBOL_TRASH, "Clear");
  lv_obj_add_event_cb(btn, onClearClicked, LV_EVENT_CLICKED, this);
}

void BLEModule::onResult(NimBLEAdvertisedDevice* adv) {
  char buf[96];
  snprintf(buf, sizeof(buf), "%s | %d", adv->getName().c_str(), adv->getRSSI());
  pending.emplace_back(buf);
  if (pending.size() > 40) pending.erase(pending.begin());
  dirty = true;
}

void BLEModule::flushPending() {
  for (auto &s : pending) {
    lv_list_add_btn(uiList, LV_SYMBOL_BLUETOOTH, s.c_str());
  }
  pending.clear();
}

void BLEModule::onClearClicked(lv_event_t* e) {
  auto self = (BLEModule*)lv_event_get_user_data(e);
  if (!self->uiList) return;
  lv_obj_t *child;
  while ((child = lv_obj_get_child(self->uiList, 1))) {
    lv_obj_del(child);
  }
}