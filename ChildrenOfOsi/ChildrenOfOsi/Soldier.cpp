#include "stdafx.h"
#include "Soldier.h"
using namespace std;


Soldier::Soldier()
{
}

Soldier::Soldier(float x, float y, bool col) :NPC(x, y, col)
{
	melee.setDestroy(false);
	melee.setSpeed(3);
	cdTotal = 60;
	cdTime = 0;
	cool = false;
	setType(3);
}

Soldier::Soldier(Vector2f p_topLeft, float p_width, float p_height):NPC(p_topLeft,p_width,p_height)
{
	melee.setX(body[0].getX());
	melee.setY(body[0].getY());
	melee.setWidth(body[0].getWidth());
	melee.setHeight(body[0].getHeight());
	melee.setDestroy(false);
	melee.setSpeed(3);
	cdTotal = 60;
	cdTime = 0;
	cool = false;
	setType(3);
}

Soldier::~Soldier()
{
}

void Soldier::addAttackType(Attack* a) {
	atkType.push_back(a);
	cdMap[a] = a->getCoolDown();
}

Attack* Soldier::newAttack(int i)
{
	if (cdMap[atkType[i]] == 0) {
		float w = atkType[i]->getWidth();
		if (w == 0)w = body[0].getWidth();
		float h = atkType[i]->getHeight();
		if (w == 0)w = body[0].getHeight();
		float x = body[0].getX();
		float y = body[0].getY();
		std::string d = getDirection();
		if (d.compare("UP")) {
			y = y - (atkType[i]->getHeight() + 1);
		}
		else if (d.compare("DOWN") == 0) {
			y = y + (getHeight() + 1);
		}
		else if (d.compare("LEFT") == 0) {
			x = x - (atkType[i]->getWidth() + 1);
		}
		else if (d.compare("RIGHT") == 0) {
			x = x + (getWidth() + 1);
		}
		Attack* p = new Attack(x, y, true);
		p->setDmg(atkType[i]->getDmg());
		p->setDuration(atkType[i]->getDuration());
		p->setDestroy(atkType[i]->getDestroy());
		p->setSpeed(atkType[i]->getSpeed());
		p->setWidth(w);
		p->setHeight(h);
		p->setDirection(d);
		cdMap[atkType[i]] = atkType[i]->getCoolDown();
		cool = false;
		cdTime = cdTotal;
		return p;
	}
}

Attack* Soldier::meleeAttack() {
	melee.addHit(this);
	float x= body[0].getX();
	float y= body[0].getY();
	melee.setDuration(5);
	melee.setPause(13);
	std::string d = getDirection();
	if (d.compare("UP")==0) {
		y= y-(melee.getHeight()+1);
		x +=( melee.getSpeed()*melee.getDuration()/2);
		melee.setDirection("LEFT");
	} else if (d.compare("DOWN")==0) {
		y = y+(body[0].getHeight() + 1);
		x -= (melee.getSpeed()*melee.getDuration()/2);
		melee.setDirection("RIGHT");
	}
	else if (d.compare("LEFT")==0) {
		x = x-(melee.getWidth() + 1);
		y -= (melee.getSpeed()*melee.getDuration()/2);
		melee.setDirection("DOWN");
	}
	else if (d.compare("RIGHT")==0) {
		x = x+(body[0].getWidth() + 1);
		y += (melee.getSpeed()*melee.getDuration()/2);
		melee.setDirection("UP");
	}
	melee.setX(x);
	melee.setY(y);
	cool = false;
	cdTime = cdTotal;
	return &melee;
}

void Soldier::updateCD() {
	if (cdTime > 0) { 
		cdTime--; 
	} else cool = true;
	for (auto i = cdMap.begin(); i != cdMap.end(); ++i) {
		if (i->second >0) {
			i->second--;
		}
	}
}