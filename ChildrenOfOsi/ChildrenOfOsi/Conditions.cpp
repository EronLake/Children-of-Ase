#include "stdafx.h"
#include "Conditions.h"

////////////////////////////////////////////////////////////////////////////////////
//PRECONDITIONS
////////////////////////////////////////////////////////////////////////////////////

Preconditions::Preconditions()
{
	LOG("Precondition Object Constructed");
}


Preconditions::~Preconditions()
{
	LOG("Precondition Object Destroyed");
}

int Preconditions::get_cost()
{
	LOG("virtual function");
	return 0.0;
}

std::string Preconditions::get_type()
{
	return type;
}

int Preconditions::get_general_type()
{
	return general_type;
}
//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIP PRECONDITIONS
////////////////////////////////////////////////////////////////////////////////////

RelPrecon::RelPrecon(int _rel_type, int _desired_rel_val)
{
	rel_type = _rel_type;
	desired_rel_val = _desired_rel_val;

	type = "relationship_" + to_string(rel_type);
	general_type = REL;

	LOG("RelPrecon Object Constructed");
}


RelPrecon::~RelPrecon()
{
	LOG("Relprecon Object Destroyed");
}

int RelPrecon::get_cost(Hero* curr_hero, Hero* other_hero)
{
	Relationship* cur_rel_map = nullptr;
	int current_rel = 0;
	int cost = 0;
	if(rel_type == AFF)
	{ 
		current_rel = curr_hero->rel[other_hero->name]->getAffinity();
		cost = float(desired_rel_val) - float(current_rel);
	} 
	else if(rel_type == NOT)
	{
		current_rel = curr_hero->rel[other_hero->name]->getNotoriety();
		cost = float(desired_rel_val) - float(current_rel);
	}
	else if(rel_type == STR)
	{
		//for (auto i : curr_hero->rel) {
		//	if (i.first == other_hero->name) { cur_rel_map = i.second; }
		//}
		//current_rel = cur_rel_map->getStrength();

		current_rel = curr_hero->rel[other_hero->name]->getStrength();
		cost = desired_rel_val - current_rel;
		//int find = curr_hero->rel.find(other_hero->name)->second->getStrength();
		//Relationship* temp_rel = curr_hero->rel[other_hero->name];
		//int temp_str = temp_rel->getStrength();
		//current_rel = curr_hero->rel[other_hero->name]->getStrength();
		
	} else if (rel_type == BAFF)
	{
		current_rel = curr_hero->rel[other_hero->name]->getAffinity();
		cost = float(current_rel) - float(desired_rel_val);
	}
	else if (rel_type == BNOT)
	{
		current_rel = curr_hero->rel[other_hero->name]->getNotoriety();
		cost = float(current_rel) - float(desired_rel_val);
	}
	else if (rel_type == BSTR)
	{
		current_rel = curr_hero->rel[other_hero->name]->getStrength();
		cost = float(current_rel) - float(desired_rel_val);
	}

	
	return cost;
}

//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIP ASSUMPTION PRECONDITION
////////////////////////////////////////////////////////////////////////////////////

RelEstimPrerec::RelEstimPrerec(int _rel_type, int _desired_rel_val)
{
	rel_type = _rel_type;
	desired_rel_val = _desired_rel_val;

	type = "relationship_estimate_" + to_string(rel_type);
	general_type = REL_EST;

	LOG("RelEstimPrerec Object Constructed");
}


RelEstimPrerec::~RelEstimPrerec()
{
	LOG("RelEstimPrerec Object Destroyed");
}

int RelEstimPrerec::get_cost(Hero* curr_hero, Hero* other_hero)
{
	int current_rel;
	int cost = 0;
	if (rel_type == AFF)
	{
		current_rel = curr_hero->rel[other_hero->name]->getAffEstimate();
		cost = desired_rel_val - current_rel;
	}
	else if (rel_type == NOT)
	{
		current_rel = curr_hero->rel[other_hero->name]->getNotorEstimate();
		cost = float(desired_rel_val) - float(current_rel);
	}
	else if (rel_type == STR)
	{
		current_rel = curr_hero->rel[other_hero->name]->getStrEstimate();
		cost = float(desired_rel_val) - float(current_rel);
	}
	else if (rel_type == BAFF)
	{
		current_rel = curr_hero->rel[other_hero->name]->getAffEstimate();
		cost = float(current_rel) - float(desired_rel_val);
	}
	else if (rel_type == BNOT)
	{
		current_rel = curr_hero->rel[other_hero->name]->getNotorEstimate();
		cost = float(current_rel) - float(desired_rel_val);
	}
	else if (rel_type == BSTR)
	{
		current_rel = curr_hero->rel[other_hero->name]->getStrEstimate();
		cost = float(current_rel) - float(desired_rel_val);
	}


	return cost;
}

//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//TIME PRECONDITION
////////////////////////////////////////////////////////////////////////////////////

TimePrerec::TimePrerec(int _time_rec)
{
	time_rec = _time_rec;

	type = "time";
	general_type= TIME;

	LOG("TimePrerec Object Constructed");
}


TimePrerec::~TimePrerec()
{
	LOG("TimePrerec Object Destroyed");
}

int TimePrerec::get_cost()
{
	int cost = 0.0;
	float magnifier = 1.0;

	/*
	if (clock->get_curr_time() < time_rec) 
	{
		cost = std::abs(clock->get_curr_time() - time_rec)*magnifier;
	}
	*/
	
	return cost;
}

//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//MEMORY NUMBER PRECONDITION
////////////////////////////////////////////////////////////////////////////////////

MemoryNumPrerec::MemoryNumPrerec(int _rec_num_of_mem)
{
	rec_num_of_mem = _rec_num_of_mem;

	type = "memory_number";
	general_type = MEM_NUM;

	LOG("MemoryNumPrerec Object Constructed");
}


MemoryNumPrerec::~MemoryNumPrerec()
{
	LOG("MemoryNumPrerec Object Destroyed");
}

int MemoryNumPrerec::get_cost(std::vector<Memory*> memories)
{
	int cost = 0.0;
	float magnifier = 10.0;//this has to essentially the cost of an average memory

	if (memories.size() < rec_num_of_mem)
	{
		cost = std::abs(((int)(memories.size()) - rec_num_of_mem))*magnifier;
	}

	return cost;
}
//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//MEMORY PRECONDITION
////////////////////////////////////////////////////////////////////////////////////
MemPrerec::MemPrerec(std::string _rec_mem)
{
	rec_mem = _rec_mem;

	type = "memory_"+rec_mem;
	general_type = MEM;

	LOG("particularMemPrerec Object Constructed");
}


MemPrerec::~MemPrerec()
{
	LOG("particularMemPrerec Object Destroyed");
}

int MemPrerec::get_cost(std::vector<Memory*> memories)
{
	int cost = 0.0;
	float magnifier = 10.0;//this has to essentially the cost of an average memory

	for (int i = 0; i < memories.size(); i++)
	{
		if (memories[i]->getContent() == rec_mem)
			return cost;
	}
	
	cost = 10.0; // cost must equal average of given mem once actions have cost of doing them
				 // we may be able to use that to make the function por acurate

	return cost;
}

////////////////////////////////////////////////////////////////////////////////////
//STATE PRECONDITION
////////////////////////////////////////////////////////////////////////////////////
StatePrerec::StatePrerec()
{
	/*state_manager st_man,
	std::string required state,
	std::vectorr<relevant villages>*/

	type = "state";
	general_type = STATE;

	LOG("particularMemPrerec Object Constructed");
}


StatePrerec::~StatePrerec()
{
	LOG("particularMemPrerec Object Destroyed");
}

int StatePrerec::get_cost()
{
	int cost = 0;
	float magnifier = 10.0;//this has to essentially the cost of an average state change

	return cost;
}








////////////////////////////////////////////////////////////////////////////////////
//MEMORY POSTCONDITION
////////////////////////////////////////////////////////////////////////////////////
Postcondition::Postcondition()
{
	/*state_manager st_man,
	std::string required state,
	std::vectorr<relevant villages>*/

	type = "state";

	LOG("particularMemPrerec Object Constructed");
}


Postcondition::~Postcondition()
{
	LOG("particularMemPrerec Object Destroyed");
}

float Postcondition::get_utility()
{
	LOG("virtual function");
	return 0.0;
}

float Postcondition::get_utility(Hero* curr_hero, Hero* other_hero)
{
	LOG("virtual function");
	return 0.0;
}

void Postcondition::apply_utility()
{
	LOG("virtual function");
}

void Postcondition::apply_utility(Hero* curr_hero, Hero* other_hero)
{
	LOG("virtual function");
}

std::string Postcondition::get_type()
{
	return type;
}

int Postcondition::get_general_type()
{
	return general_type;
}


//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIP POSTCONDITION
////////////////////////////////////////////////////////////////////////////////////

RelPost::RelPost(int _rel_type, int _utility)
{
	rel_type = _rel_type;
	utility = _utility;

	type = "relationship_"+ to_string(rel_type);
	general_type = REL;

	LOG("RelEstimPost Object Constructed");
}


RelPost::~RelPost()
{
	LOG("RelEstimPost Object Destroyed");
}

float RelPost::get_utility(Hero* curr_hero, Hero* other_hero)
{
	return utility;
}

void RelPost::apply_utility(Hero* curr_hero, Hero* other_hero)
{
	if (rel_type == AFF)
	{
		curr_hero->rel[other_hero->name]->addAffinity(utility);
	}
	else if (rel_type == NOT)
	{
		curr_hero->rel[other_hero->name]->addNotoriety(utility);
	}
	else if (rel_type == STR)
	{
		curr_hero->rel[other_hero->name]->addStrength(utility);
	} else if (rel_type == BAFF)
	{
		curr_hero->rel[other_hero->name]->addAffinity(-utility);
	}
	else if (rel_type == BNOT)
	{
		curr_hero->rel[other_hero->name]->addNotoriety(-utility);
	}
	else if (rel_type == BSTR)
	{
		curr_hero->rel[other_hero->name]->addStrength(-utility);
	}
}

//Returns null plug string if the postcondition does not complete
//any of the given preconditions
//Returns the string key of the precondition if one is found
//TODO: Make sure it only returns preconditions which aren't already fulfilled. 
RelPrecon* RelPost::fulfills_which(Precond_vec preconds, Hero* me, Hero* them)
{
	
	RelPrecon* pre_fulfilled = nullptr; 

	for (auto precond : preconds) {
		Preconditions* pre = precond.get();
		RelPrecon* rel_pre = dynamic_cast<RelPrecon*>(pre);
		if ((rel_pre != nullptr) && rel_pre->get_rel_type() == this->get_rel_type()) //Only execute if pre is a RelPrecon, and matches the Posts's type
		{
			int cost = rel_pre->get_cost(me, them);

			if (this->get_utility(me, them) >= cost)
			{
				return rel_pre;
			}
		}
	}
	return nullptr;   //No precon will be fulfilled
}

//---------------------------------------------------------------------------------



////////////////////////////////////////////////////////////////////////////////////
//RELATIONSHIP ASSUMPTION POSTCONDITION
////////////////////////////////////////////////////////////////////////////////////

RelEstimPost::RelEstimPost( int _rel_type, int _utility)
{
	rel_type = _rel_type;
	utility = _utility;

	type = "relationship_estimate_"+ to_string(rel_type);
	general_type = REL_EST;

	LOG("RelEstimPost Object Constructed");
}


RelEstimPost::~RelEstimPost()
{
	LOG("RelEstimPost Object Destroyed");
}

float RelEstimPost::get_utility(Hero* curr_hero, Hero* other_hero)
{
	return utility;
}

void RelEstimPost::apply_utility(Hero* curr_hero, Hero* other_hero)
{
	if (rel_type == AFF)
	{
		curr_hero->rel[other_hero->name]->addAffEstimate(utility);
	}
	else if (rel_type == NOT)
	{
		curr_hero->rel[other_hero->name]->addNotorEstimate(utility);
	}
	else if (rel_type == STR)
	{
		curr_hero->rel[other_hero->name]->addStrEstimate(utility);
	} else if (rel_type == BAFF)
	{
		curr_hero->rel[other_hero->name]->addAffEstimate(-utility);
	}
	else if (rel_type == BNOT)
	{
		curr_hero->rel[other_hero->name]->addNotorEstimate(-utility);
	}
	else if (rel_type == BSTR)
	{
		curr_hero->rel[other_hero->name]->addStrEstimate(-utility);
	}
}

//---------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////
//STATE POSTCONDITION
////////////////////////////////////////////////////////////////////////////////////
StatePost::StatePost(int _utility)
{
	/*state_manager st_man,
	std::string required state,
	std::vectorr<relevant villages>*/
	utility = _utility;

	type = "state";
	general_type = STATE;

	LOG("StatePost Object Constructed");
}


StatePost::~StatePost()
{
	LOG("StatePost Object Destroyed");
}

float StatePost::get_utility()
{
	return utility;
}

void StatePost::apply_utility()
{
	LOG("Still needs to be implimented");
}
