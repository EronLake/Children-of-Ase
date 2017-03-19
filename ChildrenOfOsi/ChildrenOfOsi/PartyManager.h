#pragma once
#include "common.h"
#include "Party.h"
#include "ChildrenOfOsi.h"

class PartyManager
{
public:
	PartyManager(ChildrenOfOsi* p_gameplay_func);
	~PartyManager();

	void updateSoliderStatus();
	void addToPartyList(Party* p);

private:
	vector<Party*> partyList;
	ChildrenOfOsi* gameplay_func;

};

