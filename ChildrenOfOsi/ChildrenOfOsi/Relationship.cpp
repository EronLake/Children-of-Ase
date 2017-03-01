#include "stdafx.h"
#include "Relationship.h"

Relationship::Relationship()
{
	affinity = 50;
	notoriety = 50;
	strength = 50;
	LOG("Relationship Object Constructed");
}


Relationship::~Relationship()
{
	LOG("Relationship Object Destroyed");
}