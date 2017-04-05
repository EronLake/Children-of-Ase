#include "stdafx.h"
#include "CombatController.h"


CombatController::CombatController(ChildrenOfOsi* coo)
{
	gameplay_functions=coo;
}


CombatController::~CombatController()
{
}

void CombatController::fight(Soldier* sold1, int state) {
	if (sold1->getCurrentEnemy() != nullptr) {
		if (sold1->getStamina() > 120) {
			sold1->setEvade(false);
		}
		else if (sold1->destination == sold1->getLoc() || sold1->destination == Vector2f(0, 0)) {
			sold1->setEvade(true);
			float x = rand() % 300 + 100;
			int x2 = rand() % 2;
			float y = rand() % 300 + 100;
			int y2 = rand() % 2;
			if (x2 == 0)x = -x;
			if (y2 == 0)y = -y;
			sold1->destination = Vector2f(sold1->getCurrentEnemy()->getX() + x, sold1->getCurrentEnemy()->getY() + y);
			sold1->waypoint = Vector2f(sold1->getCurrentEnemy()->getX() + x, sold1->getCurrentEnemy()->getY() + y);
		}
		// If Soldier has an enemy, move to the enemy and not in evade mode
		if (!sold1->getEvade()) {
			sold1->waypoint = Vector2f(sold1->getCurrentEnemy()->getX(), sold1->getCurrentEnemy()->getY());
			sold1->destination = Vector2f(sold1->getCurrentEnemy()->getX(), sold1->getCurrentEnemy()->getY());

			Soldier* sold2 = sold1->getCurrentEnemy();

			if (dist_by_center(sold1, sold2) < (sold1->body[0].getWidth() / 2 + sold1->melee->getHeight())) {
				sold1->destination = Vector2f(0, 0);
				sold1->waypoint = Vector2f(0, 0);
				sold1->face(sold2);
				if (sold1->getCool()) {
					sold1->meleeAttack();
					gameplay_functions->melee(sold1);
				}
			}
		} // Evade mode
		else {
			if (sold1->destination == Vector2f(-1, -1)) {
				sold1->destination = sold1->getEvadeRange(sold1->getCurrentEnemy());
			}
			if (sold1->getLoc() == sold1->destination) {
				sold1->destination = sold1->getEvadeRange(sold1->getCurrentEnemy());
			}
		}
		move_to_target(sold1, state);
	}
}

void CombatController::follow(Soldier* sold1, int state) {
	Soldier* sold2 = sold1->getCurrentLeader();
	if (sold2==nullptr)return;
	if (dist_by_center(sold1, sold2) > (sold1->body[0].getWidth() * 5)) {
		sold1->waypoint = Vector2f(sold2->body[0].getX(), sold2->body[0].getY());
		sold1->destination = Vector2f(sold2->body[0].getX(), sold2->body[0].getY());
	}
	if (dist_by_center(sold1,sold2)<(sold1->body[0].getWidth()*3)) {
		sold1->destination = Vector2f(0, 0);
		sold1->waypoint = Vector2f(0, 0);
		gameplay_functions->stop(sold1);
	}
	move_to_target(sold1,state);
}

void CombatController::find_closest_enemy(Soldier* sold1, int state) {
	vector<Party*> evil = sold1->getParty()->getCurrentEnemies();
	float least_distance = -1;
	Soldier* sold2;
	for (auto i = evil.begin(); i != evil.end(); ++i) {
		vector<Soldier*> tempEvil = (*i)->getMembers();
		for (auto it = tempEvil.begin(); it != tempEvil.end(); ++it) {
			if (least_distance == -1 || dist_by_center(sold1, *it)<least_distance) {
				least_distance = dist_by_center(sold1, *it);
				if (least_distance <= 1000) {
					sold1->setCurrentEnemy(*it);
				} else sold1->setCurrentEnemy(nullptr);
			}
		}
	}
}

void CombatController::update_soldier(Soldier* sold1, int state) {
	sold1->updateCD();
	if (sold1->getInCombat()) {
		if (sold1->getCurrentEnemy() == nullptr) {
			find_closest_enemy(sold1, state);
		} 
		if (sold1->getCurrentEnemy() != nullptr) {
			if (dist_by_center(sold1, sold1->getCurrentEnemy()) > 1000) {
				find_closest_enemy(sold1, state);
				if (sold1->getCurrentEnemy() == nullptr) {
					follow(sold1, state);
				}
				else fight(sold1, state);
			}
			else fight(sold1, state);
		} else follow(sold1, state);
	}
	else {
		follow(sold1, state);
	}
}

void CombatController::move_to_target(Soldier* sold1, int state) {
	if (sold1->destination != Vector2f(0, 0)) { //Hero has a destination
		if (sold1->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
			gameplay_functions->move_toward(sold1); //Take a step towards the current waypoint
		}
		else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
		{
			gameplay_functions->get_path(sold1); //Generate waypoints to destination
		}
	}
}

float CombatController::dist_by_center(Soldier* sold1, Soldier* sold2) {
	float a = ((sold1->body[0].getX() + (sold1->body[0].getWidth() / 2)) - (sold2->body[0].getX() + (sold2->body[0].getWidth() / 2)));
	float b= ((sold1->body[0].getY() + (sold1->body[0].getHeight() / 2)) - (sold2->body[0].getY() + (sold2->body[0].getHeight() / 2)));
	float c = sqrt(a*a + b*b);
	return c;
}

void CombatController::checkParties() {
	for (auto i = Village::villagesWorld.begin(); i != Village::villagesWorld.end(); ++i) {
		vector<Village*> warVils = (*i)->get_alliance()->get_enemy_villages();
		for (auto j = warVils.begin(); j != warVils.end();++j) {
			vector<Party*> partiesA=(*i)->getParties();
			vector<Party*> partiesB= (*j)->getParties();
			for (auto a = partiesA.begin(); a != partiesA.end(); ++a) {
				if ((*a)->getMode()!=1 && (*a)->getMode() != 2) {
					for (auto b = partiesB.begin(); b != partiesB.end(); ++b) {
						if ((*a)->getLeader() != nullptr && (*b)->getLeader() != nullptr) {
						if (dist_by_center((*a)->getLeader(), (*b)->getLeader()) < 1000) {
							(*a)->addToCurrentEnemies(*b);
							(*a)->setMode(1);
							vector<Soldier*> mema = (*a)->getMembers();
							for (auto am = mema.begin(); am != mema.end(); ++am) {
								(*am)->setInCombat(true);
							}
							(*b)->addToCurrentEnemies(*a);
							(*b)->setMode(1);
							vector<Soldier*> memb = (*b)->getMembers();
							for (auto bm = memb.begin(); bm != memb.end(); ++bm) {
								(*bm)->setInCombat(true);
							}
						}
					}
				}
			}
		}
	}
}
}