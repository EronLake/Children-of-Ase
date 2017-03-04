#include "Planner.h"

Planner::Planner() {

};
Planner::Planner(Hero* hero) {
	evaluateHero = hero;
};
int Planner::personality_appeal(Action* action) {

	return 0;
};