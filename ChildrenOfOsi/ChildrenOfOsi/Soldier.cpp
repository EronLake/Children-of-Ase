#include "Soldier.h"
#include <iostream>
#include <string>
using namespace std;


Soldier::Soldier()
{
}

Soldier::Soldier(float x, float y, bool col) :NPC(x, y, col)
{
	atk = 1;
	cout << "Attack: " << atk << endl;
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

void Soldier::goAtk(LivingObj *target)
{
	(*target).addHealth(-atk);
	cout << "attack for: " << atk << endl;
}

void Soldier::setInCombat(bool c)
{
	inCombat=c;
}

bool Soldier::getInCombat()
{
	return inCombat;
}