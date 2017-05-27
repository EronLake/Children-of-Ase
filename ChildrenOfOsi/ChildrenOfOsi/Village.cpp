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
  barracks->set_hide(true);
  parties.push_back(defenders);
  parties.push_back(barracks);
  health = 100;
}

Village::~Village()
{
  delete this->barracks;
  delete this->defenders;
}

/*bool Village::isEnemyParty(Party* p)
{
  for(auto i = enemy_parties.begin(); i != enemy_parties.end(); ++i) {
    if(p == (*i))return true;
  }
  return false;
}*/

void Village::remove_party(Party* p)
{
  parties.erase(std::remove(parties.begin(), parties.end(), p), parties.end());
}

/*void Village::remove_enemy_party(Party* p)
{
  enemy_parties.erase(std::remove(enemy_parties.begin(), enemy_parties.end(), p), enemy_parties.end());
}*/

void Village::remove_member(NPC* n)
{
  if(!this->members.empty())
    this->members.erase(std::remove(this->members.begin(), this->members.end(), n));
}

void Village::init_villages()
{
	Party::grave->set_perm(true);
	
	
	for (auto itr : Containers::hero_table)
	{
		std::string party_name;

		if (itr.second->name == YEMOJA)
		{
			party_name = "Oasis";
		}
		else if (itr.second->name == OYA)
		{
			party_name = "Jungle";
		}
		else if (itr.second->name == OSHOSI)
		{
			party_name = "Mountain";
		}
		else //if (hero_id == OGUN)
		{
			party_name = "Ogun";
		}

		Party* new_party = new Party();
		new_party->addToParty(itr.second, true);

		Village* new_village = new Village();
		new_village->set_village_location(itr.second->getLoc());
		new_village->add_member(itr.second);

		//adds soldiers to village
		for (auto itor : Containers::soldier_table)
		{
			if (itor.second->getName().find(party_name) != string::npos)
			{
				new_village->add_member(itor.second);
			}

		}

		new_village->leader = itr.second;

		//adds soldiers to party
		for (auto itor : Containers::soldier_table)
		{
			if (itor.second->getName().find(party_name) != string::npos)
			{
				new_village->barracks->addToParty(itor.second, false);
			}

		}

		Alliance* new_alliance = new Alliance(new_village);

		new_village->addToParties(new_party);

		//need to set the barracks and defenders owner of the village to the new village
		new_village->defenders->set_village(new_village);
		new_village->barracks->set_village(new_village);

		new_village->defenders->setLeader(itr.second);
		new_village->barracks->setLeader(itr.second);

	}
	Alliance::update_enemies();
}