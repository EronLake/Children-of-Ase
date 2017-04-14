#include "stdafx.h"
#include "ActionConfig.h"
#include <ctime>


ActionConfig::ActionConfig()
{
}


ActionConfig::~ActionConfig()
{
}


void ActionConfig::import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, Hero* owner)
{
	//iterates through every player
	for (auto i = Containers::hero_table.begin(); i != Containers::hero_table.end(); i++)
	{
		if (i->second->name != owner->name)
		{
			Json::Value root;
			Json::Reader reader;


			std::ifstream file("action_config.json");
			file >> root;
			for (auto itr = root.begin(); itr != root.end(); itr++)
			{
				set_action_obj(gameplay_func, tBuffer, owner, i->second,
					(*itr)["utility"].asFloat(), (*itr)["why"].asFloat(), (*itr)["type"].asString(),
					(*itr)["name"].asString(), (*itr)["exe_name"].asString(),
					(*itr)["aggression"].asInt(), (*itr)["kindness"].asInt(), (*itr)["honor"].asInt(),
					(*itr)["pride"].asInt(), (*itr)["recklessness"].asInt(), (*itr)["extroversion"].asInt(),
					(*itr)["greed"].asInt());

				//this is where the helper func should be called
				import_conditions(itr, (*itr)["name"].asString());
				owner->actionPool_map[i->second->name]->updateMiddle();

			}
		}
	}
}

void ActionConfig::set_action_obj(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, Hero* owner,
	Hero* receiver, float utility, float why, std::string type, std::string name, std::string exe_name,
	int a, int k, int h, int p, int r, int e, int g)
{

	gameplay_func->add_action(name, utility, why, owner, receiver, owner, exe_name);
	tBuffer->run();

	Containers::action_table[name]->setMultipliers(a, k, h, p, r, e, g);

	std::cout << std::to_string(Containers::action_table[name]->multipliers->getAggression()) << std::endl;

	//for the add the action pointer to the current respective reiciver action pool
	if (type == "micro") {

		//needs to differenciate from pos and neg
		owner->actionPool_map[receiver->name]->micro.push_back(Containers::action_table[name]);
	}
	//then macro
	else if (type == "macro")
	{
		//needs to differenciate from pos and neg
		owner->actionPool_map[receiver->name]->end_states.push_back(Containers::action_table[name]);
	}
	else if (type == "end_state")
	{
		//needs to differenciate from pos and neg
		owner->actionPool_map[receiver->name]->macro.push_back(Containers::action_table[name]);
		owner->actionPool_map[receiver->name]->end_states.push_back(Containers::action_table[name]);
	}

	return;
}

void ActionConfig::import_conditions(Json::Value::iterator itr, std::string name)
{

	for (auto it = (*itr)["req_preconds"].begin(); it != (*itr)["req_preconds"].end(); it++)
	{
		if ((*it)["general_type"].asInt() == 0)
		{
			RelPrecon* temp_prec  = new RelPrecon((*it)["rel_type"].asInt(), (*it)["desired_rel_val"].asInt());

		Containers::action_table[name]->req_preconds.push_back(std::make_shared<RelPrecon>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 1)
		{
			RelEstimPrerec* temp_prec = new RelEstimPrerec((*it)["rel_type"].asInt(), (*it)["desired_rel_val"].asInt());

			Containers::action_table[name]->req_preconds.push_back(std::make_shared<RelEstimPrerec>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 2)
		{
			TimePrerec* temp_prec = new TimePrerec((*it)["time_rec"].asInt());

			Containers::action_table[name]->req_preconds.push_back(std::make_shared<TimePrerec>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 3)
		{
			MemoryNumPrerec* temp_prec = new MemoryNumPrerec((*it)["rec_num_of_mem"].asInt());

			Containers::action_table[name]->req_preconds.push_back(std::make_shared<MemoryNumPrerec>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 4)
		{
			MemPrerec* temp_prec = new MemPrerec((*it)["rec_mem"].asString());

			Containers::action_table[name]->req_preconds.push_back(std::make_shared<MemPrerec>(*temp_prec));
		}
		else if ((*it)["general_type"].asInt() == 5)
		{
			StatePrerec* temp_prec = new StatePrerec();

			Containers::action_table[name]->req_preconds.push_back(std::make_shared<StatePrerec>(*temp_prec));
		}
	}

	import_post_conditions(itr, name, "succ_postconds");
	import_post_conditions(itr, name, "fail_postconds");
	
	/*
	Containers::action_table[name]->op_preconds.push_back();
	*/
}


//this is a helper function for import conditions
void ActionConfig::import_post_conditions(Json::Value::iterator itr, std::string name, std::string which_post) {

	//assigns the postconditions to the appropieate map 
	vector<std::shared_ptr<Postcondition>>* postconds;
	if (which_post == "succ_postconds")
	{
		postconds = &Containers::action_table[name]->succ_postconds;
	} 
	else //if (which_post == "fail_postconds")
	{
		postconds = &Containers::action_table[name]->fail_postconds;
	}


	for (auto it = (*itr)[which_post].begin(); it != (*itr)[which_post].end(); it++)
	{
		if ((*it)["general_type"].asInt() == 0)
		{
			RelPost* temp_post = new RelPost((*it)["rel_type"].asInt(),(*it)["utility"].asInt());

			postconds->push_back(std::make_shared<RelPost>(*temp_post));
		}
		else if ((*it)["general_type"].asInt() == 1)
		{
			RelEstimPost* temp_post = new RelEstimPost((*it)["rel_type"].asInt(), (*it)["utility"].asInt());

			postconds->push_back(std::make_shared<RelEstimPost>(*temp_post));
		}
		else if ((*it)["general_type"].asInt() == 5)
		{
			StatePost* temp_post = new StatePost((*it)["utility"].asInt());

			postconds->push_back(std::make_shared<StatePost>(*temp_post));
		}
	}
}