#pragma once
#include "Hero.h"
#include "Memory.h"
#include "common.h"
//#include "ActionPool.h"



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

class RelEstimPrerec : Preconditions
{
private:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	std::string rel_bound;
	int desired_rel_val;

public:
	
	RelEstimPrerec(Hero* curr_hero, Hero* other_hero, std::string rel_type, std::string rel_bound, int desired_rel_val);
	~RelEstimPrerec();

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


//--------------------------------------------------------

class Postcondition
{
protected:
	std::string type;

public:
	//Comparing village states
	Postcondition();
	~Postcondition();

	virtual float get_utility();
	void apply_utility();
	std::string get_type();
	

};


class RelPost : Postcondition
{
private:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	int utility;

public:

	RelPost(Hero* _curr_hero, Hero* _other_hero, std::string rel_type, int rel_val);
	~RelPost();

	//Require particular assumption of hero relationship towards sel
	float get_utility() final;
	void apply_utility();
	typedef unordered_map<std::string, std::shared_ptr<Preconditions>> Precond_map;
	std::string fulfills_which(vector<std::string> preconds, Precond_map map);
};


class RelEstimPost : Postcondition
{
private:
	Hero* curr_hero;
	Hero* other_hero;
	std::string rel_type;
	int utility;

public:

	RelEstimPost(Hero* _curr_hero, Hero* _other_hero, std::string rel_type, int rel_val);
	~RelEstimPost();

	//Require particular assumption of hero relationship towards sel
	float get_utility() final;
	void apply_utility();

};

class StatePost : Postcondition
{
private:
	/*state_manager st_man,
	std::string state,
	std::vectorr<relevant villages>*/
	int utility;
public:
	//Comparing village states
	StatePost(int _utility);
	~StatePost();
	float get_utility() final;
	void apply_utility();

};