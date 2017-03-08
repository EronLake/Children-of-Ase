#pragma once
#include "common.h"

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
private:
	double xCoord;
	double yCoord;
};

