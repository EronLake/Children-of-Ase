#include "stdafx.h"
#pragma once
#include "Vector2f.h"
#include "common.h"
#include "GLEW\glew.h"
#include "GLFW/glfw3.h"
#include "SOIL/SOIL.h"
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
	void setFile(string img);
	void load();
	unsigned char* getImage();
private:
	string imageFile;
	int width;
	int height;
	int frames;
	int frameWidth;
	bool animated;
	unsigned char *image;
};

