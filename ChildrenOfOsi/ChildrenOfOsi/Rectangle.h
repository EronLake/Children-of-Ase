#include "common.h"
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
	void setX(float x) { topLeft.setXloc(x); }
	void setY(float y) { topLeft.setYloc(y); }
	void setLoc(Vector2f l) { topLeft=l; }
	void setWidth(float w) { width=w; }
	void setHeight(float h) { height=h; }
	Sprite getSprite() { return sprite; }
	void setSprite(Sprite s) { sprite = s; }
};