/*#pragma once
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

*/
#pragma once
#include "common.h"
#include "Rectangle.h"
#include "GameWindow.h"
#include "Containers.h"

class GameMap
{
public:
	GameMap();
	~GameMap();
	void setTextures();
	void loadTexture();
	void setSprite();
	void drawMap(float _x, float _y);
	
private:
	Rectangle* map1_1;
	Rectangle* map1_2;
	Rectangle* map1_3;
	Rectangle* map1_4;
	Rectangle* map1_5;

	Rectangle* map2_1;
	Rectangle* map2_2;
	Rectangle* map2_3;
	Rectangle* map2_4;
	Rectangle* map2_5;

	Rectangle* map3_1;
	Rectangle* map3_2;
	Rectangle* map3_3;
	Rectangle* map3_4;
	Rectangle* map3_5;

	Rectangle* map4_1;
	Rectangle* map4_2;
	Rectangle* map4_3;
	Rectangle* map4_4;
	Rectangle* map4_5;

	Rectangle* map5_1;
	Rectangle* map5_2;
	Rectangle* map5_3;
	Rectangle* map5_4;
	Rectangle* map5_5;

	//Rectangle* river;

	Texture* map1_1tex;
	Texture* map1_2tex;
	Texture* map1_3tex;
	Texture* map1_4tex;
	Texture* map1_5tex;

	Texture* map2_1tex;
	Texture* map2_2tex;
	Texture* map2_3tex;
	Texture* map2_4tex;
	Texture* map2_5tex;


	Texture* map3_1tex;
	Texture* map3_2tex;
	Texture* map3_3tex;
	Texture* map3_4tex;
	Texture* map3_5tex;


	Texture* map4_1tex;
	Texture* map4_2tex;
	Texture* map4_3tex;
	Texture* map4_4tex;
	Texture* map4_5tex;

	Texture* map5_1tex;
	Texture* map5_2tex;
	Texture* map5_3tex;
	Texture* map5_4tex;
	Texture* map5_5tex;


	//Texture* riverTex;
};

