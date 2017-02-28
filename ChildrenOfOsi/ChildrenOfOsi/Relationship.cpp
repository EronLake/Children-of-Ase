#include "stdafx.h"
#include "Relationship.h"

Relationship::Relationship(int p_affi, int p_noto, int p_str)
{
	affinity = p_affi;
	notoriety = p_noto;
	strength = p_str;
	LOG("Relationship Object Constructed");
}


Relationship::~Relationship()
{
	LOG("Relationship Object Destroyed");
}

std::ostream & operator<<(std::ostream & os, const Relationship & relation)
{
	// TODO: insert return statement here
	os << "Affinity: " << relation.affinity << ", Strength: " << relation.strength << ", Notoriety: " << relation.notoriety << std::endl;
	return os;
}