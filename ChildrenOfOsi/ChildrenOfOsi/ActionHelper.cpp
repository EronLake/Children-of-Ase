#include "stdafx.h"
#include "ActionHelper.h"


ActionHelper::ActionHelper()
{
	LOG("ActionHelper Object Constructed");
}


ActionHelper::~ActionHelper()
{
	LOG("ActionHelper Object Destroyed");
}

void ActionHelper::create_memory(Action* action) {
	int type = 0;           
	vector<NPC*> people;
	people.push_back(action->getOwner());/*needs to be changed to did*/
	people.push_back(action->getHero());
	people.push_back(action->getOwner());

	string category;         //ACTIONS: fail, success, incomplete                            FACTS: fact type (i.e. name, origin, etc)
	string content;          //ACTIONS: action name                                          FACTS: actual data (i.e. "Yemoja", "Oasis", etc)
	string where;            //ACTIONS: where the event occured                              
	int why;                 //ACTIONS: do-er's motivation (0=affinity, 1=strength, 2=notoriety, -1=idk)
	int when;                //ACTIONS: when the event occured (incomplete: when it started, complete: when it completed)
	string reason;           //ACTIONS: reason for failure or success

	//int time;/ 


	//Memory(int t, int frames, vector<NPC*> p, string cat="",string cont="",string where="",int why=-1, int when=-1);

}