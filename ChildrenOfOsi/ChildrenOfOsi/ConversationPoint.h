#pragma once
#include "common.h"
#include "Conditions.h"
class ConversationPoint
{
public:
	ConversationPoint();
	~ConversationPoint();
	void setMultipliers(int a, int k, int h, int p, int r, int e, int g);
	Personality* multipliers;
	Relationship* rel_multipliers;
	typedef std::vector<std::string> dialogue_point;
	std::unordered_map<std::string, std::shared_ptr<Postcondition>> succ_postconds;
	std::unordered_map<std::string, std::shared_ptr<Postcondition>> fail_postconds;

private:
	
};

