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
		EndStateList end_states = planner->get_end_state_map();
		goals = planner->get_end_states();
		for (auto iter : end_states)
		{
			Action* goal = iter.second;
			Action* milestone = planner->choose_next_step(goal, goals);
			planner->add_milestone(goal, milestone);

		}

		// For each end state, look at the milestone and generate a path 

		MilestoneList milestones_by_goal = planner->get_milestone_map();
		for (auto iter : milestones_by_goal)
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

		Action* state = planner->get_end_state_map().at(them);  //Point to the current end_state for them 
		planner->get_milestone_map().erase(state);           //Delete the old end_state entry in the milestone list
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

		EndStateList end_states = planner->get_end_state_map();
		MilestoneList milestones = planner->get_milestone_map();

		//std::////cout << "Executing action " << curr_action->name << std::endl;

		//Call execute function pointer of the action itself
		//if you are not planning to give it as a quest
		if (!planner->give_as_quest) {
			curr_action->execute();
		}
		if (curr_action->executed) {

			milestones.at(curr_goal).pop_back();              //Remove the curr_action from curr_goal's milestone list

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

bool AIController::give_as_quest(Action* action) {
	bool is_quest = false;
	Hero* me = action->getOwner();
	Hero* them = action->getReceiver();
	Action* curr_goal = hero_planners[me->name]->get_current_end_state();
	for (int postcond_key = 0; postcond_key < action->succ_postconds.size(); postcond_key++) {
		Postcondition* post = action->succ_postconds[postcond_key].get();
		RelPost* rel_post;
		if (rel_post = dynamic_cast<RelPost*>(post)) //Only execute if dynamic cast succeeds 
		{
			string pre_fulfilled = rel_post->fulfills_which(curr_goal->req_preconds, me->rel[them->getID()]);
			if (pre_fulfilled == "\0")  //Skip if post_cond fulfills no pre-conditions
			{
				continue;
			}
		}


	}
	return is_quest;
}