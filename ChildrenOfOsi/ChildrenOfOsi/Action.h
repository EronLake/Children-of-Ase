#pragma once
#include "common.h"
#include "Player.h"
#include "Conditions.h"
#include <memory>

class ActionExecFunctions;

class Action
{
	
public:
	Action();
	Action(Hero* owner, Hero* receiver, Hero* doer, int utility,int why, std::string name, std::string _exe_name);
	~Action();
	

	unordered_map<std::string, std::shared_ptr<Preconditions>> preconds;


	unordered_map<std::string, std::shared_ptr<Postcondition>> succ_postconds;
	unordered_map<std::string, std::shared_ptr<Postcondition>> fail_postconds;

	void applyUtiliites(bool ifsucc);

	void setUtility(int u) { utility = u; };
	int getUtility() { return utility; }; //NEED TO CHANGE SO THAT IT USESES THE SUCC_POST CONDITIONS
	void setReceiver(Hero* h) { receiver = h; recieverName = h->name; };
	Hero* getReceiver() { return receiver; };

	void setOwner(Hero* o) { owner = o; };//preConditionsNeeded also sets owner
	Hero* getOwner() { return owner; };

	void setDoer(Hero* d) { doer = d; };
	Hero* getDoer() { return doer; };

	vector<std::string> preConditionsNeeded(Hero* o, Hero* h);
	int exeAction();//not sure what this does

	void setName(string n) { name = n; };
	string getName() { return name; };

	Personality* multipliers;
	void setMultipliers(int a, int k, int h, int p, int r, int e, int g);

	
	bool operator==(const Action a) const;

	void setWhy(int w) { why = w; };
	int getWhy() { return why; };

	int recieverName;
	std::string name;

	int checkpoint;	//don't initialize used in action execution
	int current_timer; //don't initialize used in action execution

	int time_stamp; // don't initialize here (get initialized when the action begins/memory gets created)

	void (*execute_ptr)(Action* cur_action);
	void execute() { execute_ptr(this); };

private:
	//std::string name;
	int utility;
	int why; //should eventually be set to a precondition

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

