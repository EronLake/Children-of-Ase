#include "stdafx.h"
#include "Relationship.h"

Relationship::Relationship()
{
	relationship_map.insert(std::make_pair("affinity", 50));
	relationship_map.insert(std::make_pair("strength", 50));
	relationship_map.insert(std::make_pair("notoriety", 50));
	LOG("Relationship Object Constructed");
}


Relationship::~Relationship()
{
	LOG("Relationship Object Destroyed");
}

void Relationship::set_val(std::string key, int value) {
	relationship_map[key] = value;
}

void Relationship::update_val(std::string key, int value) {
	relationship_map[key] += value;
}

int Relationship::get_value(std::string key) {
	return relationship_map[key];
}