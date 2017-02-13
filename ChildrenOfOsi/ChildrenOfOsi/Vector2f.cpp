#include "stdafx.h"
#include "Vector2f.h"
#include "common.h"



Vector2f::Vector2f()
{
}

Vector2f::Vector2f(float x, float y)
{
	xloc = x;
	yloc = y;
}

Vector2f::~Vector2f()
{
}

float Vector2f::getXloc()
{
	return xloc;
}

void Vector2f::setXloc(float x)
{
	xloc =x;
}

float Vector2f::getYloc()
{
	return yloc;
}

void Vector2f::setYloc(float y)
{
	yloc = y;
}

void Vector2f::shiftXloc(float dist)
{
	xloc += dist;
}

void Vector2f::shiftYloc(float dist)
{
	yloc += dist;
}