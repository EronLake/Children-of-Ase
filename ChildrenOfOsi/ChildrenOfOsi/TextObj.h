#pragma once
#include "common.h"
#include <glm/glm.hpp>

class TextObj
{
public:
	TextObj(std::string t, float xCord, float yCord, float w, float h, glm::ivec3 c);
	~TextObj();
	std::string getText() { return text; };
	std::string getFont() { return font; };
	float getX() { return x; };
	float getY() { return y; };
	float getWidth() { return width; };
	float getHeight() { return height; };
	glm::vec3 getColor() { return color; };
private:
	std::string text;
	std::string font;
	float x;
	float y;
	float width;
	float height;
	glm::ivec3 color;
};

