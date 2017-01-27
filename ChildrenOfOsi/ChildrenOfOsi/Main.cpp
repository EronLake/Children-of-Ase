//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------
//#include "Allocation.h"
//#include <conio.h>
//#include <tchar.h>
#include "stdafx.h"
#include <stdio.h>   
#include <stdlib.h>     
#include <time.h>
#include "Player.h"
#include "Factions.h"
#include <crtdbg.h>
//#include "Rectangle.h"
#include "QuadTree.h"
#include "GameWindow.h"
#include "common.h"
#include "Input.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"
#include "DummyController.h"
#include "PhysicsManager.h"
#include "Manager.h"
#include "Movement.h"
#include <conio.h>
#include "CheckClass.h"
#define _CRTDBG_MAP_ALLOC

using namespace std;


void testQuadTree();
bool checkCollision(WorldObj *recA, WorldObj *recB);	//given two bounding boxes, check if they collide
bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }		//helper func for checkCollision

void ERONS_LOOP();
void ALESSIO_TEST();
void ALEX_LOOP(QuadTree* _physicsQuadTree, WorldObj* _player, vector<WorldObj*> &_recVec);

int main() {
		LOG("Hello world!");

		/************************************************************************************************SET-UP*******************************************************/
		WorldObj* screen = new WorldObj(Vector2f(0.0, 0.0), 100.0, 100.0);	//init screen
		WorldObj* Alex = new WorldObj(Vector2f(20.0, 20.0), 20.0, 20.0);	//init player
		vector<WorldObj*> recVec;	//obj vector

		//for (int i = 0; i < 2; i++) {		//init obj vec
		//	WorldObj* myRec = new WorldObj(Vector2f(rand() % 90, rand() % 90), 10.0, 10.0);
		//	cout << "X: " << myRec->getX() << ", Y: " << myRec->getY() << endl;
		//	recVec.push_back(myRec);
		//}

		WorldObj* myRec1 = new WorldObj(Vector2f(60, 60), 10.0, 10.0);
		WorldObj* myRec2 = new WorldObj(Vector2f(80, 80), 10.0, 10.0);
		recVec.push_back(myRec1); recVec.push_back(myRec2);

		QuadTree* collideTree = new QuadTree(0, screen);

		/************************************************************************************************TESTING*******************************************************/
		
		
		////pauses the program for viewing
		//system("PAUSE");

		////demonstration of a meory leak
		///*while (true) {
		//	void* a = malloc(64);
		//	delete a;
		//}
		/*ALESSIO*/
		//ALESSIO_TEST();

		/* ALEX */
		ALEX_LOOP(collideTree, Alex, recVec);

		/* ERON */
		ERONS_LOOP();


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

void ALESSIO_TEST() {
	srand(time(NULL));
	int rInt[10];
	for (int i = 0; i < 10; i++) {
		rInt[i] = rand() % 4 - 1;
	}
	Factions fac(rInt);
	Hero person(20, 0, true);
	Texture still;
	still.setFile("img.png");
	Sprite objSpt;
	objSpt.setTexture(&still);
	person.setSprite(objSpt);
	person.drawObj();
	cout <<"Is person an NPC: "<< CheckClass::isNPC(&person) << endl;
	person.setHealth(-10);
	person.setAlive(false);
	cout << "person is " << person.getAlive() << " with " << person.getHealth() << endl;
	cout<<"at location " << person.getX() << " , " << person.getY() << endl;
	Player me(30, 32, true);
	NPC citizen(22, 2, true);
	citizen.setHealth(10);
	citizen.setInteractable(true);
	cout << "Interactable: " << citizen.getInteractable() << endl;
	person.setAtk(2);
	person.setInCombat(true);
	cout <<"In Combat: " <<person.getInCombat()<< endl;
	person.goAtk(&citizen);
	cout << "Citizen's Health: " << citizen.getHealth() << endl;
	cout << "Faction Relationship was: "<<fac.getFRel(citizen.getFaction(), person.getFaction()) << endl;
	fac.setFRel(citizen.getFaction(), person.getFaction(), -1);
	cout << "Faction Relationship now: " << fac.getFRel(citizen.getFaction(), person.getFaction()) << endl;
	citizen.setSpeed(2);
	cout << "Speed: " << citizen.getSpeed() << endl;
	citizen.shiftX(2);
	citizen.shiftY(3);
	citizen.moveUp();
	citizen.moveRight();
	cout << "citizen is now at: " << citizen.getX() << " , " << citizen.getY() << endl;
	Texture test;
	test.setFrames(5);
	test.setFWidth(100);
	Sprite sp;
	sp.setTexture(&test);
	test.setAnimated(true);
	person.setSprite(sp);
	for (int i = 0; i < 20;i++) {
		person.animateObj();
	}
}

void ALEX_LOOP(QuadTree* _physicsQuadTree, WorldObj* _player, vector<WorldObj*> &_recVec) {
	//LOG("Hello world!");

	//pauses the program for viewing
	//system("PAUSE");

	//demonstration of a meory leak
	//while (true) {
	//	void* a = malloc(64);
	//	delete a;
	//}

	//psuedo Gameloop
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);
	Input* iController = new Input(mLog, tBuffer, _player);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _physicsQuadTree);
	DumM->register_manager();
	PhysM->register_manager();


	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;



	while (true) {
		_physicsQuadTree->clear();
		for (int i = 0; i < _recVec.size(); i++) {
			_physicsQuadTree->insert(_recVec[i]);	//insert all obj into tree
		}
		//clock 
		iController->InputCheck();
		tBuffer->run();
		//draw
	}
}

void ERONS_LOOP() {
	/////////////////////////////////////////////////////////////////
	//ERON'S LOOP NO TOUCHY    **** Justin touched it, oops ****
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
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);
	Input* iController = new Input(mLog, tBuffer);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog,tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer);
	DumM->register_manager();
	PhysM->register_manager();


	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;



	while (true) {
		//clock 
		iController->InputCheck();
		tBuffer->run();
		//draw
	}
}
/////////////////////////////////////////////////////////////////
//ERON'S LOOP NO TOUCHY
/////////////////////////////////////////////////////////////////
