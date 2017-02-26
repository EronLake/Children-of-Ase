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
	cdTotal = 60;
	cdFrame = 0;
	cool = false;
}

Soldier::Soldier(Vector2f p_topLeft, float p_width, float p_height):NPC(p_topLeft,p_width,p_height)
{
	melee.setX(p_topLeft.getXloc());
	melee.setY(p_topLeft.getYloc());
	melee.setWidth(p_width);
	melee.setHeight(p_height);
	melee.setDestroy(false);
	melee.setSpeed(0);
	cdTotal = 60;
	cdFrame = 0;
	cool = false;
}

Soldier::~Soldier()
{
}

Attack* Soldier::newAttack(int i)
{
	if (available[i] != NULL) {
		float w = available[i]->getWidth();
		if (w == 0)w = getWidth();
		float h = available[i]->getHeight();
		if (w == 0)w = getHeight();
		float x = getX();
		float y = getY();
		std::string d = getDirection();
		if (d.compare("UP")) {
			y = y - (available[i]->getHeight() + 1);
		}
		else if (d.compare("DOWN") == 0) {
			y = y + (getHeight() + 1);
		}
		else if (d.compare("LEFT") == 0) {
			x = x - (available[i]->getWidth() + 1);
		}
		else if (d.compare("RIGHT") == 0) {
			x = x + (getWidth() + 1);
		}
		Attack* p = new Attack(x, y, true);
		p->setDmg(available[i]->getDmg());
		p->setDuration(available[i]->getDuration());
		p->setDestroy(available[i]->getDestroy());
		p->setSpeed(available[i]->getSpeed());
		p->setWidth(w);
		p->setHeight(h);
		p->setDirection(d);
		cdMap[available[i]] = 0;
		cool = false;
		cdFrame = 0;
		return p;
	}
}

void Soldier::meleeAttack() {
	float x=getX();
	float y=getY();
	std::string d = getDirection();
	if (d.compare("UP")) {
		y= y-(melee.getHeight()+1);
	} else if (d.compare("DOWN")==0) {
		y = y+(getHeight() + 1);
	}
	else if (d.compare("LEFT")==0) {
		x = x-(melee.getWidth() + 1);
	}
	else if (d.compare("RIGHT")==0) {
		x = x+(getWidth() + 1);
	}
	melee.setX(x);
	melee.setY(y);
	cool = false;
	cdFrame = 0;
}