#include "LogModule.hpp"
#include "hal/SDCard.hpp"

static SDCard sd;

bool LogModule::begin() { return sd.begin(); }

bool LogModule::append(const char* path, const char* line) {
  if (!sd.isOK()) return false;
  File f = sd.open(path, FILE_APPEND);
  if (!f) return false;
  f.println(line);
  f.close();
  return true;
}

bool LogModule::appendBytes(const char* path, const uint8_t* data, size_t len) {
  if (!sd.isOK()) return false;
  File f = sd.open(path, FILE_APPEND);
  if (!f) return false;
  f.write(data, len);
  f.close();
  return true;
}