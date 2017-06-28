#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
#include "DialogueGui.h"
#include "DialogueController.h"
#include "GameMap.h"
#include "Containers.h"
#include "CheckClass.h"
#include "HUD.h"
#include "common.h"
#include "RiverObj.h"
#include "UniformGrid.h"

class RenderManager;
class RenderHelper
{
  public:

  RenderHelper(QuadTree* QT, RiverObj* _rivObj, std::vector<WorldObj*>* _largeStruct, UniformGrid<WorldObj>* _worldobj_grid);
  ~RenderHelper();

  void initCamera(WorldObj* player);
  void initCameraFull(WorldObj* player);
  void initTutGui();
  void init_logo_gui();
  void init_victory_menu_gui();
  int init_map(WorldObj* obj);
  int draw_frame(WorldObj* obj);
  int sprite_up(WorldObj* obj);
  int sprite_down(WorldObj* obj);
  int sprite_left(WorldObj* obj);
  int sprite_right(WorldObj* obj);
  int sprite_atk(WorldObj* obj);
  int sprite_spin_atk(WorldObj* obj);
  int sprite_fire_atk(WorldObj* obj);
  int sprite_hurt(WorldObj* obj);
  int sprite_dead(WorldObj* obj);
  int sprite_idle(WorldObj* obj);
  int sprite_talk(WorldObj * obj); // so the talk icon apears
  int sprite_update(WorldObj* obj);
  int drawDiaGui(WorldObj* obj);
  int drawHUD(WorldObj* obj);
  int drawTut(WorldObj* obj);
  int draw_logo(WorldObj* obj);
  int draw_victory_menu(WorldObj* obj);
  Vector2f getCameraSize() { return cameraSize; }
  int setSwordGlow(WorldObj* obj);
  int setHeartGlow(WorldObj* obj);
  int setFaceGlow(WorldObj* obj);
  int setQuestionGlow(WorldObj* obj);
  void sortVec();
  bool compY(WorldObj* a, WorldObj* b);
  QuadTree* tree;
  WorldObj* camera;
  WorldObj* fullBound;
  RenderManager* manager;
  RiverObj* rivObj;
  std::vector<WorldObj*>* largeStruct;
  UniformGrid<WorldObj>* grid_game;

  static GameMap* gmap;

  private:

  DialogueGui* convoGui;
  Rectangle* TutGui;
  Rectangle* logo_gui;
  Rectangle* victory_menu;
  HUD* hud_ptr;

  std::vector<WorldObj*> objVec;
  std::vector<WorldObj*> fullVec;

  Vector2f cameraSize;
  Vector2f mapSize;
  Vector2f CamOffset;

};

