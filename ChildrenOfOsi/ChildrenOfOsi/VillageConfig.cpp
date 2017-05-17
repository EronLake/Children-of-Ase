#include "stdafx.h"
#include "VillageConfig.h"
#include "Party.h"
#include "Alliance.h"
#include "Village.h"
#include "Containers.h"


VillageConfig::VillageConfig()
{
}


VillageConfig::~VillageConfig()
{
}

void VillageConfig::init_Villages()
{
	Party::grave->set_perm(true);

	for (auto itr : Containers::hero_table)
	{
		Party* new_party = new Party();
		//add hero to party

		new_party->addToParty(itr.second, true);


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
