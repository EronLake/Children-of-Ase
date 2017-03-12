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
	//Containers::add_Attack(key,melee);
	//melee = Containers::Attack_table[key];
}

Soldier::Soldier(Vector2f p_topLeft, float p_width, float p_height):NPC(p_topLeft,p_width,p_height)
{
	key= "Soldier" + std::to_string(getID()) + "_0";
	cdTotal = 60;
	cdTime = 0;
	cool = false;
	setType(3);
	//Containers::add_Attack(key, melee);
	//melee = Containers::Attack_table[key];
}

Soldier::~Soldier()
{
}

void Soldier::addAttackType(Attack* a) {
	atkType.push_back(a);
	cdMap[a] = a->getCoolDown();
	//std::string key = "Soldier" + std::to_string(getID()) + "_"+ std::to_string(atkType.size());
	//Containers::add_Attack(key, a);
}

void Soldier::newAttack(int i, Attack* a)
{
	if (cdMap[atkType[i]] == 0) {
		std::cout << "Attack A: " << &a << std::endl;
		Attack* p = a;
		std::cout << "Attack P: " << &p << std::endl;
		*p = *atkType[i];
		float w = atkType[i]->getWidth();
		if (w == 0)w = body[0].getWidth();
		float h = atkType[i]->getHeight();
		if (h == 0)h = body[0].getHeight();
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
		p->setDirection(d);
		p->setPause(18);
		p->setKeep(false);
		cdMap[atkType[i]] = atkType[i]->getCoolDown();
		cool = false;
		cdTime = cdTotal;
		instances++;
		if (instances == 99)instances = 0;
	}
}

void Soldier::meleeAttack(Attack* a) {
	*a = *melee;
	melee = a;
	melee->addHit(this);
	float x= body[0].getX();
	float y= body[0].getY();
	melee->setDuration(5);
	melee->setPause(18);
	std::string d = getDirection();
	if (d.compare("UP")==0) {
		y= y-(melee->getHeight()+1);
		x +=( melee->getSpeed()*melee->getDuration()/2);
		melee->setDirection("LEFT");
	} else if (d.compare("DOWN")==0) {
		y = y+(body[0].getHeight() + 1);
		x -= (melee->getSpeed()*melee->getDuration()/2);
		melee->setDirection("RIGHT");
	}
	else if (d.compare("LEFT")==0) {
		x = x-(melee->getWidth() + 1);
		y -= (melee->getSpeed()*melee->getDuration()/2);
		melee->setDirection("DOWN");
	}
	else if (d.compare("RIGHT")==0) {
		x = x+(body[0].getWidth() + 1);
		y += (melee->getSpeed()*melee->getDuration()/2);
		melee->setDirection("UP");
	}
	melee->setX(x);
	melee->setY(y);
	cool = false;
	cdTime = cdTotal;
	//std::string key = "Soldier" + std::to_string(getID()) + "_0";
	//Containers::add_Attack(key, melee);
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