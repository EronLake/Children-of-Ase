#pragma once
#include "Vector2f.h"
#include "common.h"
//#include <GL/glew.h>

class Texture
{
public:
	Texture();
	~Texture();
	void Generate(unsigned char* data);
private:
	Vector2f size;
	FILE *imageFile;
	int id;
};

