#include "stdafx.h"
#include "Attack.h"


Attack::Attack()
{
}

Attack::Attack(int dmg, int duration, bool dstry, float w, float h, float s)
{
	damage=dmg;
	dur=duration;
	destroy=dstry;
	width=w;
	height=h;
	speed=s;
}

Attack::~Attack()
{
}
