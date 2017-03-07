#include "Personality.h"
#include "ActionPool.h"
#include "Hero.h"

typedef unordered_map<int, Action> StateList;
typedef unordered_map<Action, vector<Action>> MilestoneList;

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

	StateList get_end_state_map() { return end_states; }
	vector<Action> get_end_states();
	MilestoneList get_milestone_map() { return milestones; }
	vector<Action> get_milestones_for_goal(Action goal);
	vector<Action> get_milestone_frontier();
	Action get_current_action() { return current_action; }
	int get_current_action_value() { return current_action_value; }
	void add_milestone(Action goal, Action milestone);

	void generate_milestones(Action state, Action goal);

private:
	Hero* evaluateHero;

	//Map of hero numbers to the Action representing the desired end state with that hero
	StateList end_states;
	//Map of end state Actions to the Action path (last element in path is the next milestone to complete)
	MilestoneList milestones;

	Action current_action;
	int current_action_value;

	int heuristic(Action step, vector <std::string> priority_preconds, vector<Action> goals);
	
	int prereq_appeal(Action step);
	int cost(Action step);
	int personality_appeal(Action evaluateAction);
	vector<Action> prioritize_preconditions(Action goal);
	int personality_appeal(Action* evaluateAction);


};

