//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------
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
#include "AudioManager.h"
#include "Manager.h"
#include "Movement.h"
#include "RenderHelper.h"
#include "RenderManager.h"
#include <conio.h>
#include "CheckClass.h"

//#include "Pool.h"

#include "fmod.hpp"
#include "SoundSystem.h"
#include "memManager.h"

#define _CRTDBG_MAP_ALLOC

using namespace std;


//void testQuadTree();
//bool checkCollision(WorldObj *recA, WorldObj *recB);	//given two bounding boxes, check if they collide
//bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }		//helper func for checkCollision

void ERONS_LOOP();
void ALESSIO_TEST();
void ALEX_LOOP(QuadTree* _Quadtree);


//void Darion_Ian_Test();

void ANDREWS_TEST();


int main() {
		LOG("Hello world!");

		/************************************************************************************************SET-UP*******************************************************/
		WorldObj* screen = new WorldObj(Vector2f(0.0, 0.0), 960U, 540U);	//init screen

		QuadTree* collideTree = new QuadTree(0, screen);

		/************************************************************************************************TESTING*******************************************************/
		
		
		////pauses the program for viewing
		//system("PAUSE");

		////demonstration of a meory leak
		///*while (true) {
		//	void* a = malloc(64);
		//	delete a;
		//}

		/*Darion Ian Test*/
		//Darion_Ian_Test();
/* ERON */
//		ERONS_LOOP();
		/*ALESSIO*/
		//ALESSIO_TEST();

		/* ALEX */
		//testQuadTree();
		ALEX_LOOP(collideTree);

		


		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtDumpMemoryLeaks();
	                                   

	return 0;
}


//
//void testQuadTree()
//{
//	WorldObj* testrec = new WorldObj(Vector2f(0.0, 0.0), 100.0, 100.0);	//init screen
//	WorldObj* Alex = new WorldObj(Vector2f(51.0, 51.0), 20.0, 20.0);	//init player
//	vector<WorldObj*> recVec;	//obj vector
//
//	for (int i = 0; i < 100; i++) {		//init obj vec
//		WorldObj* myRec = new WorldObj(Vector2f(rand() % 90, rand() % 90), 10.0, 10.0);
//		recVec.push_back(myRec);
//	}
//	//cout << "before making tree\n";
//
//	QuadTree* myTree = new QuadTree(0, testrec);	//init 
//	//cout << "after making tree\n";
//	bool mybool = true;
//	while (mybool) {	//tick every frame
//		//cout << "before clear" << endl;
//		myTree->clear();	//clear my tree
//		//cout << "after clear" << endl;
//		for (int i = 0; i < recVec.size(); i++) {
//			//cout << "before insert" << endl;
//			myTree->insert(recVec[i]);	//insert all obj into tree
//			//cout << "after insert" << endl;
//		}
//		vector<WorldObj*> collidable;
//		myTree->retrieve(collidable, Alex);	//vector now holds all collidable obj to Alex
//		//cout << "after retrieve" << endl;
//		//int count = 0;
//		for (int i = 0; i < collidable.size(); i++) {
//			if (checkCollision(collidable[i], Alex)) {
//				cout << "collision between Alex and obj number " << i << endl;
//				cout << "Alex width and height are " << Alex->getWidth() << ", " << Alex->getHeight() << endl;
//				cout << "obj width and height are " << collidable[i]->getWidth() << ", " << collidable[i]->getHeight() << endl;
//				cout << "Alex's bounds are " << Alex->getX() << ", " << Alex->getY() << endl;
//				cout << "Obj bounds are " << collidable[i]->getX() << ", " << collidable[i]->getY() << endl;
//			}
//		}
//		mybool = false;
//	}
//	system("PAUSE");
//
//}
//
//
//bool checkCollision(WorldObj *recA, WorldObj *recB)
//{
//	bool xCollide = coordOverlap(recA->getX(), recB->getX(), recB->getX() + recB->getWidth()) || coordOverlap(recB->getX(), recA->getX(), recA->getX() + recA->getWidth());
//	bool yCollide = coordOverlap(recA->getY(), recB->getY(), recB->getY() + recB->getHeight()) || coordOverlap(recB->getY(), recA->getY(), recA->getY() + recA->getHeight());
//	return xCollide && yCollide;
//}

void ALESSIO_TEST() {
	srand(time(NULL));
	int rInt[10];
	for (int i = 0; i < 10; i++) {
		rInt[i] = rand() % 4 - 1;
	}
	Factions fac(rInt);
	Hero person2(20, 0, false);
	Texture still2;
	still2.setFile("YemojasHouse.png");
	still2.load();
	still2.setFrames(2);
	person2.sprite.setTexture(&still2);
	Hero person(20, 0, false);
	Texture still;
	still.setFile("phi.png");
	still.load();
	still.setFrames(3);
	person.sprite.setTexture(&still);
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
	person.WorldObj::setWidth(100);
	person.WorldObj::setHeight(100);
	person.setX(10);
	person.setY(300);
	person2.WorldObj::setWidth(960);
	person2.WorldObj::setHeight(540);
	person2.setX(0);
	person2.setY(0);
	
	person.setCollision(true);
	osi::GameWindow::init();
	float z = 0;
	while (osi::GameWindow::isRunning()) {
		person2.WorldObj::drawObj();
		person.WorldObj::drawObj();
		person.WorldObj::shiftX(1);
		person.WorldObj::animateObj();
		//osi::GameWindow::refresh();
		//osi::GameWindow::drawSprite(600+z,150,100,100, "phi.png");
		z += .5;
		//osi::GameWindow::drawSprite(100, 150, 100, 100, "bluewood.jpg");
		osi::GameWindow::refresh();
	}
	osi::GameWindow::terminate();
}

void ALEX_LOOP(QuadTree* _QuadTree) {
	//LOG("Hello world!");

	WorldObj* Alex = new WorldObj(Vector2f(500.0, 100.0), 100.0, 100.0);	//init player
	Texture* playerTexture = new Texture();
	playerTexture->setFile("phi.png");
	playerTexture->load();
	playerTexture->setFrames(1);
	Alex->sprite.setTexture(playerTexture);
	Alex->offsetBody(0, 50, 50, 50, 50);
	vector<WorldObj*> recVec;	

	for (int i = 1; i < 5; i++) {
		WorldObj* objs = new WorldObj(Vector2f(100 * i , 100 * i ), 200.0, 200.0);
		objs->sprite.setTexture(playerTexture);
		objs->offsetBody(0, 50, 50, 50, 50);
		recVec.push_back(objs);
	}
	//recVec.push_back(myRec1); recVec.push_back(myRec2);

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

	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);
	Input* iController = new Input(gameplay_functions, Alex);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree);
	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree);
	//memManager* memM = new memManager(mLog, tBuffer);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	//memM->register_manager();
	RenM->register_manager();


	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;

/*	Alex->WorldObj::setWidth(100);
	Alex->WorldObj::setHeight(100);
	Alex->setX(100);
	Alex->setY(100);*/

	osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	while (osi::GameWindow::isRunning()) {
		_QuadTree->clear();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->insert(recVec[i]);	//insert all obj into tree
		}
		//clock 
		iController->InputCheck();
		Alex->WorldObj::drawObj();
		for (int i = 0; i < recVec.size(); i++) {
			recVec[i]->drawObj();
		}
		//Alex->WorldObj::animateObj();
		osi::GameWindow::refresh();
		//draw
		//gameplay_functions->draw_frame(Alex);
		//run task buffer
		tBuffer->run();

		
	}
	osi::GameWindow::terminate();
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

	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);
	Input* iController = new Input(gameplay_functions);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog,tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer);
	memManager* memM = new memManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();
	AudM->register_manager();
	


	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;



	while (true) {
		//clock 
		iController->InputCheck();
		tBuffer->run();
		//draw
	}
}
 /*
void Darion_Ian_Test() {
	MemoryPool* hero_pool = create_pool(2048);
	MemNode* head_ptr = init_pool(hero_pool, 32);
	std::cout << std::endl;

	MemNode* m = head_ptr;

	while (m != NULL) {
		std::cout << "Availability:" << m->getAvailability() << std::endl;
		std::cout << "Block Pointer:" << m->getBlockPointer() << std::endl;
		if (m->hasNext() != NULL)
			std::cout << "Next Block:" << m->getNext()->getBlockPointer() << std::endl;
		std::cout << "--------------------" << std::endl;
		m = m->getNext();
	}

	std::cout << hero_pool->num_of_blocks << " Blocks" << std::endl;
	Warrior* myWarrior = new(find_available_block(head_ptr)) Warrior();
	std::cout << "Address of myWarrior:" << myWarrior << std::endl;
	std::cout << "Health:" << myWarrior->health << std::endl;

	Warrior* war = new(find_available_block(head_ptr)) Warrior(775, false, 3.9f, 2.7f);
	war->health = 69;
	std::cout << "Address of war:" << war << std::endl;
	std::cout << "Health:" << war->health << std::endl;

	destroy_pool(hero_pool);
	destroy_MemNode_list(head_ptr);


}
 */
/////////////////////////////////////////////////////////////////
//ERON'S LOOP NO TOUCHY
/////////////////////////////////////////////////////////////////

void ANDREWS_TEST() {
	FMOD::Channel *channels[32]; //all of the channels

	foo::soundType type;
	FMOD::Sound* soundSample;
	const char* name;              //the variables required
	FMOD::Channel* channel;
	bool ispaused;
	unsigned int time;

	// Initialize our sound system
	SoundSystemClass soundsystem;

	type = foo::soundType::music;
	name = "04.wav";
	channel = channels[0];//assign the channel
	ispaused = false;

	soundsystem.createSound(&soundSample, name);// Create the sound
	soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

													 //SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
													 //object stuff


	soundsystem.playSound(soundSample, false, channel, ispaused); 	// Play the sound, with loop mode


	cout << "Press return to quit." << endl;  // Do something meanwhile...
	cin.get();

	soundsystem.releaseSound(soundSample); // Release the sound
}
