#include "stdafx.h"
#include "WorldObj.h"
#include "GameWindow.h"



WorldObj::WorldObj()
{
}

WorldObj::WorldObj(float x, float y, bool col)
{
	loc.setXloc(x);
	loc.setYloc(y);
	rotation.setXloc(1);
	rotation.setYloc(1);
	collision = col;
	Rectangle init(loc,0,0);
	body.push_back(init);
	//cout <<"X-Loc: "<< loc.getXloc() << endl;
	//cout << "Y-Loc: " << loc.getYloc() << endl;
	//cout << "Rotation: " << rotation.getXloc()<<" , " << rotation.getYloc()<< endl;
	//cout << "Collision: " << collision << endl;
}

WorldObj::~WorldObj()
{
}

Vector2f WorldObj::getLoc()
{
	return loc;
}

void WorldObj::setLoc(Vector2f l)
{
	loc = l;
}

float WorldObj::getX()
{
	return loc.getXloc();
}

void WorldObj::setX(float x)
{
	for (int i = 0; i < body.size(); i++) {
		body[i].setX(x+(loc.getXloc()-body[i].getX()));
	}
	loc.setXloc(x);
}

float WorldObj::getY()
{
	return loc.getYloc();
}

void WorldObj::setY(float y)
{
	loc.setYloc(y);
	for (int i = 0; i < body.size(); i++) {
		body[i].setY(y + (loc.getYloc() - body[i].getY()));
	}
}

void WorldObj::shiftX(float dist)
{
	loc.shiftXloc(dist);
	for (int i = 0; i < body.size(); i++) {
		body[i].setX(body[i].getX() + dist);
	}
}

void WorldObj::shiftY(float dist)
{
	loc.shiftYloc(dist);
	for (int i = 0; i < body.size(); i++) {
		body[i].setY(body[i].getY()+dist);
	}
}

Vector2f WorldObj::getRot()
{
	return rotation;
}

float WorldObj::getRotX()
{
	return rotation.getXloc();
}

void WorldObj::setRotX(float x)
{
	rotation.setXloc(x);
}

float WorldObj::getRotY()
{
	return rotation.getYloc();
}

void WorldObj::setRotY(float y)
{
	rotation.setYloc(y);
}

void WorldObj::shiftRotX(float dist)
{
	rotation.shiftXloc(dist);
}

void WorldObj::shiftRotY(float dist)
{
	rotation.shiftYloc(dist);
}

void WorldObj::setRot(Vector2f r)
{
	rotation = r;
}

void WorldObj::setCollision(bool c)
{
	collision = c;
}

bool WorldObj::getCollision()
{
	return collision;
}

void WorldObj::setInteractable(bool i)
{
	interactable = i;
}

bool WorldObj::getInteractable()
{
	return interactable;
}

float WorldObj::getWidth()
{
	return width;
}

void WorldObj::setWidth(float w)
{
	width=w;
	body[0].setWidth(w);
}

float WorldObj::getHeight()
{
	return height;
}

void WorldObj::setHeight(float h)
{
	height=h;
	body[0].setHeight(h);
}

Sprite WorldObj::getSprite()
{
	return sprite;
}

void WorldObj::setSprite(Sprite s)
{
	sprite = s;
}

void WorldObj::animateObj()
{
	sprite.animate();
}

void WorldObj::drawObj()
{
	osi::GameWindow::drawSprite(loc.getXloc(), loc.getYloc(), width, height, sprite);
}

void WorldObj::setName(string na)
{
	name=na;
}

string WorldObj::getName()
{
	return name;
}

WorldObj::WorldObj(Vector2f p_topLeft, float p_width, float p_height) {
	loc= p_topLeft;
	width = p_width;
	height = p_height;
	Rectangle init(loc, p_width, p_height);
	body.push_back(init);
}

void WorldObj::offsetBody(int i, float x1, float x2, float y1, float y2) {
	body[i].setX(body[i].getX()+x1);
	body[i].setY(body[i].getY() + y1);
	body[i].setWidth(body[i].getWidth() - x2);
	body[i].setHeight(body[i].getHeight() - y2);
}