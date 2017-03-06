#include "stdafx.h"
#include "Conditions.h"


Conditions::Conditions()
{
}


Conditions::~Conditions()
{
}

float Conditions::rel_prerec(Hero* curr_hero, Hero* other_hero, std::string rel_type, int desired_rel_val)
{
	return 0.0;
}

float Conditions::rel_assump_prerec(Hero* curr_hero, Hero* other_hero, std::string rel_type, int desired_rel_val)
{
	return 0.0;
}

float Conditions::time_prerec(int time_rec)//needs to access some type of global clock
{
	return 0.0;
}

float Conditions::memory_num_prerec(std::vector<Memory>* memories, int rec_num_of_mem)
{
	//probably want to bloat this proportioally to the average cost of actions
	return memories->size();
}

float Conditions::particular_mem_prerec(std::vector<Memory>* memories, std::string rec_mem)
{
	return 0.0;
}

float Conditions::particular_mem_state_prerec(std::vector<Memory>* memories, std::string rec_mem/*, state_manager*, required state, relevant villages */)
{
	return 0.0;
}

float Conditions::particular_state_prerec(/*, state_manager*, required state, std::vectorr<relevant villages> */)
{
	return 0.0;
}