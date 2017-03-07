#include "Planner.h"

Planner::Planner() {

};
Planner::Planner(Hero* hero) {
	evaluateHero = hero;
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
	vector<Action> preconlist; //temporary
	//eventually wanna do for every precondition, generate cost and return a map from precondition to cost 
	struct lesserCost{
		inline bool operator()(Action& action1, Action& action2) {//is temporarily an action
			return (action1.getUtility() < action2.getUtility());		
		};
	};
	std::sort(preconlist.begin(), preconlist.end(), lesserCost());
	return preconlist;
};