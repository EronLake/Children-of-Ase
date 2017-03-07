#include "Planner.h"

Planner::Planner() {

};
Planner::Planner(Hero* hero) {
	evaluateHero = hero;
	//actions = new ActionPool(evaluateHero);
}

vector<std::string> prioritize_preconds(Action goal) {
	return{ "Precondition 1" };
}

int Planner::cost(Action step) {
	int cost = 0;

	return cost;
}
int Planner::prereq_appeal(Action step) {
	int appeal = 0;

	return appeal;
}

int Planner::heuristic(Action step, vector<std::string> priority_preconds, vector<Action> goals) {
	int value = 0;

	value += personality_appeal(step);
	value += prereq_appeal(step);
	value -= cost(step);

	return value;
}

void Planner::choose_end_with(int hero) {
	switch (hero) {
	case YEMOJA:
		//evaluate relationship
		// end_states[YEMOJA] = picked_state
		// insert the endstate into milestones, with empty milestone vector
		break;
	case OYA:
		break;
	case OSHOSI:
		break;
	case OGUN:
		break;
	case SHANGO:
		break;
	}
}

Action Planner::choose_next_step(Action goal, vector<Action> goals) {
	Action* best_step = nullptr;
	int best_value = 0;

	vector<std::string> priority_preconds = prioritize_preconds(goal);
	vector<Action> possible_steps = evaluateHero->actionPool->getActions(evaluateHero, goal);

	for (Action step : possible_steps) {
		int step_value = heuristic(step, priority_preconds, goals);
		if (step_value > best_value)
		{
			best_value = step_value;
			best_step = &step;
		}
	}
	best_step->setUtility(best_value);
	return *best_step;
}

int Planner::personality_appeal(Action action) {

	return 0;
};
int Planner::personality_appeal(Action* evaluateAction) {
	
	return ((evaluateHero->traits->getHonor()*evaluateAction->multipliers->getHonor())+
		(evaluateHero->traits->getPride()*evaluateAction->multipliers->getPride())+
		(evaluateHero->traits->getAggression()*evaluateAction->multipliers->getAggression())+
		(evaluateHero->traits->getKindness()*evaluateAction->multipliers->getKindness())+
		(evaluateHero->traits->getGreed()*evaluateAction->multipliers->getGreed())+
		(evaluateHero->traits->getRecklessness()*evaluateAction->multipliers->getRecklessness())+
		(evaluateHero->traits->getExtroversion()*evaluateAction->multipliers->getExtroversion()));
};
vector<Action> Planner::prioritize_preconditions(Action goal) {
	vector<Action> actionlist; //temporary
	struct greaterAction {
		inline bool operator()(Action& action1, Action& action2) {
			return (action1.getUtility() > action2.getUtility());		
		};
	};
	std::sort(actionlist.begin(), actionlist.end(), greaterAction());
	return actionlist;
};

//Returns a vector holding all 4 ideal end_states (as actions)
vector<Action> Planner::get_end_states() {
	vector<Action> states;
	for (auto iter : *end_states)
	{
		states.push_back(iter.second);
	}
	return states;
}

//Returns the current Action list of milestones for the given end_state
//vector<Action> Planner::get_milestones_for_goal(Action goal)
//{
//	vector<Action> milestones_for_goal = milestones.at(goal);
//	return milestones_for_goal;
//}

vector<Action> Planner::get_milestone_frontier() {
	vector<Action> frontier;
	for (auto iter : *milestones)
	{
		Action goal = iter.first;           //The goal associated with the milestone list
		vector<Action> path = iter.second;  //The milestone list

		if (path.size() == 0) {               //If there are no milestones yet
			frontier.push_back(goal);       //Put the goal itself in the frontier
		}
		else
		{
			frontier.push_back(path.back());  //Otherwise, put the back of the path (current milestone) in the frontier
		}
	}
	return frontier;
}

//Adds the milestone action to the Goal action's milestonelist
void Planner::add_milestone(Action goal, Action milestone) {
	milestones->at(goal).push_back(milestone);
}

void Planner::generate_milestones(Action state, Action goal) {
	if (goal.preConditionsNeeded(evaluateHero, goal.getHero()).size() == 0)
	{
		if (goal.getUtility() > current_action_value)
		{
			current_end_state = state;
			current_action = goal;
			current_action_value = goal.getUtility();
		}
	}
	else
	{
		milestones->at(state).push_back(choose_next_step(goal, get_milestone_frontier()));
		generate_milestones(state, milestones->at(state).back());
	}
}