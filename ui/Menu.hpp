#pragma once
#include <vector>
#include <functional>
#include "modules/PentestModule.hpp"

void menu_init(const std::vector<PentestModule*>& mods,
               std::function<void(PentestModule*)> onLaunch);

void menu_showLauncher(const std::vector<PentestModule*>& mods,
                       std::function<void(PentestModule*)> onLaunch);

void menu_showModule(PentestModule* mod, std::function<void()> onHome);
void menu_loop();