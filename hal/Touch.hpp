// hal/Touch.hpp
#pragma once
#include <Wire.h>
#define FT3267_ADDR 0x38

class Touch {
  TwoWire &_wire;
public:
  Touch(TwoWire &w = Wire) : _wire(w) {}
  bool begin(int sda = 11, int scl = 12) {  // TODO: verify pins
    _wire.begin(sda, scl, 400000);
    // Basic presence check
    _wire.beginTransmission(FT3267_ADDR);
    return (_wire.endTransmission() == 0);
  }
  bool read(uint16_t &x, uint16_t &y, bool &pressed) {
    uint8_t buf[6];
    _wire.beginTransmission(FT3267_ADDR);
    _wire.write(0x00); // start reg
    if (_wire.endTransmission(false) != 0) return false;
    _wire.requestFrom((uint8_t)FT3267_ADDR, (uint8_t)6);
    for (int i = 0; i < 6; i++) buf[i] = _wire.read();
    pressed = (buf[0] & 0x0F) != 0;
    x = ((buf[1] & 0x0F) << 8) | buf[2];
    y = ((buf[3] & 0x0F) << 8) | buf[4];
    // Map 0..366 to 0..466 depending on your touch IC max val
    x = (uint16_t)(x * 466.0 / 366.0);
    y = (uint16_t)(y * 466.0 / 366.0);
    return true;
  }
};