//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------
#include "Allocation.h"
#include <conio.h>
#include <tchar.h>
#include <stdio.h>   
#include <stdlib.h>     
#include <time.h>
#include <iostream>
#include "WorldObj.h"
#include "LivingObj.h"
#include "NPC.h"
#include "Soldier.h"
#include "SplSoldier.h"
#include "Hero.h"
#include "Vector2f.h"
#include "Player.h"
#include "Factions.h"
#include <crtdbg.h>
//#include "Rectangle.h"
#include "QuadTree.h"

#include "common.h"
#include <iostream>
#include "Input.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"
#include "DummyController.h"
#include "Manager.h"
#define _CRTDBG_MAP_ALLOC

using namespace std;


void testQuadTree();
bool checkCollision(WorldObj *recA, WorldObj *recB);	//given two bounding boxes, check if they collide
bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }		//helper func for checkCollision

void ERONS_LOOP();

int main() {
		LOG("Hello world!");
		srand(time(NULL));
		int rInt[10];
		for (int i = 0; i < 10; i++) {
			rInt[i] = rand() % 4 - 1;
		}
		Factions fac(rInt);
		Hero person(20, 0, true);
		//Hero* person= NEW(POOL("HeroPool")) Hero(20, 0, true);
		//cout << "It got here" << endl;
		//ERONS_LOOP();
		//person.setHealth(-10);
		//person.setAlive(false);
		//cout << "person is " << person.getAlive() << " with " << person.getHealth() << endl;
		//cout<<"at location " << person.getX() << " , " << person.getY() << endl;
		//Player me(30, 32, true);
		//NPC citizen(22, 2, true);
		//citizen.setHealth(10);
		//citizen.setInteractable(true);
		//cout << "Interactable: " << citizen.getInteractable() << endl;
		//person.setAtk(2);
		//person.setInCombat(true);
		//cout <<"In Combat: " <<person.getInCombat()<< endl;
		//person.goAtk(&citizen);
		//cout << "Citizen's Health: " << citizen.getHealth() << endl;
		//cout << "Faction Relationship was: "<<fac.getFRel(citizen.getFaction(), person.getFaction()) << endl;
		//fac.setFRel(citizen.getFaction(), person.getFaction(), -1);
		//cout << "Faction Relationship now: " << fac.getFRel(citizen.getFaction(), person.getFaction()) << endl;
		//citizen.setSpeed(2);
		//cout << "Speed: " << citizen.getSpeed() << endl;
		//citizen.shiftX(2);
		//citizen.shiftY(3);
		//citizen.moveUp();
		//citizen.moveRight();
		//cout << "citizen is now at: " << citizen.getX() << " , " << citizen.getY() << endl;
		////pauses the program for viewing
		//system("PAUSE");

		////demonstration of a meory leak
		///*while (true) {
		//	void* a = malloc(64);
		//	delete a;
		//}


		//Alex: test QT tomorrow on hero obj, and make QT generic to take in any obj
		testQuadTree();

		//Texture test;
		//test.setFrames(5);
		//test.setFWidth(100);
		//Sprite sp;
		//sp.setTexture(&test);
		//test.setAnimated(true);
		//person.setSprite(sp);
		//for (int i = 0; i < 20;i++) {
		//	person.animateObj();
		//}
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtDumpMemoryLeaks();
	                                                                       

	return 0;
}


void testQuadTree()
{
	WorldObj* testrec = new WorldObj(Vector2f(0.0, 0.0), 100.0, 100.0);	//init screen
	WorldObj* Alex = new WorldObj(Vector2f(51.0, 51.0), 20.0, 20.0);	//init player
	vector<WorldObj*> recVec;	//obj vector

	for (int i = 0; i < 100; i++) {		//init obj vec
		WorldObj* myRec = new WorldObj(Vector2f(rand() % 90, rand() % 90), 10.0, 10.0);
		recVec.push_back(myRec);
	}
	//cout << "before making tree\n";

	QuadTree* myTree = new QuadTree(0, testrec);	//init 
	//cout << "after making tree\n";
	bool mybool = true;
	while (mybool) {	//tick every frame
		//cout << "before clear" << endl;
		myTree->clear();	//clear my tree
		//cout << "after clear" << endl;
		for (int i = 0; i < recVec.size(); i++) {
			//cout << "before insert" << endl;
			myTree->insert(recVec[i]);	//insert all obj into tree
			//cout << "after insert" << endl;
		}
		vector<WorldObj*> collidable;
		myTree->retrieve(collidable, Alex);	//vector now holds all collidable obj to Alex
		//cout << "after retrieve" << endl;
		//int count = 0;
		for (int i = 0; i < collidable.size(); i++) {
			if (checkCollision(collidable[i], Alex)) {
				cout << "collision between Alex and obj number " << i << endl;
				cout << "Alex width and height are " << Alex->getWidth() << ", " << Alex->getHeight() << endl;
				cout << "obj width and height are " << collidable[i]->getWidth() << ", " << collidable[i]->getHeight() << endl;
				cout << "Alex's bounds are " << Alex->getX() << ", " << Alex->getY() << endl;
				cout << "Obj bounds are " << collidable[i]->getX() << ", " << collidable[i]->getY() << endl;
			}
		}
		mybool = false;
	}
	system("PAUSE");

}



bool checkCollision(WorldObj *recA, WorldObj *recB)
{
	bool xCollide = coordOverlap(recA->getX(), recB->getX(), recB->getX() + recB->getWidth()) || coordOverlap(recB->getX(), recA->getX(), recA->getX() + recA->getWidth());
	bool yCollide = coordOverlap(recA->getY(), recB->getY(), recB->getY() + recB->getHeight()) || coordOverlap(recB->getY(), recA->getY(), recA->getY() + recA->getHeight());
	return xCollide && yCollide;
}


void ERONS_LOOP() {
	/////////////////////////////////////////////////////////////////
	//ERON'S LOOP NO TOUCHY
	/////////////////////////////////////////////////////////////////
	LOG("Hello world!");

	//pauses the program for viewing
	system("PAUSE");

	//demonstration of a meory leak
	//while (true) {
	//	void* a = malloc(64);
	//	delete a;
	//}

	//psuedo Gameloop
	Input* iController = new Input();
	TaskBuffer* tBuffer = new TaskBuffer();
	MessageLog* mLog = new MessageLog();

	//create Managers and add to Manager table

	DummyController* DumM = new DummyController();

	std::unordered_map<std::string, Manager*> manager_table;

	manager_table["DumM"] = DumM;



	while (true) {
		//clock 
		iController->InputCheck(tBuffer, mLog);
		tBuffer->run(mLog, manager_table);
	}
}
/////////////////////////////////////////////////////////////////
//ERON'S LOOP NO TOUCHY
/////////////////////////////////////////////////////////////////
