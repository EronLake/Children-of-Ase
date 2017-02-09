#pragma once
#include "stdafx.h"
#include "Vector2f.h"
#include "common.h"
#include "Texture.h"
using namespace std;

class Sprite
{
public:
	Sprite();
	~Sprite();
	void setTexture(Texture *t);
	void animate();
	string getTfile();
	Texture getTexture();
	float getStart();
	float getStop();
	float getTop();
	float getBottom();
private:
	float start;
	float stop;
	float top;
	float bottom;
	Texture *tex;
	int index;
	int tempTime;
};

