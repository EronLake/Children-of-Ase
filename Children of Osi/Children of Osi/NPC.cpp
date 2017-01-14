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