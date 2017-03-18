#include "stdafx.h"
#include "Village.h"
using namespace std;

vector<Village*> Village::villagesWorld;

Village::Village()
{
	villagesWorld.push_back(this);
}

Village::~Village()
{
}

bool Village::isEnemyParty(Party* p) {
	for (auto i = enemyParties.begin(); i != enemyParties.end(); ++i) {
		if (p == (*i))return true;
	}
	return false;
}

void Village::removeFromParties(Party* p) {
	for (auto i = enemyParties.begin(); i != enemyParties.end(); ++i) {
		if (p == (*i))parties.erase(i);
	}
}
