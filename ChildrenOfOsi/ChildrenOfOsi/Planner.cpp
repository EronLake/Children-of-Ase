#include "stdafx.h"
#include "Planner.h"



Planner::Planner()
{
};
Planner::~Planner() {

};
Planner::Planner(Hero* hero) {
	evaluateHero = hero;
	give_as_quest = true;
	//actions = new ActionPool(evaluateHero);
}




int Planner::cost(Action* step) {
	int cost = 0;

	return cost;
}
int Planner::prereq_appeal(Action* step, vector<std::shared_ptr<Preconditions>> priority_preconds) {
	int appeal = 0;
	//iterate through postconditions.
	for (int i = 0; i < priority_preconds.size(); i++) {
		for (int itr = 0; itr < step->succ_postconds.size(); itr++) {
			if (step->succ_postconds[itr]->get_type() == priority_preconds[i]->get_type()) {
				
				appeal += step->succ_postconds[itr]->get_utility()*(i+1);

			}
		}
	}
	//for each one, get its corresponding precondition rank
	//	(this is done by comparing types)
	//	multiply the rank of the precondition by the utility of the postcondition that satisfies it
	//  += appeal
	return appeal;
}

int Planner::heuristic(Action* step, vector<std::shared_ptr<Preconditions>> priority_preconds, vector<Action*> goals) {
	int value = 0;

	value += personality_appeal(step);
	value += prereq_appeal(step,priority_preconds);
	value -= cost(step);

	return value;
}

/*
* Calculates the best end state with the given hero out of the 3 possible states (Alliance,
* Conquer, and Permanently Conquer)
* Considers the appeal of that action according to your relationship with the receiver, and 
* adjusts this upward or downward acccording to how that action (regardless of receiver) appeals
* to your personality. The action with the highest value is picked.
*/
void Planner::choose_end_with(int hero) {

	//this for loop had to be added so missing heroes wouldn't cause an error
	bool if_should_choose = false;
	for (auto itr = Containers::hero_table.begin(); itr != Containers::hero_table.end(); itr++) {
		if (itr->second == NULL) continue;
		if (hero == itr->second->name) { if_should_choose = true; }
	}
	if (if_should_choose)
	{
		ActionPool* action_pool = evaluateHero->actionPool_map[hero];
		Action* best_end_state = nullptr;
		int value = 0;
		int best_value = 0;

		for (auto state : action_pool->end_states) {
			value = 0;
			value += personality_appeal(state);
			value += relationship_appeal(state);
			if (value > best_value) {
				best_value = value;
				best_end_state = state;
			}
		}
		/*
		if (this->end_states.find(hero) == this->end_states.end())
		{
			this->end_states.insert(std::make_pair(hero, *best_end_state));
		}
		else
		{
			this->end_states.at(hero) = *best_end_state;
		}
		*/
		this->end_states[hero] = best_end_state;
		std::cout << "///////////////////////////////////////////////////////" << std::endl;
		std::cout << "BEST END STATE: " << best_end_state->getName() << std::endl;
		std::cout << "///////////////////////////////////////////////////////" << std::endl;
	}
}

Action* Planner::choose_next_step(Action* goal, vector<Action*> goals) {
	Action* best_step = nullptr;
	int best_value = 0;

	vector<std::shared_ptr<Preconditions>> priority_preconds = prioritize_preconditions(goal);
	vector<Action*> possible_steps = evaluateHero->actionPool_map[goal->getReceiver()->name]->getActions(goal->getReceiver(), goal);

	for (Action* step : possible_steps) {
		//if statement to initialize the best_value to be the first step
		if (best_step == nullptr) { best_step = step; }

		int step_value = heuristic(step, priority_preconds, goals);
		if (step_value > best_value)
		{
			best_value = step_value;
			best_step = step;
		}
	}


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//I dont think we should have this line utilites of actions are not supposed to change
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	best_step->setUtility(best_value);
	return best_step;
}
/*
* Calcualtes the appeal of a given end_state based on your relationship with the receiver
* Each relationship stat is weighted by a multiplier
* 
*/
int Planner::relationship_appeal(Action* state) {
	int appeal = 0;
	int str_mult = *(evaluateHero->traits) * *(state->str_mult);
	int aff_mult = *(evaluateHero->traits) * *(state->aff_mult);
	int noto_mult = *(evaluateHero->traits) * *(state->noto_mult);
	Relationship* my_rel = evaluateHero->rel[state->recieverName];
	appeal += my_rel->getStrength() * str_mult;
	appeal += my_rel->getAffinity() * aff_mult;
	appeal += my_rel->getNotoriety() * noto_mult;
	return appeal;
}

int Planner::personality_appeal(Action* evaluateAction) {
	
	return *(evaluateHero->traits) * *(evaluateAction->multipliers);

	/*return ((evaluateHero->traits->getHonor()*evaluateAction->multipliers->getHonor())+
		(evaluateHero->traits->getPride()*evaluateAction->multipliers->getPride())+
		(evaluateHero->traits->getAggression()*evaluateAction->multipliers->getAggression())+
		(evaluateHero->traits->getKindness()*evaluateAction->multipliers->getKindness())+
		(evaluateHero->traits->getGreed()*evaluateAction->multipliers->getGreed())+
		(evaluateHero->traits->getRecklessness()*evaluateAction->multipliers->getRecklessness())+
		(evaluateHero->traits->getExtroversion()*evaluateAction->multipliers->getExtroversion()));*/
};
vector<std::shared_ptr<Preconditions>> Planner::prioritize_preconditions(Action* goal) {
	vector<std::shared_ptr<Preconditions>> preconlist;
	for (int i = 0; i < goal->req_preconds.size();i++) {
		preconlist.push_back(goal->req_preconds[i]);
	}
	
	//temporary
	//eventually wanna do for every precondition, generate cost and return a map from precondition to cost 
	struct lesserCost{
		inline bool operator()(std::shared_ptr<Preconditions> & precond1, std::shared_ptr<Preconditions> & precond2) {//is temporarily an action
			return (precond1->get_cost() > precond2->get_cost());		
		};
	};

	std::sort(preconlist.begin(), preconlist.end(), lesserCost());
	return preconlist;
};		

//Returns a vector holding all 4 ideal end_states (as actions)
vector<Action*> Planner::get_end_states() {
	//return &end_states;
	vector<Action*> states;
	for (auto iter : end_states)
	//for (auto iter = end_states.begin(); iter != end_states.end();iter++)
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

vector<Action*> Planner::get_milestone_frontier() {
	vector<Action*> frontier;
	for (auto iter : milestones)
	{
		Action* goal = iter.first;           //The goal associated with the milestone list
		vector<Action*> path = iter.second;  //The milestone list

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
void Planner::add_milestone(Action* goal, Action* milestone) {
	milestones[(goal)].push_back(milestone);
}

void Planner::generate_milestones(Action* state, Action* goal) {
	if (goal->preConditionsNeeded(evaluateHero, goal->getReceiver()).size() == 0)
	{
		int post_cond_utility = 0;
		
		for (auto post_cond : goal->succ_postconds) 
		{
			post_cond_utility += post_cond->get_utility(goal->getOwner(), goal->getReceiver());
		}
			
		std::cout << post_cond_utility << std::endl;

		if (post_cond_utility > current_action_value)
		{
			current_end_state = state;
			current_action = goal;
			current_action_value = post_cond_utility;
		}
	}
	else
	{
		milestones.at(state).push_back(choose_next_step(goal, get_milestone_frontier()));
		generate_milestones(state, milestones.at(state).back());
	}
}

//Returns the value of the given action according to the end state you are currently focusing on,
//with consideration towards the other three end states
int Planner::value_of(Action* action) {
	int action_value;

	action_value = heuristic(action, prioritize_preconditions(current_end_state), get_end_states());

	return action_value;
}