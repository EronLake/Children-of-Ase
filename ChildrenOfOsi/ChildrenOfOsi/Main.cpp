//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------

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
#define _CRTDBG_MAP_ALLOC

//toggles debug longging statements 
#define DEBUG 1

#if DEBUG 
#define LOG(input) std::cout << "LOG:" << input << std::endl
#else 
#define LOG(input) 

#endif

using namespace std;


void testQuadTree() {
	Rectangle* testrec = new Rectangle(Vector2f(0.0, 0.0), 100.0, 100.0);	//init screen
	Rectangle* Alex = new Rectangle(Vector2f(51.0,51.0),20.0,20.0);	//init player
	vector<Rectangle*> recVec;	//obj vector

	for (int i = 0; i < 100; i++) {		//init obj vec
		Rectangle* myRec = new Rectangle(Vector2f(rand() % 90, rand() % 90), 10.0, 10.0);
		recVec.push_back(myRec);
	}
	cout << "before making tree\n";

	QuadTree* myTree = new QuadTree(0, testrec);	//init 
	cout << "after making tree\n";
	bool mybool = true;
	while (mybool) {	//tick every frame
		cout << "before clear" << endl;
		myTree->clear();	//clear my tree
		cout << "after clear" << endl;
		for (int i = 0; i < recVec.size(); i++) {
			cout << "before insert" << endl;
			myTree->insert(recVec[i]);	//insert all obj into tree
			cout << "after insert" << endl;
		}
		vector<Rectangle*> collidable;	
		myTree->retrieve(collidable, Alex);	//vector now holds all collidable obj to Alex
		cout << "after retrieve" << endl;
		int count = 0;
		for (int i = 0; i < collidable.size(); i++) {
			count++;
			cout << "this is a collidable obj number " << i << endl;
		}
		cout << "total number of collidable obj is " << count << endl;
		mybool = false;
	}
	system("PAUSE");
}


int main() {
	LOG("Hello world!");
	srand(time(NULL));
	int rInt[10];
	for (int i = 0; i < 10; i++) {
		rInt[i] = rand() % 4 - 1;
	}
	//Factions fac(rInt);
	//Hero person(20,0,true);
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
	//}*/


	//Alex: test QT tomorrow on hero obj, and make QT generic to take in any obj
	testQuadTree();



	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}



