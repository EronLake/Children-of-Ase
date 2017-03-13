#include "stdafx.h"

#include <cmath>

#include "Vector2f.h"

float Vector2f::dist(Vector2f end)
{
	float xDiff = abs(xloc - (end.getXloc()));
	float yDiff = abs(yloc - (end.getYloc()));
	return (xDiff + yDiff);
}
