#include "stdafx.h"
#include "PlayerActExecFunctions.h"


PlayerActExecFunctions::PlayerActExecFunctions()
{
}


PlayerActExecFunctions::~PlayerActExecFunctions()
{
}

/*
void ActionExecFunctions::execute_train(Action* train) {

	ActionHelper::create_memory(train, train->getDoer());
}


void ActionExecFunctions::execute_train(Action* train) {
		
			Memory* doer_mem = train->getDoer()->find_mem(train->getName() + std::to_string(train->time_stamp));
			//Memory* receiver_mem = fight->getReceiver()->find_mem(fight->getName() + std::to_string(fight->time_stamp));
			if (doer_mem == nullptr)
			{
				perror("something is wrong with the current hero memory creation function");
			}
			train->getDoer()->set_action_destination(&train->getDoer()->getVillage()->get_village_location()); //Also predefined, maybe as "home_location" in hero
			train->apply_postconditions(true);				 //Apply post-conditions
			train->executed = true;
			doer_mem->setCategory("success");			 //Call update_memory function
			doer_mem->setReason("I am good at training");
			doer_mem->setWhen(/*get global frame0);
		}
		break;

	}
}
*/