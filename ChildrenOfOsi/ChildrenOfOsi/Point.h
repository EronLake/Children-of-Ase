#pragma once
#include "common.h"
#include "Sprite.h"
#include "GameWindow.h"





class Point
{
public:
	Point();
	Point(double p_x, double p_y);
	~Point();
	void setX(double p_x);
	void setY(double p_y);
	double getX();
	double getY();

	Sprite sprite;
	static Texture* tex;
	std::pair<int, int> grid_location;

	void drawObj(float _x, float _y)
	{
		GameWindow::drawSprite(getX() - _x, getY() - _y, 50, 50, sprite);
	}
	void drawObjRiv(float _x, float _y) {
		GameWindow::drawSprite(getX() - _x, (25000 - getY()) - _y, 20, 20, sprite);
	}

private:
	double xCoord;
	double yCoord;
};

