#pragma once
//#include "Village.h"
#include "Alliance.h"
#include "common.h"
//class Village;
//class Alliance;

class War
{
private:
	std::pair<Village*, Village*> warParties;
	static std::vector<War*> wars;

public:
	War(Village* one, Village* two);
	~War();
	void setWarParties(Village* p_alliance1, Village* p_alliance2);
	std::pair<Village*, Village*> getWarParties();
	static void endWar(Village* one, Village* two);
	static std::vector<Village*> getWars(Village* vil);
	bool static at_war(Village* one, Village* two);
	static void end_wars();
};

