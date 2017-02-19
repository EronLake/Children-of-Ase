#pragma once
#include "common.h"
#include "Rectangle.h"
#include "GameWindow.h"

class GameMap
{
public:
	GameMap();
	~GameMap();
	void loadTexture();
	void setSprite();
	void drawMap(float _x, float _y);
	
private:
	Rectangle* mapTopLeft;
	Rectangle* mapTopRight;
	Rectangle* mapBottomLeft;
	Rectangle* mapBottomRight;
	//Rectangle* river;

	Texture* topLeftTex;
	Texture* topRightTex;
	Texture* bottomLeftTex;
	Texture* bottomRightTex;
	//Texture* riverTex;
};

