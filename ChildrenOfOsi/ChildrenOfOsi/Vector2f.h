#pragma once
#include "stdafx.h"
class Vector2f
{
public:
	Vector2f();
	Vector2f(float x, float y);
	~Vector2f();
	void setXloc(float x);
	void setYloc(float y);
	float getXloc();
	float getYloc();
	void shiftXloc(float dist);
	void shiftYloc(float dist);
	float dist(Vector2f end);
    bool operator==(const Vector2f v) const;
	bool operator<(const Vector2f v) const;
//private:
	float xloc;
	float yloc;
};

