#pragma once
#include "Vector2f.h"
#include "common.h"
#include "Texture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
	void setTexture(Texture *t);
	void animate();
private:
	Texture *tex;
	int index;
	float start;
	float stop;
};

