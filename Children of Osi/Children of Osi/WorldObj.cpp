#include "WorldObj.h"
#include <iostream>
#include <string>


using namespace std;



WorldObj::WorldObj()
{
}

WorldObj::WorldObj(int a, int rot, bool col)
{
	x = a;
	rotation = rot;
	collision = col;
	cout <<"Xpos: "<< x << endl;
	cout << "Rotation: " << rotation << endl;
	cout << "Collision: " << collision << endl;
}

WorldObj::~WorldObj()
{
}

LivingObj::LivingObj()
{
}

LivingObj::LivingObj(int a, int rot, bool col, int b, bool life): WorldObj(a,rot,col)
{
	health = b;
	alive = life;
	cout <<"Health: "<< health << endl;
	cout <<"Alive: " << alive << endl;
}

LivingObj::~LivingObj()
{
}

NPC::NPC()
{
}

NPC::NPC(int a, int rot, bool col,  int b, bool life, int c):LivingObj(a, rot, col,b,life)
{
	faction = c;
	cout <<"Faction: "<< faction << endl;
}

NPC::~NPC()
{
}

Soldier::Soldier()
{
}

Soldier::Soldier(int a, int rot, bool col, int b, bool life, int c, int d) :NPC(a, rot, col, b,life,c)
{
	atk = d;
	cout <<"Attack: "<< atk << endl;
}

Soldier::~Soldier()
{
}

SplSoldier::SplSoldier()
{
}

SplSoldier::SplSoldier(int a, int rot, bool col, int b, bool life, int c, int d, int e) :Soldier(a, rot, col, b,life, c,d)
{
	ase = e;
	cout <<"Ase: "<< ase << endl;
}

SplSoldier::~SplSoldier()
{
}

Hero::Hero()
{
}

Hero::Hero(int a, int rot, bool col, int b, bool life, int c, int d, int e,int f) :SplSoldier(a, rot, col, b,life, c, d,e)
{
	affinity = f;
	cout << "Affinity: "<<affinity<< endl;
}

Hero::~Hero()
{
}
