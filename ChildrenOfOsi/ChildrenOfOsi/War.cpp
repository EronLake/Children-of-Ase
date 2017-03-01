#include "stdafx.h"
#include "War.h"


War::War()
{
}


War::~War()
{
}

void War::setWarParties(Alliance * p_alliance1, Alliance * p_alliance2)
{
	warParties.first = p_alliance1;
	warParties.second = p_alliance2;
}

std::pair<Alliance*, Alliance*> War::getWarParties()
{
	return warParties;
}

