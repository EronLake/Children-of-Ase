#pragma once
#include "common.h"
#include "Point.h"

class Line
{
public:
	Line();
	Line(Point p_1, Point p_2);
	~Line();
	void setP1(Point p_1);
	void setP2(Point p_2);
	Point getP1();
	Point getP2();
private:
	Point p1;
	Point p2;
};

