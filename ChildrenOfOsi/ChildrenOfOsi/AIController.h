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
	unordered_map<int, Planner*> hero_planners;

public:
	AIController();
	~AIController();

	Hero* get_hero_object(int h);

	void generate_end_state(int me, int them);

	void init_plans();

	void reevaluate_state(int me, int them);

	void execute();
};