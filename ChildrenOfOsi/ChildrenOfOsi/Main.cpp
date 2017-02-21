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
#include "TaskBufferTestSuite.h"
#include <Windows.h>
//#include "DialogueGui.h"

//#include "Pool.h"

#include "fmod.hpp"
#include "SoundSystem.h"
#include "memManager.h"

#include "MemoryTestSuite.h"
#include "AudioTestSuite.h"

#include "TestManager.h"
#include "PhysicsTestSuite.h"
#include <ctime> 

#include "DialogueController.h"
#include "DialogueHelper.h"
#include "DialougeTestSuite.h"

using namespace std;



//void testQuadTree();
//bool checkCollision(WorldObj *recA, WorldObj *recB);	//given two bounding boxes, check if they collide
//bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }		//helper func for checkCollision

void ERONS_LOOP();
void ALESSIO_TEST();
void ALEX_LOOP(QuadTree* _Quadtree);
void ANDREWS_LOOP(QuadTree* _QuadTree);
void FPS(bool b);
void GAMEPLAY_LOOP(QuadTree* _Quadtree);

//bool collide(WorldObj* recA, WorldObj* recB);
//void Darion_Ian_Test();

void ANDREWS_TEST();
void PHYSICS_TEST();


int main() {

	    //DialogueHelper* dhelper = new DialogueHelper();
		//dhelper->get_dialog("Yemoja");
		//LOG("Hello world!");
		//ERONS_LOOP();
		/************************************************************************************************SET-UP*******************************************************/
		WorldObj* screen = new WorldObj(Vector2f(0.0, 0.0), 960U, 540U);	//init screen

		QuadTree* collideTree = new QuadTree(0, screen);

		/************************************************************************************************TESTING*******************************************************/
		
		osi::GameWindow::init();
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
		//ERONS_LOOP();
		/*ALESSIO*/
		//ALESSIO_TEST();

		/* ALEX */
		//ALEX_LOOP(collideTree);
		//ANDREWS_LOOP(collideTree);

		

	                                   
		//testQuadTree();
		//ALEX_LOOP(collideTree);        
		GAMEPLAY_LOOP(collideTree);


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

void GAMEPLAY_LOOP(QuadTree* _QuadTree)
{


	Player* Alex = new Player(SHANGO, Vector2f(1000.0, 600.0), 100.0, 100.0);	//init player
	cout << "Alex's width and height is " << Alex->getWidth() << ", " << Alex->getHeight() << endl;

	//DialogueGui* convoGui = new DialogueGui();

	//Player* Alex = new Player(1000,600, true);	//init player
	//WorldObj* Alex = new WorldObj(1000, 600, true);

	Texture* playerTexture = new Texture();
	Texture* playerIdleTex = new Texture();
	Texture* objTexture = new Texture();
	Texture* upRunTex = new Texture();
	Texture* downRunTex = new Texture();
	Texture* leftRunTex = new Texture();
	Texture* rightRunTex = new Texture();
	Texture* upIdleTex = new Texture();
	Texture* downIdleTex = new Texture();
	Texture* leftIdleTex = new Texture();
	Texture* rightIdleTex = new Texture();

	//load sprite from a configuration file?
	objTexture->setFile("YemojasHouse.png");
	playerTexture->setFile("ShangoFrontIdle.png");
	playerIdleTex->setFile("ShangoFrontIdle.png");
	upRunTex->setFile("ShangoBackSprite.png");
	downRunTex->setFile("ShangoForwardSprite.png");
	leftRunTex->setFile("ShangoLeftSprite.png");
	rightRunTex->setFile("ShangoRightSprite.png");
	upIdleTex->setFile("ShangoBackIdle.png");
	downIdleTex->setFile("ShangoFrontIdle.png");
	leftIdleTex->setFile("ShangoLeftIdle.png");
	rightIdleTex->setFile("ShangoRightIdle.png");

	/* SET UP SPRITE CHANGE, MIGHT NEED A SINGLETON?*/

	playerTexture->load();
	playerIdleTex->load();
	upRunTex->load();
	downRunTex->load();
	leftRunTex->load();
	rightRunTex->load();
	upIdleTex->load();
	downIdleTex->load();
	leftIdleTex->load();
	rightIdleTex->load();
	objTexture->load();
	playerTexture->setFrames(1);
	playerIdleTex->setFrames(1);
	upRunTex->setFrames(26);
	downRunTex->setFrames(26);
	leftRunTex->setFrames(26);
	rightRunTex->setFrames(26);
	upIdleTex->setFrames(1);
	downIdleTex->setFrames(1);
	leftIdleTex->setFrames(1);
	rightIdleTex->setFrames(1);
	objTexture->setFrames(1);
	Alex->sprite.setTexture(playerTexture);
	Alex->sprite.setIdleTexture(playerIdleTex);
	Alex->sprite.up = upRunTex;
	Alex->sprite.down = downRunTex;
	Alex->sprite.left = leftRunTex;
	Alex->sprite.right = rightRunTex;

	Alex->sprite.id_up = upIdleTex;
	Alex->sprite.id_left =leftIdleTex;
	Alex->sprite.id_right = rightIdleTex;
	Alex->sprite.id_down = downIdleTex;


	Alex->offsetBody(0, 50, 50, 50, 50);
	Alex->setInteractable(true);
	Alex->setName("Alex");
	Alex->setTalkDist(20);
	for (int i = 0; i < 100;i++) {
		cout << "NAME " << Alex->name << endl;
	}
	DialogueController::setPlayer(Alex);
	vector<WorldObj*> recVec;

	for (int i = 1; i < 5; i++) {
		WorldObj* objs = new WorldObj(Vector2f(100 * i, 100 * i), 200.0, 200.0);
		objs->sprite.setTexture(objTexture);
		objs->setInteractable(false);
		std::string building="Building ";
		objs->setName(building+= std::to_string(i));
		//objs->offsetBody(0, 50, 50, 50, 50);
		//objs->offsetBody(0, 70, 70, 70, 70);
		recVec.push_back(objs);
	}
	Hero* staticRec = new Hero(YEMOJA,Vector2f(1800, 1350), 100.0, 100.0);
	staticRec->sprite.setTexture(playerTexture);
	staticRec->setName("Yemoja");
	staticRec->setInteractable(true);
	staticRec->sprite.setIdleTexture(playerIdleTex);
	staticRec->sprite.up = upRunTex;
	staticRec->sprite.down = downRunTex;
	staticRec->sprite.left = leftRunTex;
	staticRec->sprite.right = rightRunTex;
	staticRec->sprite.id_up = upIdleTex;
	staticRec->sprite.id_left = leftIdleTex;
	staticRec->sprite.id_right = rightIdleTex;
	staticRec->sprite.id_down = downIdleTex;
	recVec.push_back(staticRec);

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
	memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();
	RenM->register_manager();
	AudM->register_manager();
	TestM->register_manager();


	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;

	//Alex->WorldObj::setWidth(100);
	//Alex->WorldObj::setHeight(100);
	//Alex->setX(10);
	//Alex->setY(10);

	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	clock_t start_tick, current_ticks, delta_ticks;
	clock_t fps = 0;
	int fs = 60;
	while (osi::GameWindow::isRunning()) {
		start_tick = clock();
		_QuadTree->clear();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->insert(recVec[i]);	//insert all obj into tree
	
		}
		//clock 
		gameplay_functions->move_up_left(staticRec);
		iController->InputCheck();

		//Alex->WorldObj::drawObj(0,0);
		//for (int i = 0; i < recVec.size(); i++) {
		//	recVec[i]->drawObj(0,0);
		//}
		//Alex->WorldObj::animateObj();
		////Alex->WorldObj::shiftX(.5);
		//osi::GameWindow::refresh();
		//draw
		if (DialogueController::getState() == 0) {
			//LOG("ERROR AFTER PRESSING Q TO QUIT THE DIALOGUE GUI");
			gameplay_functions->draw_frame(Alex);
		}
		else if (DialogueController::getState() > 0) {
			gameplay_functions->drawDiaGui(Alex);
		}
		//convoGui->drawGui();

		//gameplay_functions->draw_frame(convoGui);
		//run task buffer
		//iController->InputCheck();
		tBuffer->run();
		//	cout << tBuffer->queue_buffer.size() << endl;
		//tBuffer->empty();


		if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks) {www
			Sleep((1000 / fs) - (clock() - start_tick));
		}
		delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
			fps = CLOCKS_PER_SEC / delta_ticks;
		cout << "FPS: " << fps << endl;


	}
	osi::GameWindow::terminate();
}

void ALESSIO_TEST() {
	srand(time(NULL));
	int rInt[10];
	for (int i = 0; i < 10; i++) {
		rInt[i] = rand() % 4 - 1;
	}
	Factions fac(rInt);
	Hero person2(OYA, 20, 0, false);
	Texture still2;
	still2.setFile("YemojasHouse.png");
	still2.load();
	still2.setFrames(2);
	person2.sprite.setTexture(&still2);
	Hero person(YEMOJA, 20, 0, false);
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
	Player me(SHANGO,30, 32, true);
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
	//osi::GameWindow::init();
	float z = 0;
	while (osi::GameWindow::isRunning()) {
		/*person2.WorldObj::drawObj();
		person.WorldObj::drawObj();*/
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

	WorldObj* Alex = new WorldObj(Vector2f(1000.0, 600.0), 100.0, 100.0);	//init player
	Texture* playerTexture = new Texture();
	Texture* objTexture = new Texture();
	Texture* uptex = new Texture();
	Texture* downtex = new Texture();
	Texture* lefttex = new Texture();
	Texture* righttex = new Texture();


	objTexture->setFile("YemojasHouse.jpg");
	playerTexture->setFile("phi.png");

	//uptex->setFile("Shango")

	playerTexture->load();
	objTexture->load();
	playerTexture->setFrames(1);
	objTexture->setFrames(1);
	Alex->sprite.setTexture(playerTexture);
	Alex->sprite.up = uptex;
	Alex->sprite.down = downtex;
	Alex->sprite.left = lefttex;
	Alex->sprite.right = righttex;
	Alex->offsetBody(0, 50, 50, 50, 50);
	vector<WorldObj*> recVec;	

	for (int i = 1; i < 5; i++) {
		WorldObj* objs = new WorldObj(Vector2f(100 * i , 100 * i ), 200.0, 200.0);
		objs->sprite.setTexture(objTexture);
		//objs->offsetBody(0, 50, 50, 50, 50);
		//objs->offsetBody(0, 70, 70, 70, 70);
		recVec.push_back(objs);
	}
	WorldObj* staticRec = new WorldObj(Vector2f(1800, 1350), 100.0, 100.0);
	staticRec->sprite.setTexture(playerTexture);
	recVec.push_back(staticRec);

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
	memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();
	RenM->register_manager();
	TestM->register_manager();


	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;

	//Alex->WorldObj::setWidth(100);
	//Alex->WorldObj::setHeight(100);
	//Alex->setX(10);
	//Alex->setY(10);

	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	clock_t start_tick, current_ticks, delta_ticks;
	clock_t fps = 0;
	int fs = 60;
	while (osi::GameWindow::isRunning()) {
		start_tick = clock();
		_QuadTree->clear();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->insert(recVec[i]);	//insert all obj into tree
		}
		//clock 
		iController->InputCheck();
		//Alex->WorldObj::drawObj(0,0);
		//for (int i = 0; i < recVec.size(); i++) {
		//	recVec[i]->drawObj(0,0);
		//}
		//Alex->WorldObj::animateObj();
		////Alex->WorldObj::shiftX(.5);
		//osi::GameWindow::refresh();
		//draw
		//gameplay_functions->draw_frame(Alex);
		//run task buffer
		//iController->InputCheck();
		tBuffer->run();
	//	cout << tBuffer->queue_buffer.size() << endl;
		//tBuffer->empty();
	
		
		if ((1000/fs) > (clock() - start_tick)){ //delta_ticks) {www
			Sleep((1000/fs) - (clock() - start_tick));
		}
		delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
		fps = CLOCKS_PER_SEC / delta_ticks;
		cout << "FPS: "<<fps << endl;
	}
	osi::GameWindow::terminate();
}


void ERONS_LOOP() {
	/////////////////////////////////////////////////////////////////
	//ERON'S LOOP NO TOUCHY    **** Justin touched it, oops ****  ****Ian did too. Sue me****
	/////////////////////////////////////////////////////////////////
	LOG("Hello world!");

	//pauses the program for viewing
	system("PAUSE");

	//demonstration of a meory leak
	//while (true) {
	//	void* a = malloc(64);
	//	delete a;
	//}
	/*
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
	TestManager* TestM = new TestManager(mLog, tBuffer);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();
	AudM->register_manager();
	TestM->register_manager();
	
	AudioTestSuite* aTest = new AudioTestSuite();
	bool test = aTest->execute_tests();
	if (test) LOG("AudioTestSuite: PASSED");
	else LOG("AudioTestSuite: FAILED");

	TaskBufferTestSuite* TB_Test = new TaskBufferTestSuite(); //Ian Testing
	bool test_2 = TB_Test->execute_tests();
	if (test_2) LOG("TaskBufferTestSuite: PASSED");
	else LOG("TaskBufferTestSuite: FAILED");

	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;



	while (true) {
		//clock 
		iController->InputCheck();
		tBuffer->run();
		//draw
	}
	*//*
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);

	DialougeTestSuite* dilg_tester = new DialougeTestSuite();
	//* test_dManager = new memManager(mLog, tBuffer);

	
	std::cout << dilg_tester->execute_tests() << std::endl;
	std::cout << "true: " << true << std::endl;
	std::cout << "false: " << false << std::endl;
	delete dilg_tester;
	*/

	//DialogueHelper* dilgH = new DialogueHelper();

	//Hero* yemoja = new Hero(YEMOJA, 20, 0, false);

	//dialogue_point point1 = dilgH->choose_conv_pt({""});

	//std::string sentence1 = dilgH->gen_dialog({ "name","question_name" }, yemoja);
	//std::cout << sentence1 << std::endl;

	//dialogue_point point2 = dilgH->choose_reply_pt({ "name","question_name" });

	//std::string sentence2 = dilgH->gen_dialog(point2, yemoja);
	//std::cout << sentence2 << std::endl;
	//dilgH->gen_dialog({ "what", "variable" }, yemoja);
	std::cout << "///////////////////////////" << endl;
	system("PAUSE");
	
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
	SoundSystem soundsystem;

	type = foo::soundType::music;
	name = "04.wav";
	channel = channels[0];//assign the channel
	ispaused = false;

	soundsystem.createSound(&soundSample, name);// Create the sound
	soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

													 //SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
													 //object stuff


	//soundsystem.playSound(soundSample, false, channel, ispaused, 1); 	// Play the sound, with loop mode


	cout << "Press return to quit." << endl;  // Do something meanwhile...
	cin.get();

	soundsystem.releaseSound(soundSample); // Release the sound
}
void ANDREWS_LOOP(QuadTree* _QuadTree) {
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
		WorldObj* objs = new WorldObj(Vector2f(100 * i, 100 * i), 200.0, 200.0);
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
	TestManager* TestM = new TestManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	//memM->register_manager();
	RenM->register_manager();
	TestM->register_manager();
	AudM->register_manager();

	cout << endl;
	cout << "STARTING PHYSICS TESTS" << endl;
	PHYSICS_TEST();

	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;

	/*	Alex->WorldObj::setWidth(100);
	Alex->WorldObj::setHeight(100);
	Alex->setX(100);
	Alex->setY(100);*/

	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	while (osi::GameWindow::isRunning()) {
		_QuadTree->clear();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->insert(recVec[i]);	//insert all obj into tree
		}
		//clock 
		iController->InputCheck();
		//Alex->WorldObj::drawObj();
		//for (int i = 0; i < recVec.size(); i++) {
		//	recVec[i]->drawObj();
		//}
		//Alex->WorldObj::animateObj();
		osi::GameWindow::refresh();
		//draw
		//gameplay_functions->draw_frame(Alex);
		//run task buffer
		tBuffer->run();


	}
	osi::GameWindow::terminate();
}

void PHYSICS_TEST() {
	PhysicsTestSuite* test = new PhysicsTestSuite();
	if (test->test_movement()) {
		cout << "MOVEMENT TEST SUCCEEDED" << endl;
	}
	else {
		cout << "MOVEMENT TEST FAILED" << endl;
	}

	if (test->test_collision()) {
		cout << "COLLISION TEST SUCCEEDED" << endl;
	}
	else {
		cout << "COLLISION TEST FAILED" << endl;
	}
}

void FPS(bool b) {
	if (b) {
		time_t sec;
		time(&sec);
	}
	time_t now; 
	time(&now);

}
