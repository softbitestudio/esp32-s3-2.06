#include "AppManager.hpp"
#include "ui/Menu.hpp"

void AppManager::begin() {
  menu_init(modules, [this](PentestModule* m){ this->launch(m); });
}

void AppManager::launch(PentestModule* mod) {
  if (current) current->onExit();
  current = mod;
  if (current) current->onEnter();
  menu_showModule(current, [this](){ this->goHome(); });
}

void AppManager::goHome() {
  if (current) current->onExit();
  current = nullptr;
  menu_showLauncher(modules, [this](PentestModule* m){ this->launch(m); });
}

void AppManager::tick() {
  if (current) current->onLoop();
}