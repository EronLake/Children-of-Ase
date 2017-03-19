#include "stdafx.h"
#include "CombatController.h"


CombatController::CombatController(ChildrenOfOsi* coo)
{
	gameplay_functions=coo;
}


CombatController::~CombatController()
{
}

void CombatController::update()
{
	for (int i = 0; i < soldiers.size(); i++) {

	}
}

void CombatController::fight(Soldier* sold1, int state) {
	if (sold1->getInCombat()) {
		if (sold1->getCurrentEnemy() == nullptr) {
			//if discovered Alex, set silverSoldier combat mode to 0(attack).
			vector<Party*> evil = sold1->getParty()->getCurrentEnemies();
			float leastDist=-1;
			Soldier* sold2;
			for (auto i = evil.begin(); i != evil.end(); ++i) {
				vector<Soldier*> tempEvil = (*i)->getMembers();
				for (auto it = tempEvil.begin(); it != tempEvil.end(); ++it) {
					if (leastDist==-1 || dist_by_center(sold1,*it)<leastDist) {
						sold1->setEvade(false);
						sold1->setCurrentEnemy(*it);
						leastDist = dist_by_center(sold1, *it);
					}
				}
			}
		}
		/*for (auto it : enemyVec) {
			//if discovered Alex, set silverSoldier combat mode to 0(attack).
			if (sold1->getCurrentEnemy() != nullptr) break;
			if (it != sold1) {
				//cout << "*************************************FOUND ENEMY****************************************" << endl;
				//silverSoldier->setMode(0);
				sold1->setEvade(false);
				sold1->setCurrentEnemy(it);
				break;
			}
		}*/
		if (sold1->getCurrentEnemy() != nullptr) {
			if (sold1->getStamina()>sold1->melee->getStaminaCost()) {
				sold1->setEvade(false);
			}
			else if (sold1->destination == sold1->getLoc() || sold1->destination == Vector2f(0, 0)) {
				sold1->setEvade(true);
				//silverSoldier->waypoint = Vector2f(-1, -1);
				float x = rand() % 300 + 100;
				int x2 = rand() % 2;
				float y = rand() % 300 + 100;
				int y2 = rand() % 2;
				if (x2 == 0)x = -x;
				if (y2 == 0)y = -y;
				cout << "GEY Y () RETURNS ******* " << (sold1->getCurrentEnemy()) << endl;
				sold1->destination = Vector2f(sold1->getCurrentEnemy()->getX() + x, sold1->getCurrentEnemy()->getY() + y);
				sold1->waypoint = Vector2f(sold1->getCurrentEnemy()->getX() + x, sold1->getCurrentEnemy()->getY() + y);
			}

		}

		// If Soldier has an enemy, move to the enemy and not in evade mode
		if (sold1->getCurrentEnemy() != nullptr && !sold1->getEvade()) {//&& silverSoldier->destination != Vector2f(0,0)) {
			std::cout << "*************************************************MOVING TO ENEMY******************************************" << endl;

			sold1->waypoint = Vector2f(sold1->getCurrentEnemy()->getX() /*+ (sold1->getCurrentEnemy()->getWidth() / 4)*/, sold1->getCurrentEnemy()->getY() /*+ (sold1->getCurrentEnemy()->getHeight() / 4)*/);
			sold1->destination = Vector2f(sold1->getCurrentEnemy()->getX() /*+ (sold1->getCurrentEnemy()->getWidth() / 4)*/, sold1->getCurrentEnemy()->getY() /*+ (sold1->getCurrentEnemy()->getHeight() / 4)*/);

			Soldier* sold2 = sold1->getCurrentEnemy();
			std::cout << dist_by_center(sold1, sold2) << std::endl;

			if (dist_by_center(sold1, sold2) < (sold1->body[0].getWidth() / 2 + sold1->melee->getHeight())) {
				sold1->destination = Vector2f(0, 0);
				sold1->waypoint = Vector2f(0, 0);
				//gameplay_functions->stop(sold1);
				sold1->face(sold2);
				if (sold1->getCool()) {
					std::cout << "Pressed F" << std::endl;
					//gameplay_functions->special(silverSoldier, 0);
					sold1->meleeAttack();
					gameplay_functions->melee(sold1);
					// Why are we setting currentEnemy to nullptr here?
					sold1->setCurrentEnemy(nullptr);
				}
			}
			/*
					vector<Vector2f> dirs;

					dirs.push_back( { sold1->waypoint.getXloc() - 30, sold1->waypoint.getYloc() - 80 });
					dirs.push_back({ sold1->waypoint.getXloc() - 30, sold1->waypoint.getYloc() + 30 });
					dirs.push_back({ sold1->waypoint.getXloc() - 80, sold1->waypoint.getYloc() - 30 });
					dirs.push_back({ sold1->waypoint.getXloc() + 30, sold1->waypoint.getYloc() - 30 });

					float smallest = -1;
					int small;
					for (int i = 0; i < dirs.size(); i++) {
						float x = dirs[i].getXloc() - sold1->getX();
						float y = dirs[i].getYloc() - sold1->getY();
						float dist = sqrt(x*x + y*y);
						if (smallest == -1 || dist < smallest) {
							smallest = dist;
							small = i;
						}
					}

					sold1->waypoint = dirs[small];
					sold1->destination = dirs[small];

					//enemy is facing up
				/*	if (sold1->getCurrentEnemy()->getDirection() == 8) {

						sold1->waypoint.shiftYloc(-80);
						sold1->destination.shiftYloc(-80);
						sold1->waypoint.shiftXloc(-30);
						sold1->destination.shiftXloc(-30);

						//enemy is facing right
					}
					else if (sold1->getCurrentEnemy()->getDirection() == 6) {

						sold1->waypoint.shiftXloc(30);
						sold1->destination.shiftXloc(30);
						sold1->waypoint.shiftYloc(-30);
						sold1->destination.shiftYloc(-30);
					}
					//enemy is facing left
					else if (sold1->getCurrentEnemy()->getDirection() == 4) {
						sold1->waypoint.shiftXloc(-80);
						sold1->destination.shiftXloc(-80);
						sold1->waypoint.shiftYloc(-30);
						sold1->destination.shiftYloc(-30);
					}
					//enemy is facing down
					else if (sold1->getCurrentEnemy()->getDirection() == 2) {
						sold1->waypoint.shiftYloc(30);
						sold1->destination.shiftYloc(30);
						sold1->waypoint.shiftXloc(-30);
						sold1->destination.shiftXloc(-30);
					}// /

					//gameplay_functions->move_toward(silverSoldier);

					//npc is at enemy destination, attack.
					if (sold1->destination == sold1->getLoc()) {
						sold1->face(sold1->getCurrentEnemy());
						//cout << "COOL DOWN FOR ATTACK IS " << sold1->getCool() << endl;
						if (sold1->getCool()) {
							//std:://cout << "Pressed F" << std::endl;
							//gameplay_functions->special(silverSoldier, 0);
							sold1->meleeAttack();
							gameplay_functions->melee(sold1);
							sold1->setCurrentEnemy(nullptr);
						}


					}
			*/
		}

		// Evade mode
		if (sold1->getCurrentEnemy() != nullptr && sold1->getEvade()) {//&& silverSoldier->destination != Vector2f(0, 0)) {
																	   //if OS is in evade mode, use the getEvadeRange method to find the waypoint and set it to destination
			if (sold1->destination == Vector2f(-1, -1)) {
				//cout << "****INSIDE THE EVADE MODE SETTER*****" << endl;
				//silverSoldier->waypoint = silverSoldier->getEvadeRange(silverSoldier->getCurrentEnemy());
				sold1->destination = sold1->getEvadeRange(sold1->getCurrentEnemy());
				//cout << "shango waypoint is " << sold1->waypoint.getXloc() << sold1->waypoint.getYloc() << endl;
			}
			//if reached destination, strafe left or right
			if (sold1->getLoc() == sold1->destination) {
				//cout << "******* INSIDE THE EVADE MODE STRAFE *******" << endl;
				//silverSoldier->waypoint = silverSoldier->getStrafeLocation(silverSoldier->getCurrentEnemy());
				sold1->destination = sold1->getEvadeRange(sold1->getCurrentEnemy());
			}
			/*if (silverSoldier->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
			gameplay_functions->move_toward(silverSoldier); //Take a step towards the current waypoint
			//	//std:://cout << "Request a step" << std::endl;
			}
			else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
			{
			gameplay_functions->get_path(silverSoldier); //Generate waypoints to destination
			}/**/
			//gameplay_functions->move_toward(silverSoldier);
		}
		//	ai->graph.insert(silverSoldier->destination);
		//ai->graph.insert(silverSoldier->getLoc());
		if (sold1->destination != Vector2f(0, 0)) { //Hero has a destination
			if (sold1->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
				gameplay_functions->move_toward(sold1); //Take a step towards the current waypoint
														//	//std:://cout << "Request a step" << std::endl;
			}
			else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
			{
				gameplay_functions->get_path(sold1); //Generate waypoints to destination
			}
		}
		else {

		}
	}
}

void CombatController::follow(Soldier* sold1, int state) {
	Soldier* sold2 = sold1->getCurrentLeader();
	if (sold2==nullptr)return;
	if (dist_by_center(sold1, sold2) > (sold1->body[0].getWidth() * 5)) {
		sold1->waypoint = Vector2f(sold2->body[0].getX(), sold2->body[0].getY());
		sold1->destination = Vector2f(sold2->body[0].getX(), sold2->body[0].getY());
	}
	/*//enemy is facing up
	if (sold1->getCurrentEnemy()->getDirection() == 2) {

		sold1->waypoint.shiftYloc(-100);
		sold1->destination.shiftYloc(-100);
		sold1->waypoint.shiftXloc(-30);
		sold1->destination.shiftXloc(-30);

		//enemy is facing right
	}
	else if (sold1->getCurrentEnemy()->getDirection() == 4) {

		sold1->waypoint.shiftXloc(60);
		sold1->destination.shiftXloc(60);
		sold1->waypoint.shiftYloc(-30);
		sold1->destination.shiftYloc(-30);
	}
	//enemy is facing left
	else if (sold1->getCurrentEnemy()->getDirection() == 6) {
		sold1->waypoint.shiftXloc(-100);
		sold1->destination.shiftXloc(-100);
		sold1->waypoint.shiftYloc(-30);
		sold1->destination.shiftYloc(-30);
	}
	//enemy is facing down
	else if (sold1->getCurrentEnemy()->getDirection() == 8) {
		sold1->waypoint.shiftYloc(60);
		sold1->destination.shiftYloc(60);
		sold1->waypoint.shiftXloc(-30);
		sold1->destination.shiftXloc(-30);
	}*/
	if (dist_by_center(sold1,sold2)<(sold1->body[0].getWidth()*3)) {
		sold1->destination = Vector2f(0, 0);
		sold1->waypoint = Vector2f(0, 0);
		gameplay_functions->stop(sold1);
	}
	if (sold1->destination != Vector2f(0, 0)) { //Hero has a destination
		if (sold1->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
			gameplay_functions->move_toward(sold1); //Take a step towards the current waypoint
													//	//std:://cout << "Request a step" << std::endl;
		}
		else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
		{
			gameplay_functions->get_path(sold1); //Generate waypoints to destination
		}
	}
}

float CombatController::dist_by_center(Soldier* sold1, Soldier* sold2) {
	//std::cout << "Soldier: " <<
  cout << "* * * * * * * * * * Soldier1 physics body length: " << sold1->body.size() << " * * * * * * * * * *" << endl;
  cout << "* * * * * * * * * * Address of Soldier 2: " << sold2 << endl;
  cout << "* * * * * * * * * * Soldier2 physics body length: " << sold2->body.size() << " * * * * * * * * * *" << endl;
	float a = ((sold1->body[0].getX() + (sold1->body[0].getWidth() / 2)) - (sold2->body[0].getX() + (sold2->body[0].getWidth() / 2)));
	float b= ((sold1->body[0].getY() + (sold1->body[0].getHeight() / 2)) - (sold2->body[0].getY() + (sold2->body[0].getHeight() / 2)));
	float c = sqrt(a*a + b*b);
	return c;
}

void CombatController::checkParties() {
	for (auto i = Village::villagesWorld.begin(); i != Village::villagesWorld.end(); ++i) {
		vector<Village*> warVils = War::getWars(*i);
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