#include "stdafx.h"
#include "Relationship.h"

Relationship::Relationship()
{
	affinity = 50;
	notoriety = 50;
	strength = 50;
	affEstimate=50;
	notorEstimate=50;
	strEstimate=50;
	LOG("Relationship Object Constructed");
}


Relationship::~Relationship()
{
	LOG("Relationship Object Destroyed");
}