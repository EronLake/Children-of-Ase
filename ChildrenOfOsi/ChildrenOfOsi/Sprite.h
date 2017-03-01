#pragma once

#include "stdafx.h"

#include "common.h"
#include "Texture.h"

class Sprite
{
  public:

  Sprite():
    start(0), stop(0), top(0), bottom(0), index(0), tempTime(0), tex(nullptr),lock(false) {};
  ~Sprite() = default;

  int getStart() { return this->start; };
  int getStop() { return this->stop; };
  int getTop() { return this->top; };
  int getBottom() { return this->bottom; };
  Texture getTexture() { return *(this->tex); }
  Texture* getIdleTexture() { return(this->idle); }
  std::string getTexFile() { return this->tex->getFile(); }
  bool isIdle() { return (this->idle == this->tex); }

  void setTexture(Texture *t);
  void setIdleTexture(Texture *t);
  void animate();
  //Texture *tex;
  
  void lockAnimation() { lock = true; };
  void unlockAnimation() { lock = false; };
  bool getLock() { return lock; };

  Texture *id_up;
  Texture *id_left;
  Texture *id_right;
  Texture *id_down;

  Texture *up;
  Texture *down;
  Texture *left;
  Texture *right;

  Texture *atk_up;
  Texture *atk_down;
  Texture *atk_left;
  Texture *atk_right;

  private:

  int start, stop;
  int top, bottom;

  Texture *tex;
  Texture *idle;

  int index, tempTime;

  bool lock;
};

