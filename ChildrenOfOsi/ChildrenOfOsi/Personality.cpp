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

int Personality::operator*(const Personality that) const {
	return ((this->honor * that.honor) +
		(this->pride * that.pride) +
		(this->agg * that.agg) +
		(this->kind * that.kind) +
		(this->greed * that.greed) +
		(this->reck * that.reck) +
		(this->extro * that.extro));
}