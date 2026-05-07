#include "WiFiModule.hpp"
#include <lvgl.h>

void WiFiModule::onEnter() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  aps.clear();
  scanning = false;
  startScan();
}

void WiFiModule::onExit() {
  WiFi.scanDelete();
}

void WiFiModule::onLoop() {
  if (!scanning) return;
  int n = WiFi.scanComplete();
  if (n < 0) return;
  aps.clear();
  for (int i = 0; i < n; i++) {
    APInfo ap{ WiFi.SSID(i), {}, WiFi.RSSI(i), WiFi.channel(i) };
    memcpy(ap.bssid, WiFi.BSSID(i), 6);
    aps.push_back(ap);
  }
  WiFi.scanDelete();
  scanning = false;
  refreshList();
}

void WiFiModule::buildUI(lv_obj_t *parent) {
  uiList = lv_list_create(parent);
  lv_obj_set_size(uiList, 440, 400);
  lv_obj_center(uiList);

  auto btn = lv_list_add_btn(uiList, LV_SYMBOL_REFRESH, "Scan Networks");
  lv_obj_add_event_cb(btn, onBtnClicked, LV_EVENT_CLICKED, this);
  refreshList();
}

void WiFiModule::startScan() {
  if (scanning) return;
  scanning = true;
  WiFi.scanNetworks(true, true);
}

void WiFiModule::refreshList() {
  if (!uiList) return;
  lv_obj_t *child;
  while ((child = lv_obj_get_child(uiList, 1))) {
    lv_obj_del(child);
  }
  for (auto &ap : aps) {
    char buf[80];
    snprintf(buf, sizeof(buf), "%s | %d dBm | CH:%d", ap.ssid.c_str(), ap.rssi, ap.ch);
    lv_list_add_btn(uiList, LV_SYMBOL_WIFI, buf);
  }
}

void WiFiModule::onBtnClicked(lv_event_t* e) {
  auto self = (WiFiModule*)lv_event_get_user_data(e);
  self->aps.clear();
  self->refreshList();
  self->startScan();
}