#pragma once
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
private:
	Texture *tex;
	int index;
	float start;
	float stop;
};

