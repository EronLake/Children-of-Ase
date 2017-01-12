#include "WorldObj.h"
#include <iostream>

using namespace std;



WorldObj::WorldObj()
{
}

WorldObj::WorldObj(int a)
{
	x = a;
	cout <<"Xpos: "<< x << endl;
}

WorldObj::~WorldObj()
{
}

LivingObj::LivingObj()
{
}

LivingObj::LivingObj(int a,int b): WorldObj(a)
{
	health = b;
	cout <<"Health: "<< b << endl;
}

LivingObj::~LivingObj()
{
}

NPC::NPC()
{
}

NPC::NPC(int a, int b, int c):LivingObj(a,b)
{
	faction = c;
	cout <<"Faction: "<< c << endl;
}

NPC::~NPC()
{
}

Soldier::Soldier()
{
}

Soldier::Soldier(int a, int b, int c, int d) :NPC(a, b,c)
{
	atk = d;
	cout <<"Attack: "<< d << endl;
}

Soldier::~Soldier()
{
}

SplSoldier::SplSoldier()
{
}

SplSoldier::SplSoldier(int a, int b, int c, int d, int e) :Soldier(a, b, c,d)
{
	ase = e;
	cout <<"Ase: "<< e << endl;
}

SplSoldier::~SplSoldier()
{
}

Hero::Hero()
{
}

Hero::Hero(int a, int b, int c, int d, int e,int f) :SplSoldier(a, b, c, d,e)
{
	affinity = f;
	cout << "Affinity: "<<f << endl;
}

Hero::~Hero()
{
}
