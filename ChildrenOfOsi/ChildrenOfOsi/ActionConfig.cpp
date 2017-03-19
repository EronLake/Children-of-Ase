#include "stdafx.h"
#include "ActionConfig.h"
#include <ctime>


ActionConfig::ActionConfig()
{
}


ActionConfig::~ActionConfig()
{
}


void ActionConfig::import_config(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{

	Json::Value root;
	Json::Reader reader;


	std::ifstream file("action_config.json");
	file >> root;
	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		set_action_obj(recVec, gameplay_func, tBuffer,
			(*itr)["owner"].asInt(), (*itr)["receiver"].asInt(), (*itr)["doer"].asInt(),
			(*itr)["utility"].asFloat(), (*itr)["why"].asFloat(),
			(*itr)["name"].asString(), (*itr)["exe_name"].asString());

	}

}





void ActionConfig::set_action_obj(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, int owner,
									int receiver, int doer, float utility, float why, std::string name, std::string exe_name)
{
	//need to grab these from containers
	Hero* owner_prt = NULL;
	Hero* receiver_ptr = NULL;
	Hero* doer_ptr = NULL;

	gameplay_func->add_action(name, utility, why, owner_prt,receiver_ptr, doer_ptr, exe_name);
	//gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	//Action(Hero* owner, Hero* receiver, Hero* doer, int utility, int why, std::string name, std::string _exe_name);

	tBuffer->run();

	//setMultipliers

	//vector<std::shared_ptr<Preconditions>> req_preconds;
	//vector<vector<std::shared_ptr<Preconditions>>> op_preconds;

	//vector<std::shared_ptr<Postcondition>> succ_postconds;
	//vector<std::shared_ptr<Postcondition>> fail_postconds;

	recVec->push_back(Containers::worldObj_table[name]);

}

