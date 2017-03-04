#include "stdafx.h"
#include "Personality.h"


Personality::Personality()
{
}

Personality::Personality(int a, int k, int h, int p, int r, int e, int g) {
	agg = a;
	kind = k;
	honor = h;
	pride = p;
	reck = r;
	extro = e;
	greed = g;
}


Personality::~Personality()
{
}
