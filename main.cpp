// main.cpp
#include "hal/Display.hpp"
#include "hal/Touch.hpp"
#include "ui/Menu.hpp"
#include "core/AppManager.hpp"
#include "modules/WiFiModule.hpp"
#include "modules/BLEModule.hpp"
#include "modules/RFModule.hpp"
#include "modules/USBModule.hpp"

Touch touch;
static WiFiModule modWiFi;
static BLEModule modBLE;
static RFModule modRF;
static USBModule modUSB;

void setup() {
  Serial.begin(115200);
  lvgl_init();          // from Section 4
  touch.begin();        // SDA/SCL pins per schematic

  static std::vector<PentestModule*> mods = {&modWiFi, &modBLE, &modRF, &modUSB};
  menu_init(mods);
}

void loop() {
  lv_timer_handler();   // LVGL task
  menu_loop();          // Current module tick
  delay(5);             // Yield
}