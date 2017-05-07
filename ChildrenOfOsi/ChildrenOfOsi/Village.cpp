#include "stdafx.h"
#include "Village.h"
#include "Alliance.h"

using namespace std;

vector<Village*> Village::villagesWorld;

Village::Village()
{
  Village::villagesWorld.push_back(this);
  defenders = new Party();
  barracks = new Party();
  defenders->set_perm(true);
  barracks->set_perm(true);
  parties.push_back(defenders);
  parties.push_back(barracks);
  health = 100;
}

Village::~Village()
{
  delete this->barracks;
  delete this->defenders;
}

bool Village::isEnemyParty(Party* p)
{
  for(auto i = enemy_parties.begin(); i != enemy_parties.end(); ++i) {
    if(p == (*i))return true;
  }
  return false;
}

void Village::remove_party(Party* p)
{
  parties.erase(std::remove(parties.begin(), parties.end(), p), parties.end());
}

void Village::remove_enemy_party(Party* p)
{
  enemy_parties.erase(std::remove(enemy_parties.begin(), enemy_parties.end(), p), enemy_parties.end());
}

void Village::remove_member(NPC* n)
{
  if(!this->members.empty())
    this->members.erase(std::remove(this->members.begin(), this->members.end(), n));
}

void Village::init_Villages()
{
	Party::grave->set_perm(true);

	for (auto itr : Containers::hero_table)
	{
		Party* new_party = new Party();
		//add hero to party

		new_party->addToParty(itr.second, true);
		itr.second->cur_party = new_party;


		//NEED TO ACCESS SOLDIERS FROM CONTAINER BY NAME 
		/*
		for (int i = 0; i < silverSoldier.size(); i++) {
		new_party->addToParty(silverSoldier[i], false);
		}
		*/

		Village* new_village = new Village();

		new_village->set_village_location(itr.second->getLoc());
		new_village->add_member(itr.second);

		//v2->set_village_location({ 6030, 4000 });

		//NEED TO ACCESS SOLDIERS FROM CONTAINER BY NAME 
		/*
		for (int i = 0; i < blueSoldiers.size(); i++) {
		new_village->add_member(blueSoldiers[i]);
		}
		*/

		new_village->leader = itr.second;
		Alliance* new_alliance = new Alliance(new_village);

		new_village->addToParties(new_party);

		Alliance::update_enemies();
	}
}
