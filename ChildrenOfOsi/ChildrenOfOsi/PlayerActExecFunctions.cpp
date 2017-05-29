#include "stdafx.h"
#include "PlayerActExecFunctions.h"


PlayerActExecFunctions::PlayerActExecFunctions()
{
}


PlayerActExecFunctions::~PlayerActExecFunctions()
{
}


void PlayerActExecFunctions::execute_start(std::string act_name, Hero* receiver) {


	std::cout << "------------EX_START-------------" << std::endl;

	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	//note: act_name should corrispond to the action names in json so they can be looked up in action table
	
	// import action based off of an already exting action of the reciver
	Action* ref_action = Containers::action_table[act_name + "_" + std::to_string(receiver->name)];
	
	Action* cur_action = new Action(player, receiver, player, ref_action->getUtility(), ref_action->getWhy(),
		ref_action->name, ref_action->exe_name);

	//for multipliers and preconditions it points the the references' actual objects
	//sets multipliers to references multipliers
	cur_action->multipliers = ref_action->multipliers;
	cur_action->aff_mult = cur_action->aff_mult;
	cur_action->str_mult = cur_action->str_mult;
	cur_action->noto_mult = cur_action->noto_mult;

	//sets preconditions to references preconditions
	cur_action->req_preconds = ref_action->req_preconds;

	cur_action->doer_succ_postconds = ref_action->doer_succ_postconds;
	cur_action->receiver_succ_postconds = ref_action->receiver_succ_postconds;

	cur_action->doer_fail_postconds = ref_action->doer_fail_postconds;
	cur_action->receiver_fail_postconds = ref_action->receiver_fail_postconds;

	//set to current action 
	if (!player->quests_log.empty()) {
		for (auto i : player->quests_log) {
			if(i->getReceiver() == receiver && i->getName() == act_name + "_" + std::to_string(i->getOwner()->name))
				player->cur_action = i;

		}

	}
	else {
		player->cur_action = cur_action;
	}
	//create the memory based off of the newly created current action
	//ActionHelper::create_memory(cur_action, player);
	//creates the memory for the reciever as well
	//ActionHelper::create_memory(cur_action, receiver);

	receiver->set_busy(Hero::BUSY_REC_FIGHT);

	if (act_name == "Fight" && !War::at_war(player->getVillage(), receiver->getVillage())) {
		new War(player->getVillage(), receiver->getVillage());
	}

	if ((act_name == "Occupy" || act_name == "Fight" || act_name == "Conquer") &&
		((!player->getInCombat()) && (!receiver->getInCombat())))
	{
		//we need to create a fight here if their action is a violent action
		Fight* fight_obj = new Fight(player->getParty(), receiver->getParty(), 0);
	} else if (act_name == "Duel") {
		Fight* fight_obj = new Fight(player->getParty(), receiver->getParty(), 1);
	}
	else if (act_name == "Spar") {
		Fight* fight_obj = new Fight(player->getParty(), receiver->getParty(), 2);
	}
	else if (act_name == "Train With") {
		Fight* fight_obj = new Fight(player->getParty(), receiver->getParty(), 3);
		
	}

	//ADITIONAL FUNCTION act_name == "Conquer" || act_name == "Duel" ||act_name == "Spar" ||

}



void PlayerActExecFunctions::execute_end(bool if_succ) {

	std::cout << "------------EX_END-------------" << std::endl;

	//STILL NEED TO DO QUEST CHECK
	
	///////////////////////////////////////////


	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	Action* cur_action = player->cur_action;

	//these two lines strip the number off the end of the name 
	std::string::size_type name_end = cur_action->getName().find_first_of('_');
	std::string act_name = cur_action->getName().substr(0, name_end);

	///////////////////////////////////////////////////////////////////////////////////
	//special cases that need to be handled are in this gaurd (may want to make a helper function)

	//NEEDS TO BE TESTED... should it check for Occupy?
	if (act_name == "Conquer" && player->getParty()->get_fight()->is_over() && if_succ) {
		cur_action->getReceiver()->getVillage()->add_to_village_health(cur_action->getDoer()->getParty()->getMembers().size()*(-25));
		if (cur_action->getReceiver()->getVillage()->get_village_health() > 0) {
			cur_action->getReceiver()->getVillage()->defenders->add_party_to_party(cur_action->getReceiver()->getVillage()->barracks);
			//if (player->getParty()->get_fight()!=nullptr)player->getParty()->get_fight()->add_to_defenders(cur_action->getReceiver()->getVillage()->defenders);
			return;
		}
	}

	//NEEDS TO BE IMPLIMENTED
	if (act_name == "Duel") {
		DialogueController::duel_pop_up(cur_action);
		LOG("print to the screen something that the person you were fighting would say then finish action");
	}
	else if (act_name == "Spar") {
		DialogueController::spar_pop_up(cur_action);
	}

	///////////////////////////////////////////////////////////////////////////////////


	//Memory* doer_mem = player->find_mem(cur_action->getName() + "_" + std::to_string(cur_action->time_stamp));
	//Memory* receiver_mem = cur_action->getReceiver()->find_mem(cur_action->getName() + "_" +
	//						std::to_string(cur_action->time_stamp));


	//if (doer_mem == nullptr)
	//{
//		perror("something is wrong with the current hero memory creation function");
	//}
	
	cur_action->apply_postconditions(if_succ);	//Apply post-conditions based off if it was succesful or not
	cur_action->executed = true;
	
	//if the action was successful check if the action was in the active quests
	if (if_succ) { check_quest(); }
	if (player->cur_action->executed) {


		//reason sould be handled as a dialog response choice
		if (if_succ) {
			if (!player->quests_log.empty()) {
				for (auto i : player->quests_log) {
					if (i->getReceiver() == cur_action->getReceiver() && i->getName() == cur_action->getName())
						player->quest_status[i->getOwner()->name] = Player::SUCC_QUEST;// set shango to "succeeded quest"

				}
			}
			
			//doer_mem->setCategory("success");
			//receiver_mem->setCategory("failure");
		}
		else {
			if (!player->quests_log.empty()) {
				for (auto i : player->quests_log) {
					if (i->getReceiver() == cur_action->getReceiver() && i->getName() == cur_action->getName())
						player->quest_status[i->getOwner()->name] = Player::FAIL_QUEST;// set shango to "failed quest"

				}
			}
			
			//doer_mem->setCategory("failure");
		//	receiver_mem->setCategory("success");
		}

		//sets the quest to executed for the owner of the quest
		int my_hero = player->cur_action->getOwner()->name;
		Planner* plan = AIController::get_plan(my_hero);
		for (int i = 0; i < plan->quests_given.size(); ++i) {
			if (plan->quests_given[i]->getDoer()->name == SHANGO && plan->quests_given[i]->getReceiver() == player->cur_action->getReceiver()
				&& plan->quests_given[i]->getOwner() == player->cur_action->getOwner()) {
				plan->quests_given[i]->executed = true;
			}
		}
	}
//	doer_mem->setWhen(/*get global frame*/0);

	/*
	dealocate memory for fight if there was a fight
	and end the fight if a fight was involved
	*/
	if (player->getInCombat()) {
		Fight* tmp= player->getParty()->get_fight();
		player->getParty()->get_fight()->end_combat();
		delete tmp; 
	}

	//dealocate memory for action
	
	//for multipliers and preconditions it points the the references' actual objects
	//sets multipliers to references multipliers
	cur_action->multipliers = nullptr;
	cur_action->aff_mult = nullptr;
	cur_action->str_mult = nullptr;
	cur_action->noto_mult = nullptr;
	//sets preconditions to references preconditions

	// delete player->cur_action;
	player->cur_action = nullptr;
}

void PlayerActExecFunctions::execute_dialog()
{
	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	Action* cur_action = player->cur_action;

	//these two lines strip the number off the end of the name 
	std::string::size_type name_end = cur_action->getName().find_last_of('_');
	std::string act_name = cur_action->getName().substr(0, name_end);

	//Need TO ADD FUNCTION TO DO THIS
	if (act_name == "Train") {
		LOG("PRINT FOLLOW ME TO SCREEN AND MOVE TO TRAIN LOCATION");
	}

	if (!player->getInCombat())
	{
		if (act_name == "Duel") {
			Fight* fight_obj = new Fight(player->getParty(), cur_action->getReceiver()->getParty(), 1);
		}
		else if (act_name == "Spar") {
			Fight* fight_obj = new Fight(player->getParty(), cur_action->getReceiver()->getParty(), 2);
		}
		else if (act_name == "Train With") {
			Fight* fight_obj = new Fight(player->getParty(), cur_action->getReceiver()->getParty(), 3);
		}
	}

	//Need TO ADD FUNCTION TO DO THIS - needs to be done here because you have to be outside dialog first
	if (act_name == "Form_Alliance") {
		LOG("PRINT FORM ALLIANCE TO THE SCREEN DO similar to a fairwell");
		execute_end(true);
	}
}


void PlayerActExecFunctions::check_quest() {

	std::cout << "------------CHECK QUEST-------------" << std::endl;

	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	for (auto itr : player->get_quests())
	{
		if (player->cur_action == itr.first)
		{
			player->cur_action->executed = true;
		}
	}

}

