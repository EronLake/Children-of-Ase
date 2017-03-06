#include "Personality.h"
#include "ActionPool.h"
#include "Hero.h"

namespace std {
	template <>
	struct hash<Action> {
		inline size_t operator()(const Action &action) const {
			return (hash<int>()((action.recieverName)) ^ (hash<string>()(action.name) << 1));
		}
	};
}
class Planner {
public:
	Planner();
	Planner(Hero* evaluateHero);

	void choose_end_with(int hero);

	Action choose_next_step(Action goal, vector<Action> goals);

private:
	Hero* evaluateHero;

	unordered_map<int, Action> end_states;
	unordered_map<Action, vector<Action>> milestones;
	Action current_action;

	int heuristic(Action step, vector <std::string> priority_preconds, vector<Action> goals);
	
	int prereq_appeal(Action step);
	int cost(Action step);
	int personality_appeal(Action evaluateAction);
	vector<Action> prioritize_preconditions(Action goal);
	int personality_appeal(Action* evaluateAction);


};

