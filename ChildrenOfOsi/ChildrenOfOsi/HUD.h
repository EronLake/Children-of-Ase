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

  static constexpr float HEALTHBAR_DECOR_SEGMENT_X = 106.0F;
  static constexpr float HEALTHBAR_DECOR_SEGMENT_Y = 41.0F;
  static constexpr float HEALTHBAR_DECOR_SEGMENT_WIDTH = 92.0F;
  static constexpr float HEALTHBAR_DECOR_SEGMENT_HEIGHT = 50.0F;
  static constexpr float HEALTHBAR_DECOR_TAIL_X = 362.5F;
  static constexpr float HEALTHBAR_DECOR_TAIL_Y = 41.0F;
  static constexpr float HEALTHBAR_DECOR_TAIL_WIDTH = 77.5F;
  static constexpr float HEALTHBAR_DECOR_TAIL_HEIGHT = 50.0F;
  static constexpr float HEALTHBAT_DECOR_PIECE_OVERLAP = 32.0F;
  static constexpr int HEALTHBAR_DECOR_PIECE_COUNT = 4;

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
  static constexpr float MAP_WIDTH = 25000.0F;
  static constexpr float MAP_HEIGHT = 25000.0F;

  static constexpr float KEYBIND_DISPLAY_X = 775.0F;
  static constexpr float KEYBIND_DISPLAY_Y = 355.0F;
  static constexpr float KEYBIND_DISPLAY_WIDTH = 175.0F;
  static constexpr float KEYBIND_DISPLAY_HEIGHT = 175.0F;


  //Eron: definitly need to change all this so it uses proportions

  static constexpr float ORI_FLAME_X = 0.0F;
  static constexpr float ORI_FLAME_Y = 355.0F;
  static constexpr float ORI_CROWN_X = 0.0F;
  static constexpr float ORI_CROWN_Y = 355.0F;

  static constexpr float ORI_FLAME_WIDTH = 50.0F;
  static constexpr float ORI_FLAME_HEIGHT = 50.0F;
  static constexpr float ORI_CROWN_WIDTH = 150.0F;
  static constexpr float ORI_CROWN_HEIGHT = 150.0F;

  static bool if_animating;

  static bool show_active_quests;

  Rectangle *healthbar_empty_rect;
  Rectangle *healthbar_full_rect;
  Rectangle *healthbar_decor_segment_rect;
  Rectangle *healthbar_decor_tail_rect;
  Rectangle *aseflame_empty_rect;
  Rectangle *aseflame_full_rect;
  Rectangle *portrait_background_rect;
  Rectangle *portrait_rect;

  Rectangle *minimap_rect;
  Rectangle *minimap_frame_rect;
  Rectangle *minimap_cursor_rect;
  Rectangle *keybind_display_rect;

  Rectangle *keybind_attack01_rect;
  Rectangle *keybind_attack02_rect;
  Rectangle *keybind_attack03_rect;
  Rectangle *keybind_attack04_rect;

  Rectangle *ori_flame_rect;
  Rectangle *ori_crown_rect;

  Texture *healthbar_empty_tex;
  Texture *healthbar_full_tex;
  Texture *healthbar_decor_segment_tex;
  Texture *healthbar_decor_tail_tex;
  Texture *aseflame_empty_tex;
  Texture *aseflame_full_tex;
  Texture *portrait_background_tex;
  Texture *portrait_full_tex;
  Texture *portrait_empty_tex;

  Texture *minimap_tex;
  Texture *minimap_frame_tex;
  Texture *minimap_cursor_tex;
  Texture *keybind_display_tex;

  Texture *keybind_attack01_tex;
  Texture *keybind_attack02_tex;
  Texture *keybind_attack03_tex;
  Texture *keybind_attack04_tex;

  Texture *ori_flame_tex;
  Texture *ori_crown_tex;


  void drawMainHUD(Player *player);
  void drawMinimap(Player* player, Hero* yemoja, Hero* oya, Hero* ogun);
  void drawOri(Player* player);
  void drawKeybindDisplay(Player *player);
};
