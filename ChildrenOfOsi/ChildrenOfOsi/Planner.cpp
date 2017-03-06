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