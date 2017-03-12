#include "stdafx.h"
#include "Soldier.h"
using namespace std;


Soldier::Soldier()
{
}

Soldier::Soldier(float x, float y, bool col) :NPC(x, y, col)
{
	key = "Soldier" + std::to_string(getID()) + "_0";
	cdTotal = 60;
	cdTime = 0;
	cool = false;
	setType(3);
}

Soldier::Soldier(Vector2f p_topLeft, float p_width, float p_height):NPC(p_topLeft,p_width,p_height)
{
	key= "Soldier" + std::to_string(getID()) + "_0";
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

void Soldier::newAttack(int i, Attack* a)
{
	if (cdMap[atkType[i]] == 0) {
		Attack* p = a;
		*p = *atkType[i];
		float w = atkType[i]->getWidth();
		if (w == 0)w = body[0].getWidth();
		float h = atkType[i]->getHeight();
		if (h == 0)h = body[0].getHeight();
		float x = body[0].getX();
		float y = body[0].getY();
		int d = getDirection();
		if (d == 8) {
			y = y - (atkType[i]->getHeight() + 1);
		}
		else if (d == 2) {
			y = y + (body[0].getHeight() + 1);
		}
		else if (d == 4) {
			x = x - (atkType[i]->getWidth() + 1);
		}
		else if (d == 6) {
			x = x + (body[0].getWidth() + 1);
		}
		p->setX(x);
		p->setY(y);
		p->setCollision(true);
		p->addHit(this);
		p->setDmg(atkType[i]->getDmg());
		p->setDuration(atkType[i]->getDuration());
		p->setDestroy(atkType[i]->getDestroy());
		p->setSpeed(atkType[i]->getSpeed());
		p->setWidth(w);
		p->setHeight(h);
		p->setDirWithBase(d);
		p->setPause(atkType[i]->getPause());
		p->setKeep(false);
		cdMap[atkType[i]] = atkType[i]->getCoolDown();
		cool = false;
		cdTime = cdTotal;
		instances++;
		if (instances == 99)instances = 0;
	}
}

void Soldier::meleeAttack() {
	melee->addHit(this);
	float x= body[0].getX();
	float y= body[0].getY();
	melee->setDuration(5);
	melee->setPause(18);
	int d = getDirection();
	melee->setBaseDir(4);//shouldn't need to be done
	if (d==8) {
		y= y-(melee->getHeight()+1);
		x +=( melee->getSpeed()*melee->getDuration()/2);
	} else if (d==2) {
		y = y+(body[0].getHeight() + 1);
		x -= (melee->getSpeed()*melee->getDuration()/2);
	}
	else if (d==4) {
		x = x-(melee->getWidth() + 1);
		y -= (melee->getSpeed()*melee->getDuration()/2);
	}
	else if (d==6) {
		x = x+(body[0].getWidth() + 1);
		y += (melee->getSpeed()*melee->getDuration()/2);
	}
	melee->setDirWithBase(d);
	melee->setX(x);
	melee->setY(y);
	cool = false;
	cdTime = cdTotal;
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

bool Soldier::getCool(int c) {
	return (cool && (cdMap[atkType[c]]==0));
}

void Soldier::resetCD(int c) {
	cdTime = 0;
	cdMap[atkType[c]] = 0;
}