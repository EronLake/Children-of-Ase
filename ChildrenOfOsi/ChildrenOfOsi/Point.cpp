#include "stdafx.h"
#include "Point.h"


Point::Point()
{
	sprite.setTexture(tex);
}

Point::Point(double p_x, double p_y)
{
	sprite.setTexture(tex);
	xCoord = p_x;
	yCoord = p_y;
}


Point::~Point()
{
}

void Point::setX(double p_x)
{
	xCoord = p_x;
}

void Point::setY(double p_y)
{
	yCoord = p_y;
}

double Point::getX()
{
	return xCoord;
}

double Point::getY()
{
	return yCoord;
}
