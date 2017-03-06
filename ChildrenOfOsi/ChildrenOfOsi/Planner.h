#include "Personality.h"
#include "ActionPool.h"
#include "Hero.h"

class Planner {
public:
	Planner();
	Planner(Hero* evaluateHero);
private:
	Hero* evaluateHero;

	vector<Action> prioritize_preconditions(Action goal);
	int personality_appeal(Action* evaluateAction);


};