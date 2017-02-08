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
	int start;
	int stop;
private:
	Texture *tex;
	int index;
};

