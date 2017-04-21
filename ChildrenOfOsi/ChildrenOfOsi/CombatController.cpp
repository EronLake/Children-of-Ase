#include "stdafx.h"
#include "CombatController.h"

std::mutex mux;

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
					//std::lock_guard<std::mutex> guard(mux);
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
		//std::lock_guard<std::mutex> guard(mux);
		move_to_target(sold1, state);
	}
}

void CombatController::follow(Soldier* sold1, int state) {
	Soldier* sold2 = sold1->getCurrentLeader();
	if (sold2 == nullptr) {
		//std::lock_guard<std::mutex> guard(mux);
		party_leader_update(sold1,state);
		////std:://cout << sold1->getID()<<" update leader" << std::endl;
		return;
	}
	if (dist_by_center(sold1, sold2) > (sold1->body[0].getWidth() * 6)) {
		sold1->waypoint = Vector2f(sold2->body[0].getX(), sold2->body[0].getY());
		sold1->destination = Vector2f(sold2->body[0].getX(), sold2->body[0].getY());
	}
	if (dist_by_center(sold1,sold2)<(sold1->body[0].getWidth()*3)) {
		sold1->destination = Vector2f(0, 0);
		sold1->waypoint = Vector2f(0, 0);
////std:://cout << sold1->getID() << " reached its leader, " << sold2->getID() << std::endl;
	//	std::lock_guard<std::mutex> guard(mux);
		gameplay_functions->stop(sold1);
		return;
	}
	//std::lock_guard<std::mutex> guard(mux);
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
				if (least_distance <= 600) {
					sold1->setCurrentEnemy(*it);
				} else sold1->setCurrentEnemy(nullptr);
			}
		}
	}
}

bool CombatController::find_closest_friend(Soldier* sold1, int state) {
	if (sold1->getCurrentLeader() == nullptr)return false;
	float least_distance = -1;
	Soldier* fr= new Soldier();
	vector<Soldier*> temp_good = sold1->getParty()->getMembers();
	for (auto it = temp_good.begin(); it != temp_good.end(); ++it) {
		if (sold1 != (*it)) {
			if ((least_distance == -1 || dist_by_center(sold1, *it) < least_distance)) {
				least_distance = dist_by_center(sold1, *it);
				fr = (*it);
			}
		}
	}
	if (least_distance <= 30) {
		int x = sold1->getX() - fr->getX();
		int y = sold1->getY() - fr->getY();
		Vector2f tmp(sold1->getX() + x, sold1->getY() + y);
		sold1->destination = tmp;
		sold1->waypoint = tmp;
		return true;
	} else {
		return false;
	}
}

void CombatController::update_soldier(Soldier* sold1, int state) {
	///update cooldowns
	sold1->updateCD();
	if (sold1->getParty() == nullptr || sold1->getParty() == NULL)return;
	if (find_closest_friend(sold1, state)) {
		//std::lock_guard<std::mutex> guard(mux);
		move_to_target(sold1, state);
	}
	else {
		///check if the soldier is supposed to hold position and if they are more than 500 away from the point
		if ((sold1->getHold()) && (dist_soldier_to_location(sold1, sold1->getParty()->get_defend()) > sold1->getParty()->get_def_rad())) {
			sold1->destination = sold1->getParty()->get_defend();
			sold1->waypoint = sold1->getParty()->get_defend();
		//	std::lock_guard<std::mutex> guard(mux);
			move_to_target(sold1, state);
		}
		else {
			///check if the soldier is in combat and not 1000 away from the leader
			//cout << dist_by_center(sold1, sold1->getCurrentLeader()) << endl;
			if ((sold1->getInCombat()) && (dist_by_center(sold1, sold1->getCurrentLeader()) < 600)) {
				///if no enemy find the closest one
				if (sold1->getCurrentEnemy() == nullptr) {
					find_closest_enemy(sold1, state);
				}
				if (sold1->getCurrentEnemy() != nullptr) {
					///if the current enemy is more than 1000 away, try to find another
					if (dist_by_center(sold1, sold1->getCurrentEnemy()) > 600) {
						find_closest_enemy(sold1, state);
						///follow the leader if none
						if (sold1->getCurrentEnemy() == nullptr) {
							follow(sold1, state);
						}
						///fight if there is a valid enemy
						else {
							fight(sold1, state);
						}
					}
					else {
						fight(sold1, state);
					}
				} /// follow the leader if there is no valid enemy or not in combat
				else {
					follow(sold1, state);
				}
			}
			else {
				follow(sold1, state);
			}
		}
	}
}

void CombatController::move_to_target(Soldier* sold1, int state) {
	if (sold1->destination != Vector2f(0, 0)) { //Hero has a destination
		if (sold1->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
			if (sold1->getHold()) {//getMode() == Party::MODE_DEFEND) {
				if (!sold1->getInCombat()) {
					if (dist(sold1->destination, sold1->getParty()->get_defend()) > sold1->getParty()->get_def_rad()) {
						//		//std:://cout << "leader too far" << std::endl;
						sold1->waypoint = sold1->getParty()->get_home();
						sold1->destination = sold1->getParty()->get_home();
						gameplay_functions->stop(sold1);
						return;
					}
				}
			}
			gameplay_functions->move_toward(sold1); //Take a step towards the current waypoint
			////std:://cout << sold1->getID() << " MOVING TOWARDS " << sold1->waypoint.getXloc() << ", " << sold1->waypoint.getYloc() << std::endl;
		}
		else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
		{
		//	//std:://cout << sold1->getID() << " WHERE AM I GOING" << std::endl;
			gameplay_functions->get_path(sold1); //Generate waypoints to destination
		}
	}
}

float CombatController::dist_by_center(Soldier* sold1, Soldier* sold2) {
	if (sold1==nullptr || sold2 == nullptr)return 0;
	float a = ((sold1->body[0].getX() + (sold1->body[0].getWidth() / 2)) - (sold2->body[0].getX() + (sold2->body[0].getWidth() / 2)));
	float b= ((sold1->body[0].getY() + (sold1->body[0].getHeight() / 2)) - (sold2->body[0].getY() + (sold2->body[0].getHeight() / 2)));
	float c = sqrt(a*a + b*b);
	return c;
}

float CombatController::dist_soldier_to_location(Soldier* sold1, Vector2f loc) {
	float a = ((sold1->body[0].getX() + (sold1->body[0].getWidth() / 2)) - (loc.getXloc()));
	float b = ((sold1->body[0].getY() + (sold1->body[0].getHeight() / 2)) - (loc.getYloc()));
	float c = sqrt(a*a + b*b);
	return c;
}

float CombatController::dist(Vector2f start, Vector2f end) {
	float a = (start.getXloc() - end.getXloc());
	float b = (start.getYloc() - end.getYloc());
	float c = sqrt(a*a + b*b);
	return c;
}

void CombatController::checkParties() {
	for (auto i = Village::villagesWorld.begin(); i != Village::villagesWorld.end(); ++i) {
		vector<Village*> warVils = (*i)->get_alliance()->get_enemy_villages();
		for (auto j = warVils.begin(); j != warVils.end(); ++j) {
			vector<Party*> partiesA = (*i)->getParties();
			vector<Party*> partiesB = (*j)->getParties();
			for (auto a = partiesA.begin(); a != partiesA.end(); ++a) {
				if ((*a)->getMembers().size() == 0) {
					if (!(*a)->get_perm()) {
						(*i)->remove_party((*a));
						delete (*a);
					}
				} else if ((*a)->getMode() != Party::MODE_FLEE && !(*a)->getLeader()->getInCombat()) {
					for (auto b = partiesB.begin(); b != partiesB.end(); ++b) {
						if ((*b)->getMembers().size() == 0 ) {
							if (!(*b)->get_perm()) {
								(*j)->remove_party((*b));
								delete (*b);
							}
						} else if (dist_by_center((*a)->getLeader(), (*b)->getLeader()) < 1000) {
							if ((*b)->getMode() != Party::MODE_FLEE) {
								if ((*b)->getLeader()->getInCombat()) {
									(*b)->get_fight()->add_to_attackers((*a));
								} else {
									Fight* fight = new Fight();
									fight->set_loc((*b)->getLeader()->getLoc());
									fight->add_to_attackers((*a));
									fight->add_to_attackers((*b));
								}
							}
						}
					}
				}
			}
		}
	}
	Fight::bring_out_your_dead();
	Fight::update_all_fights();
}

void CombatController::party_leader_update(Soldier* sold1, int state) {
	if (sold1->get_action_destination() != nullptr) {
		if (Party::dist_location_to_location(sold1->getLoc(), *sold1->get_action_destination()) < 500) {
			sold1->set_action_destination(nullptr);
		}
		else {
			Vector2f quest = *sold1->get_action_destination();
			sold1->destination = quest;
			sold1->waypoint = quest;
			move_to_target(sold1, state);
		}
	} else if (sold1->getParty()->getMode() == Party::MODE_PATROL) {
		Vector2f next = sold1->getParty()->get_current_patrol_loc(sold1->getLoc());
		sold1->destination = next;
		sold1->waypoint = next;
		move_to_target(sold1, state);
	} else if (sold1->getParty()->getMode() == Party::MODE_FLEE) {
		Vector2f home = sold1->getParty()->get_home();
		sold1->destination = home;
		sold1->waypoint = home;
		move_to_target(sold1, state);
		if (sold1->destination == Vector2f(0, 0)) {
			sold1->getParty()->setMode(Party::MODE_FLEE);
			if (home == sold1->getParty()->get_village()->get_village_location()) {
				sold1->getParty()->removeSoldier(sold1,false);
				sold1->getParty()->get_village()->barracks->addToParty(sold1,false);
			}
			////std:://cout << sold1->getID() << " is idling now" << std::endl;
		}
	}
}

void CombatController::updateSoliderStatus()
{
	//iterate through the list of party
	for (auto it = Party::partiesWorld.begin(); it != Party::partiesWorld.end(); it++) {
		//for current party, get list of member as a vector of soldier*. Maybe here I am getting a copy of members
		vector<Soldier *> soldiers = (*it)->getMembers();
		for (auto itj = soldiers.begin(); itj != soldiers.end(); itj++) {
			//for each soldier, check to see if its alive. If not, remove from party.
			if ((*itj)->getHealth() <= 0) {
				//cout << "RIGHT BEFORE REMOVING THE NPC WITH LESS THAN 0 HP ******** " << endl;
				(*itj)->getParty()->removeSoldier(*itj, false);
			}
			if ((*itj)->getInCombat() == false) {
				if ((*itj)->getType()== WorldObj::TYPE_PLAYER) break;
				gameplay_functions->stop(*itj);
			}
		}


	}
}

std::thread CombatController::threaded_update_soldier(Soldier* s, int n) {
	return std::thread(&CombatController::update_soldier, this, s, n);
}