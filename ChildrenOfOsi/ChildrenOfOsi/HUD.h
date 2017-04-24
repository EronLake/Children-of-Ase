#pragma once
#include "common.h"
#include "Rectangle.h"
#include "GameWindow.h"
#include "DialogueController.h"

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

  static constexpr float HUD_WIDTH = 400.0F;
  static constexpr float HUD_HEIGHT = 400.0F;
  static constexpr float HEALTHBAR_WIDTH = 400.0F;
  static constexpr float HEALTHBAR_HEIGHT = 400.0F;
  static constexpr float ASEBAR_WIDTH = 400.0F;
  static constexpr float ASEBAR_HEIGHT = 400.0F;

  static bool show_active_quests;

  Rectangle* hud_empty;
  Rectangle* hud_ase;
  Rectangle* hud_health;
  Rectangle* hud_portrait;

  Texture* hud_empty_tex;
  Texture* hud_ase_tex;
  Texture* hud_health_tex;
  Texture* hud_portrait_tex;

  glm::vec3 black;
};

