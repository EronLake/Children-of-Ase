#include "stdafx.h"
#include "AIController.h"

Planner* AIController::yemoja_planner = nullptr;
Planner* AIController::oya_planner = nullptr;
Planner* AIController::oshosi_planner = nullptr;
Planner* AIController::ogun_planner = nullptr;

AIController::AIController()
{
	LOG("AIController object constructed");

}

AIController::~AIController()
{
	LOG("AIController object destructed");
}

Planner* AIController::get_plan(int id) {
	Planner* plan = nullptr;
	switch (id)
	{
	case YEMOJA:
		plan = yemoja_planner;
		break;
	case OYA:
		plan = oya_planner;
		break;
	case OSHOSI:
		plan = oshosi_planner;
		break;
	case OGUN:
		plan = ogun_planner;
		break;
	}
	return plan;
}

void AIController::set_plan(int id, Planner* plan) {
	switch (id) {
	case YEMOJA:
		yemoja_planner = plan;
		break;
	case OYA:
		 oya_planner = plan;
		break;
	case OSHOSI:
		oshosi_planner = plan;
		break;
	case OGUN:
		ogun_planner = plan;
		break;
	}
}

void AIController::generate_end_state(int me, int them)
{
	if (!(me == 4 || them == 4)) {
		get_plan(me)->choose_end_with(them);
	}

	/*switch (me) {
	case YEMOJA:
		yemoja->choose_end_with(them);
		break;
	case OYA:
		oya->choose_end_with(them);
		break;
	case OSHOSI:
		oshosi->choose_end_with(them);
		break;
	case OGUN:
		ogun->choose_end_with(them);
		break;
	}*/
}

Hero* AIController::get_hero_object(int h)
{
	Hero* hero = nullptr;
	switch (h) {
	case SHANGO:
		hero = Containers::hero_table["Shango"];
		break;
	case YEMOJA:
		hero = Containers::hero_table["Yemoja"];
		break;
	case OYA:
		hero = Containers::hero_table["Oya"];
		break;
	case OSHOSI:
		hero = Containers::hero_table["Oshosi"];
		break;
	case OGUN:
		hero = Containers::hero_table["Ogun"];
		break;
	}
	return hero;
}

void AIController::init_plans() {
	for(auto me : Containers::hero_table){
	//for (int me = 2; me < 4; me++) {
		if (me.second->name == SHANGO) { continue; } //skip shango
		Hero* hero = get_hero_object(me.second->name);
		Planner* planner = get_plan(me.second->name);

		vector<Action*> goals;

		for (auto them : Containers::hero_table)	//Look at every other character...
		//for (int them = 1; them < 4; them++)   
		{
			if (them.second->name != me.second->name)                    //...that is not myself...
			{
				generate_end_state(me.second->name, them.second->name);  //...and pick my ideal state with them

			}

		}

		// Go through each ideal end state and generate a milestone
		EndStateList* end_states = planner->get_end_state_map();

		goals = planner->get_end_states();
		for (auto iter : *end_states)
		{
			Action* goal = iter.second;
			Action* milestone = planner->choose_next_step(goal, goals);
			planner->add_milestone(goal, milestone);

		}

		// For each end state, look at the milestone and generate a path 

		MilestoneList* milestones_by_goal = planner->get_milestone_map();
		for (auto iter : *milestones_by_goal)
		{
			vector<Action*> milestones = iter.second;
			Action* state = iter.first;
			Action* curr_milestone = milestones.back();

			//Recursive function that continues to append actions to 
			//"state"'s list of milestones until it reaches an action with no
			//preconditions left
			planner->generate_milestones(state, curr_milestone);
			
		}

	}
}

void AIController::reevaluate_state(int me, int them) {

	Planner* planner = get_plan(me);

	Action* state = planner->get_end_state_map()->at(them);  //Point to the current end_state for them 
	planner->get_milestone_map()->erase(state);            //Delete the old end_state entry in the milestone list
	generate_end_state(me, them);                          //Generate a new end_state for them, which updates state pointer



	//planner->get_milestone_map().at(state).clear();        //Clear the milestones leading to that end_state


	Action* milestone = planner->choose_next_step(state, planner->get_end_states()); //Get the first milestone

	//Eron's Fix: if milestone = endstate fot them then don't cont
	planner->add_milestone(state, milestone);                  //Add the first milestone to the action path


	planner->generate_milestones(state, milestone);          //Generate the rest of the milestones for this state

}

void AIController::execute() {
	int action_wait_time = 120; //2sec           //Wait time is approx. 2 minutes (7200)
	for(auto me : Containers::hero_table){
	//for (int me = 2; me < 4; me++) {
		if (me.second->name == SHANGO) { continue; } //skip the player
		Hero* hero = get_hero_object(me.second->name);
		Planner* planner = get_plan(me.second->name);

		// IN MAIN, DURING THE EXECUTION, WE DO NOT HAVE AN ACTION
		Action* curr_action = planner->get_current_action();
		Action* curr_goal = planner->get_current_end_state();

		EndStateList* end_states = planner->get_end_state_map();
		MilestoneList* milestones = planner->get_milestone_map();

		//std::cout << "Executing action " << curr_action->name << std::endl;

		//Call execute function pointer of the action itself
		//if you are not planning to give it as a quest

		//if (me->get_action_timer() < 0)
		//{

		//}
		//me->init_action_timer(action_wait_time);                    //Start a timer for approx. 2 minutes

	//	std::cout << "before: " << hero->update_action_timer() << endl;
		if (hero->update_action_timer() == 0)
		{
		//	std::cout << "after: " << hero->update_action_timer() << endl;
			if (curr_action != nullptr) { //used to be : "!planner->give_as_quest" //and then it was "true"
			//	std::cout << "execute" << endl;
				if (hero->getParty()->getLeader()==hero)curr_action->execute();

				//cout << "hero number " << me << "'s current action has been executed" << endl;

				//cout << "hero number " << me << "'s current action has been executed" << endl;
//				cout << "dest is " << hero->get_action_destination()->getXloc() << ", " << hero->get_action_destination()->getYloc() << endl;

			}
			else {
				//cout << "hero number "<< me << "'s CURRENT ACTION IS A NULLPTR!!!" << endl;
			}
			if (curr_action != nullptr && curr_action->executed) {	//need to check to make sure curr_action is not nullptr

				//*Alex* I never get here. Set up incorrectly or action execute not working right?

				// the issue here is that the key for the milestonees (curr_goal) exsits
				//but the value does not exsit because it was popped after completion
				//need to fix error where milestones are readded

				//we may just want to push the goal onto the milestone list

				//**ERONS FIX**
				curr_action->executed = false; //resets the execuded so action can be executed again
				curr_action = nullptr;

				if (milestones->at(curr_goal).size() > 0)
				{

					if (milestones->at(curr_goal).size() == 1 &&			//checks if the goal had been previously added to milestone list
						milestones->at(curr_goal)[0] == curr_goal)
					{
						AIController::init_plans();
						/*
						for (auto curr_hero : Containers::hero_table)
						{ 
							if (curr_hero.second->name = SHANGO) continue;

							for (auto iter : curr_hero.second->rel) {
								Relationship* my_rel = iter.second;
								int with_hero = iter.first;

									//reevaluate goals for with_hero
									//Eron: This is a temporary fix
									///////////////////////////////////////////////////////
									Hero* other_hero = nullptr;

									for (auto itr : Containers::hero_table)
									{
										if (itr.second->name == with_hero)
										{
											other_hero = itr.second;
										}
									}

									if (curr_hero.second != nullptr && other_hero != nullptr)
									{
										Alliance* curr_alliance = curr_hero.second->getVillage()->get_alliance();
										Alliance* other_alliance = other_hero->getVillage()->get_alliance();

										if (curr_alliance != other_alliance)
										{
											AIController::reevaluate_state(curr_hero.second->name, with_hero);
										}
									}

									///////////////////////////////////////////////////////

									my_rel->setChanged(0);
								}
								
							}*/
							
					}
					else
					{
						milestones->at(curr_goal).pop_back();              //Remove the curr_action from curr_goal's milestone list
					}
				}
				else
				{
					milestones->at(curr_goal).push_back(curr_goal);
				}

				vector<Action*> frontier = planner->get_milestone_frontier();
				Action* best_action = nullptr;
				//Loop over all the next milestones to find the most valuable action, and set it to current action
				int best_utility = 0;
				for (auto itor : frontier) {
					//initializes the best action
					if(best_action == nullptr) {
						best_action = itor;
					}

					if (itor->getUtility() > best_utility) {
						best_utility = itor->getUtility();
						best_action = itor;
					}

				}
				if(planner->get_current_action()->getDoer()->SUGG_ACT_STATUS != 1)
				    planner->set_current_action(best_action);                   //Current action is set
				hero->init_action_timer(action_wait_time);                    //Start a timer for approx. 2 minutes
				planner->give_as_quest = give_as_quest(best_action);  //Check and store in planner whether this is appropriate to give as a quest

			}
			else {
				//cout << "hero number " << me << "'s action NOT FINISHED EXECUTING" << endl;
			}

		}
		//planner->get_milestones_for_goal(curr_goal).pop_back();  



	}
}
/*
* Decides if the Action's doer is at all willing to pass this action on as a quest
* The action's Relationship postconditions are compared to the required Relationship preconditions
* of the doer's current goal. If any postcondition fulfills a precondition, but fails to fulfill it
* when the action is given as a quest (i.e. when utility is reduced by 20%), the function returns
* false, otherwise it returns true
*/
bool AIController::give_as_quest(Action* action) {
	bool is_quest = true;
	Hero* me = action->getOwner();
	Hero* them = action->getReceiver();
	Action* curr_goal = new Action();// hero_planners[me->name]->get_current_end_state();
	for (int postcond_key = 0; postcond_key < action->doer_succ_postconds.size(); postcond_key++) {
		Postcondition* post = action->doer_succ_postconds[postcond_key].get();
		RelPost* rel_post;
		if (rel_post = dynamic_cast<RelPost*>(post)) //Only execute if dynamic cast succeeds 
		{
			RelPrecon* pre_fulfilled = rel_post->fulfills_which(curr_goal->req_preconds, me, them);
			if (pre_fulfilled != nullptr)  //Found a precon that will be fulfilled as a non-quest
			{
				int util_as_quest = (rel_post->get_utility(me, them))*.80; //Owner's of quests only get 80% utility
				if (util_as_quest < pre_fulfilled->get_cost(me, them)) //Precon no longer fulfilled as a quest
				{
					is_quest = false;
				}
			}
		}


	}
	return is_quest;
}

/*
* WARNING: Returns NULLPTR if no hero meets the base affinity req. Caller of function must handle this case
* Considers Heroes (other than the receiver of action) with Affinity > 80, and picks the most
* appealing one based on notoriety + (strength/2). 
* Currently doesn't break ties (i.e. the one looked at earlier takes priority)
*/
Hero* AIController::pick_quest_doer(Action* quest) {
	int highest_appeal = 0;
	Hero* doer = nullptr;
	Hero* me = quest->getOwner();
	Hero* them = quest->getReceiver(); //Have to know receiver so we don't assign quest to them
	for (auto relation : me->rel) //Loop over the heroes in your relationship map
	{
		int doer_id = relation.first;
		Relationship* our_rel = relation.second;
		if (doer_id != them->name && our_rel->getAffinity() >= 80) //Hero is not receiver of action and meets affinity req
		{
			int hero_appeal = (our_rel->getNotoriety() + our_rel->getStrength() / 2);
			if (hero_appeal > highest_appeal) 
			{
				doer = get_hero_object(doer_id);
				highest_appeal = hero_appeal;
			}
		}
	}
	return doer;
}

/*
* Used when someone (asker) requests a quest from a hero (doer) 
*
* Returns true if the asker meets minimum relationship requirements (all stats above 50)
* Returns false otherwise, and if the reciever of the doer's current action is the asker themself
*/
bool AIController::quest_response(Hero* doer, Hero* asker) {
	bool response = true;//changed to true for testing purposes
	Relationship* our_rel = doer->rel[asker->name];
	if (our_rel->getAffinity() > 50 && our_rel->getNotoriety() > 50 && our_rel->getStrength() > 50)
	{
		response = true;
	}
	if (get_plan(doer->name)->get_current_action()->getReceiver() == asker) 
	{
		response = false;
	}

	return response;
}