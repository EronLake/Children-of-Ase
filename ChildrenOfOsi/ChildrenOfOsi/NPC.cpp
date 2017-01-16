#include "NPC.h"
#include <iostream>
#include <string>
using namespace std;


NPC::NPC()
{
}

NPC::NPC(float x, float y, bool col) :LivingObj(x, y, col)
{
	faction = 0;
	cout << "Faction: " << faction << endl;
}

NPC::~NPC()
{
}

void NPC::setFaction(int f)
{
	faction=f;
}

int NPC::getFaction()
{
	return faction;
}

void NPC::setSpeed(float s)
{
	speed=s;
}

float NPC::getSpeed()
{
	return speed;
}
