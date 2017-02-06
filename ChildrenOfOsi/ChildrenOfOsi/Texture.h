#include "stdafx.h"
#pragma once
#include "Vector2f.h"
#include "common.h"
using namespace std;

class Texture
{
public:
	Texture();
	~Texture();
	void setWidth(int w);
	float getWidth();
	void setHeight(int h);
	float getHeight();
	void setFrameWidth(int w);
	float getFrameWidth();
	void setFrames(int f);
	int getFrames();
	void setAnimated(bool a);
	bool getAnimated();
	string getFile();
	void setFile(string image);
private:
	string imageFile;
	int width;
	int height;
	int frames;
	int frameWidth;
	bool animated;
};

