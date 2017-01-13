#include "WorldObj.h"
#include <iostream>
#include <string>

using namespace std;



WorldObj::WorldObj()
{
}

WorldObj::WorldObj(float x, float y, bool col)
{
	loc.setXloc(x);
	loc.setYloc(y);
	rotation.setXloc(1);
	rotation.setYloc(1);
	collision = col;
	cout <<"X-Loc: "<< loc.getXloc() << endl;
	cout << "Y-Loc: " << loc.getYloc() << endl;
	cout << "Rotation: " << rotation.getXloc()<<" , " << rotation.getYloc()<< endl;
	cout << "Collision: " << collision << endl;
}

WorldObj::~WorldObj()
{
}

Vector2f WorldObj::getLoc()
{
	return loc;
}

Vector2f WorldObj::getRot()
{
	return rotation;
}

void WorldObj::setLoc(Vector2f l)
{
	loc = l;
}

void WorldObj::setRot(Vector2f r)
{
	rotation = r;
}

void WorldObj::setCollision(bool c)
{
	collision = c;
}

bool WorldObj::getCollision()
{
	return collision;
}

LivingObj::LivingObj()
{
}

LivingObj::LivingObj(float x, float y, bool col): WorldObj(x,y,col)
{
	health = 1;
	alive = true;
	cout <<"Health: "<< health << endl;
	cout <<"Alive: " << alive << endl;
}

LivingObj::~LivingObj()
{
}

int LivingObj::getHealth()
{
	return health;
}

void LivingObj::setHealth(int h)
{
	health=h;
}

bool LivingObj::getAlive()
{
	return alive;
}

void LivingObj::setAlive(bool v)
{
	alive=v;
}

NPC::NPC()
{
}

NPC::NPC(float x, float y, bool col):LivingObj(x,y, col)
{
	faction = 0;
	cout <<"Faction: "<< faction << endl;
}

NPC::~NPC()
{
}

Soldier::Soldier()
{
}

Soldier::Soldier(float x, float y, bool col) :NPC(x, y, col)
{
	atk = 1;
	cout <<"Attack: "<< atk << endl;
}

Soldier::~Soldier()
{
}

void Soldier::setAtk(int a)
{
	atk = a;
}

int Soldier::getAtk()
{
	return atk;
}

SplSoldier::SplSoldier()
{
}

SplSoldier::SplSoldier(float x, float y, bool col) :Soldier(x, y, col)
{
	ase = 10;
	cout <<"Ase: "<< ase << endl;
}

SplSoldier::~SplSoldier()
{
}

void SplSoldier::setAse(int a)
{
	ase = a;
}

int SplSoldier::getAse()
{
	return ase;
}

Hero::Hero()
{
}

Hero::Hero(float x, float y, bool col) :SplSoldier(x, y, col)
{
	affinity = 0;
	cout << "Affinity: "<<affinity<< endl;
}

Hero::~Hero()
{
}
