#include "stdafx.h"
#include "Soldier.h"
using namespace std;


Soldier::Soldier()
{
}

Soldier::Soldier(float x, float y, bool col) :NPC(x, y, col)
{
	melee.setDestroy(false);
	melee.setSpeed(2);
	cdTotal = 60;
	cdFrame = 0;
	cool = false;
}

Soldier::Soldier(Vector2f p_topLeft, float p_width, float p_height):NPC(p_topLeft,p_width,p_height)
{
	melee.setX(body[0].getX());
	melee.setY(body[0].getY());
	melee.setWidth(body[0].getWidth());
	melee.setHeight(body[0].getHeight());
	melee.setDestroy(false);
	melee.setSpeed(2);
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
		if (w == 0)w = body[0].getWidth();
		float h = available[i]->getHeight();
		if (w == 0)w = body[0].getHeight();
		float x = body[0].getX();
		float y = body[0].getY();
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
		available.erase(available.begin()+i);
		return p;
	}
}

Attack* Soldier::meleeAttack() {
	melee.addHit(this);
	float x= body[0].getX();
	float y= body[0].getY();
	melee.setDuration(3);
	melee.setPause(12);
	std::string d = getDirection();
	if (d.compare("UP")) {
		y= y-(melee.getHeight()+1);
		x +=( melee.getSpeed()*melee.getDuration());
		melee.setDirection("LEFT");
	} else if (d.compare("DOWN")==0) {
		y = y+(body[0].getHeight() + 1);
		x -= (melee.getSpeed()*melee.getDuration());
		melee.setDirection("RIGHT");
	}
	else if (d.compare("LEFT")==0) {
		x = x-(melee.getWidth() + 1);
		y -= (melee.getSpeed()*melee.getDuration());
		melee.setDirection("DOWN");
	}
	else if (d.compare("RIGHT")==0) {
		x = x+(body[0].getWidth() + 1);
		y += (melee.getSpeed()*melee.getDuration());
		melee.setDirection("UP");
	}
	melee.setX(x);
	melee.setY(y);
	cool = false;
	cdFrame = 0;
	return &melee;
}

void Soldier::updateCD() {
	if (cdFrame < cdTotal) { 
		cdFrame++; 
	}
	else cool = true;
	for (auto i = cdMap.begin(); i != cdMap.end(); ++i) {
		if (i->second < i->first->getCoolDown()) {
			i->second++;
			if (i->second >= i->first->getCoolDown()) {
				available.push_back(i->first);
			}
		}
	}
}