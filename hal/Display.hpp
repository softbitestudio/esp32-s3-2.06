// hal/Display.hpp
#pragma once
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_RM690B0 _panel_instance;   // Or GC9503, SH8601A per your panel
  lgfx::Bus_QSPI      _bus_instance;

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config();
      // TODO: Replace with Waveshare 2.06" QSPI pins
      cfg.pin_sclk  = 5;   // CLK
      cfg.pin_d0    = 7;   // D0
      cfg.pin_d1    = 8;   // D1
      cfg.pin_d2    = 9;   // D2
      cfg.pin_d3    = 10;  // D3
      cfg.pin_dcs   = 6;   // CS
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
    {
      auto cfg = _panel_instance.config();
      cfg.pin_rst   = 4;   // RST
      cfg.panel_width  = 466;
      cfg.panel_height = 466;
      cfg.offset_x  = 0;
      cfg.offset_y  = 0;
      cfg.invert    = true;   // AMOLED often needs invert
      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);
  }
};