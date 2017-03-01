#include "stdafx.h"
#include "TextObj.h"


TextObj::TextObj(std::string t, float xCord, float yCord, float w, float h, glm::ivec3 c)
{
	font = "Arial 48";
	text = t;
	x = xCord;
	y = yCord;
	width = w;
	height = h;
	color = c;
}


TextObj::~TextObj()
{
}
