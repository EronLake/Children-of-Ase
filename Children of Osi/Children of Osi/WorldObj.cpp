#include "WorldObj.h"
#include <iostream>
#include <string>


using namespace std;



WorldObj::WorldObj()
{
}

WorldObj::WorldObj(float x, float y, bool col)
{
	xloc = x;
	yloc = y;
	rotation = 0;
	collision = col;
	cout <<"X-Loc: "<< xloc << endl;
	cout << "Y-Loc: " << yloc << endl;
	cout << "Rotation: " << rotation << endl;
	cout << "Collision: " << collision << endl;
}

WorldObj::~WorldObj()
{
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
