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
	static float rel_prerec_cost(Hero* curr_hero, Hero* other_hero, std::string rel_type, int desired_rel_val);
	//Require particular assumption of hero relationship towards sel
	static float rel_assump_prerec_cost(Hero* curr_hero, Hero* other_hero, std::string rel_type, int desired_rel_val);
	//Global Time restrictions
	static float time_prerec_cost(int time_rec);//needs to access some type of global clock
										   //Memories is not empty
	static float memory_num_prerec_cost(std::vector<Memory>* memories, int rec_num_of_mem);//Hero* curr_hero could also just pass in the hero
																					  //Having particular memory
	static float particular_mem_prerec_cost(std::vector<Memory>* memories, std::string rec_mem);//Hero* curr_hero could also just pass in the hero
																						   //Having Particular memory and village state[for revolt]
	static float particular_mem_state_prerec_cost(std::vector<Memory>* memories, std::string rec_mem/*, state_manager*, required state, std::vectorr<relevant villages> */);
	//Comparing village states
	static float particular_state_prerec_cost(/*, state_manager*, required state, std::vectorr<relevant villages> */);
	//? ? ? Betrayal ? ? ?
	//maybe can be handled in the past memories?

};

class RelPrerec
{
public:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	std::string rel_dir;
	int desired_rel_val;

};

class RelAssumpPrerec
{
public:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	int desired_rel_val;

};

class TimePrerec
{
public:
	int time_rec;

};

class MemoryNumPrerec
{
public:
	std::vector<Memory>* memories;
	int rec_num_of_mem;
};

class particularMemPrerec
{
public:
	std::vector<Memory>* memories;
	std::string rec_mem;
};

class ParticularMemStatePrerec
{
public:
	std::vector<Memory>* memories;
	std::string rec_mem;
	/*, state_manager*, required state, std::vectorr<relevant villages> */
};

class ParticularStatePrerec
{
public:
	/*, state_manager*, required state, std::vectorr<relevant villages> */
};
