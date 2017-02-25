#pragma once

//#include "common.h"
#include "stdafx.h"
#include "Vector2f.h"
#include "Sprite.h"

using namespace std;

class Rectangle
{
private:
	Vector2f topLeft;
	float width, height;
public:
	Rectangle(Vector2f p_topLeft, float p_width, float p_height) {
		topLeft = p_topLeft;
		width = p_width;
		height = p_height;
	}
	Rectangle() {}
	~Rectangle() {}
	Sprite sprite;
	float getX() { return topLeft.getXloc(); }
	float getY() { return topLeft.getYloc(); }
	float getWidth() { return width; }
	float getHeight() { return height; }
	Vector2f getLoc() { return topLeft; }
	Vector2f getBL() { return{ getX()-105, getY() + height + 5 }; }
	Vector2f getTR() { return{ getX()+width+5, getY()-105 }; }
	Vector2f getBR() { return{ getX()+width+5, getY() + height+5 }; }
	void setX(float x) { topLeft.setXloc(x); }
	void setY(float y) { topLeft.setYloc(y); }
	void setWidth(float w) { width=w; }
	void setHeight(float h) { height=h; }
	void setLoc(Vector2f l) { topLeft=l; }
	Sprite getSprite() { return sprite; }
	void setSprite(Sprite s) { sprite = s; }
};