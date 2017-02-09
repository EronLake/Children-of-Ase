#include "stdafx.h"
#include "Texture.h"
vector<GLuint> Texture::textureId;

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
	frameWidth = width / frames;
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
	txId = textureId.size()+1;
	image = SOIL_load_image(imageFile.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	textureId.push_back(txId);
	glGenTextures(1, &textureId[txId-1]);
	glBindTexture(GL_TEXTURE_2D, textureId[txId-1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image(imageFile.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getId()
{
	return txId;
}