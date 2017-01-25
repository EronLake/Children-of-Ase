#pragma once
#include "Vector2f.h"
#include "common.h"

class Texture
{
public:
	Texture();
	~Texture();
	void setWidth(float w);
	float getWidth();
	void setHeight(float h);
	float getHeight();
	void setFWidth(float w);
	float getFWidth();
	void setFrames(int f);
	int getFrames();
	void setAnimated(bool a);
	bool getAnimated();
private:
	FILE *imageFile;
	float width;
	float height;
	int frames;
	float frameW;
	bool animated;
};

