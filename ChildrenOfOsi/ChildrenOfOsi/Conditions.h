#pragma once
#include "Hero.h"
#include "Memory.h"
#include "common.h"
#include "Action.h"

class Conditions
{
public:
	Conditions();
	~Conditions();

	//prerecs

	//Require particular relationship towards a hero
	static float rel_prerec(Hero* curr_hero, Hero* other_hero, std::string rel_type, int desired_rel_val);
	//Require particular assumption of hero relationship towards sel
	static float rel_assump_prerec(Hero* curr_hero, Hero* other_hero, std::string rel_type, int desired_rel_val);
	//Global Time restrictions
	static float time_prerec(int time_rec);//needs to access some type of global clock
										   //Memories is not empty
	static float memory_num_prerec(std::vector<Memory>* memories, int rec_num_of_mem);//Hero* curr_hero could also just pass in the hero
																					  //Having particular memory
	static float particular_mem_prerec(std::vector<Memory>* memories, std::string rec_mem);//Hero* curr_hero could also just pass in the hero
																						   //Having Particular memory and village state[for revolt]
	static float particular_mem_state_prerec(std::vector<Memory>* memories, std::string rec_mem/*, state_manager*, required state, std::vectorr<relevant villages> */);
	//Comparing village states
	static float particular_state_prerec(/*, state_manager*, required state, std::vectorr<relevant villages> */);
	//? ? ? Betrayal ? ? ?
	//maybe can be handled in the past memories?

};

