#include "stdafx.h"
#include "Texture_Thread.h"

GLuint Texture_Thread::textureSize = 0;
std::mutex mtx;

/**
* Loads in the image data corresponding to this texture's filename.
*/
void Texture_Thread::load()
{

	txId = Texture_Thread::textureSize;
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenTextures(1, &txId);
	glBindTexture(GL_TEXTURE_2D, txId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *image = SOIL_load_image(imageFile.c_str(), &(width), &(height), 0, SOIL_LOAD_RGBA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture_Thread::setFile(const std::string& fileName, int f) {
	//std::cout << "WORKING WITH PATH " << fileName << std::endl;
	Texture_Thread::textureSize++;
	this->imageFile = fileName;
	this->load();
	this->setFrames(f);
}