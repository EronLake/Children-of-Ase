#pragma once
#include "Hero.h"
#include "Memory.h"
#include "common.h"
#include "Action.h"

class Preconditions
{
protected:
	std::string type;
public:
	Preconditions();
	~Preconditions();
	virtual float get_cost();
	std::string get_type();
};

class RelPrecon : public Preconditions
{
private:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	std::string rel_bound;
	int desired_rel_val;

public:
	RelPrecon(Hero* curr_hero, Hero* other_hero, std::string rel_type, std::string rel_bound, int desired_rel_val);
	~RelPrecon();

	//Require particular relationship towards a hero
	virtual float get_cost() final;
};

class RelEstimpPrerec : Preconditions
{
private:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	std::string rel_bound;
	int desired_rel_val;

public:
	
	RelEstimpPrerec(Hero* curr_hero, Hero* other_hero, std::string rel_type, std::string rel_bound, int desired_rel_val);
	~RelEstimpPrerec();

	//Require particular assumption of hero relationship towards sel
	float get_cost() final;

};

class TimePrerec : Preconditions
{
private:
	int time_rec;

public:
	TimePrerec(int time_rec);
	~TimePrerec();

	//Global Time restrictions
	virtual float get_cost() final;//needs to access some type of global clock

};

class MemoryNumPrerec : Preconditions
{
private:
	std::vector<Memory>* memories;
	int rec_num_of_mem;
public:
	MemoryNumPrerec(std::vector<Memory>* memories, int rec_num_of_mem);
	~MemoryNumPrerec();

	//Memories is not empty
	float get_cost();//Hero* curr_hero could also just pass in the hero
};

class MemPrerec : Preconditions
{
private:
	std::vector<Memory>* memories;
	std::string rec_mem;
public:
	MemPrerec(std::vector<Memory>* memories, std::string rec_mem);
	~MemPrerec();

	//Having particular memory
	virtual float get_cost() final;//Hero* curr_hero could also just pass in the hero
};


class StatePrerec : Preconditions
{
private:
	/*state_manager st_man, 
	std::string required state, 
	std::vectorr<relevant villages>*/
public:
	//Comparing village states
	StatePrerec();
	~StatePrerec();
	virtual float get_cost() final;
};

//BETRAYALS NEED TO BE ACCOUNTED FOR