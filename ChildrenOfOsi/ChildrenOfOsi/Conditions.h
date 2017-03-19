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
	std::string rel_type;
	std::string rel_bound;
	int desired_rel_val;

public:
	RelPrecon(std::string rel_type, std::string rel_bound, int desired_rel_val);
	~RelPrecon();

	//Require particular relationship towards a hero
	virtual float get_cost(Hero* curr_hero, Hero* other_hero) final;
};

class RelEstimPrerec : Preconditions
{
private:
	std::string rel_type;
	std::string rel_bound;
	int desired_rel_val;

public:
	
	RelEstimPrerec(std::string rel_type, std::string rel_bound, int desired_rel_val);
	~RelEstimPrerec();

	//Require particular assumption of hero relationship towards sel
	virtual float get_cost(Hero* curr_hero, Hero* other_hero) final;

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
	int rec_num_of_mem;
public:
	MemoryNumPrerec(int rec_num_of_mem);
	~MemoryNumPrerec();

	//Memories is not empty
	float get_cost(std::vector<Memory>* memories);//Hero* curr_hero could also just pass in the hero
};

class MemPrerec : Preconditions
{
private:
	std::string rec_mem;
public:
	MemPrerec(std::string rec_mem);
	~MemPrerec();

	//Having particular memory
	virtual float get_cost(std::vector<Memory>* memories) final;//Hero* curr_hero could also just pass in the hero
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
	virtual float get_utility(Hero* curr_hero, Hero* other_hero);
	
	void apply_utility();
	void apply_utility(Hero* curr_hero, Hero* other_hero);
	std::string get_type();
	

};


class RelPost : Postcondition
{
private:
	std::string rel_type;
	int utility;

public:

	RelPost(std::string rel_type, int rel_val);
	~RelPost();

	//Require particular assumption of hero relationship towards sel
	virtual float get_utility(Hero* curr_hero, Hero* other_hero) final;
	virtual void apply_utility(Hero* curr_hero, Hero* other_hero) final;
	typedef vector<std::shared_ptr<Preconditions>> Precond_vec;
	std::string fulfills_which(vector<std::string> preconds, Precond_vec vec);
};


class RelEstimPost : Postcondition
{
private:
	std::string rel_type;
	int utility;

public:

	RelEstimPost(std::string rel_type, int rel_val);
	~RelEstimPost();

	//Require particular assumption of hero relationship towards sel
	virtual float get_utility(Hero* curr_hero, Hero* other_hero) final;
	virtual void apply_utility(Hero* curr_hero, Hero* other_hero) final;

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
	StatePost(int utility);
	~StatePost();
	virtual float get_utility() final;
	virtual void apply_utility() final;

};