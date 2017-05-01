#pragma once
#include "Hero.h"
#include "Memory.h"
#include "common.h"
//#include "Alliance.h"
#include "War.h"
//#include "ActionPool.h"

class Alliance;

class Preconditions
{
protected:
	std::string type;
	int general_type;
public:
	static constexpr int REL = 0;
	static constexpr int REL_EST = 1;
	static constexpr int TIME = 2;
	static constexpr int MEM_NUM = 3;
	static constexpr int MEM = 4;
	static constexpr int STATE = 5;

	static constexpr int STR = 6;
	static constexpr int AFF = 7;
	static constexpr int NOT = 8;
	static constexpr int BSTR = 9;
	static constexpr int BAFF = 10;
	static constexpr int BNOT = 11;

	static constexpr int ALL = 6;
	static constexpr int OCC = 7;
	static constexpr int CON = 8;

	Preconditions();
	~Preconditions();
	virtual int get_cost();
	std::string get_type();
	int get_general_type();

	//for relprecons 
	virtual int get_rel_type();
	//for state_precons 
	virtual int get_state_type();


};

class RelPrecon : public Preconditions
{
private:
	int rel_type;
	int desired_rel_val;

public:
	RelPrecon(int rel_type, int desired_rel_val);
	~RelPrecon();

	virtual int get_rel_type() final { return rel_type; };
	//Require particular relationship towards a hero
	virtual int get_cost(Hero* curr_hero, Hero* other_hero) final;
};

class RelEstimPrerec : public Preconditions
{
private:
	int rel_type;
	int desired_rel_val;

public:
	
	RelEstimPrerec(int rel_type, int desired_rel_val);
	~RelEstimPrerec();

	int get_rel_type() { return rel_type; };
	//Require particular assumption of hero relationship towards sel
	virtual int get_cost(Hero* curr_hero, Hero* other_hero) final;

};

class TimePrerec : public Preconditions
{
private:
	int time_rec;

public:
	TimePrerec(int time_rec);
	~TimePrerec();

	//Global Time restrictions
	virtual int get_cost() final;//needs to access some type of global clock

};

class MemoryNumPrerec : public Preconditions
{
private:
	int rec_num_of_mem;
public:
	MemoryNumPrerec(int rec_num_of_mem);
	~MemoryNumPrerec();

	//Memories is not empty
	int get_cost(std::vector<Memory*> memories);//Hero* curr_hero could also just pass in the hero
};

class MemPrerec : public Preconditions
{
private:
	std::string rec_mem;
public:
	MemPrerec(std::string rec_mem);
	~MemPrerec();

	std::string get_rec_mem() { return rec_mem; };
	//Having particular memory
	virtual int get_cost(std::vector<Memory*> memories) final;//Hero* curr_hero could also just pass in the hero
};


class StatePrerec : public Preconditions
{
private:
	/*state_manager st_man, 
	std::string required state, 
	std::vectorr<relevant villages>*/
public:
	//Comparing village states
	StatePrerec();
	~StatePrerec();
	virtual int get_cost() final;
};

//BETRAYALS NEED TO BE ACCOUNTED FOR


//--------------------------------------------------------

class Postcondition
{
protected:
	std::string type;
	int general_type;

public:
	static constexpr int REL = 0;
	static constexpr int REL_EST = 1;
	static constexpr int TIME = 2;
	static constexpr int MEM_NUM = 3;
	static constexpr int MEM = 4;
	static constexpr int STATE = 5;

	static constexpr int STR = 6;
	static constexpr int AFF = 7;
	static constexpr int NOT = 8;
	static constexpr int BSTR = 9;
	static constexpr int BAFF = 10;
	static constexpr int BNOT = 11;

	static constexpr int ALL = 6;
	static constexpr int OCC = 7;
	static constexpr int CONF = 8;
	static constexpr int CONV = 9;
	
	//Comparing village states
	Postcondition();
	~Postcondition();

	virtual float get_utility();
	virtual float get_utility(Hero* curr_hero, Hero* other_hero);

	virtual void apply_utility();
	virtual void apply_utility(Hero* curr_hero, Hero* other_hero, bool if_doer);
	virtual void apply_utility(Hero* curr_hero, Hero* other_hero);
	std::string get_type();
	int get_general_type();
	//for rel_postcons 
	virtual int get_rel_type(); 
	//for state_postcons 
	virtual int get_state_type();
	

};


class RelPost : public Postcondition
{
private:
	int rel_type;
	int utility;

public:

	RelPost(int rel_type, int rel_val);
	~RelPost();

	int get_rel_type() { return rel_type; };

	//Require particular assumption of hero relationship towards sel
	virtual float get_utility(Hero* curr_hero, Hero* other_hero) final;
	virtual void apply_utility(Hero* curr_hero, Hero* other_her, bool if_doer) final;
	typedef vector<std::shared_ptr<Preconditions>> Precond_vec;
	RelPrecon* fulfills_which(Precond_vec preconds, Hero* me, Hero* them);
};


class RelEstimPost : public Postcondition
{
private:
	int rel_type;
	int utility;

public:

	RelEstimPost(int rel_type, int rel_val);
	~RelEstimPost();

	virtual int get_rel_type() final { return rel_type; };

	//Require particular assumption of hero relationship towards sel
	virtual float get_utility(Hero* curr_hero, Hero* other_hero) final;
	virtual void apply_utility(Hero* curr_hero, Hero* other_hero, bool if_doer) final;

};

class StatePost : public Postcondition
{
private:
	/*state_manager st_man,
	std::string state,
	std::vectorr<relevant villages>*/
	int utility;
	int state_type;
public:
	//Comparing village states
	StatePost(int utility, int _state_type);
	~StatePost();

	virtual int get_state_type() final { return state_type; };
	virtual float get_utility() final;
	virtual void apply_utility(Hero* curr_hero, Hero* other_hero) final;

};