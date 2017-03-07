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
		vector<Action> goals;

		for (int them = 1; them < 6; them++)   //Look at every other character...
		{
			if (them != me)                    //...that is not myself...
			{
				generate_end_state(me, them);  //...and pick my ideal state with them

			}

		}

		// Go through each ideal end state and generate a milestone
		StateList end_states = planner->get_end_state_map();
		goals = planner->get_end_states();
		for (auto iter : end_states)
		{
			Action goal = iter.second;
			Action milestone = planner->choose_next_step(goal, goals);
			planner->add_milestone(goal, milestone);

		}

		// For each end state, look at the milestone and generate a path 
		MilestoneList milestones_by_goal = planner->get_milestone_map();
		for (auto iter : milestones_by_goal)
		{
			vector<Action> milestones = iter.second;
			Action state = iter.first;
			Action curr_milestone = milestones.back();

			//Recursive function that continues to append actions to 
			//"state"'s list of milestones until it reaches an action with no
			//preconditions left
			planner->generate_milestones(state, curr_milestone);
			
		}

	}
}
