#include "stdafx.h"
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

void Texture::setWidth(int w)
{
	width = w;
}

float Texture::getHeight()
{
	return height;
}

void Texture::setHeight(int h)
{
	height = h;
}

float Texture::getFrameWidth()
{
	return frameWidth;
}

void Texture::setFrameWidth(int w)
{
	frameWidth = w;
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

void Texture::setFile(string img)
{
	imageFile = img;
}

unsigned char* Texture::getImage()
{
	return image;
}

void Texture::load()
{
	image = SOIL_load_image(imageFile.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	//SOIL_free_image_data(image);
}