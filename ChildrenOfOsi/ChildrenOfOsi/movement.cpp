#pragma comment(lib, "user32.lib")
#include "common.h"
#include "Movement.h"


Movement::Movement() {

}
Movement::~Movement() {

}

//use speed variable instead of .1

std::vector <WorldObj*> Movement::objs;
QuadTree* Movement::tree;

int Movement::move_up(WorldObj* player) {
	player->shiftY((float).1);
	if (collision(player)) {
		player->shiftY((float)-.1);
	}
	LOG("X: " << player->getX() << " Y: " << player->getY());
	return 0;
}
int Movement::move_down(WorldObj* player) {
	player->shiftY((float)-.1);

	if (collision(player)) {
		player->shiftY((float).1);
	}
	LOG("X: " << player->getX() << " Y: " << player->getY());

	return 0;
}
int Movement::move_left(WorldObj* player) {
	player->shiftX((float)-.1);
	if (collision(player)) {
		player->shiftX((float).1);
	}
	LOG("X: " << player->getX() << " Y: " << player->getY());

	return 0;
}
int Movement::move_right(WorldObj* player) {
	player->shiftX((float).1);

	if (collision(player)) {
		player->shiftX((float)-.1);
	}
	LOG("X: " << player->getX() << " Y: " << player->getY());
	return 0;
}

bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }

bool Movement::collision(WorldObj *player)
{
	bool collide = false;
	tree->clear();
	bool xCollide = false;
	bool yCollide = false;
	for (int i = 0; i < objs.size(); i++) {
		tree->insert(objs[i]);
	}
	vector<WorldObj*> collidable;
	tree->retrieve(collidable, player);
	for (int i = 0; i < collidable.size(); i++) {
		xCollide = coordOverlap(collidable[i]->getX(), player->getX(), player->getX() + player->getWidth()) || coordOverlap(player->getX(), collidable[i]->getX(), collidable[i]->getX() + collidable[i]->getWidth());
		yCollide = coordOverlap(collidable[i]->getY(), player->getY(), player->getY() + player->getHeight()) || coordOverlap(player->getY(), collidable[i]->getY(), collidable[i]->getY() + collidable[i]->getHeight());
		if (xCollide && yCollide) {
			LOG("Collided with object");
			collide = true;
		}

	}
	return collide;

}

void Movement::initTree(WorldObj* screen) {

	for (int i = 0; i < 20; i++) {
		WorldObj* collidable = new WorldObj(rand() % 10, rand() % 10, true);// 5.0, 5.0);
		collidable->setWidth(5.0);
		collidable->setHeight(5.0);
		objs.push_back(collidable);
	}
	tree = new QuadTree(0, screen);
}

