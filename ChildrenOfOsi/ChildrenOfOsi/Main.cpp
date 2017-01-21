//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------

#include <conio.h>
#include <tchar.h>
#include "Allocation.h"
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

#include "Common.h"
#include <iostream>
#include "Input.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"
#include "DummyController.h"
#include "Manager.h"
#define _CRTDBG_MAP_ALLOC

typedef unsigned char BYTE;

using namespace std;


//void testQuadTree();
//bool checkCollision(Rectangle *recA, Rectangle *recB);	//given two bounding boxes, check if they collide
//bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }		//helper func for checkCollision

void ERONS_LOOP();

class Warrior {
public:
	Warrior(int hp, bool ali, float _x, float _y)
	{
		health = hp;
		alive = ali;
		x = _x;
		y = _y;
	}

	Warrior()
	{
		health = 500;
		alive = true;
		x = 0;
		y = 200;
	}

	int health;
	bool alive;
	float x;
	float y;


};

/**
*   \brief Execute a test on several pool's functionalities.
*/
bool memoryStandardUnitTest(MemoryPool* pool, bool dumpMemoryStates)
{
	// If bounds check is on, we need to alter some math here and there
	bool hasBoundsCheckOn = pool->hasBoundsCheckOn();
	BYTE poolSizeOffset = hasBoundsCheckOn ? 48 : 16;

	// Trash tests -------------------------------------------------------------------------
	// Check trash on creation
	BYTE* ptr = (BYTE*)pool->allocate(1);
	// I read outside the allocated chunk to check the memory creation trashing
	if (*(ptr + 100) != pool->s_trashOnCreation) { return false; }

	// Check trash on alloc
	if (*ptr != pool->s_trashOnAllocSignature) return false;

	// Check trash on Free
	pool->free(ptr);
	if (*ptr != pool->s_trashOnFreeSignature) return false;

	// Full allocation test ----------------------------------------------------------------
	ptr = (BYTE*)pool->allocate(1024);

	// Not enough memory
	if (ptr != NULL) return false;

	// Now should be fine
	ptr = (BYTE*)pool->allocate(1024 - 16 * 6);
	if (hasBoundsCheckOn && pool->integrityCheck() != true) return false;
	pool->free(ptr);
	if (hasBoundsCheckOn && pool->integrityCheck() != true) return false;

	// Integrity tests ---------------------------------------------------------------------
	// Allocate some memory
	BYTE* block[4];
	block[0] = (BYTE*)pool->allocate(140);
	block[1] = (BYTE*)pool->allocate(70);
	block[2] = (BYTE*)pool->allocate(16);
	block[3] = (BYTE*)pool->allocate(1);

	if (hasBoundsCheckOn)
	{
		// Copy several bytes around
		memset(block[0], 65, 140);
		memset(block[1], 67, 70);
		memset(block[2], 69, 8);
		memset(block[2] + 8, 70, 8);
		*block[3] = 'A';

		// This copy is fine, lets check this
		if (pool->integrityCheck() != true) return false;

		// Copy some bytes around stomping over a block
		memset(block[0], 65, 141);

		// This copy is wrong, integrity check must detect this
		if (pool->integrityCheck() != false) return false;

		//Lets fix the memory
		memset(block[0] + 140, '[', 1);

		// This copy is fine, lets check this
		if (pool->integrityCheck() != true) return false;
	}

	if (dumpMemoryStates)
		MemoryPoolManager::it().dumpPool("severalAllocations_", pool);

	pool->free(block[0]);
	pool->free(block[1]);
	pool->free(block[2]);
	pool->free(block[3]);

	// This copy is fine, lets check this
	if (pool->getFreePoolSize() != pool->getTotalPoolSize() - poolSizeOffset) return false;

	// Sparse allocation deallocation --------------------------------------------------------
	// Allocate some memory
	block[0] = (BYTE*)pool->allocate(512);
	block[1] = (BYTE*)pool->allocate(128);
	block[2] = (BYTE*)pool->allocate(64);
	block[3] = (BYTE*)pool->allocate(8);

	// This copy is fine, lets check this
	if (pool->integrityCheck() != true) return false;

	pool->free(block[0]);
	if (hasBoundsCheckOn && pool->integrityCheck() != true) return false;
	pool->free(block[2]);
	if (hasBoundsCheckOn && pool->integrityCheck() != true) return false;
	pool->free(block[3]);
	if (hasBoundsCheckOn && pool->integrityCheck() != true) return false;
	pool->free(block[1]);
	if (hasBoundsCheckOn && pool->integrityCheck() != true) return false;

	block[0] = (BYTE*)pool->allocate(128);
	block[1] = (BYTE*)pool->allocate(128);
	block[2] = (BYTE*)pool->allocate(128);
	pool->free(block[1]);
	block[1] = (BYTE*)pool->allocate(64);
	block[3] = (BYTE*)pool->allocate(64);
	pool->free(block[2]);
	block[2] = (BYTE*)pool->allocate(150);

	if (dumpMemoryStates)
		MemoryPoolManager::it().dumpPool("sparseAllocations_", pool);

	pool->free(block[0]);
	pool->free(block[1]);
	pool->free(block[2]);
	pool->free(block[3]);

	// This copy is fine, lets check this
	if (hasBoundsCheckOn && pool->integrityCheck() != true) return false;

	if (pool->getFreePoolSize() != pool->getTotalPoolSize() - poolSizeOffset) return false;

	if (dumpMemoryStates)
		MemoryPoolManager::it().dumpPool("allFree_", pool);

	return true;
}

bool memoryObjectStorageTest(MemoryPool* pool, bool dumpMemoryStates)
{
	/*Test that adds 2 Hero objects to the pool HeroPool specified in
	pools.xml file and then deletes both objects from the pool.*/
	Warrior* myWarrior = NEW(POOL("HeroPool")) Warrior(500, true, 5.0, 6.0);
	Warrior* Oshosi = NEW(POOL("HeroPool")) Warrior();
	std::cout << myWarrior->health << std::endl;
	std::cout << myWarrior->alive << std::endl;
	std::cout << myWarrior->x << std::endl;
	std::cout << myWarrior->y << std::endl;

	std::cout << Oshosi->health << std::endl;
	std::cout << Oshosi->alive << std::endl;
	std::cout << Oshosi->x << std::endl;
	std::cout << Oshosi->y << std::endl;
	std::cout << myWarrior << std::endl;
	std::cout << Oshosi << std::endl;

	//DELETE(POOL("HeroPool"), myWarrior);
	//DELETE(POOL("HeroPool"), Oshosi);
	if (dumpMemoryStates)
		MemoryPoolManager::it().dumpPool("allFree_", pool);
	return true;
}

int main(int argc, _TCHAR* argv[]) {
	bool want = false;
	if (want) {
		LOG("Hello world!");
		srand(time(NULL));
		int rInt[10];
		for (int i = 0; i < 10; i++) {
			rInt[i] = rand() % 4 - 1;
		}
		Factions fac(rInt);
		Hero person(20, 0, true);

		ERONS_LOOP();
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
	}
	bool dumpMemoryStates = true;

	if (!memoryStandardUnitTest(POOL("TestPool"), dumpMemoryStates))              printf("Memory test on TestPool failed\n");
	else                                                                            printf("Memory test on TestPool succeeded\n");




	if (!memoryStandardUnitTest(POOL("BoundedTestPool"), dumpMemoryStates))         printf("Memory test on BoundedTestPool failed\n");
	else                                                                            printf("Memory test on BoundedTestPool succeeded\n");

	if (!memoryObjectStorageTest(POOL("HeroPool"), dumpMemoryStates))               printf("Memory test on HeroPool failed\n");
	else                                                                            printf("Memory test on HeroPool succeeded\n");

	_getch();

	return 0;
}


void testQuadTree()
{
	Rectangle* testrec = new Rectangle(Vector2f(0.0, 0.0), 100.0, 100.0);	//init screen
	Rectangle* Alex = new Rectangle(Vector2f(51.0, 51.0), 20.0, 20.0);	//init player
	vector<Rectangle*> recVec;	//obj vector

	for (int i = 0; i < 100; i++) {		//init obj vec
		Rectangle* myRec = new Rectangle(Vector2f(rand() % 90, rand() % 90), 10.0, 10.0);
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
		vector<Rectangle*> collidable;
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



bool checkCollision(Rectangle *recA, Rectangle *recB)
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
