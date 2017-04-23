#include "stdafx.h"
#include "ActionExecFunctions.h"

std::unordered_map<std::string, execute_ptr> ActionExecFunctions::ActionExecMap{
	{ "execute_train",			&execute_train			},
	{ "execute_train_with",		&execute_train_with		},
	{ "execute_fight",			&execute_fight			},
	{ "execute_conquer",		&execute_conquer		},
	{ "execute_duel",			&execute_duel			},
	{ "execute_spar",			&execute_duel			},
	{ "execute_form_alliance",	&execute_form_alliance	},
	{ "execute_fight_bandits",	&execute_fight_bandits	},
	{ "execute_bribe",	        &execute_bribe          },
	{ "execute_compliment",	    &execute_compliment     }
};


ActionExecFunctions::ActionExecFunctions()
{
};


ActionExecFunctions::~ActionExecFunctions()
{
};

void ActionExecFunctions::execute_fight_bandits(Action* fight_bandits) {
	std::cout << "/////////////////////////fighting bandits///////////////////////" << std::endl;
	if (/*the bandits->party.size() == 0*/true) {
		fight_bandits->executed = true;
	}
}


void ActionExecFunctions::execute_temp_allign(Action* fight_bandits) {
	if (/*the bandits->party.size() == 0*/false) {
		fight_bandits->executed = true;
	}
}




void ActionExecFunctions::execute_train(Action* train) {
	//cout << "++++++++++++++++PLEASE BE FIGHTING++++++++++++++++" << endl;
	
	switch (train->checkpoint) {
	case 0: //Pick training location, create memory, increment checkpoint
		std::cout << "---------------------CASE 0---------------------" << std::endl;
		//std::cout << (train->getDoer()->destination).getXloc() << ":" << (train->getDoer()->destination).getXloc() << std::endl;

		train->getDoer()->set_action_destination(&train->getDoer()->getVillage()->get_village_location()); //should select from set of pre-defined, stored in Hero, or village?
		ActionHelper::create_memory(train, train->getDoer());
		train->checkpoint++;
		break;
	case 1: //If destination is reached, start a timer and move to next checkpoint
	//	std::cout << "---------------------CASE 1---------------------" << endl;

		//THIS IS NOT WORKING BECAUSE THE HEROES DESTINATION KEEPS GETTING RESET BY SOME OTHER CODE

		//std::cout << (train->getDoer()->destination).getXloc() << ":" << (train->getDoer()->destination).getXloc() << std::endl;

		if (train->getDoer()->get_action_destination() == nullptr) {
			ActionHelper::set_timer(train, 3600);  //Wait 1 minute (60 frames times 60 seconds)
			train->checkpoint++;
		}
		break;
	case 2: //If timer is complete, set village as destination, apply postconds, update memory
		//////cout << "---------------------CASE 2---------------------" << endl;
		if (ActionHelper::retrieve_time(train) == 0) {
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
			doer_mem->setWhen(/*get global frame*/0);        
		}
		break;

	}
}

void ActionExecFunctions::execute_train_with(Action* train_with) {
	switch (train_with->checkpoint) {
	case 0: //Pick training location, create memory, increment checkpoint
		ActionHelper::create_memory(train_with, train_with->getDoer());
		if (ActionHelper::hero_respond(train_with)) //Other hero agrees to train with you
		{
			train_with->getDoer()->set_action_destination(&train_with->getReceiver()->getVillage()->get_village_location());
			train_with->checkpoint++;
		}
		else
		{
			Memory* doer_mem = train_with->getDoer()->find_mem(train_with->getName() + std::to_string(train_with->time_stamp));
			doer_mem->setCategory("fail");
			doer_mem->setReason("they did not want to train with me");
			doer_mem->setWhen(/*get global frame*/0); 
		}

		break;
	case 1: //If destination is reached, start a timer and move to next checkpoint
		if (train_with->getDoer()->get_action_destination() == nullptr) {
			ActionHelper::set_timer(train_with, 1200);  //Wait 20 seconds for greetings (60 frames times 20 seconds)
			train_with->checkpoint++;
		}
		break;
	case 2: //When greeting timer is complete, set train destination for both heros
		if (ActionHelper::retrieve_time(train_with) == 0) //Greeting timer complete
		{
			train_with->getDoer()->set_action_destination(&train_with->getReceiver()->getLoc());
			train_with->checkpoint++;
		}
		break;
	case 3:  //When train destination is reached, start a time for 1 minute
		if (train_with->getDoer()->get_action_destination() == nullptr)
		{
			ActionHelper::set_timer(train_with, 3600); //Wait 1 minute for training (60 frames times 60 seconds)
			train_with->checkpoint++;
			Fight* fight = new Fight(train_with->getDoer()->getParty(), train_with->getReceiver()->getParty(),true);
		}
		break;
	case 4: //If timer is complete, set village as destination, apply postconds, update memory
		if (ActionHelper::retrieve_time(train_with) == 0) {
			Memory* doer_mem = train_with->getDoer()->find_mem(train_with->getName() + std::to_string(train_with->time_stamp));
			//Memory* receiver_mem = fight->getReceiver()->find_mem(fight->getName() + std::to_string(fight->time_stamp));
			if (doer_mem == nullptr)
			{
				perror("something is wrong with the current hero memory creation function");
			}
			train_with->getDoer()->getParty()->get_fight()->end_combat();
			train_with->getDoer()->set_action_destination(&train_with->getDoer()->getVillage()->get_village_location()); //Also predefined, maybe as "home_location" in hero
			train_with->apply_postconditions(true);				 //Apply post-conditions
			train_with->executed = true;
			doer_mem->setCategory("success");			 //Call update_memory function
			doer_mem->setReason("I am good at training");
			doer_mem->setWhen(/*get global frame*/0);
		}
		break;

	}
}


void ActionExecFunctions::execute_form_alliance(Action* form_alliance) {
	form_alliance->executed = true;
	std::cout << "/////////////////////////execute_form_alliance///////////////////////" << std::endl;
	/*
	Hero* doer = form_alliance->getDoer();
	Hero* responder = form_alliance->getReceiver();
	switch (form_alliance->checkpoint) {
	case 0:
		ActionHelper::create_memory(form_alliance, doer);

		form_alliance->getDoer()->set_action_destination(&form_alliance->getReceiver()->getVillage()->get_village_location());
		form_alliance->checkpoint++;
		break;

	case 1:
		if (form_alliance->getDoer()->get_action_destination() == nullptr) {
			Planner* hero_planner = ActionHelper::ai->hero_planners[responder->name];
			if (ActionHelper::hero_respond(form_alliance)) {
			

					//success
					form_alliance->apply_postconditions(true);
					form_alliance->executed = true;

			}
			else {
				//update memory failed
			}

		}

	}
	*/
	
}



void ActionExecFunctions::execute_fight(Action* fight)
{
	/*Create Memory
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
		fight->getDoer()->set_action_destination(&fight->getReceiver()->getVillage()->get_village_location()); //need to somehow retrieve location of target village
		ActionHelper::create_memory(fight, fight->getDoer());
		fight->checkpoint++;
		break;
	case 1: //If destination is reached, check if hero is there start a timer and move if not, fight otherwise
		if (fight->getDoer()->get_action_destination() == nullptr)//needs to be changed to use party location right 
		{
			//if the target hero is in the village then begin the battle
			if (fight->getDoer()->getLoc() == fight->getReceiver()->getLoc()) // need to change this so it checks if the party is close by
			{
				fight->checkpoint++;
				ActionHelper::create_memory(fight, fight->getReceiver());
			}
			ActionHelper::set_timer(fight, 3600);  //Wait 1 minute (60 frames times 60 seconds) trying to find out the hero's location
			fight->checkpoint++;
		}
		break;
	case 2: //If timer is complete, set village as destination to the location of the target hero 
		if (ActionHelper::retrieve_time(fight) == 0)
		{
			fight->getDoer()->set_action_destination(&fight->getReceiver()->getLoc()); //go to the target hero's location
			fight->checkpoint++;
			ActionHelper::create_memory(fight, fight->getReceiver());
		}
		break;
	case 3: //If both niether party is empty then contiue the fight 
			//(may need to change this to account for hero death)
		if (fight->getDoer()->get_action_destination() == nullptr) {
			//do a single round of battle every 10 sec
			if (ActionHelper::retrieve_time(fight) == 0)
			{
				Fight* fight_obj = new Fight(fight->getDoer()->getParty(), fight->getReceiver()->getParty(), false);
				//ActionHelper::set_timer(fight, 600);
			}
			if (fight->getDoer()->getParty()->get_fight()->is_over())
			{
				fight->checkpoint++;
			}
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
		if (fight->getReceiver()->getParty()->getMembers().size() == fight->getReceiver()->getParty()->get_down_members().size()) {
			//Apply succ-post-conditions
			fight->apply_postconditions(true);
			//update_memory category as a success 
			doer_mem->setCategory("success"); receiver_mem->setCategory("fail");
			//update reason
			doer_mem->setReason("They couldn't handle me"); //need to create a reason function
			receiver_mem->setReason("They attacked while my guard was down");
		}
		else
		{
			//Apply fail-post-conditions
			fight->apply_postconditions(false);
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
		doer_mem->setWhen(frame_count);
		receiver_mem->setWhen(frame_count);

		fight->getDoer()->getParty()->get_fight()->end_combat();
		//Mark action as executed?
		fight->executed = true;

		//create prompt for kill action
		(fight->getDoer(), fight->getReceiver());
		fight->getDoer()->set_action_destination(&fight->getDoer()->getVillage()->get_village_location());
		break;

	}

}


void ActionExecFunctions::execute_conquer(Action* conq)
{
	switch (conq->checkpoint) {
	case 0: //Pick village location(location of fight target), create memory, increment checkpoint
		conq->getDoer()->set_action_destination(&conq->getReceiver()->getVillage()->get_village_location()); //need to somehow retrieve location of target village
		ActionHelper::create_memory(conq, conq->getDoer());
		conq->checkpoint++;
		break;
	case 1: //If destination is reached, check if hero is there start a timer and move if not, fight otherwise
		if (conq->getDoer()->get_action_destination() == nullptr)//needs to be changed to use party location right 
		{
			ActionHelper::set_timer(conq, 3600);  //Wait 1 minute (60 frames times 60 seconds) trying to find out the hero's location
			conq->checkpoint++;
			conq->getReceiver()->getVillage()->defenders->add_party_to_party(conq->getReceiver()->getVillage()->barracks);
			ActionHelper::create_memory(conq, conq->getReceiver());
			new Fight(conq->getDoer()->getParty(), conq->getReceiver()->getParty(), false);
		}
		break;
	case 2: //If both niether party is empty then contiue the fight 
			//(may need to change this to account for hero death)
		if (conq->getDoer()->getParty()->getMembers().size() == 0)
		{
			conq->checkpoint++;
		} else if (conq->getReceiver()->getVillage()->defenders->getMembers().size() == 
			conq->getReceiver()->getVillage()->defenders->get_down_members().size()) {
			conq->getReceiver()->getVillage()->add_to_village_health(conq->getDoer()->getParty()->getMembers().size()*10);
			if (conq->getReceiver()->getVillage()->get_village_health()<=0) {
				conq->checkpoint++;
			}else {
				//ActionHelper::set_timer(conq, 600);
				conq->getDoer()->getParty()->get_fight()->not_over();
				conq->getReceiver()->getVillage()->defenders->add_party_to_party(conq->getReceiver()->getVillage()->barracks);
			}
		}
		//do a single round of battle every 10 sec
		/*if (ActionHelper::retrieve_time(conq) == 0)
		{
			ActionHelper::battle_sim(conq, conq->getReceiver()->getVillage()->defenders);
			ActionHelper::set_timer(conq, 600);
		}*/

		//NEED TO SOMEHOW ACCOUNT FOR IF A PLAYER GETS CLOSE

		break;
	case 3: //If win update apply win-post else apply loss-post and update memory
			//create_memory(fight, fight->getOwner()); do we want to update the owner immeadiately?

		Memory* doer_mem = conq->getDoer()->find_mem(conq->getName() + std::to_string(conq->time_stamp));
		Memory* receiver_mem = conq->getReceiver()->find_mem(conq->getName() + std::to_string(conq->time_stamp));
		if (doer_mem == nullptr || receiver_mem == nullptr)
		{
			perror("something is wrong with the current hero memory creation function");
		}

		//check if the target's party is empty(may need to change this to account for hero death)
		if (conq->getReceiver()->getVillage()->get_village_health() <= 0) {
			//Apply succ-post-conditions
			conq->apply_postconditions(true);
			//update_memory category as a success 
			doer_mem->setCategory("success"); receiver_mem->setCategory("fail");
			//update reason
			doer_mem->setReason("They couldn't handle me"); //need to create a reason function
			receiver_mem->setReason("They attacked while my guard was down");
			conq->getDoer()->getVillage()->conquer(conq->getReceiver()->getVillage());
		}
		else
		{
			//Apply fail-post-conditions
			conq->apply_postconditions(false);
			//update_memory as faiure
			doer_mem->setCategory("fail"); receiver_mem->setCategory("success");
			//update reason
			doer_mem->setReason("I was too weak");//need to create a reason function
			receiver_mem->setReason("They were foolish to attack");
		}
		//update where
		doer_mem->setWhere(std::to_string(conq->getDoer()->getLoc().xloc));
		receiver_mem->setWhere(std::to_string(conq->getReceiver()->getLoc().xloc));
		//update when
		doer_mem->setWhen(frame_count);
		receiver_mem->setWhen(frame_count);

		conq->getDoer()->getParty()->get_fight()->end_combat();
		//Mark action as executed?
		conq->executed = true;
		conq->getDoer()->set_action_destination(&conq->getDoer()->getVillage()->get_village_location());
		break;

	}

}

void ActionExecFunctions::execute_duel(Action* duel)
{
	switch (duel->checkpoint) {
	case 0: //Pick village location(location of fight target), create memory, increment checkpoint
		duel->getDoer()->set_action_destination(&duel->getReceiver()->getVillage()->get_village_location());
		ActionHelper::create_memory(duel, duel->getDoer());
		duel->checkpoint++;
		break;
	case 1: //If destination is reached, check if hero is there start a timer and move if not, fight otherwise
		if (Party::dist_location_to_location(duel->getDoer()->getLoc(), *duel->getDoer()->get_action_destination())<500)//needs to be changed to use party location right 
		{
			//if the target hero is in the village then begin the battle
			if (duel->getDoer()->getLoc() == duel->getReceiver()->getLoc()) // need to change this so it checks if the party is close by
			{
				duel->checkpoint++;
				ActionHelper::create_memory(duel, duel->getReceiver());
			}
			ActionHelper::set_timer(duel, 3600);  //Wait 1 minute (60 frames times 60 seconds) trying to find out the hero's location
			duel->checkpoint++;
		}
		break;
	case 2: //If timer is complete, set village as destination to the location of the target hero 
		if (ActionHelper::retrieve_time(duel) == 0)
		{
			duel->getDoer()->set_action_destination(&duel->getReceiver()->getLoc()); //go to the target hero's location
			duel->checkpoint++;
			ActionHelper::create_memory(duel, duel->getReceiver());
		}
		break;
	case 3: //If both niether party is empty then contiue the fight 
			//(may need to change this to account for hero death)
		if (Party::dist_location_to_location(duel->getDoer()->getLoc(), *duel->getDoer()->get_action_destination())<500) {
			Fight* fight = new Fight(duel->getDoer()->getParty(), duel->getReceiver()->getParty(), true);
			duel->checkpoint++;
		}
		//NEED TO SOMEHOW ACCOUNT FOR IF A PLAYER GETS CLOSE
		break;
	case 4:
		if (duel->getDoer()->getParty()->get_fight()->is_over())
		{
			duel->checkpoint++;
		}
		break;
	case 5: //If win update apply win-post else apply loss-post and update memory
			//create_memory(fight, fight->getOwner()); do we want to update the owner immeadiately?

		Memory* doer_mem = duel->getDoer()->find_mem(duel->getName() + std::to_string(duel->time_stamp));
		Memory* receiver_mem = duel->getReceiver()->find_mem(duel->getName() + std::to_string(duel->time_stamp));
		if (doer_mem == nullptr || receiver_mem == nullptr)
		{
			perror("something is wrong with the current hero memory creation function");
		}

		//check if the target's party is empty(may need to change this to account for hero death)
		if (duel->getReceiver()->getParty()->getMembers().size() == duel->getReceiver()->getParty()->get_down_members().size()) {
			//Apply succ-post-conditions
			duel->apply_postconditions(true);
			//update_memory category as a success 
			doer_mem->setCategory("success"); receiver_mem->setCategory("fail");
			//update reason
			doer_mem->setReason("They couldn't handle me"); //need to create a reason function
			receiver_mem->setReason("They attacked while my guard was down");
		}
		else
		{
			//Apply fail-post-conditions
			duel->apply_postconditions(false);
			//update_memory as faiure
			doer_mem->setCategory("fail"); receiver_mem->setCategory("success");
			//update reason
			doer_mem->setReason("I was too weak");//need to create a reason function
			receiver_mem->setReason("They were foolish to attack");
		}
		//update where
		doer_mem->setWhere(std::to_string(duel->getDoer()->getLoc().xloc));
		receiver_mem->setWhere(std::to_string(duel->getReceiver()->getLoc().xloc));
		//update when
		doer_mem->setWhen(frame_count);
		receiver_mem->setWhen(frame_count);

		duel->getDoer()->getParty()->get_fight()->end_combat();
		//Mark action as executed?
		duel->executed = true;

		//create prompt for kill action
		//(duel->getDoer(), duel->getReceiver());
		duel->getDoer()->set_action_destination(&duel->getDoer()->getVillage()->get_village_location());
		break;

	}

}

void ActionExecFunctions::execute_conversation(Action* conv)
{
	switch (conv->checkpoint) {
	case 0: //Pick training location, create memory, increment checkpoint
		ActionHelper::create_memory(conv, conv->getDoer());
		conv->getDoer()->set_action_destination(&conv->getReceiver()->getVillage()->get_village_location());
		conv->checkpoint++;
		break;

	case 1: //If destination is reached, start a timer and move to next checkpoint
		if (conv->getDoer()->get_action_destination() == nullptr) {
			ActionHelper::set_timer(conv, 60);  
			conv->checkpoint++;
		}
		break;

	case 2: //When greeting timer is complete, set train destination for both heros
		if (ActionHelper::retrieve_time(conv) == 0) //Greeting timer complete
		{
			conv->getDoer()->set_action_destination(&conv->getReceiver()->getLoc());
			conv->checkpoint++;
		}
		break;
	case 3:  //When train destination is reached, start a time for 1 minute
		if (conv->getDoer()->get_action_destination() == nullptr)
		{
			ActionHelper::set_timer(conv, 3600); //Wait 1 minute for training (60 frames times 60 seconds)
			conv->checkpoint++;
		}
		break;
	case 4: //If timer is complete, set village as destination, apply postconds, update memory
		if (ActionHelper::retrieve_time(conv) == 0) {
			Memory* doer_mem = conv->getDoer()->find_mem(conv->getName() + std::to_string(conv->time_stamp));
			//Memory* receiver_mem = fight->getReceiver()->find_mem(fight->getName() + std::to_string(fight->time_stamp));
			if (doer_mem == nullptr)
			{
				perror("something is wrong with the current hero memory creation function");
			}
			conv->getDoer()->set_action_destination(&conv->getDoer()->getVillage()->get_village_location()); //Also predefined, maybe as "home_location" in hero
			if (ActionHelper::conversation(conv)) {
				conv->apply_postconditions(true);				 //Apply post-conditions
				doer_mem->setCategory("success");			 //Call update_memory function
				doer_mem->setReason("The bribe went well");
			} else {
				conv->apply_postconditions(false);				 //Apply post-conditions
				doer_mem->setCategory("fail");			 //Call update_memory function
				doer_mem->setReason("The bribe didn't go well");
			}
			conv->executed = true;
			doer_mem->setWhen(/*get global frame*/0);
		}
		break;

	}
}

void ActionExecFunctions::execute_bribe(Action* bribe)
{
	int monopoly_money = 420;
	switch (bribe->checkpoint) {
	case 0: //Determine the location that the bribe is happening
		ActionHelper::create_memory(bribe, bribe->getDoer());
		bribe->getDoer()->set_action_destination(&bribe->getReceiver()->getVillage()->get_village_location());
		bribe->checkpoint++;
		break;

	case 1: //Create a greeting timer
		if (bribe->getDoer()->get_action_destination() == nullptr) {
			ActionHelper::set_timer(bribe, 60);
			bribe->checkpoint++;
		}
		break;

	case 2: //Once the greeting timer is completed, take away money(placeholder) to simulate giving something for the bribe
		if (ActionHelper::retrieve_time(bribe) == 0) //Greeting timer complete
		{
			//bribe->getDoer()->set_action_destination(&bribe->getReceiver()->getLoc());
			monopoly_money = monopoly_money - 69;//Taking away money
			bribe->checkpoint++;
		}
		break;
	case 3: //If timer is complete, set village as destination, apply postconds, update memory
		if (ActionHelper::retrieve_time(bribe) == 0) {
			Memory* doer_mem = bribe->getDoer()->find_mem(bribe->getName() + std::to_string(bribe->time_stamp));
			//Memory* receiver_mem = fight->getReceiver()->find_mem(fight->getName() + std::to_string(fight->time_stamp));
			if (doer_mem == nullptr)
			{
				perror("something is wrong with the current hero memory creation function");
			}
			bribe->getDoer()->set_action_destination(&bribe->getDoer()->getVillage()->get_village_location()); //Also predefined, maybe as "home_location" in hero
			if (ActionHelper::conversation(bribe)) {
				bribe->apply_postconditions(true);				 //Apply post-conditions
				doer_mem->setCategory("success");			 //Call update_memory function
				doer_mem->setReason("The conversaton went well");
			}
			else {
				bribe->apply_postconditions(false);				 //Apply post-conditions
				doer_mem->setCategory("fail");			 //Call update_memory function
				doer_mem->setReason("The conversaton didn't go well");
			}
			bribe->executed = true;
			doer_mem->setWhen(/*get global frame*/0);
		}
		break;

	}
}

void ActionExecFunctions::execute_compliment(Action* compliment)
{
	switch (compliment->checkpoint) {
	case 0: //Determine the location that the compliment is happening
		ActionHelper::create_memory(compliment, compliment->getDoer());
		compliment->getDoer()->set_action_destination(&compliment->getReceiver()->getVillage()->get_village_location());
		compliment->checkpoint++;
		break;

	case 1: //Create a greeting timer
		if (compliment->getDoer()->get_action_destination() == nullptr) {
			ActionHelper::set_timer(compliment, 60);
			compliment->checkpoint++;
		}
		break;
	case 2:
		if (ActionHelper::retrieve_time(compliment) == 0) {//checks to see if greeting timer is done
			Memory* doer_mem = compliment->getDoer()->find_mem(compliment->getName() + std::to_string(compliment->time_stamp));
			//Memory* receiver_mem = fight->getReceiver()->find_mem(fight->getName() + std::to_string(fight->time_stamp));
			if (doer_mem == nullptr)
			{
				perror("something is wrong with the current hero memory creation function");
			}
			compliment->getDoer()->set_action_destination(&compliment->getDoer()->getVillage()->get_village_location()); //Also predefined, maybe as "home_location" in hero
			if (ActionHelper::conversation(compliment)) {
				compliment->apply_postconditions(true);				 //Apply post-conditions
				doer_mem->setCategory("success");			 //Call update_memory function
				doer_mem->setReason("It looks like my compliment was received well");
			}
			else {
				compliment->apply_postconditions(false);				 //Apply post-conditions
				doer_mem->setCategory("fail");			 //Call update_memory function
				doer_mem->setReason("They didn't accept my compliment well");
			}
			compliment->executed = true;
			doer_mem->setWhen(/*get global frame*/0);
		}
		break;

	}
}

