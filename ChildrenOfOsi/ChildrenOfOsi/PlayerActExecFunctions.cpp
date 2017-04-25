#include "stdafx.h"
#include "PlayerActExecFunctions.h"


PlayerActExecFunctions::PlayerActExecFunctions()
{
}


PlayerActExecFunctions::~PlayerActExecFunctions()
{
}


void PlayerActExecFunctions::execute_start(std::string act_name, Player* player/*this is always the player*/, Hero* receiver) {

	//note: act_name should corrispond to the action names in json so they can be looked up in action table

	// import action based off of an already exting action of the reciver
	Action* ref_action = Containers::action_table[act_name + "_" + std::to_string(receiver->name)];

	Action* cur_action = new Action(player, receiver, player, ref_action->getUtility(), ref_action->getWhy(),
		ref_action->name, ref_action->exe_name);

	//for multipliers and preconditions it points the the references' actual objects
	//sets multipliers to references multipliers
	cur_action->multipliers = ref_action->multipliers;
	//sets preconditions to references preconditions
	cur_action->req_preconds = ref_action->req_preconds;

	cur_action->doer_succ_postconds = ref_action->doer_succ_postconds;
	cur_action->receiver_succ_postconds = ref_action->receiver_succ_postconds;

	cur_action->doer_fail_postconds = ref_action->doer_fail_postconds;
	cur_action->doer_succ_postconds = ref_action->doer_succ_postconds;

	//set to current action 
	player->cur_action = cur_action;

	//create the memory based off of the newly created current action
	ActionHelper::create_memory(cur_action, player);

	if (act_name == "occupy" || act_name == "conquer" || act_name == "duel" || act_name == "spar")
	{
		//we need to create a fight here if their action is a violent action
		LOG("need to create a fight");
	}
}


/*
void PlayerActExecFunctions::execute_end() {

Memory* doer_mem = train->getDoer()->find_mem(train->getName() + std::to_string(train->time_stamp));
//Memory* receiver_mem = fight->getReceiver()->find_mem(fight->getName() + std::to_string(fight->time_stamp));
if (doer_mem == nullptr)
{
perror("something is wrong with the current hero memory creation function");
}
train->getDoer()->set_action_destination(&train->getDoer()->getVillage()->get_village_location()); //Also predefined, maybe as "home_location" in hero
train->apply_postconditions(true);				 //Apply post-conditions
train->executed = true;
doer_mem->setCategory("success");			 //Call update_memory function
doer_mem->setReason("I am good at training");
doer_mem->setWhen(/*get global frame);


}
*/