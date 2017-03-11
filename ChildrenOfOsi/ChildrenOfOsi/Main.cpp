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
#include "Village.h"
#include <crtdbg.h>
#include "Rectangle.h"
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

#include "AIManager.h"
#include "AIController.h"

#include "ObjConfig.h"
#include "ActionPool.h"

#include "Line.h"

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
bool lineCollision(Line l1, Line l2);

int main() {

	 //   DialogueHelper* dhelper = new DialogueHelper();

		//ERONS_LOOP();
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
		/* ERON */
		
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


	Player* Alex = new Player(SHANGO, Vector2f(4900.0, 3700.0), 150.0, 150.0);	//init player
	cout << "Alex's width and height is " << Alex->getWidth() << ", " << Alex->getHeight() << endl;

	vector<WorldObj*> recVec;
	vector<WorldObj*>* recVec_ptr = &recVec;

	//psuedo Gameloop
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);

	//need this here for map editor
	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree);

	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);
	Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, recVec_ptr);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree);
	
	memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);
	AIHelper* ai = new AIHelper();
	AIManager* AIM = new AIManager(mLog, tBuffer, ai);

	AIController* AiController = new AIController();

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();
	RenM->register_manager();
	AudM->register_manager();
	//TestM->register_manager();
	AIM->register_manager();


	//DialogueGui* convoGui = new DialogueGui();

	//Player* Alex = new Player(1000,600, true);	//init player
	//WorldObj* Alex = new WorldObj(1000, 600, true);

	ObjConfig::import_config(recVec_ptr, gameplay_functions, tBuffer);

    Texture* objTexture = new Texture();

	Texture* playerTexture = new Texture();
	Texture* playerIdleTex = new Texture();

	Texture* upRunTex = new Texture();
	Texture* downRunTex = new Texture();
	Texture* leftRunTex = new Texture();
	Texture* rightRunTex = new Texture();
	Texture* upIdleTex = new Texture();
	Texture* downIdleTex = new Texture();
	Texture* leftIdleTex = new Texture();
	Texture* rightIdleTex = new Texture();
	Texture* upAtkTex = new Texture();
	Texture* downAtkTex = new Texture();
	Texture* leftAtkTex = new Texture();
	Texture* rightAtkTex = new Texture();
	Texture* upHurtTex = new Texture();
	Texture* downHurtTex = new Texture();
	Texture* leftHurtTex = new Texture();
	Texture* rightHurtTex = new Texture();

	Texture* yemojaTexture = new Texture();
	Texture* yemojaIdleTex = new Texture();

	Texture* h_upRunTex = new Texture();
	Texture* h_downRunTex = new Texture();
	Texture* h_leftRunTex = new Texture();
	Texture* h_rightRunTex = new Texture();
	Texture* h_upIdleTex = new Texture();
	Texture* h_downIdleTex = new Texture();
	Texture* h_leftIdleTex = new Texture();
	Texture* h_rightIdleTex = new Texture();

	Texture* treeTex = new Texture();
	Texture* treeTex1 = new Texture();
	Texture* treeTex2 = new Texture();

	Texture* rockTex = new Texture();
	Texture* rockTex1 = new Texture();
	Texture* rockTex2 = new Texture();

	Texture* pierTex = new Texture();

	Texture* blank = new Texture();

	//load sprite from a configuration file?
	blank->setFile("Assets/Sprites/blank.png", 1);
	objTexture->setFile("Assets/Sprites/YemojasHouse.png",1);

	playerTexture->setFile("Assets/Sprites/ShangoForwardIdle.png",22);
	playerIdleTex->setFile("Assets/Sprites/ShangoForwardIdle.png",22);

	upRunTex->setFile("Assets/Sprites/ShangoBackSprint.png",16);
	downRunTex->setFile("Assets/Sprites/ShangoForwardSprint.png",16);
	leftRunTex->setFile("Assets/Sprites/ShangoLeftSprint.png",16);
	rightRunTex->setFile("Assets/Sprites/ShangoRightSprint.png",16);
	upIdleTex->setFile("Assets/Sprites/ShangoBackIdle.png",22);
	downIdleTex->setFile("Assets/Sprites/ShangoForwardIdle.png",22);
	leftIdleTex->setFile("Assets/Sprites/ShangoLeftIdle.png",22);
	rightIdleTex->setFile("Assets/Sprites/ShangoRightIdle.png",22);
	upAtkTex->setFile("Assets/Sprites/ShangoBackSwing.png", 24);
	downAtkTex->setFile("Assets/Sprites/ShangoForwardSwing.png", 24);
	leftAtkTex->setFile("Assets/Sprites/ShangoLeftSwing.png", 24);
	rightAtkTex->setFile("Assets/Sprites/ShangoRightSwing.png", 24);
	upHurtTex->setFile("Assets/Sprites/ShangoBackRecoil.png", 18);
	downHurtTex->setFile("Assets/Sprites/ShangoForwardRecoil.png", 18);
	leftHurtTex->setFile("Assets/Sprites/ShangoLeftRecoil.png", 18);
	rightHurtTex->setFile("Assets/Sprites/ShangoRightRecoil.png", 18);


	yemojaTexture->setFile("Assets/Sprites/YemojaFrontIdle.png", 1);
	yemojaIdleTex->setFile("Assets/Sprites/YemojaFrontIdle.png", 1);

	h_upRunTex->setFile("Assets/Sprites/YemojaBackSprite.png", 26);
	h_downRunTex->setFile("Assets/Sprites/YemojaForwardSprite.png", 26);
	h_leftRunTex->setFile("Assets/Sprites/YemojaLeftSprite.png", 26);
	h_rightRunTex->setFile("Assets/Sprites/YemojaRightSprite.png", 26);
	h_upIdleTex->setFile("Assets/Sprites/YemojaBackIdle.png", 1);
	h_downIdleTex->setFile("Assets/Sprites/YemojaFrontIdle.png", 1);
	h_leftIdleTex->setFile("Assets/Sprites/YemojaLeftIdle.png", 1);
	h_rightIdleTex->setFile("Assets/Sprites/YemojaRightIdle.png", 1);

	treeTex->setFile("Assets/Sprites/tree.png", 1);
	treeTex1->setFile("Assets/Sprites/tree1.png", 1);
	treeTex2->setFile("Assets/Sprites/tree2.png", 1);

	rockTex->setFile("Assets/Sprites/rock_1.png", 1);
	rockTex2->setFile("Assets/Sprites/rock_2.png", 1);

	pierTex->setFile("Assets/Sprites/pier.png", 1);
	/* SET UP SPRITE CHANGE, MIGHT NEED A SINGLETON?*/


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

	Alex->sprite.atk_up = upAtkTex;
	Alex->sprite.atk_down = downAtkTex;
	Alex->sprite.atk_left = leftAtkTex;
	Alex->sprite.atk_right = rightAtkTex;

	Alex->sprite.hurt_up = upHurtTex;
	Alex->sprite.hurt_down = downHurtTex;
	Alex->sprite.hurt_left = leftHurtTex;
	Alex->sprite.hurt_right = rightHurtTex;

	Alex->offsetBody(0, 50, 50, 50, 50);
	Alex->setInteractable(true);
	Alex->setName("Alex");
	Alex->setTalkDist(20);
	Alex->melee.setCollision(true);
	Alex->melee.setDmg(10);
	Alex->melee.setDestroy(false);
	Alex->melee.setWidth(Alex->body[0].getWidth());
	Alex->melee.setHeight(Alex->body[0].getHeight());
	Attack* rockThrow = new Attack();
	rockThrow->setDmg(5);
	rockThrow->setSpeed(10);
	rockThrow->setDestroy(true);
	rockThrow->setDuration(1000);
	rockThrow->setCoolDown(124);
	rockThrow->setPause(0);
	rockThrow->sprite.setTexture(rockTex);
	Alex->addAttackType(rockThrow);
	Alex->melee.sprite.setTexture(blank);
	//Alex->melee.sprite.setTexture(rockTex);
	DialogueController::setPlayer(Alex);
	//vector<WorldObj*> recVec;

	vector<WorldObj*> vec;
	//vec.push_back(&Alex->melee);

	for (int i = 1; i < 6; i++) {
		if (i > 4) {
			WorldObj* obj = new WorldObj(Vector2f(4100, 3550),500,333);
		
			obj->sprite.setTexture(objTexture);
			obj->setInteractable(true);
			std::string building = "Building ";
			obj->setName(building += std::to_string(i));
			//objs->offsetBody(0, 50, 50, 50, 50);
			obj->offsetBody(0, 25, 50, 25, 25);
			vec.push_back(obj);
			continue;
		}

		WorldObj* objs = new WorldObj(Vector2f(220+50 * i, 300 * (i*2)), 600.0, 400.0);
		objs->sprite.setTexture(objTexture);
		objs->setInteractable(true);
		std::string building="Building ";
		objs->setName(building+= std::to_string(i));
		//objs->offsetBody(0, 50, 50, 50, 50);
		objs->offsetBody(0, 110, 150, 120, 60);
		recVec.push_back(objs);
		
	}

	vector<Vector2f> vertices;
	vector<pair<Vector2f, Vector2f>> edges;
	
	for (int i = 0; i < vec.size(); i++) {
		WorldObj *obj = vec[i];
		float w = obj->body[0].getWidth();
		float h = obj->body[0].getHeight();
		Vector2f p1 = { obj->body[0].getX() - 105,obj->body[0].getY() - 105 };
		Vector2f p2 = obj->body[0].getTR();
		Vector2f p3 = obj->body[0].getBL();
		Vector2f p4 = obj->body[0].getBR();
		vertices.push_back(p1);
		vertices.push_back(p2);
		vertices.push_back(p3);
		vertices.push_back(p4);
		edges.push_back({ p1, p2 });
		edges.push_back({ p1, p3 });
		edges.push_back({ p2, p4 });
		edges.push_back({ p3, p4 });
		//Put edges in the hit box to prevent
		//visibility lines through the diagonal
		edges.push_back({ p2, p3 });
		edges.push_back({ p1, p4 });
	}
	
	gameplay_functions->add_hero("Yemoja", 4600, 3600, true);

	tBuffer->run();

	Hero* staticRec = Containers::hero_table["Yemoja"];

	staticRec->setWidth(100);
	staticRec->setHeight(100);
	staticRec->name = YEMOJA;
	//Hero* staticRec = new Hero(YEMOJA, Vector2f(4600, 3600), 100.0, 100.0);
	///should actually use gameplay_functions->add_hero("Yemoja", 4600, 3600, true)
	/// Containers::hero_table[name]->setWidht(widht)



	staticRec->sprite.setTexture(yemojaTexture);
	staticRec->sprite.setIdleTexture(yemojaIdleTex);
	staticRec->sprite.up = h_upRunTex;
	staticRec->sprite.down = h_downRunTex;
	staticRec->sprite.left = h_leftRunTex;
	staticRec->sprite.right = h_rightRunTex;
	staticRec->sprite.id_up = h_upIdleTex;
	staticRec->sprite.id_left = h_leftIdleTex;
	staticRec->sprite.id_right = h_rightIdleTex;
	staticRec->sprite.id_down = h_downIdleTex;
	staticRec->sprite.hurt_up = upHurtTex;
	staticRec->sprite.hurt_down = downHurtTex;
	staticRec->sprite.hurt_left = leftHurtTex;
	staticRec->sprite.hurt_right = rightHurtTex;



	//VisibilityGraph graph;
	ai->graph.vertices = vertices;
	ai->graph.obstacles = edges;
	for (Vector2f vert : ai->graph.vertices) {
		std::cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		std::cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	bool visible = true;
	/*for (Vector2f first : ai->graph.vertices) {
		//ai->graph.insert(first);
		for (Vector2f second : ai->graph.vertices) {
			if (first == second) continue;
			visible = true;
			for (auto check : ai->graph.obstacles) {
				if (ai->graph.intersect(first, second, check.first, check.second)) {
					visible = false;
					break;
				}
			}
			if (visible) { //put vertices in each other's neighbor list
				ai->graph.edges[first].push_back(second);
				ai->graph.edges[second].push_back(first);
			}
		}
	}*/

	staticRec->setName("Yemoja");
	staticRec->setInteractable(true);
	staticRec->setHealth(100);
	/*
	WorldObj* tree = new WorldObj(Vector2f(4000, 2600), 800, 500);
	tree->sprite.setTexture(treeTex);
	tree->offsetBody(0, 275, 375, 375, 75);
	WorldObj* tree1 = new WorldObj(Vector2f(3300, 4600), 700, 600);
	tree1->sprite.setTexture(treeTex1);
	tree1->offsetBody(0, 275, 375, 375, 75);
	WorldObj* tree2 = new WorldObj(Vector2f(4700, 4500), 700, 600);
	tree2->sprite.setTexture(treeTex2);
	tree2->offsetBody(0, 275, 375, 375, 75);
	//WorldObj* tree1 = new WorldObj(Vector2f())
	//staticRec->goal.setXloc(500);
	//staticRec->goal.setYloc(1200);
	*/
	recVec.push_back(staticRec);
	//recVec.push_back(tree);
	//recVec.push_back(tree1);
	//recVec.push_back(tree2);
	//recVec.push_back(vec[0]);
	
	//recVec.push_back(vec[1]);
	//recVec.push_back(myRec1); recVec.push_back(myRec2);

	//pauses the program for viewing
	//system("PAUSE");

	//demonstration of a meory leak
	//while (true) {
	//	void* a = malloc(64);
	//	delete a;
	//}
	
/*	VisibilityGraph graph{ {
		{{1400.00,800.00}, {{1400.00, 900.00},{1200.00,800.00}}},
		{{1400.00,900.00}, {{1400.00,800.00},{1200.00,800.00},{1300.00,1000.00}}},
		{{1200.00,800.00}, {{1400.00,800.00},{1400.00,900.00},{1100.00,900.00}}},
		{{1300.00,1000.00}, {{1400.00,900.00},{1100.00,900.00},{1200.00,600.00}}},
		{{1100.00,900.00}, {{1200.00,800.00},{1300.00,1000.00},{1200.00,600.00}}},
		{{1200.00,600.00}, {{1100.00,900.00},{1300.00,1000.00}}}
	} };
	*/
	//ai->graph = graph;
	ai->start = staticRec->getLoc();
	ai->goal = { 1100.00,1100.00 };

	ai->graph.insert(ai->start);
	//ai->graph.insert(ai->goal);

	staticRec->destination = { 4600.00,3600.00 };
	ai->graph.insert(staticRec->destination);
	ai->graph.insert(Vector2f(5000.00, 4100.00));
	ai->graph.insert(Vector2f(4600.00, 3600.00));
	ai->graph.insert(Vector2f(4500.00, 4000.00));
	ai->graph.insert(Vector2f(5650.00, 3700.00));
	for (Vector2f vert : ai->graph.vertices) {
		std::cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		std::cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	ai->graph._print();

	ActionPool* poolAct = new ActionPool(Alex);
	Alex->actionPool = poolAct;
	Action mic = Action();
	//mic.preconds["affAbove"] = 50;
	mic.postconds["aff"] = 5;
	Action mac = Action();
	//mac.preconds["affAbove"] = 55;
	mac.postconds["aff"] = 5;
	mac.setOwner(Alex);
	mac.setHero(staticRec);
	poolAct->micro.push_back(mic);
	poolAct->macro.push_back(mac);
	poolAct->updateMiddle();
	std::cout << poolAct->macro.back().getName()<< endl;
	vector<Action> test= poolAct->getActions(staticRec,poolAct->macro.back());
	for (int i = 0; i < test.size(); i++) {
		int t=test[i].exeAction();
	}
	poolAct->macro.back().exeAction();


	//ai->astar_search(staticRec);

	//vector<Vector2f> path = ai->get_path();


	//for (Vector2f next : path) {
	//	std::cout << "X: " << next.getXloc() << " Y: " << next.getYloc() << std::endl;
	//}

	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;

	//Alex->WorldObj::setWidth(100);
	//Alex->WorldObj::setHeight(100);
	//Alex->setX(10);
	//Alex->setY(10);
	ai->astar_search(staticRec);
   // gameplay_functions->get_path(staticRec); //Generate the waypoints to the destination
	staticRec->setMode(WANDER);
	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	clock_t start_tick, current_ticks, delta_ticks;
	clock_t fps = 0;
	int fs = 60;
	int wait_time = fs*3; //always wait 3 seconds
	int count = 0;
	int state = 0;
	while (osi::GameWindow::isRunning()) {
		start_tick = clock();
		_QuadTree->clear();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->insert(recVec[i]);	//insert all obj into tree
	
		}
		state = DialogueController::getState();

		if (staticRec->destination != Vector2f(0, 0)) { //Hero has a destination
			if (staticRec->waypoint != Vector2f(0,0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
				gameplay_functions->move_toward(staticRec); //Take a step towards the current waypoint
				std::cout << "Request a step" << std::endl;
			}
			else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
			{
				gameplay_functions->get_path(staticRec); //Generate waypoints to destination
			}
		}

		else if (staticRec->getMode() != WAIT) //Hero has no destination, and not in wait mode.
		{
			int r = rand() % 4;
			ai->start = staticRec->getLoc();
			std::cout << "at " << ai->start.getXloc() << "," << ai->start.getYloc() << std::endl;
			std::cout << "picked " << r << std::endl;
			switch (r) {
			case 0:
				
				staticRec->destination = Vector2f(5000.00, 4100.00);
				break;
			case 1:
				staticRec->destination = Vector2f(4600.00, 3600.0);
				break;
			case 2:
				staticRec->destination = Vector2f(4500.00, 4000.0);
				break;
			case 3:
				staticRec->destination = Vector2f(5650.00, 3700.00);
				break;
			}
			//Generate the destination
		}
		else   //Hero has no destination and is waiting to generate one
		{
			count++;
			if (count >= wait_time) {
				count = 0;
				staticRec->setMode(WANDER);
			}
		}
		//ai->plan_step(staticRec);
		//clock 

		/*float diffX = staticRec->getX() - staticRec->goal.getXloc();

		float diffY = staticRec->getY() - staticRec->goal.getYloc();
		float slope = abs(diffY / diffX);

		float diagSpeed = sqrt(staticRec->getSpeed()*staticRec->getSpeed() / (slope + 1));

		staticRec->setDiagXSpeed(diagSpeed);
		staticRec->setDiagYSpeed((slope*diagSpeed));


		X: 1520 Y: 970
		X: 1520 Y: 1230
		X: 1450 Y: 1050
		X: 1520 Y: 970
		X: 1520 Y: 1230
		X: 1450 Y: 1050

		if (abs(diffX) < 6) diffX = 0;
		if (abs(diffY) < 6) diffY = 0;
		bool left = false;
		bool up = false;
		bool down = false;
		bool right = false;

		//gameplay_functions->move_toward(staticRec);

		if (diffX < 0) right = true;
		if (diffX > 0) left = true;
		if (diffY < 0) down = true;
		if (diffY > 0) up = true;
		if (up) {
			gameplay_functions->move_toward(staticRec);
		//	if (right) gameplay_functions->move_up_right(staticRec);
		//	else if (left) gameplay_functions->move_up_left(staticRec);
			//else gameplay_functions->move_up(staticRec);
		}
		else if (down) {
			gameplay_functions->move_toward(staticRec);
			//if (right) gameplay_functions->move_down_right(staticRec);
			//else if (left) gameplay_functions->move_down_left(staticRec);
			//else gameplay_functions->move_down(staticRec);
		}
		else if (right) {
			gameplay_functions->move_toward(staticRec);
		//	gameplay_functions->move_right(staticRec);
		}
		else if (left) {
			gameplay_functions->move_toward(staticRec);
			//gameplay_functions->move_left(staticRec);
		}
		else {
			gameplay_functions->stop(staticRec);
		}*/
		iController->InputCheck();

		//Alex->WorldObj::drawObj(0,0);
		//for (int i = 0; i < recVec.size(); i++) {
		//	recVec[i]->drawObj(0,0);
		//}
		//Alex->WorldObj::animateObj();
		////Alex->WorldObj::shiftX(.5);
		//osi::GameWindow::refresh();
		//draw
		Alex->updateCD();
		if (state == 0) {
			//LOG("ERROR AFTER PRESSING Q TO QUIT THE DIALOGUE GUI");
			gameplay_functions->draw_frame(Alex);
			
		}
		else if (state > 0) {
			gameplay_functions->drawDiaGui(Alex);
			gameplay_functions->stop(staticRec);
		}
		//convoGui->drawGui();

		//gameplay_functions->draw_frame(convoGui);
		//run task buffer
		//iController->InputCheck();
		tBuffer->run();
		//	cout << tBuffer->queue_buffer.size() << endl;
		//tBuffer->empty();

		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		for (auto iter : staticRec->rel) {
			Relationship* my_rel = iter.second;
			int with_hero = iter.first;

			if (my_rel->isChanged()) {
				//reevaluate goals for with_hero
				AiController->reevaluate_state(YEMOJA, with_hero);
				my_rel->setChanged(false);
			}
		}
		AiController->execute();

		if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks) {www
			Sleep((1000 / fs) - (clock() - start_tick));
		}
		delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
			fps = CLOCKS_PER_SEC / delta_ticks;
		if (DialogueController::getState() == 0) {
			cout << "FPS: " << fps << endl;
		}


	}
	osi::GameWindow::terminate();
}

void ALESSIO_TEST() {
	
}

void ALEX_LOOP(QuadTree* _QuadTree) {
	//LOG("Hello world!");

	Player* Alex = new Player(SHANGO,Vector2f(1000.0, 600.0), 100.0, 100.0);	//init player
	Texture* playerTexture = new Texture();
	Texture* objTexture = new Texture();
	Texture* uptex = new Texture();
	Texture* downtex = new Texture();
	Texture* lefttex = new Texture();
	Texture* righttex = new Texture();


	objTexture->setFile("YemojasHouse.jpg",1);
	playerTexture->setFile("phi.png",1);

	//uptex->setFile("Shango")

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

	//need this for map editor
	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree);

	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);
	Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, &recVec);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree);
	
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

	DialogueHelper* dilgH = new DialogueHelper();

	Hero* oya = new Hero(OYA, 20, 0, false);
	dilgH->gen_dialog({ "what", "variable" }, oya);

	//std::string sentence1 = dilgH->gen_dialog({ "name","question_name" }, yemoja);
	//std::cout << sentence1 << std::endl;

	//dialogue_point point2 = dilgH->choose_reply_pt({ "name","question_name" });

	//std::string sentence2 = dilgH->gen_dialog(point2, yemoja);
	//std::cout << sentence2 << std::endl;
	//dilgH->gen_dialog({ "what", "variable" }, yemoja);

	
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


	soundsystem.playSound(soundSample, false, channel, ispaused, 1); 	// Play the sound, with loop mode


	cout << "Press return to quit." << endl;  // Do something meanwhile...
	cin.get();

	soundsystem.releaseSound(soundSample); // Release the sound
}
void ANDREWS_LOOP(QuadTree* _QuadTree) {
	//LOG("Hello world!");

	Player* Alex = new Player(SHANGO,Vector2f(500.0, 100.0), 100.0, 100.0);	//init player
	Texture* playerTexture = new Texture();
	playerTexture->setFile("phi.png",1);
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

	//need this here for map editor
	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree);

	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);
	Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, &recVec);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree);
	
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

bool lineCollision(Line l1, Line l2)
{
	float denom = ((l1.getP2().getX() - l1.getP1().getX()) * (l2.getP2().getY() - l2.getP1().getY())) - ((l1.getP2().getY() - l1.getP1().getY()) * (l2.getP2().getX() - l2.getP1().getX()));
    float num1 = ((l1.getP1().getY() - l2.getP1().getY()) * (l2.getP2().getX() - l2.getP1().getX())) - ((l1.getP1().getX() - l2.getP1().getX()) * (l2.getP2().getY() - l2.getP1().getY()));
    float num2 = ((l1.getP1().getY() - l2.getP1().getY()) * (l1.getP2().getX() - l1.getP1().getX())) - ((l1.getP1().getX() - l2.getP1().getX()) * (l1.getP2().getY() - l1.getP1().getY()));

    if (denom == 0) return num1 == 0 && num2 == 0;

    float r = num1 / denom;
    float s = num2 / denom;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

void FPS(bool b) {
	if (b) {
		time_t sec;
		time(&sec);
	}
	time_t now; 
	time(&now);

}
