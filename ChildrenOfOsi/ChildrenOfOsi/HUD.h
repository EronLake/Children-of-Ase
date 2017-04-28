#pragma once

#include "common.h"

#include "AssetInfo.h"
#include "DialogueController.h"
#include "GameWindow.h"
#include "Rectangle.h"

class HUD
{
  public:

  HUD();
  ~HUD();

  void loadTexture();
  void setSprite();
  void drawHUD(WorldObj* obj);
  //void setTextures();

  static void toggle_quests() { show_active_quests = !show_active_quests; };

  static int FPS;
  static int AVG;

  private:

  static constexpr float HEALTHBAR_X = 125.0F;
  static constexpr float HEALTHBAR_Y = 50.0F;
  static constexpr float HEALTHBAR_WIDTH = 300.0F;
  static constexpr float HEALTHBAR_HEIGHT = 32.0F;

  static constexpr float ASEFLAME_X = 175.0F;
  static constexpr float ASEFLAME_Y = 100.0F;
  static constexpr float ASEFLAME_WIDTH = 20.0F;
  static constexpr float ASEFLAME_HEIGHT = 20.0F;
  static constexpr float ASEFLAME_MARGIN = 10.0F;
  static constexpr int ASEFLAME_COUNT = 4;

  static constexpr float PORTRAIT_X = 10.0F;
  static constexpr float PORTRAIT_Y = 10.0F;
  static constexpr float PORTRAIT_WIDTH = 150.0F;
  static constexpr float PORTRAIT_HEIGHT = 150.0F;

  static constexpr float MINIMAP_X = 790.375F;
  static constexpr float MINIMAP_Y = 19.625F;
  static constexpr float MINIMAP_WIDTH = 150.0F;
  static constexpr float MINIMAP_HEIGHT = 150.0F;
  static constexpr float MINIMAP_FRAME_X = 780.75F;
  static constexpr float MINIMAP_FRAME_Y = 10.0F;
  static constexpr float MINIMAP_FRAME_WIDTH = 169.25F;
  static constexpr float MINIMAP_FRAME_HEIGHT = 169.25F;
  static constexpr float MINIMAP_CURSOR_X = 786.375F;
  static constexpr float MINIMAP_CURSOR_Y = 15.625F;
  static constexpr float MINIMAP_CURSOR_WIDTH = 8.0F;
  static constexpr float MINIMAP_CURSOR_HEIGHT = 8.0F;

  static constexpr float KEYBIND_DISPLAY_X = 825.0F;
  static constexpr float KEYBIND_DISPLAY_Y = 405.0F;
  static constexpr float KEYBIND_DISPLAY_WIDTH = 125.0F;
  static constexpr float KEYBIND_DISPLAY_HEIGHT = 125.0F;

  static bool show_active_quests;

  Rectangle *healthbar_empty_rect;
  Rectangle *healthbar_full_rect;
  Rectangle *aseflame_empty_rect;
  Rectangle *aseflame_full_rect;
  Rectangle *portrait_background_rect;
  Rectangle *portrait_rect;

  Rectangle *minimap_rect;
  Rectangle *minimap_frame_rect;
  Rectangle *minimap_cursor_rect;
  Rectangle *keybind_display_rect;

  Texture *healthbar_empty_tex;
  Texture *healthbar_full_tex;
  Texture *aseflame_empty_tex;
  Texture *aseflame_full_tex;
  Texture *portrait_background_tex;
  Texture *portrait_full_tex;
  Texture *portrait_empty_tex;

  Texture *minimap_tex;
  Texture *minimap_frame_tex;
  Texture *minimap_cursor_tex;
  Texture *keybind_display_tex;

  void drawMainHUD(Player *player);
  void drawMinimap(Player *player);
  void drawKeybindDisplay();
};
