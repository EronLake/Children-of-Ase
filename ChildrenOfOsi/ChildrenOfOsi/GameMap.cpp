#include "stdafx.h"
#include "GameMap.h"


GameMap::GameMap()
{
	mapTopLeft = new Rectangle(Vector2f(0.0, 0.0), 5000.0, 5000.0);
	mapTopRight = new Rectangle(Vector2f(5000.0, 0.0), 5000.0, 5000.0);
	mapBottomLeft = new Rectangle(Vector2f(0.0, 5000.0), 5000.0, 5000.0);
	mapBottomRight = new Rectangle(Vector2f(5000.0, 5000.0), 5000.0, 5000.0);
	//alllocate mem for texture
	topLeftTex = new Texture();
	topRightTex = new Texture();
	bottomLeftTex = new Texture();
	bottomRightTex = new Texture();
}


GameMap::~GameMap()
{
}

void GameMap::loadTexture()
{
	topLeftTex->setFile("MapTopLeft.png");
	topRightTex->setFile("MapTopRight.png");
	bottomLeftTex->setFile("MapBottomLeft.png");
	bottomRightTex->setFile("MapBottomRight.png");

	topLeftTex->load();
	topRightTex->load();
	bottomLeftTex->load();
	bottomRightTex->load();

	topLeftTex->setFrames(1);
	topRightTex->setFrames(1);
	bottomLeftTex->setFrames(1);
	bottomRightTex->setFrames(1);
}

void GameMap::setSprite()
{
	mapTopLeft->sprite.setTexture(topLeftTex);
	mapTopRight->sprite.setTexture(topRightTex);
	mapBottomLeft->sprite.setTexture(bottomLeftTex);
	mapBottomRight->sprite.setTexture(bottomRightTex);
}

void GameMap::drawMap(float _x, float _y)
{
	osi::GameWindow::drawSprite(mapTopLeft->getX()- _x, mapTopLeft->getY()- _y, mapTopLeft->getWidth(), mapTopLeft->getHeight(), mapTopLeft->sprite);
	osi::GameWindow::drawSprite(mapTopRight->getX()- _x, mapTopRight->getY()- _y, mapTopRight->getWidth(), mapTopRight->getHeight(), mapTopRight->sprite);
	osi::GameWindow::drawSprite(mapBottomLeft->getX()- _x, mapBottomLeft->getY()- _y, mapBottomLeft->getWidth(), mapBottomLeft->getHeight(), mapBottomLeft->sprite);
	osi::GameWindow::drawSprite(mapBottomRight->getX()- _x, mapBottomRight->getY()- _y, mapBottomRight->getWidth(), mapBottomRight->getHeight(), mapBottomRight->sprite);

}
