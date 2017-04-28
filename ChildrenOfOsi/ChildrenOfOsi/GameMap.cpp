#include "stdafx.h"
#include "GameMap.h"


GameMap::GameMap()
{
	mapTopLeft = new Rectangle(Vector2f(0.0, 0.0), 5000.0, 20000.0);
	mapTopRight = new Rectangle(Vector2f(20000.0, 0.0), 20000.0, 20000.0);
	mapBottomLeft = new Rectangle(Vector2f(0.0, 20000.0), 20000.0, 20000.0);
	mapBottomRight = new Rectangle(Vector2f(20000.0, 20000.0), 20000.0, 20000.0);
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
	topLeftTex->setFile("Assets/Sprites/smap1_1.png", 1);
	topRightTex->setFile("Assets/Sprites/smap1_2.png", 1);
	bottomLeftTex->setFile("Assets/Sprites/smap2_1.png", 1);
	bottomRightTex->setFile("Assets/Sprites/smap2_2.png", 1);
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
	osi::GameWindow::drawSprite(mapTopLeft->getX() - _x, mapTopLeft->getY() - _y, mapTopLeft->getWidth(), mapTopLeft->getHeight(), mapTopLeft->sprite);
	osi::GameWindow::drawSprite(mapTopRight->getX() - _x, mapTopRight->getY() - _y, mapTopRight->getWidth(), mapTopRight->getHeight(), mapTopRight->sprite);
	osi::GameWindow::drawSprite(mapBottomLeft->getX() - _x, mapBottomLeft->getY() - _y, mapBottomLeft->getWidth(), mapBottomLeft->getHeight(), mapBottomLeft->sprite);
	osi::GameWindow::drawSprite(mapBottomRight->getX() - _x, mapBottomRight->getY() - _y, mapBottomRight->getWidth(), mapBottomRight->getHeight(), mapBottomRight->sprite);
	//osi::GameWindow::drawSprite(river->getX() - _x, river->getY() - _y, river->getWidth(), river->getHeight(), river->sprite);



}

*/



/////////////////////////////////NewMapMode/////////////////

#include "stdafx.h"
#include "GameMap.h"


GameMap::GameMap()
{

	map1_1 = new Rectangle(Vector2f(0.0,0.0), 5000.0, 5000.0); //these we had changed to all be 3000
	map1_2 = new Rectangle(Vector2f(5000.0, 0.0), 5000.0, 5000.0);
	map1_3 = new Rectangle(Vector2f(10000.0, 0.0), 5000.0, 5000.0);
	map1_4 = new Rectangle(Vector2f(15000, 0.0), 5000.0, 5000.0);
	map1_5 = new Rectangle(Vector2f(20000.0, 0.0), 5000.0, 5000.0);
	
	map2_1 = new Rectangle(Vector2f(0.0, 5000.0), 5000.0, 5000.0);
	map2_2 = new Rectangle(Vector2f(5000.0, 5000.0), 5000.0, 5000.0);
	map2_3 = new Rectangle(Vector2f(10000.0, 5000.0), 5000.0, 5000.0);
	map2_4 = new Rectangle(Vector2f(15000.0, 5000.0), 5000.0, 5000.0);
	map2_5 = new Rectangle(Vector2f(20000.0, 5000.0), 5000.0, 5000.0);

	map3_1 = new Rectangle(Vector2f(0.0, 10000.0), 5000.0, 5000.0); 
	map3_2 = new Rectangle(Vector2f(5000.0, 10000.0), 5000.0, 5000.0);
	map3_3 = new Rectangle(Vector2f(10000.0, 10000.0), 5000.0, 5000.0);
	map3_4 = new Rectangle(Vector2f(15000, 10000.0), 5000.0, 5000.0);
	map3_5 = new Rectangle(Vector2f(20000, 10000.0), 5000.0, 5000.0);

	map4_1 = new Rectangle(Vector2f(0.0, 15000.0), 5000.0, 5000.0);
	map4_2 = new Rectangle(Vector2f(5000.0, 15000.0), 5000.0, 5000.0);
	map4_3 = new Rectangle(Vector2f(10000.0, 15000.0), 5000.0, 5000.0);
	map4_4 = new Rectangle(Vector2f(15000, 15000.0), 5000.0, 5000.0);
	map4_5 = new Rectangle(Vector2f(20000, 15000.0), 5000.0, 5000.0);
	


	map5_1 = new Rectangle(Vector2f(0.0, 20000.0), 5000.0, 5000.0);
	map5_2 = new Rectangle(Vector2f(5000.0, 20000.0), 5000.0, 5000.0);
	map5_3 = new Rectangle(Vector2f(10000.0, 20000.0), 5000.0, 5000.0);
	map5_4 = new Rectangle(Vector2f(15000, 20000.0), 5000.0, 5000.0);
	map5_5 = new Rectangle(Vector2f(20000, 20000.0), 5000.0, 5000.0);
	

	//river = new Rectangle(Vector2f(0.0, 0.0), 10000.0, 10000.0);
	//alllocate mem for texture


	//riverTex = new Texture();
}


GameMap::~GameMap()
{
}

void GameMap::setTextures() {
	map1_1tex = Containers::texture_table["map1_1"];
	map1_2tex = Containers::texture_table["map1_2"];
	map1_3tex = Containers::texture_table["map1_3"];
	map1_4tex = Containers::texture_table["map1_4"];
	map1_5tex = Containers::texture_table["map1_5"];

	map2_1tex = Containers::texture_table["map2_1"];
	map2_2tex = Containers::texture_table["map2_2"];
	map2_3tex = Containers::texture_table["map2_3"];
	map2_4tex = Containers::texture_table["map2_4"];
	map2_5tex = Containers::texture_table["map2_5"];

	map3_1tex = Containers::texture_table["map3_1"];
	map3_2tex = Containers::texture_table["map3_2"];
	map3_3tex = Containers::texture_table["map3_3"];
	map3_4tex = Containers::texture_table["map3_4"];
	map3_5tex = Containers::texture_table["map3_5"];

	map4_1tex = Containers::texture_table["map4_1"];
	map4_2tex = Containers::texture_table["map4_2"];
	map4_3tex = Containers::texture_table["map4_3"];
	map4_4tex = Containers::texture_table["map4_4"];
	map4_5tex = Containers::texture_table["map4_5"];

	map5_1tex = Containers::texture_table["map5_1"];
	map5_2tex = Containers::texture_table["map5_2"];
	map5_3tex = Containers::texture_table["map5_3"];
	map5_4tex = Containers::texture_table["map5_4"];
	map5_5tex = Containers::texture_table["map5_5"];
}

void GameMap::loadTexture()
{
	map1_1tex->setFile("Assets/Sprites/map1_1_4000.png", 1);
	map1_2tex->setFile("Assets/Sprites/map1_2_4000.png", 1);
	map1_3tex->setFile("Assets/Sprites/map1_3_4000.png", 1);
	map1_4tex->setFile("Assets/Sprites/map1_4_4000.png", 1);
	map1_5tex->setFile("Assets/Sprites/map1_5_4000.png", 1);

	map2_1tex->setFile("Assets/Sprites/map2_1_4000.png", 1);
	map2_2tex->setFile("Assets/Sprites/map2_2_4000.png", 1);
	map2_3tex->setFile("Assets/Sprites/map2_3_4000.png", 1);
	map2_4tex->setFile("Assets/Sprites/map2_4_4000.png", 1);
	map2_5tex->setFile("Assets/Sprites/map2_5_4000.png", 1);

	map3_1tex->setFile("Assets/Sprites/map3_1_4000.png", 1);
	map3_2tex->setFile("Assets/Sprites/map3_2_4000.png", 1);
	map3_3tex->setFile("Assets/Sprites/map3_3_4000.png", 1);
	map3_4tex->setFile("Assets/Sprites/map3_4_4000.png", 1);
	map3_5tex->setFile("Assets/Sprites/map3_5_4000.png", 1);

	map4_1tex->setFile("Assets/Sprites/map4_1_4000.png", 1);
	map4_2tex->setFile("Assets/Sprites/map4_2_4000.png", 1);
	map4_3tex->setFile("Assets/Sprites/map4_3_4000.png", 1);
	map4_4tex->setFile("Assets/Sprites/map4_4_4000.png", 1);
	map4_5tex->setFile("Assets/Sprites/map4_5_4000.png", 1);

	map5_1tex->setFile("Assets/Sprites/map5_1_4000.png", 1);
	map5_2tex->setFile("Assets/Sprites/map5_2_4000.png", 1);
	map5_3tex->setFile("Assets/Sprites/map5_3_4000.png", 1);
	map5_4tex->setFile("Assets/Sprites/map5_4_4000.png", 1);
	map5_5tex->setFile("Assets/Sprites/map5_5_4000.png", 1);
	//riverTex->setFile("River.png");
}

void GameMap::setSprite()
{
	map1_1->sprite.setTexture(map1_1tex);
	map1_2->sprite.setTexture(map1_2tex);
	map1_3->sprite.setTexture(map1_3tex);
	map1_4->sprite.setTexture(map1_4tex);
	map1_5->sprite.setTexture(map1_5tex);

	map2_1->sprite.setTexture(map2_1tex);
	map2_2->sprite.setTexture(map2_2tex);
	map2_3->sprite.setTexture(map2_3tex);
	map2_4->sprite.setTexture(map2_4tex);
	map2_5->sprite.setTexture(map2_5tex);

	map3_1->sprite.setTexture(map3_1tex);
	map3_2->sprite.setTexture(map3_2tex);
	map3_3->sprite.setTexture(map3_3tex);
	map3_4->sprite.setTexture(map3_4tex);
	map3_5->sprite.setTexture(map3_5tex);

	map4_1->sprite.setTexture(map4_1tex);
	map4_2->sprite.setTexture(map4_2tex);
	map4_3->sprite.setTexture(map4_3tex);
	map4_4->sprite.setTexture(map4_4tex);
	map4_5->sprite.setTexture(map4_5tex);

	map5_1->sprite.setTexture(map5_1tex);
	map5_2->sprite.setTexture(map5_2tex);
	map5_3->sprite.setTexture(map5_3tex);
	map5_4->sprite.setTexture(map5_4tex);
	map5_5->sprite.setTexture(map5_5tex);

	//river->sprite.setTexture(riverTex);
}

void GameMap::drawMap(float _x, float _y)
{
	
	if (Party::dist_location_to_location(map1_1->getLoc(), {_x,_y}) < 7500)GameWindow::drawSprite(map1_1->getX() - _x, map1_1->getY() - _y, map1_1->getWidth(), map1_1->getHeight(), map1_1->sprite);
	if (Party::dist_location_to_location(map1_2->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map1_2->getX() - _x, map1_2->getY() - _y, map1_2->getWidth(), map1_2->getHeight(), map1_2->sprite);
	if (Party::dist_location_to_location(map1_3->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map1_3->getX() - _x, map1_3->getY() - _y, map1_3->getWidth(), map1_3->getHeight(), map1_3->sprite);
	if (Party::dist_location_to_location(map1_4->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map1_4->getX() - _x, map1_4->getY() - _y, map1_4->getWidth(), map1_4->getHeight(), map1_4->sprite);
	if (Party::dist_location_to_location(map1_5->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map1_5->getX() - _x, map1_5->getY() - _y, map1_5->getWidth(), map1_5->getHeight(), map1_5->sprite);

	if (Party::dist_location_to_location(map2_1->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map2_1->getX() - _x, map2_1->getY() - _y, map2_1->getWidth(), map2_1->getHeight(), map2_1->sprite);
	if (Party::dist_location_to_location(map2_2->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map2_2->getX() - _x, map2_2->getY() - _y, map2_2->getWidth(), map2_2->getHeight(), map2_2->sprite);
	if (Party::dist_location_to_location(map2_3->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map2_3->getX() - _x, map2_3->getY() - _y, map2_3->getWidth(), map2_3->getHeight(), map2_3->sprite);
	if (Party::dist_location_to_location(map2_4->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map2_4->getX() - _x, map2_4->getY() - _y, map2_4->getWidth(), map2_4->getHeight(), map2_4->sprite);
	if (Party::dist_location_to_location(map2_5->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map2_5->getX() - _x, map2_5->getY() - _y, map2_5->getWidth(), map2_5->getHeight(), map2_5->sprite);

	if (Party::dist_location_to_location(map3_1->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map3_1->getX() - _x, map3_1->getY() - _y, map3_1->getWidth(), map3_1->getHeight(), map3_1->sprite);
	if (Party::dist_location_to_location(map3_2->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map3_2->getX() - _x, map3_2->getY() - _y, map3_2->getWidth(), map3_2->getHeight(), map3_2->sprite);
	if (Party::dist_location_to_location(map3_3->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map3_3->getX() - _x, map3_3->getY() - _y, map3_3->getWidth(), map3_3->getHeight(), map3_3->sprite);
	if (Party::dist_location_to_location(map3_4->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map3_4->getX() - _x, map3_4->getY() - _y, map3_4->getWidth(), map3_4->getHeight(), map3_4->sprite);
	if (Party::dist_location_to_location(map3_5->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map3_5->getX() - _x, map3_5->getY() - _y, map3_5->getWidth(), map3_5->getHeight(), map3_5->sprite);

	if (Party::dist_location_to_location(map4_1->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map4_1->getX() - _x, map4_1->getY() - _y, map4_1->getWidth(), map4_1->getHeight(), map4_1->sprite);
	if (Party::dist_location_to_location(map4_2->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map4_2->getX() - _x, map4_2->getY() - _y, map4_2->getWidth(), map4_2->getHeight(), map4_2->sprite);
	if (Party::dist_location_to_location(map4_3->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map4_3->getX() - _x, map4_3->getY() - _y, map4_3->getWidth(), map4_3->getHeight(), map4_3->sprite);
	if (Party::dist_location_to_location(map4_4->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map4_4->getX() - _x, map4_4->getY() - _y, map4_4->getWidth(), map4_4->getHeight(), map4_4->sprite);
	if (Party::dist_location_to_location(map4_5->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map4_5->getX() - _x, map4_5->getY() - _y, map4_5->getWidth(), map4_5->getHeight(), map4_5->sprite);

	if (Party::dist_location_to_location(map5_1->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map5_1->getX() - _x, map5_1->getY() - _y, map5_1->getWidth(), map5_1->getHeight(), map5_1->sprite);
	if (Party::dist_location_to_location(map5_2->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map5_2->getX() - _x, map5_2->getY() - _y, map5_2->getWidth(), map5_2->getHeight(), map5_2->sprite);
	if (Party::dist_location_to_location(map5_3->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map5_3->getX() - _x, map5_3->getY() - _y, map5_3->getWidth(), map5_3->getHeight(), map5_3->sprite);
	if (Party::dist_location_to_location(map5_4->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map5_4->getX() - _x, map5_4->getY() - _y, map5_4->getWidth(), map5_4->getHeight(), map5_4->sprite);
	if (Party::dist_location_to_location(map5_5->getLoc(), { _x,_y }) < 7500)GameWindow::drawSprite(map5_5->getX() - _x, map5_5->getY() - _y, map5_5->getWidth(), map5_5->getHeight(), map5_5->sprite);

	
	//GameWindow::drawSprite(river->getX() - _x, river->getY() - _y, river->getWidth(), river->getHeight(), river->sprite);

	

}



