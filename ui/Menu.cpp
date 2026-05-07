// ui/Menu.cpp
#include "Menu.hpp"
#include "Theme.hpp"
#include <vector>

static lv_obj_t *scr = nullptr;
static lv_obj_t *tile_cont = nullptr;
static PentestModule *currentMod = nullptr;
static std::vector<PentestModule*> modules;

void menu_init(const std::vector<PentestModule*> &mods) {
  modules = mods;
  scr = lv_scr_act();
  lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

  tile_cont = lv_obj_create(scr);
  lv_obj_set_size(tile_cont, 466, 466);
  lv_obj_set_layout(tile_cont, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(tile_cont, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_flex_align(tile_cont, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  for (auto *mod : modules) {
    auto btn = lv_btn_create(tile_cont);
    lv_obj_set_size(btn, 130, 110);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x2a2a2a), 0);
    lv_obj_set_style_radius(btn, 12, 0);

    auto cont = lv_obj_create(btn);
    lv_obj_set_size(cont, 120, 100);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_align(cont, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    auto icon = lv_label_create(cont);
    lv_label_set_text(icon, mod->getIcon());
    lv_obj_set_style_text_font(icon, &lv_font_montserrat_28, 0);

    auto lbl = lv_label_create(cont);
    lv_label_set_text(lbl, mod->getName());
    lv_obj_set_style_text_font(lbl, &lv_font_montserrat_14, 0);

    lv_obj_add_event_cb(btn, [](lv_event_t *e){
      PentestModule *m = (PentestModule*)lv_event_get_user_data(e);
      launchModule(m);
    }, LV_EVENT_CLICKED, mod);
  }
}

void launchModule(PentestModule *mod) {
  if (currentMod) currentMod->onExit();
  currentMod = mod;

  lv_obj_clean(scr);
  // Back button
  auto back = lv_btn_create(scr);
  lv_obj_set_size(back, 80, 40);
  lv_obj_align(back, LV_ALIGN_TOP_LEFT, 10, 10);
  auto bl = lv_label_create(back);
  lv_label_set_text(bl, LV_SYMBOL_LEFT " Back");
  lv_obj_add_event_cb(back, [](lv_event_t *e){
    // Return to menu
    if (currentMod) currentMod->onExit();
    currentMod = nullptr;
    lv_obj_clean(scr);
    menu_init(modules); // simplistic reload
  }, LV_EVENT_CLICKED, nullptr);

  // Module UI container
  auto cont = lv_obj_create(scr);
  lv_obj_set_size(cont, 440, 390);
  lv_obj_align(cont, LV_ALIGN_BOTTOM_MID, 0, -10);
  lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

  mod->onEnter();
  mod->buildUI(cont);
}

void menu_loop() {
  if (currentMod) currentMod->onLoop();
}