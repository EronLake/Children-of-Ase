#include "stdafx.h"
#include "Line.h"


Line::Line()
{
}

Line::Line(Point p_1, Point p_2)
{
	p1 = p_1;
	p2 = p_2;
}


Line::~Line()
{
}

void Line::setP1(Point p_1)
{
	p1 = p_1;
}

void Line::setP2(Point p_2)
{
	p2 = p_2;
}

Point Line::getP1()
{
	return p1;
}

Point Line::getP2()
{
	return p2;
}
