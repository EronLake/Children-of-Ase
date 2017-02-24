#include "stdafx.h"
#include "Soldier.h"
using namespace std;


Soldier::Soldier()
{
}

Soldier::Soldier(float x, float y, bool col) :NPC(x, y, col)
{
	melee.setDestroy(false);
	melee.setSpeed(0);
}

Soldier::Soldier(Vector2f p_topLeft, float p_width, float p_height):NPC(p_topLeft,p_width,p_height)
{
	melee.setWidth(p_width);
	melee.setHeight(p_height);
	melee.setDestroy(false);
	melee.setSpeed(0);
}

Soldier::~Soldier()
{
}

Projectile* Soldier::newAttack(int i)
{
	float w = atkTypes[i]->getWidth();
	if (w == 0)w = getWidth();
	float h = atkTypes[i]->getHeight();
	if (w == 0)w = getHeight();
	float x=getX();
	float y=getY();
	std::string d = getDirection();
	if (d.compare("UP")) {
		y-= atkTypes[i]->getHeight()+1;
	} else if (d.compare("DOWN")) {
		y += getHeight() + 1;
	}
	else if (d.compare("LEFT")) {
		x -= atkTypes[i]->getWidth() + 1;
	}
	else if (d.compare("RIGHT")) {
		x += getWidth() + 1;
	}
	Projectile* p = new Projectile(x, y, true);
	p->setDmg(atkTypes[i]->getDmg());
	p->setDuration(atkTypes[i]->getDuration());
	p->setDestroy(atkTypes[i]->getDestroy());
	p->setSpeed(atkTypes[i]->getSpeed());
	p->setWidth(w);
	p->setHeight(h);
	p->setDirection(d);
	return p;
}