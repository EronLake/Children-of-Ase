#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "stdafx.h"

#include "common.h"
#include "Vector2f.h"

#include "GLEW\glew.h"
#include "GLFW/glfw3.h"
#include "SOIL/SOIL.h"
#include <thread> 
#include <mutex> 

class Texture_Thread
{
public:

	Texture_Thread() = default;
	Texture_Thread(const std::string& fileName) :
		imageFile(fileName) {}
	Texture_Thread(const std::string& fileName, int w, int h, int frames = 1) :
		imageFile(fileName), width(w), height(h), frames(frames), frameWidth(width) {}
	~Texture_Thread() = default;

	static GLuint textureSize;

	GLuint getId() const { return this->txId; }
	std::string getFile() const { return this->imageFile; }
	int getWidth() const { return this->width; }
	int getHeight() const { return this->height; }
	int getFrames() const { return this->frames; }
	int getFrameWidth() const { return this->frameWidth; }
	bool getAnimated() const { return this->animated; }

	void setFile(const std::string& fileName, int f);
	void setWidth(int w) { this->width = w; }
	void setHeight(int h) { this->height = h; }
	void setFrames(int f) { this->frameWidth = this->width / (this->frames = f); }
	void setFrameWidth(int fw) { this->frameWidth = fw; }
	void setAnimated(bool a) { this->animated = a; }

	void load();

private:

	GLuint txId;
	std::string imageFile;

	int width, height;
	int frames, frameWidth;

	bool animated;
};
