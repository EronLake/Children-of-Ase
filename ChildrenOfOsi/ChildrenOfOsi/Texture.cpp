#include "stdafx.h"
#include "Texture.h"

std::vector<GLuint> Texture::textureId;

/**
 * Loads in the image data corresponding to this texture's filename.
 */
void Texture::load()
{
  Texture::textureId.push_back(this->txId = Texture::textureId.size() + 1);
	this->image = SOIL_load_image(imageFile.c_str(), &(this->width), &(this->height), 0, SOIL_LOAD_RGBA);

	glGenTextures(1, &Texture::textureId[txId - 1]);
	glBindTexture(GL_TEXTURE_2D, Texture::textureId[txId - 1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image(imageFile.c_str(), &(this->width), &(this->height), 0, SOIL_LOAD_RGBA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setFile(const std::string& fileName, int f) {
	this->imageFile = fileName; 
	this->load();
	this->setFrames(f);
}