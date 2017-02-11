#pragma once
#include "stdafx.h"
#include "common.h"
#include "Vector2f.h"
#include "Sprite.h"
#include "Rectangle.h"

using namespace std;

class WorldObj
{
public:
	WorldObj();
	WorldObj(float x,float y, bool col);
	virtual ~WorldObj();
	void setLoc(Vector2f l);
	Vector2f getLoc();
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	void shiftX(float dist);
	void shiftY(float dist);
	void setRot(Vector2f r);
	Vector2f getRot();
	void setRotX(float x);
	void setRotY(float y);
	float getRotX();
	float getRotY();
	void shiftRotX(float dist);
	void shiftRotY(float dist);	
	void setCollision(bool c);
	bool getCollision();
	void setInteractable(bool i);
	bool getInteractable();
	void setWidth(float w);
	float getWidth();
	void setHeight(float h);
	float getHeight();
	Sprite getSprite();
	void setSprite(Sprite s);
	void animateObj();
	void setName(string n);
	string getName();
	WorldObj(Vector2f p_topLeft, float p_width, float p_height);
	void drawObj(float _x, float _y);
	Sprite sprite;
	vector<Rectangle> body;
	void offsetBody(int i, float x1, float x2, float y1, float y2);
	void _print();
private:
	Vector2f loc;
	Vector2f rotation;
	bool collision;
	bool interactable;
	float width;
	float height;
	string name;
};


