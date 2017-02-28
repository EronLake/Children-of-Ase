#pragma once

#include "Alliance.h"
class War
{
private:
	std::pair<Alliance*, Alliance*> warParties;

public:
	War();
	~War();
	void setWarParties(Alliance* p_alliance1, Alliance* p_alliance2);
	std::pair<Alliance*, Alliance*> getWarParties();
};

