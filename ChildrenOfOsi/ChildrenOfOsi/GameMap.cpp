#include "stdafx.h"
#include "GameMap.h"


GameMap::GameMap()
{
	mapTopLeft = new Rectangle(Vector2f(0.0, 0.0), 5000.0, 5000.0);
	mapTopRight = new Rectangle(Vector2f(5000.0, 0.0), 5000.0, 5000.0);
	mapBottomLeft = new Rectangle(Vector2f(0.0, 5000.0), 5000.0, 5000.0);
	mapBottomRight = new Rectangle(Vector2f(5000.0, 5000.0), 5000.0, 5000.0);
	//river = new Rectangle(Vector2f(0.0, 0.0), 10000.0, 10000.0);
	//alllocate mem for texture
	topLeftTex = new Texture();
	topRightTex = new Texture();
	bottomLeftTex = new Texture();
	bottomRightTex = new Texture();
	//riverTex = new Texture();
}


GameMap::~GameMap()
{
}

void GameMap::loadTexture()
{
	topLeftTex->setFile("Assets/Sprites/MapTopLeft.png",1);
	topRightTex->setFile("Assets/Sprites/MapTopRight.png",1);
	bottomLeftTex->setFile("Assets/Sprites/MapBottomLeft.png",1);
	bottomRightTex->setFile("Assets/Sprites/MapBottomRight.png",1);
	//riverTex->setFile("River.png");
}

void GameMap::setSprite()
{
	mapTopLeft->sprite.setTexture(topLeftTex);
	mapTopRight->sprite.setTexture(topRightTex);
	mapBottomLeft->sprite.setTexture(bottomLeftTex);
	mapBottomRight->sprite.setTexture(bottomRightTex);
	//river->sprite.setTexture(riverTex);
}

void GameMap::drawMap(float _x, float _y)
{
	osi::GameWindow::drawSprite(mapTopLeft->getX()- _x, mapTopLeft->getY()- _y, mapTopLeft->getWidth(), mapTopLeft->getHeight(), mapTopLeft->sprite);
	osi::GameWindow::drawSprite(mapTopRight->getX()- _x, mapTopRight->getY()- _y, mapTopRight->getWidth(), mapTopRight->getHeight(), mapTopRight->sprite);
	osi::GameWindow::drawSprite(mapBottomLeft->getX()- _x, mapBottomLeft->getY()- _y, mapBottomLeft->getWidth(), mapBottomLeft->getHeight(), mapBottomLeft->sprite);
	osi::GameWindow::drawSprite(mapBottomRight->getX()- _x, mapBottomRight->getY()- _y, mapBottomRight->getWidth(), mapBottomRight->getHeight(), mapBottomRight->sprite);
	//osi::GameWindow::drawSprite(river->getX() - _x, river->getY() - _y, river->getWidth(), river->getHeight(), river->sprite);



}
