#pragma once

#include "stdafx.h"

#include "common.h"
#include "Texture.h"

class Sprite
{
  public:

  Sprite():
	  start(0), stop(0), top(0), bottom(0), index(0), tempTime(0), tex(nullptr), lock(false), dying(false) {
	  mut = new std::mutex();
  };
  ~Sprite() = default;

  int getStart() { return this->start; };
  int getStop() { return this->stop; };
  int getTop() { return this->top; };
  int getBottom() { return this->bottom; };
  Texture& getTexture() { return *(this->tex); }
  Texture* get_texture() { return (this->tex); }
  Texture* getIdleTexture() { return this->idle; }
  std::string getTexFile() { return this->tex->getFile(); }

  bool isIdle() { return (this->idle == this->tex); }
  bool getLock() { return this->lock || this->dying; };
  bool getDying() { return this->dying; }

  void setStart(int start) { this->start = start; };
  void setStop(int stop) { this->stop = stop; };
  void setTexture(Texture *t);
  void setIdleTexture(Texture *t);
  void reset_texture();
  
  void animate();
  void lockAnimation() { this->lock = true; };
  void unlockAnimation() { if (!dying)this->lock = false; };
  void lockIntoDeathAnimation() { this->dying = true; this->lock = true;}

  Texture *id_up;
  Texture *id_down;
  Texture *id_left;
  Texture *id_right;

  Texture *up;
  Texture *down;
  Texture *left;
  Texture *right;

  Texture *atk_up;
  Texture *atk_down;
  Texture *atk_left;
  Texture *atk_right;

  Texture *atk2_up;
  Texture *atk2_down;
  Texture *atk2_left;
  Texture *atk2_right;

  Texture *spin_up;
  Texture *spin_down;
  Texture *spin_left;
  Texture *spin_right;

  Texture *breathe_up;
  Texture *breathe_down;
  Texture *breathe_left;
  Texture *breathe_right;

  Texture *hurt_up;
  Texture *hurt_down;
  Texture *hurt_left;
  Texture *hurt_right;

  Texture *death_up;
  Texture *death_down;
  Texture *death_left;
  Texture *death_right;

  private:
  
  std::mutex* mut;
  int start, stop;
  int top, bottom;
  Texture *tex;
  Texture *idle;
  int index, tempTime;
  bool lock, dying;
};

