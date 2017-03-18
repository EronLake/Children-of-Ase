#include "Personality.h"
#include "Hero.h"

#include "Conditions.h"

#include "ActionPool.h"

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
	~Planner();
	Planner(Hero* evaluateHero);

	void choose_end_with(int hero);

	Action choose_next_step(Action goal, vector<Action> goals);

	StateList* get_end_state_map() { return end_states; }
	vector<Action> get_end_states();
	MilestoneList* get_milestone_map() { return milestones; }
	//vector<Action> get_milestones_for_goal(Action goal);
	vector<Action> get_milestone_frontier();
	Action* get_current_action() { return current_action; }
	int get_current_action_value() { return current_action_value; }
	Action get_current_end_state() { return current_end_state; }
	void set_current_action(Action* action) { current_action = action; current_action_value = action->getUtility(); }
	void add_milestone(Action goal, Action milestone);

	void generate_milestones(Action state, Action* goal);

	int value_of(Action* action);

private:
	Hero* evaluateHero;

	//Map of hero numbers to the Action representing the desired end state with that hero
	StateList* end_states;
	//Map of end state Actions to the Action path (last element in path is the next milestone to complete)
	MilestoneList* milestones;

	Action current_end_state;
	Action* current_action = NULL;
	int current_action_value;

	int heuristic(Action step, vector <std::shared_ptr<Preconditions>> priority_preconds, vector<Action> goals);
	
	int prereq_appeal(Action step, vector<std::shared_ptr<Preconditions>> priority_preconds);
	int cost(Action step);

	vector<std::shared_ptr<Preconditions>> prioritize_preconditions(Action goal);
	int personality_appeal(Action* evaluateAction);


};

