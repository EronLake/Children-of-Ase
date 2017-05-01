#include "stdafx.h"
#include "Conditions.h"
#include "Alliance.h"

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
	return 0;
}
int Preconditions::get_cost(Hero* curr_hero, Hero* other_hero)
{
	LOG("virtual function");
	return 0;
}

std::string Preconditions::get_type()
{
	return type;
}

int Preconditions::get_general_type()
{
	return general_type;
}

int Preconditions::get_rel_type()
{
	LOG("virtual function");
	return 0;
}

int Preconditions::get_state_type()
{
	LOG("virtual function");
	return 0;
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
		cost = desired_rel_val - current_rel;
	} 
	else if(rel_type == NOT)
	{
		current_rel = curr_hero->rel[other_hero->name]->getNotoriety();
		cost = desired_rel_val - current_rel;
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
		cost = current_rel - desired_rel_val;
	}
	else if (rel_type == BNOT)
	{
		current_rel = curr_hero->rel[other_hero->name]->getNotoriety();
		cost = current_rel - desired_rel_val;
	}
	else if (rel_type == BSTR)
	{
		current_rel = curr_hero->rel[other_hero->name]->getStrength();
		cost = current_rel - desired_rel_val;
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
		cost = desired_rel_val - current_rel;
	}
	else if (rel_type == STR)
	{
		current_rel = curr_hero->rel[other_hero->name]->getStrEstimate();
		cost = desired_rel_val - current_rel;
	}
	else if (rel_type == BAFF)
	{
		current_rel = curr_hero->rel[other_hero->name]->getAffEstimate();
		cost = current_rel - desired_rel_val;
	}
	else if (rel_type == BNOT)
	{
		current_rel = curr_hero->rel[other_hero->name]->getNotorEstimate();
		cost = current_rel - desired_rel_val;
	}
	else if (rel_type == BSTR)
	{
		current_rel = curr_hero->rel[other_hero->name]->getStrEstimate();
		cost = current_rel - desired_rel_val;
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

void Postcondition::apply_utility(Hero* curr_hero, Hero* other_hero, bool if_doer)
{
	LOG("virtual function");
	cout << "virtual function";
}

void Postcondition::apply_utility(Hero* curr_hero, Hero* other_hero)
{
	LOG("virtual function");
	cout << "virtual function";
}

std::string Postcondition::get_type()
{
	return type;
}

int Postcondition::get_general_type()
{
	return general_type;
}

int Postcondition::get_rel_type()
{
	LOG("virtual function");
	return 0;
}

int Postcondition::get_state_type()
{
	LOG("virtual function");
	return 0;
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

/*
applies the the utility of a post condition with two options:
if the doer: applies postconditions to doer
if the reciever: applies postconditions to reciver and the world
*/
void RelPost::apply_utility(Hero* curr_hero, Hero* other_hero, bool if_doer)
{
	//checks if the apply is for the doer or reciever
	if (if_doer == true) {

		//applies relationship updates to the doer
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
		}
		else if (rel_type == BAFF)
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
	else 
	{
		//applies relationship updates to the reciver
		if (rel_type == AFF)
		{
			other_hero->rel[curr_hero->name]->addAffinity(utility);
		}
		else if (rel_type == NOT)
		{
			other_hero->rel[curr_hero->name]->addNotoriety(utility);
		}
		else if (rel_type == STR)
		{
			other_hero->rel[curr_hero->name]->addStrength(utility);
		}
		else if (rel_type == BAFF)
		{
			other_hero->rel[curr_hero->name]->addAffinity(-utility);
		}
		else if (rel_type == BNOT)
		{
			other_hero->rel[curr_hero->name]->addNotoriety(-utility);
		}
		else if (rel_type == BSTR)
		{
			other_hero->rel[curr_hero->name]->addStrength(-utility);
		}

		for (auto hero : Containers::hero_table) {
			//check that the hero is not the doer or reciever 
			if (!(hero.second->name == curr_hero->name) && 
				!(hero.second->name == other_hero->name)) {

				//applies relationship updates to other heroes
				/*
				for AFF:
				uses the affinity of the reciever as a magnifier for the
				affinity change EX - if you win a fight:
				reciver: -5 (they like you less)
				Hero who likes the reciver (60aff): ((60-50)/50)*util = 1/5*(-5) = -1
				Hero who dislikes the reciver (40aff): ((40-50)/50)*util = (-1/5)*(-5) = 1
				the second hero actually like you more becaues you beat their enemy
				*/

				//NOT and STR are 1/3 of reciver AFF is a unique equation
				if (rel_type == AFF)
				{
					//get the affinity change using the relationship with reciver "other_hero"
					int aff_change = ((hero.second->rel[other_hero->name]->getAffinity() - 50) / 50) * utility;
					hero.second->rel[curr_hero->name]->addAffinity(std::ceil(aff_change));
				}
				else if (rel_type == NOT)
				{
					hero.second->rel[curr_hero->name]->addNotoriety(std::ceil(utility/3));
				}
				else if (rel_type == STR)
				{
					hero.second->rel[curr_hero->name]->addStrength(std::ceil(utility/3));
				}
				else if (rel_type == BAFF)
				{
					//get the affinity change using the relationship with reciver "other_hero"
					int aff_change = ((hero.second->rel[other_hero->name]->getAffinity() - 50) / 50) * utility;
					hero.second->rel[curr_hero->name]->addAffinity(std::ceil(-aff_change));
				}
				else if (rel_type == BNOT)
				{
					hero.second->rel[curr_hero->name]->addNotoriety(std::ceil(-utility/3));
				}
				else if (rel_type == BSTR)
				{
					hero.second->rel[curr_hero->name]->addStrength(std::ceil(-utility/3));
				}
			}
		}
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

void RelEstimPost::apply_utility(Hero* curr_hero, Hero* other_hero, bool if_doer)
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
StatePost::StatePost(int _utility, int _state_type)
{
	/*state_manager st_man,
	std::string required state,
	std::vectorr<relevant villages>*/
	utility = _utility;
	state_type = _state_type;

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

void StatePost::apply_utility(Hero* curr_hero, Hero* other_hero)
{
	
	if (state_type == ALL)
	{
		//curr_hero and other_hero are put in the same alliance
		Alliance* curr_alliance = curr_hero->getVillage()->get_alliance();
		Alliance* other_alliance = other_hero->getVillage()->get_alliance();
		curr_alliance->add_alliance_to_alliance(other_alliance);
	}
	else if (state_type == OCC)
	{
		//curr_hero is set the conqurer of the other hero
		curr_hero->getVillage()->conquer(other_hero->getVillage());
		War::endWar(curr_hero->getVillage(), other_hero->getVillage());
		std::cout << "OCC";
	}
	
	else if (state_type == CONF)
	{
		War* new_war = new War();
		new_war->setWarParties(curr_hero->getVillage(), other_hero->getVillage());
		std::cout << "CONF";
	}
	
}