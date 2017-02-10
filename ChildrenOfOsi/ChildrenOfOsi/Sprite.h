#pragma once

#include "stdafx.h"

#include "common.h"
#include "Texture.h"

class Sprite
{
  public:

  Sprite():
    start(0), stop(0), top(0), bottom(0), index(0), tempTime(0), tex(nullptr) {};
  ~Sprite() = default;

  int getStart() { return this->start; };
  int getStop() { return this->stop; };
  int getTop() { return this->top; };
  int getBottom() { return this->bottom; };
  Texture getTexture() { return *(this->tex); }
  std::string getTexFile() { return this->tex->getFile(); }

  void setTexture(Texture *t);
  void animate();

  private:

  int start, stop;
  int top, bottom;

  Texture *tex;
  int index, tempTime;
};

