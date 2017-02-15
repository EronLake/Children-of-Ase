#include "stdafx.h"
#include "Sprite.h"

/**
 * Changes this sprite to wrap the texture specified.
 */
void Sprite::setTexture(Texture *t)
{
	if (tex == t) return; 
  tex = t;
  index = 0;
  start = 0;
  stop = tex->getFrameWidth();
  top = tex->getHeight();
  bottom = 0;
  tempTime = 0;
}

/**
 * Advances this sprite's animation, if any, by one frame.
 */
void Sprite::animate()
{
  ++this->tempTime;
  if(this->tempTime == 2) {
    if(this->index < this->tex->getFrames()-1) {
      ++this->index;
      this->start = tex->getFrameWidth() * index;
      this->stop = tex->getFrameWidth() * (index + 1);
      LOG("Animated start: " << this->start << " stop: " << this->stop << std::endl);
    }
    else {
      this->index = 0;
      this->start = 0;
      this->stop = this->tex->getFrameWidth();
    }

    this->tempTime = 0;
  }
}
