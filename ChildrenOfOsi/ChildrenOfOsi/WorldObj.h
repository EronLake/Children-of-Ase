#pragma once
#include "stdafx.h"

#include <vector>

#include "Rectangle.h"
#include "Sprite.h"
#include "Vector2f.h"

using namespace std;

class WorldObj
{
  public:

  WorldObj():
    ID(idNum++), loc(0, 0), collision(false), type(0)
  { this->body.push_back({{0.0F, 0.0F}, 1.0F, 1.0F}); };

  WorldObj(Vector2f p_topLeft, float p_width, float p_height):
    ID(idNum++), loc(p_topLeft), width(p_width), height(p_height), collision(false), type(0)
  { this->body.push_back({loc, p_width, p_height}); }

  WorldObj(float x, float y, bool col):
    ID(idNum++), loc({x, y}), collision(col), type(0)
  { this->body.push_back({loc, 1.0F, 1.0F}); }

  virtual ~WorldObj() = default;

  // Basic geometric information getters
  Vector2f getLoc() { return this->loc; };
  float getX() { return this->loc.getXloc(); };
  float getY() { return this->loc.getYloc(); };
  Vector2f getRot() { return this->rotation; };
  float getRotX() { return this->rotation.getXloc(); };
  float getRotY() { return this->rotation.getYloc(); };
  float getWidth() { return this->width; };
  float getHeight() { return this->height; };

  // Higher-level getter methods
  int getID() { return this->ID; };
  std::string getName() { return this->name; };
  int getType() { return this->type; };
  Sprite getSprite() { return this->sprite; };
  int getDirection() { return this->direction; };
  bool getCollision() { return this->collision; };
  bool getInteractable() { return this->interactable; };

  // Combat AI information getters
  int getEvasionRadius() { return this->evasionRadius; };
  Vector2f getEvadeRange(WorldObj* _enemy);
  Vector2f getCombatMoveDestination() { return this->combatMoveDestination; };

  int getBaseDir() const { return baseDir; };

  // Basic geometric information getters
  void setLoc(Vector2f l) { this->loc = l; };
  void setX(float x);
  void setY(float y);
  void shiftX(float dist);
  void shiftY(float dist);
  void setRot(Vector2f r) { this->rotation = r; };
  void setRotX(float x) { this->rotation.setXloc(x); };
  void setRotY(float y) { this->rotation.setYloc(y); };
  void shiftRotX(float dist) { this->rotation.shiftXloc(dist); };
  void shiftRotY(float dist) { this->rotation.shiftYloc(dist); };
  void setWidth(float w);
  void setHeight(float h);

  // Higher-level setter methods
  void setName(std::string n) { this->name = n; };
  void setType(int t) { this->type = t; };
  void setSprite(Sprite s) { this->sprite = s; };
  void setDirection(int d) { this->direction = d; };
  void setCollision(bool c) { this->collision = c; };
  void setInteractable(bool i) { this->interactable = i; };

  // Higher-level setters cont.
  void offsetBody(int i, float x1, float x2, float y1, float y2);
  void drawObj(float _x, float _y);
  void animateObj() { this->sprite.animate(); };

  // Combat AI information setters
  void setEvasionRadius(int _radius) { this->evasionRadius = _radius; }

  void setBaseDir(int d) { this->baseDir = d; };
  void setDirWithBase(int od);

  // String conversion
  void _print();

  Sprite sprite;
  vector<Rectangle> body;

  private:

  static constexpr int TYPE_ATTACK = -1;
  static constexpr int TYPE_WORLDOBJ = 0;
  static constexpr int TYPE_LIVINGOBJ = 1;
  static constexpr int TYPE_NPC = 2;
  static constexpr int TYPE_SOLDIER = 3;
  static constexpr int TYPE_SPLSOLDIER = 4;
  static constexpr int TYPE_HERO = 5;
  static constexpr int TYPE_PLAYER = 6;

  static constexpr int DIRECTION_UP = 8;
  static constexpr int DIRECTION_DOWN = 2;
  static constexpr int DIRECTION_LEFT = 4;
  static constexpr int DIRECTION_RIGHT = 6;

  static int idNum;

  Vector2f loc;
  Vector2f rotation;
  float width;
  float height;

  int ID;
  std::string name;
  int type;
  int direction;
  bool collision;
  bool interactable;

  int evasionRadius = 225;
  Vector2f combatMoveDestination;

  int baseDir;

  bool targetIsWithinRange(Rectangle _bound);
};


