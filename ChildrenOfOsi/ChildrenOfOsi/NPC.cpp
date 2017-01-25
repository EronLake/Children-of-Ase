#include "NPC.h"
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

void NPC::moveRight()
{
	(*this).shiftX(speed);
}

void NPC::moveLeft()
{
	(*this).shiftX(-speed);
}

void NPC::moveUp()
{
	(*this).shiftY(speed);
}

void NPC::moveDown()
{
	(*this).shiftY(-speed);
}