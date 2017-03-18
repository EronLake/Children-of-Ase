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
	if (enemyVec.empty()) sold1->setEvade(true);
	while(sold1->getCurrentEnemy() == nullptr){
		//if discovered Alex, set silverSoldier combat mode to 0(attack).
		auto it =enemyVec[rand() % enemyVec.size()];
		if (it != sold1) {
			//cout << "*************************************FOUND ENEMY****************************************" << endl;
			//silverSoldier->setMode(0);
			sold1->setEvade(false);
			sold1->setCurrentEnemy(it);
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

	if (sold1->getCool()) {
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
		sold1->destination = Vector2f(sold1->getCurrentEnemy()->getX() + x, sold1->getCurrentEnemy()->getY() + y);
		sold1->waypoint = Vector2f(sold1->getCurrentEnemy()->getX() + x, sold1->getCurrentEnemy()->getY() + y);
	}

	//if OS has an enemy, move to the enemy
	if (sold1->getCurrentEnemy() != nullptr && !sold1->getEvade()) {//&& silverSoldier->destination != Vector2f(0,0)) {
		//cout << "*************************************************MOVING TO ENEMY******************************************" << endl;

		sold1->waypoint = Vector2f(sold1->getCurrentEnemy()->getX() + (sold1->getCurrentEnemy()->getWidth() / 4), sold1->getCurrentEnemy()->getY() + (sold1->getCurrentEnemy()->getHeight() / 4));
		sold1->destination = Vector2f(sold1->getCurrentEnemy()->getX() + (sold1->getCurrentEnemy()->getWidth() / 4), sold1->getCurrentEnemy()->getY() + (sold1->getCurrentEnemy()->getHeight() / 4));

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
		}*/

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
	}

	////evade mode
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

void CombatController::follow(Soldier* sold1, int state) {
	Soldier* sold2 = sold1->getCurrentLeader();
	if (sold2==nullptr)return;
	sold1->waypoint = Vector2f(sold2->body[0].getX() + (sold2->body[0].getWidth() / 2), sold2->body[0].getY() + (sold2->body[0].getHeight() / 2));
	sold1->destination = Vector2f(sold2->body[0].getX() + (sold2->body[0].getWidth() / 2), sold2->body[0].getY() + (sold2->body[0].getHeight() / 2));

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
	if (distBetween(sold1,sold2)<(sold1->body[0].getWidth()*3)) {
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

float CombatController::distBetween(Soldier* sold1, Soldier* sold2) {
	float a = (sold1->body[0].getX() + (sold1->body[0].getWidth() / 2) - sold2->body[0].getX() + (sold2->body[0].getWidth() / 2));
	float b= (sold1->body[0].getY() + (sold1->body[0].getHeight() / 2) - sold2->body[0].getY() + (sold2->body[0].getHeight() / 2));
	float c = sqrt(a*a + b*b);
	return c;
}
