#include "Hero.h"
#include "Planner.h"


class AIController {
private:
	//Hero* yemoja;
	//Hero* oshosi;
	//Hero* oya;
	//Hero* ogun;

	Planner* yemoja;
	Planner* oshosi;
	Planner* oya;
	Planner* ogun;

public:
	AIController();
	~AIController();

	void generate_end_state(int me, int them);

};