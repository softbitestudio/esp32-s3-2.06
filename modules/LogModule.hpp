#pragma once
#include <Arduino.h>

class LogModule {
public:
  static bool begin();
  static bool append(const char* path, const char* line);
  static bool appendBytes(const char* path, const uint8_t* data, size_t len);
};