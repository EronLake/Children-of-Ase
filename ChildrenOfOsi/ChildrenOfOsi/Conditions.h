#pragma once
#include "Hero.h"
#include "Memory.h"
#include "common.h"
#include "Action.h"


/*
class Conditions
{
public:
	Conditions();
	~Conditions();

	//prerecs

	
	
	
	
																					  //Having particular memory
	static float particular_mem_prerec_cost(std::vector<Memory>* memories, std::string rec_mem);//Hero* curr_hero could also just pass in the hero
																						   //Having Particular memory and village state[for revolt]
	static float particular_mem_state_prerec_cost(std::vector<Memory>* memories, std::string rec_mem/*, state_manager*, required state, std::vectorr<relevant villages> );
	//Comparing village states
	static float particular_state_prerec_cost(/*, state_manager*, required state, std::vectorr<relevant villages> );
	//? ? ? Betrayal ? ? ?
	//maybe can be handled in the past memories?

};
*/
class Preconditions
{
public:
	virtual float get_cost();
};

class RelPrecon : public Preconditions
{
private:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	std::string rel_dir;
	int desired_rel_val;

public:
	//RelPrecon();
	//~RelPrecon();

	//Require particular relationship towards a hero
	virtual float get_cost(Hero* curr_hero, Hero* other_hero, std::string rel_type, int desired_rel_val); //override;
};
/*
class RelAssumpPrerec
{
private:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	int desired_rel_val;

public:
	
	RelAssumpPrerec();
	~RelAssumpPrerec();

	//Require particular assumption of hero relationship towards sel
	float cost(Hero* curr_hero, Hero* other_hero, std::string rel_type, int desired_rel_val) override;

};

class TimePrerec
{
private:
	int time_rec;

public:
	TimePrerec();
	~TimePrerec();

	//Global Time restrictions
	float cost(int time_rec) override;//needs to access some type of global clock

};

class MemoryNumPrerec
{
private:
	std::vector<Memory>* memories;
	int rec_num_of_mem;
public:

	//Memories is not empty
	float memory_num_prerec_cost(std::vector<Memory>* memories, int rec_num_of_mem);//Hero* curr_hero could also just pass in the hero
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
	/*, state_manager*, required state, std::vectorr<relevant villages> 
};

class ParticularStatePrerec
{
public:
	, state_manager*, required state, std::vectorr<relevant villages> 
};
*/