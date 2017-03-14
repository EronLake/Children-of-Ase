#include "stdafx.h"
#include "ActionExecFunctions.h"


ActionExecFunctions::ActionExecFunctions()
{
}


ActionExecFunctions::~ActionExecFunctions()
{
}

void ActionExecFunctions::execute_train(Action* train) {
	switch (train->checkpoint) {
	case 0: //Pick training location, create memory, increment checkpoint
		train->getDoer()->destination = { 1000,1000 }; //should select from set of pre-defined, stored in Hero, or village?
		ActionHelper::create_memory(train, train->getDoer());
		train->checkpoint++;
		break;
	case 1: //If destination is reached, start a timer and move to next checkpoint
		if (train->getDoer()->destination == Vector2f(0, 0)) {
			ActionHelper::set_timer(train, 3600);  //Wait 1 minute (60 frames times 60 seconds)
			train->checkpoint++;
		}
		break;
	case 2: //If timer is complete, set village as destination, apply postconds, update memory
		if (ActionHelper::retrieve_time(train) == 0) {
			train->getDoer()->destination = { 500,500 }; //Also predefined, maybe as "home_location" in hero
														 //Apply post-conditions
														 //Call update_memory function
														 //Mark action as executed?
		}
		break;

	}
}

void ActionExecFunctions::execute_train_with(Action* train_with) {

}
void ActionExecFunctions::execute_form_alliance(Action* form_alliance) {
	Hero* doer = form_alliance->getDoer();
	Hero* responder = form_alliance->getReceiver();
	switch (form_alliance->checkpoint) {
	case 0:
		ActionHelper::create_memory(form_alliance, doer);

		form_alliance->getDoer()->destination = { 1000,1000 };
		form_alliance->checkpoint++;
		break;

	case 1:
		if (form_alliance->getDoer()->destination == Vector2f(0, 0)) {
			Planner* hero_planner = ActionHelper::ai->hero_planners[responder->name];
			if (form_alliance->getName() == ((*hero_planner->get_end_state_map())[responder->name]).getName()) {
				int temp = 0;
				for (auto& iter : form_alliance->preconds) {

					temp += iter.second->get_cost();
				}
				if (temp != 0) {
					//success
					form_alliance->applyUtiliites(true);
				}
				else {
					//failed
				}
			}
			else {
				//update memory failed
			}

		}

	}
}

void ActionExecFunctions::execute_fight(Action* fight)
{
	/*	/Create Memory
	/Locate hero (maybe start by going to heroes village)
	/Travel to village
	/check if there/reset desination and find target
	/Engage in battle (talk first?)
	If win - update with win post conditions
	Else - update with lost post conditions
	Update memory all participants with memory
	Prompt for kill?
	*/

	switch (fight->checkpoint) {
	case 0: //Pick village location(location of fight target), create memory, increment checkpoint
		fight->getDoer()->destination = { 1000,1000 }; //need to somehow retrieve location of target village
		ActionHelper::create_memory(fight, fight->getDoer());
		fight->checkpoint++;
		break;
	case 1: //If destination is reached, check if hero is there start a timer and move if not, fight otherwise
		if (fight->getDoer()->destination == Vector2f(0, 0))//needs to be changed to use party location right 
		{
			//if the target hero is in the village then begin the battle
			if (fight->getDoer()->getLoc() == fight->getReceiver()->getLoc()) // need to change this so it checks if the party is close by
			{
				fight->checkpoint += 2;
			}
			ActionHelper::set_timer(fight, 3600);  //Wait 1 minute (60 frames times 60 seconds) trying to find out the hero's location
			fight->checkpoint++;
		}
		break;
	case 2: //If timer is complete, set village as destination to the location of the target hero 
		if (ActionHelper::retrieve_time(fight) == 0)
		{
			fight->getDoer()->destination = fight->getReceiver()->getLoc(); //go to the target hero's location
			fight->checkpoint++;
		}
		break;
	case 3: //If both niether party is empty then contiue the fight 
			//(may need to change this to account for hero death)
		if (fight->getDoer()->getParty()->getMembers().size() == 0 || fight->getReceiver()->getParty()->getMembers().size() == 0)
		{
			fight->checkpoint++;
		}
		//do a single round of battle every 10 sec
		if (ActionHelper::retrieve_time(fight) == 0)
		{
			ActionHelper::create_memory(fight, fight->getReceiver());
			ActionHelper::battle_sim(fight);
			ActionHelper::set_timer(fight, 600);
		}

		//NEED TO SOMEHOW ACCOUNT FOR IF A PLAYER GETS CLOSE

		break;
	case 4: //If win update apply win-post else apply loss-post and update memory
			//create_memory(fight, fight->getOwner()); do we want to update the owner immeadiately?

		Memory* doer_mem = fight->getDoer()->find_mem(fight->getName() + std::to_string(fight->time_stamp));
		Memory* receiver_mem = fight->getReceiver()->find_mem(fight->getName() + std::to_string(fight->time_stamp));
		if (doer_mem == nullptr || receiver_mem == nullptr)
		{
			perror("something is wrong with the current hero memory creation function");
		}

		//check if the target's party is empty(may need to change this to account for hero death)
		if (fight->getReceiver()->getParty()->getMembers().size() == 0) {
			//Apply succ-post-conditions
			fight->applyUtiliites(true);
			//update_memory category as a success 
			doer_mem->setCategory("success"); receiver_mem->setCategory("fail");
			//update reason
			doer_mem->setReason("They couldnt handle me"); //need to create a reason function
			receiver_mem->setReason("They attack while my gard was down");
		}
		else
		{
			//Apply fail-post-conditions
			fight->applyUtiliites(false);
			//update_memory as faiure
			doer_mem->setCategory("fail"); receiver_mem->setCategory("success");
			//update reason
			doer_mem->setReason("I was too weak");//need to create a reason function
			receiver_mem->setReason("They were foolish to attack");
		}
		//update where
		doer_mem->setWhere(std::to_string(fight->getDoer()->getLoc().xloc));
		receiver_mem->setWhere(std::to_string(fight->getReceiver()->getLoc().xloc));
		//update when
		doer_mem->setWhen(/*get global frame*/0);
		receiver_mem->setWhen(/*get global frame*/0);


		//Mark action as executed?

		//create prompt for kill action
		(fight->getDoer(), fight->getReceiver());
		break;

	}

}
