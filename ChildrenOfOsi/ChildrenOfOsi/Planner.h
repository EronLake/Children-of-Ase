#include "Personality.h"
#include "ActionPool.h"
#include "Hero.h"

class Planner {
public:
	Planner();
	Planner(Hero* evaluateHero);
private:
	Hero* evaluateHero;

	
	int personality_appeal(Action* evaluateAction);


};