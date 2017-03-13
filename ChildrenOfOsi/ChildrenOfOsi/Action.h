#pragma once
#include "common.h"
#include "Player.h"
#include "Conditions.h"
#include <memory>



class Action
{
	
public:
	Action();
	~Action();
	

	unordered_map<std::string, std::shared_ptr<Preconditions>> preconds;
	unordered_map<std::string, std::shared_ptr<Postcondition>> postconds;

	void setUtility(int u) { utility = u; };
	int getUtility() { return utility; };
	void setReceiver(Hero* h) { receiver = h; recieverName = h->name; };
	Hero* getReceiver() { return receiver; };

	void setOwner(Hero* o) { owner = o; };//preConditionsNeeded also sets owner
	Hero* getOwner() { return owner; };

	void setDoer(Hero* d) { doer = d; };
	Hero* getDoer() { return doer; };

	vector<std::string> preConditionsNeeded(Hero* o, Hero* h);
	int exeAction();

	void setName(string n) { name = n; };
	string getName() { return name; };

	Personality* multipliers;
	void setMultipliers(int a, int k, int h, int p, int r, int e, int g);

	int recieverName;
	std::string name;
	bool operator==(const Action a) const;

	int checkpoint;

private:
	//std::string name;
	int utility;
	Hero* owner;
	Hero* receiver;
	Hero* doer;

	//std::vector<RelPrerec*> rel_prerec_list;
	//std::vector<RelAssumpPrerec*> rel_assump_prerec_list;
	//std::vector<TimePrerec*> time_prerec_list;
	//std::vector<MemoryNumPrerec*> memory_num_prerec_list;
	//std::vector<particularMemPrerec*> particular_mem_prerec_list;
	//std::vector<ParticularMemStatePrerec*> particular_mem_state_prerec_list;
	//std::vector<ParticularStatePrerec*> particular_state_prerec_list;
};

