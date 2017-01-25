#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

float Texture::getWidth()
{
	return width;
}

void Texture::setWidth(float w)
{
	width = w;
}

float Texture::getHeight()
{
	return height;
}

void Texture::setHeight(float h)
{
	height = h;
}

float Texture::getFWidth()
{
	return frameW;
}

void Texture::setFWidth(float w)
{
	frameW = w;
}

int Texture::getFrames()
{
	return frames;
}

void Texture::setFrames(int f)
{
	frames = f;
}

bool Texture::getAnimated()
{
	return animated;
}

void Texture::setAnimated(bool a)
{
	animated=a;
}

string Texture::getFile()
{
	return imageFile;
}

void Texture::setFile(string image)
{
	imageFile = image;
}