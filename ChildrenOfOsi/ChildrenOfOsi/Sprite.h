#pragma once
#include "Vector2f.h"
#include "common.h"
#include "Texture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
private:
	Vector2f coordinates;
	Vector2f angle;
	Texture tex;
};

