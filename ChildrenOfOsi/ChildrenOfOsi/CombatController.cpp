#include "stdafx.h"
#include "CombatController.h"


CombatController::CombatController()
{
}


CombatController::~CombatController()
{
}

void CombatController::update()
{
	for (int i = 0; i < soldiers.size(); i++) {

	}
	for (int i = 0; i < attacks.size(); i++) {
		if (attacks[i]->getPause() == 0) {
			attacks[i]->move();
			if (!attacks[i]->updateDuration()) {
				attacks.erase(attacks.begin() + i);
			}
		} else {
			attacks[i]->updatePause();
			std::cout << "Pause: "<<attacks[i]->getPause() << std::endl;
		}
	}
}

void CombatController::removeAttack(Attack* a) {
	for (auto i = attacks.begin(); i != attacks.end(); ++i) {
		if (*i == a) attacks.erase(i);
	}
}