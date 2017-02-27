#pragma once
#include "common.h"

class Relationship {
private:
	std::unordered_map<std::string, int> relationship_map;
	int affinity;
	int notoriety;
	int strength;

public:
	Relationship();
	~Relationship();
	void set_val(std::string key, int value);
	void update_val(std::string key, int value);
	int get_value(std::string key);


};