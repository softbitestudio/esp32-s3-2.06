// modules/WiFiModule.hpp
#pragma once
#include "PentestModule.hpp"
#include <WiFi.h>
#include <vector>

struct APInfo { String ssid; uint8_t bssid[6]; int rssi; int ch; };

class WiFiModule : public PentestModule {
  std::vector<APInfo> aps;
  lv_obj_t *list = nullptr;
  bool scanning = false;
public:
  const char* getName() const override { return "WiFi"; }
  const char* getIcon() const override { return LV_SYMBOL_WIFI; }

  void onEnter() override {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    aps.clear();
    scanning = true;
    scanAsync();
  }
  void onLoop() override {
    if (scanning && WiFi.scanComplete() >= 0) {
      int n = WiFi.scanComplete();
      aps.reserve(n);
      for (int i = 0; i < n; i++) {
        APInfo ap{WiFi.SSID(i), {0}, WiFi.RSSI(i), WiFi.channel(i)};
        memcpy(ap.bssid, WiFi.BSSID(i), 6);
        aps.push_back(ap);
      }
      WiFi.scanDelete();
      scanning = false;
      refreshList();
    }
  }
  void buildUI(lv_obj_t *parent) override {
    list = lv_list_create(parent);
    lv_obj_set_size(list, 440, 400);
    lv_obj_center(list);
    lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_REFRESH, "Scan");
    lv_obj_add_event_cb(btn, [](lv_event_t *e){
      auto self = (WiFiModule*)lv_event_get_user_data(e);
      self->scanAsync();
    }, LV_EVENT_CLICKED, this);
    refreshList();
  }

private:
  void scanAsync() {
    if (scanning) return;
    scanning = true;
    WiFi.scanNetworks(true, true); // async, show hidden
  }
  void refreshList() {
    if (!list) return;
    // Remove old items (keep first button)
    lv_obj_t *child = lv_obj_get_child(list, 1);
    while (child) {
      lv_obj_del(child);
      child = lv_obj_get_child(list, 1);
    }
    for (auto &ap : aps) {
      char buf[64];
      snprintf(buf, sizeof(buf), "%s (%d dBm) CH:%d", ap.ssid.c_str(), ap.rssi, ap.ch);
      lv_list_add_btn(list, LV_SYMBOL_WIFI, buf);
    }
  }
};