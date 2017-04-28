#pragma once
#include "Hero.h"
#include "Planner.h"
#include "Containers.h"
#include "ActionPool.h"

class AIController {
private:

	//planners[2] = yemoja
	//planners[3] = oya
	//planners[4] = oshosi
	//planners[5] = ogun
	static Planner* yemoja_planner;
	static Planner* oya_planner;
	static Planner* oshosi_planner;
	static Planner* ogun_planner;
	//unordered_map<int, Planner*> planners;
public:
	AIController();
	~AIController();

	//static unordered_map<int, Planner*> hero_planners;

	static Planner* get_plan(int id);

	static void set_plan(int id, Planner* plan);

	static Hero* get_hero_object(int h);

	static void generate_end_state(int me, int them);

	static void init_plans();

	static void reevaluate_state(int me, int them);

	static void execute();

	static bool give_as_quest(Action* action);

	static bool quest_response(Hero* doer, Hero* asker);

	static Hero* pick_quest_doer(Action* quest);

};

