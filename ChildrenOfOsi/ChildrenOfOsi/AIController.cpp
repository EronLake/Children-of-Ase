#include "stdafx.h"
#include "AIController.h"



AIController::AIController()
{
	LOG("AIController object constructed");

}

AIController::~AIController()
{
	LOG("AIController object destructed");
}

void AIController::generate_end_state(int me, int them)
{
	hero_planners[me]->choose_end_with(them);

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
	for (auto iter : hero_planners) {   //For each hero Planner
		int me = iter.first;
		Hero* hero = get_hero_object(me);
		Planner* planner = iter.second;
		vector<Action*> goals;

		for (int them = 1; them < 6; them++)   //Look at every other character...
		{
			if (them != me)                    //...that is not myself...
			{
				generate_end_state(me, them);  //...and pick my ideal state with them

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
	auto iter = hero_planners.find(me);

	if (iter != hero_planners.end())
	{
		Planner* planner = iter->second;

		Action* state = planner->get_end_state_map()->at(them);  //Point to the current end_state for them 
		planner->get_milestone_map()->erase(state);           //Delete the old end_state entry in the milestone list
		generate_end_state(me, them);                          //Generate a new end_state for them, which updates state pointer


		
		//planner->get_milestone_map().at(state).clear();        //Clear the milestones leading to that end_state


		Action* milestone = planner->choose_next_step(state, planner->get_end_states()); //Get the first milestone

		planner->add_milestone(state, milestone);                  //Add the first milestone to the action path

		planner->generate_milestones(state, milestone);          //Generate the rest of the milestones for this state
	}
	else
	{
		LOG("Error: No planner for hero #" << me);
	}
}

void AIController::execute() {
	for (auto iter : hero_planners) {
		Planner* planner = iter.second;
		Action* curr_action = planner->get_current_action();
		Action* curr_goal = planner->get_current_end_state();

		EndStateList* end_states = planner->get_end_state_map();
		MilestoneList* milestones = planner->get_milestone_map();

		//std::////cout << "Executing action " << curr_action->name << std::endl;

		//Call execute function pointer of the action itself
		//if you are not planning to give it as a quest
		if (!planner->give_as_quest) {
			curr_action->execute();
		}
		if (curr_action->executed) {

			// the issue here is that the key for the milestonees (curr_goal) exsits
			//but the value does not exsit because it was popped after completion
			//need to fix error where milestones are readded

			//we may just want to push the goal onto the milestone list

			//**ERONS FIX**
			if(milestones->at(curr_goal).size() > 0 )
			{ 
				if (milestones->at(curr_goal).size() == 1 &&			//checks if the goal had been previously added to milestone list
					milestones->at(curr_goal)[0] == curr_goal)
				{
					init_plans();
				}
				milestones->at(curr_goal).pop_back();              //Remove the curr_action from curr_goal's milestone list
			}
			else 
			{
				milestones->at(curr_goal).push_back(curr_goal);
			}

			
			vector<Action*> frontier = planner->get_milestone_frontier();

			//Loop over all the next milestones to find the most valuable action, and set it to current action
			int best = 0;
			for (auto itor : frontier) {
				if (itor->getUtility() > best) {
					best = itor->getUtility();
					planner->set_current_action(itor);
				}
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
	Action* curr_goal = hero_planners[me->name]->get_current_end_state();
	for (int postcond_key = 0; postcond_key < action->succ_postconds.size(); postcond_key++) {
		Postcondition* post = action->succ_postconds[postcond_key].get();
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
* Currently doesn't break ties (i.e. the first hero found takes priority)
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
				doer = this->get_hero_object(doer_id);
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
*/
bool AIController::quest_response(Hero* doer, Hero* asker) {
	bool response = false;
	Relationship* our_rel = doer->rel[asker->name];
	if (our_rel->getAffinity() > 50 && our_rel->getNotoriety() > 50 && our_rel->getStrength() > 50)
	{
		response = true;
	}

	return response;
}