#include "stdafx.h"
#include "PartyManager.h"



PartyManager::PartyManager(ChildrenOfOsi* p_gameplay_func, WorldObj* p_player)
{
	gameplay_func = p_gameplay_func;
	player = p_player;
}


PartyManager::~PartyManager()
{
}

void PartyManager::updateSoliderStatus()
{
	//iterate through the list of party
	for (auto it = partyList.begin(); it != partyList.end(); it++) {
		//for current party, get list of member as a vector of soldier*. Maybe here I am getting a copy of members
		vector<Soldier *> soldiers = (*it)->getMembers();
		for (auto itj = soldiers.begin(); itj != soldiers.end(); itj++) {
			//for each soldier, check to see if its alive. If not, remove from party.
			if ((*itj)->getHealth() <= 0) {
				//cout << "RIGHT BEFORE REMOVING THE NPC WITH LESS THAN 0 HP ******** " << endl;
				(*itj)->getParty()->removeSoldier(*itj,false);
			}
			if ((*itj)->getInCombat() == false) {
				if ((*itj) == player) break;
				gameplay_func->stop(*itj);
			}
		}
		

	}
}

void PartyManager::addToPartyList(Party * p)
{
	partyList.push_back(p);
}
