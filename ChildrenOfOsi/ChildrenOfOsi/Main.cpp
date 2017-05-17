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
#include "RegionState.h"
#include "Tutorial.h"
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
#include "DialogueConfig.h"
#include "TagConfig.h"

#include "AIManager.h"
#include "AIController.h"

#include "ObjConfig.h"
#include "HeroConfig.h"
#include "SoldierConfig.h"

#include "ActionPool.h"
#include "ActionHelper.h"
#include "ActionConfig.h"
//class ActionHelper;
#include "Line.h"
#include "ActionExecFunctions.h"
#include "Alliance.h"
#include "PartyManager.h"
//#include <boost/thread/thread.hpp>  //This is used for Ian's multithread section, but the user needs the boost compiled library installed on their computer
#include "thread"
#include "threadManager.h"

#include "QuestManager.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

/*
this variable is used to keep track of time (in frames)
it is imcremented in the game loop
*/
extern int frame_count = 0;
extern bool game_ended = false;

using namespace std;

Texture* Point::tex = new Texture();
Texture* Rectangle::tex = new Texture();
Texture* Rectangle::texUP = new Texture();
Texture* Rectangle::texDOWN = new Texture();
Texture* Rectangle::texLEFT = new Texture();
Texture* Rectangle::texRIGHT = new Texture();
Texture* Rectangle::texAtkUP = new Texture();
Texture* Rectangle::texAtkDOWN = new Texture();
Texture* Rectangle::texAtkLEFT = new Texture();
Texture* Rectangle::texAtkRIGHT = new Texture();
std::mutex mu;
//void testQuadTree();
//bool checkCollision(WorldObj *recA, WorldObj *recB);	//given two bounding boxes, check if they collide
//bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }		//helper func for checkCollision

void FPS(bool b);
void GAMEPLAY_LOOP(QuadTree* _Quadtree);

bool lineCollision(Line l1, Line l2);
/// Helper function passed to thread to set file. Param is a tuple, first being the Texture* to work on, and second being the param needed to call setFile().
void set_file_with_thread(Texture* t, const pair<string, int>* p_tuple) {
	//std::lock_guard<std::mutex> guard(mu); 
	t->setFile(p_tuple->first, p_tuple->second);
}

/*
int getFreeVideoMemory()
{
	int availableKB[4];
	if(GLEW_NVX_gpu_memory_info)
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX,&availableKB[0]);
	int temp=GLEW_ATI_meminfo;
	if(GLEW_ATI_meminfo)
		glGetIntegerv(GL_TEXTURE_FREE_MEMORY_ATI,availableKB);
	return availableKB[0];
}
*/

void test(int i) { for(int i=0;i<100;i++) cout << "hello this is the thread running" << endl; }

int main() {
	WorldObj* screen = new WorldObj(Vector2f(0.0, 0.0), 25000U, 25000U);	//init screen

	QuadTree* collideTree = new QuadTree(0, *screen);
	GameWindow::init();
  Tutorial::init();
	GAMEPLAY_LOOP(collideTree);
  Tutorial::destroy();

	return 0;
}


void GAMEPLAY_LOOP(QuadTree* _QuadTree)
{
	game_state current_game_state = game_state::load_game;
	//threadmanager::thread_pool pool(5);
	Rectangle::tex->setFile("Assets/Sprites/blankr.png", 1);
	Point::tex->setFile("Assets/Sprites/point.png", 1);

	RiverObj* rivObj = new RiverObj();
	rivObj->initialize_lines();

	UniformGrid<Line>* grid_line = new UniformGrid<Line>();
	UniformGrid<WorldObj>* grid_worldobj = new UniformGrid<WorldObj>();
	grid_line->insert_objs_to_grid(rivObj->getLines());
	
	vector<WorldObj*> recVec;
	vector<WorldObj*> movVec;
	vector<WorldObj*>* largeStruct = new vector<WorldObj*>();
	vector<WorldObj*>* recVec_ptr = &recVec;
	vector<WorldObj*>* movVec_ptr = &movVec;
	vector<Hero*> heroes;

	/* MULTITHREADING SETUP */

	//unordered_map<Texture*, pair<string, int>> textureMap ;
	int num_of_threads = std::thread::hardware_concurrency();
	vector<thread> thread_Vec;

	//psuedo Gameloop
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);

	//need this here for map editor
	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);

	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree, gameplay_functions, rivObj, largeStruct, grid_worldobj);
	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree, grid_line, rivObj, grid_worldobj);
	//PartyManager* partyM = new PartyManager(gameplay_functions, Alex);
	memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);
	AIHelper* ai = new AIHelper();
	AIManager* AIM = new AIManager(mLog, tBuffer, ai);
	//AIController* AiController = new AIController();
	//ActionHelper::ai = AiController;
	ActionHelper::gameplay_func = gameplay_functions;
	CombatController* combatControl = new CombatController(gameplay_functions);
	QuestManager* questM = new QuestManager;

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();

	AudM->register_manager();
	//TestM->register_manager();
	AIM->register_manager();

	RenM->register_manager();
	bool switch_music = false;
	bool in_village = false;

	gameplay_functions->add_texture("treeTex", 0, 0, 0);

	gameplay_functions->add_texture("rockTex1", 0, 0, 0);
	gameplay_functions->add_texture("rockTex2", 0, 0, 0);
	tBuffer->run();

	ObjConfig::textureMap[Containers::texture_table["rockTex1"]] = pair<string, int>("Assets/Sprites/rock_1.png", 1);
	ObjConfig::textureMap[Containers::texture_table["rockTex2"]] = pair<string, int>("Assets/Sprites/rock_2.png", 1);
	ObjConfig::standard_con.push_back(Containers::texture_table["rockTex1"]);
	ObjConfig::standard_con.push_back(Containers::texture_table["rockTex2"]);

	gameplay_functions->add_texture("blank", 0, 0, 0);
	gameplay_functions->add_texture("border", 0, 0, 0);
/*
=======
	gameplay_functions->add_hero("Shango", 5045, 10465, true);
*/

	tBuffer->run();

	ObjConfig::textureMap[Containers::texture_table["blank"]] = pair<string, int>("Assets/Sprites/blank.png", 1);
	ObjConfig::textureMap[Containers::texture_table["border"]] = pair<string, int>("Assets/Sprites/border.png", 1);
	ObjConfig::standard_con.push_back(Containers::texture_table["blank"]);
	ObjConfig::standard_con.push_back(Containers::texture_table["border"]);


	HeroConfig::import_config(movVec_ptr, &ObjConfig::textureMap, gameplay_functions, tBuffer);
	SoldierConfig::import_config(movVec_ptr, &ObjConfig::textureMap, gameplay_functions, tBuffer);
	Village::init_villages();

	Player* Alex = dynamic_cast<Player*>(Containers::hero_table["Shango"]);


	//draws the logo on startup
	gameplay_functions->draw_logo(Alex);
	tBuffer->run();

	// Player* Alex = new Player(SHANGO, Vector2f(6445.0, 10155.0), 150.0, 150.0);	//init player
	


	std::vector<Region*> reg = RegionState::regions;
	
	Region current_region = *RegionState::regions[RegionState::DESERT];
	Region next_region = *RegionState::regions[RegionState::DESERT];


	RegionState::current_region = current_region;
	RegionState::next_region = next_region;


	Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, recVec_ptr, movVec_ptr);

	Hero* yemoja = Containers::hero_table["Yemoja"];
	heroes.push_back(yemoja);
	Hero* oya = Containers::hero_table["Oya"];
	heroes.push_back(oya);

	vector<vector<Texture*>> starting_location;
	
	ObjConfig::import_config(recVec_ptr, gameplay_functions, tBuffer);

	DialogueConfig::import_config(gameplay_functions, tBuffer);
	DialogueController::getDialogueHelper()->fill_conversations();
	TagConfig::import_config(gameplay_functions, tBuffer);

	WorldObj* barrel = new WorldObj(Vector2f(5200, 3900), 75, 75);
	
	//added so loading the map is optional
	if (LOAD_MAP) {

		gameplay_functions->add_texture("map1_1", 0, 0, 0);
		gameplay_functions->add_texture("map1_2", 0, 0, 0);
		gameplay_functions->add_texture("map1_3", 0, 0, 0);
		gameplay_functions->add_texture("map1_4", 0, 0, 0);
		gameplay_functions->add_texture("map1_5", 0, 0, 0);

		gameplay_functions->add_texture("map2_1", 0, 0, 0);
		gameplay_functions->add_texture("map2_2", 0, 0, 0);
		gameplay_functions->add_texture("map2_3", 0, 0, 0);
		gameplay_functions->add_texture("map2_4", 0, 0, 0);
		gameplay_functions->add_texture("map2_5", 0, 0, 0);

		gameplay_functions->add_texture("map3_1", 0, 0, 0);
		gameplay_functions->add_texture("map3_2", 0, 0, 0);
		gameplay_functions->add_texture("map3_3", 0, 0, 0);
		gameplay_functions->add_texture("map3_4", 0, 0, 0);
		gameplay_functions->add_texture("map3_5", 0, 0, 0);

		gameplay_functions->add_texture("map4_1", 0, 0, 0);
		gameplay_functions->add_texture("map4_2", 0, 0, 0);
		gameplay_functions->add_texture("map4_3", 0, 0, 0);
		gameplay_functions->add_texture("map4_4", 0, 0, 0);
		gameplay_functions->add_texture("map4_5", 0, 0, 0);

		gameplay_functions->add_texture("map5_1", 0, 0, 0);
		gameplay_functions->add_texture("map5_2", 0, 0, 0);
		gameplay_functions->add_texture("map5_3", 0, 0, 0);
		gameplay_functions->add_texture("map5_4", 0, 0, 0);
		gameplay_functions->add_texture("map5_5", 0, 0, 0);

		tBuffer->run();
		RenderHelper::gmap->setTextures();
		RenderHelper::gmap->setSprite();
	}

	HDC hdc = wglGetCurrentDC();
	HGLRC mainContext = wglGetCurrentContext();
	HGLRC loaderContextM = wglCreateContext(hdc);
	wglShareLists(mainContext, loaderContextM);
	std::thread tm([=]() {
		wglMakeCurrent(hdc, loaderContextM);
		RenderHelper::gmap->loadTexture(Alex->getLoc());
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(loaderContextM);
		glFinish();
	});

	Rectangle::texRIGHT->setFile("Assets/Sprites/LeftRecoilSpark.png", 18);
	Rectangle::texLEFT->setFile("Assets/Sprites/RightRecoilSpark.png", 18);
	Rectangle::texUP->setFile("Assets/Sprites/ForwardRecoilSpark.png", 18);
	Rectangle::texDOWN->setFile("Assets/Sprites/BackRecoilSpark.png", 18);

	Rectangle::texAtkRIGHT->setFile("Assets/Sprites/LeftRecoilSpark.png", 18);
	Rectangle::texAtkLEFT->setFile("Assets/Sprites/RightRecoilSpark.png", 18);
	Rectangle::texAtkUP->setFile("Assets/Sprites/ForwardRecoilSpark.png", 18);
	Rectangle::texAtkDOWN->setFile("Assets/Sprites/BackRecoilSpark.png", 18);

	for (int i = 0; i < 100; i++) {
		//std:://cout << "AT THE THREAD INITIALIZTION CALL!!!****** " << endl;
	}

	/*
		TRYING TO MULTITHREAD THE SETFILE METHODS ABOVE.
		First, iterate through textureMap and for each texture, assign a new thread to set_file_with_thread().
		When all available threads are working, call join() on all threads before continuing.
		We know all concurrent threads are being utilized when the counter we use while iterating through textureMap has a remainder of 0 when we take the modulo of num_of_threads.

	*/
	//int textureMapCounter = 0;
	//for (const auto& it : ObjConfig::textureMap) {
	//	pair<Texture*, pair<string, int>>* temp_tuple = new pair<Texture*, pair<string, int>>(it.first, it.second);
	//	//cout << "WORKING ON " << temp_tuple->second.first << endl;
	//	// If there are still less than "num_of_threads" in thread_Vec:
	//	if (textureMapCounter % num_of_threads != 0) {

	//		//std::thread temp_thread(set_file_with_thread, std::ref(temp_tuple));
	//		thread_Vec.push_back(std::thread(set_file_with_thread, std::move(temp_tuple)));
	//	}
	//	else {
	//		//cout << "THE THREAD VEC HAS " << thread_Vec.size() << "THREADS" << endl;
	//		for (auto& itr : thread_Vec) {
	//			itr.join();
	//		}
	//		thread_Vec.clear();
	//		thread_Vec.push_back(std::thread(set_file_with_thread, std::ref(temp_tuple)));
	//	}
	//	textureMapCounter++;

	//}
	//for (auto& it : thread_Vec) {
	//	it.join();
	//}
	//thread_Vec.clear();
	 //windows handle

	vector<WorldObj*> vec;

	int closest;
	int least_dist;
	int tmp;
	while (reg.size() > 0) {
		closest = 0;
		least_dist = -1;
		for (int i = 0; i < reg.size(); i++) {
			tmp = Party::dist_location_to_location(Alex->getLoc(), reg[i]->loc);
			if (tmp < least_dist || least_dist == -1) {
				closest = i;
				least_dist = tmp;
			}
		}
		if (reg[closest] == RegionState::regions[RegionState::DESERT]) {
			starting_location.push_back(ObjConfig::oasis_con);
		}
		else if (reg[closest] == RegionState::regions[RegionState::MOUNTAIN]) {
			starting_location.push_back(ObjConfig::mountain_con);
		}
		else if (reg[closest] == RegionState::regions[RegionState::JUNGLE]) {
			starting_location.push_back(ObjConfig::jungle_con);
		}
		else if (reg[closest] == RegionState::regions[RegionState::MARSH]) {
			starting_location.push_back(ObjConfig::marsh_con);
		}
		reg.erase(reg.begin()+closest);
	}

	HGLRC loaderContext0 = wglCreateContext(hdc);
	wglShareLists(mainContext, loaderContext0);
	std::thread t0([=]() {
		wglMakeCurrent(hdc, loaderContext0);
		for (int i = 0; i < ObjConfig::standard_con.size(); i++) {
			set_file_with_thread(ObjConfig::standard_con[i], &ObjConfig::textureMap.find(ObjConfig::standard_con[i])->second);
		}
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(loaderContext0);
		/*for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}*/
		Alex->sprite.reset_texture();
		glFinish();
	});

	HGLRC loaderContext1 = wglCreateContext(hdc);
	wglShareLists(mainContext, loaderContext1);
	std::thread t1([=]() {
		wglMakeCurrent(hdc, loaderContext1);
		for (int i = 0; i < (starting_location[0]).size(); i++) {
			set_file_with_thread(starting_location[0].at(i), &ObjConfig::textureMap.find(starting_location[0].at(i))->second);
		}
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (int i = 0; i < (starting_location[3]).size(); i++) {
			set_file_with_thread(starting_location[3].at(i), &ObjConfig::textureMap.find(starting_location[3].at(i))->second);
		}
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(loaderContext1);
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		glFinish();
	});

	HGLRC loaderContext2 = wglCreateContext(hdc);//Creates the new GL context that we will use for loading
	wglShareLists(mainContext, loaderContext2);//Shares the information between the loading context and the main context
	std::thread t2([=]() {//makes the thread. [=] is a cpp Lambda representation
		wglMakeCurrent(hdc, loaderContext2);//Sets the current context to the loader context
		for (int i = 0; i < (starting_location[1]).size(); i++) {
			set_file_with_thread(starting_location[1].at(i), &ObjConfig::textureMap.find(starting_location[1].at(i))->second);
		}
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (int i = 0; i < (starting_location[2]).size(); i++) {
			set_file_with_thread(starting_location[2].at(i), &ObjConfig::textureMap.find(starting_location[2].at(i))->second);
		}
		wglMakeCurrent(nullptr, nullptr);//unassigns the current gl context
		wglDeleteContext(loaderContext2);//deletes the loading context now that it is not needed
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		glFinish(); //Forces all gl calls to be completed before execution
	});
	


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


/*
	yemoja->setWidth(150);
	yemoja->setHeight(150);
	yemoja->name = YEMOJA;

	yemoja->sprite.setTexture(Containers::texture_table["h_downIdleTex"]);
	yemoja->sprite.setIdleTexture(Containers::texture_table["h_downIdleTex"]);
  yemoja->sprite.id_up = Containers::texture_table["h_upIdleTex"];
  yemoja->sprite.id_down = Containers::texture_table["h_downIdleTex"];
  yemoja->sprite.id_left = Containers::texture_table["h_leftIdleTex"];
  yemoja->sprite.id_right = Containers::texture_table["h_rightIdleTex"];
	yemoja->sprite.up = Containers::texture_table["h_upWalkTex"];
	yemoja->sprite.down = Containers::texture_table["h_downWalkTex"];
	yemoja->sprite.left = Containers::texture_table["h_leftWalkTex"];
	yemoja->sprite.right = Containers::texture_table["h_rightWalkTex"];
	yemoja->sprite.hurt_up = Containers::texture_table["YhurtUp"];
	yemoja->sprite.hurt_down = Containers::texture_table["YhurtDown"];
	yemoja->sprite.hurt_left = Containers::texture_table["YhurtLeft"];
	yemoja->sprite.hurt_right = Containers::texture_table["YhurtRight"];
	yemoja->sprite.atk_up = Containers::texture_table["YswingUp"];
	yemoja->sprite.atk_down = Containers::texture_table["YswingDown"];
	yemoja->sprite.atk_left = Containers::texture_table["YswingLeft"];
	yemoja->sprite.atk_right = Containers::texture_table["YswingRight"];
	yemoja->sprite.death_up = Containers::texture_table["YdeathUp"];
	yemoja->sprite.death_down = Containers::texture_table["YdeathDown"];
	yemoja->sprite.death_left = Containers::texture_table["YdeathLeft"];
	yemoja->sprite.death_right = Containers::texture_table["YdeathRight"];

  oya->sprite.setTexture(Containers::texture_table["Oya_IdleDownTex"]);
  oya->sprite.setIdleTexture(Containers::texture_table["Oya_IdleDownTex"]);
  oya->sprite.id_up = Containers::texture_table["Oya_IdleUpTex"];
  oya->sprite.id_down = Containers::texture_table["Oya_IdleDownTex"];
  oya->sprite.id_left = Containers::texture_table["Oya_IdleLeftTex"];
  oya->sprite.id_right = Containers::texture_table["Oya_IdleRightTex"];
  oya->sprite.up = Containers::texture_table["Oya_WalkUpTex"];
  oya->sprite.down = Containers::texture_table["Oya_WalkDownTex"];
  oya->sprite.left = Containers::texture_table["Oya_WalkLeftTex"];
  oya->sprite.right = Containers::texture_table["Oya_WalkRightTex"];
  oya->sprite.atk_up = Containers::texture_table["Oya_AttackUpTex"];
  oya->sprite.atk_down = Containers::texture_table["Oya_AttackDownTex"];
  oya->sprite.atk_left = Containers::texture_table["Oya_AttackLeftTex"];
  oya->sprite.atk_right = Containers::texture_table["Oya_AttackRightTex"];
  oya->sprite.hurt_up = Containers::texture_table["Oya_RecoilUpTex"];
  oya->sprite.hurt_down = Containers::texture_table["Oya_RecoilDownTex"];
  oya->sprite.hurt_left = Containers::texture_table["Oya_RecoilLeftTex"];
  oya->sprite.hurt_right = Containers::texture_table["Oya_RecoilRightTex"];
  oya->sprite.death_up = Containers::texture_table["Oya_DeathUpTex"];
  oya->sprite.death_down = Containers::texture_table["Oya_DeathDownTex"];
  oya->sprite.death_left = Containers::texture_table["Oya_DeathLeftTex"];
  oya->sprite.death_right = Containers::texture_table["Oya_DeathRightTex"];

	
*/
	/*
	gameplay_functions->add_Attack(yemoja->getKey(), yemoja->body[0].getX(), yemoja->body[0].getY(), true, 10);
	gameplay_functions->add_Attack(oya->getKey(), oya->body[0].getX(), oya->body[0].getY(), true, 10);
	tBuffer->run();

	yemoja->melee = Containers::Attack_table[yemoja->getKey()];
	yemoja->melee->setDmg(15);
	yemoja->melee->setSpeed(8);
	yemoja->melee->setBaseDir(4);
	yemoja->melee->setCoolDown(60);
	yemoja->melee->setPause(-1);
	yemoja->melee->setDestroy(false);
	yemoja->melee->setKeep(true);
	yemoja->melee->setWidth(50);
	yemoja->melee->setHeight(50);
	yemoja->set_creator_of_melee();
	yemoja->melee->setStaminaCost(90);
	yemoja->setHealth(140);
	yemoja->setMaxStamina(300);
	yemoja->melee->sprite.setTexture(Containers::texture_table["border"]);

	oya->melee = Containers::Attack_table[oya->getKey()];
	oya->melee->setDmg(18);
	oya->melee->setSpeed(7);
	oya->melee->setBaseDir(4);
	oya->melee->setCoolDown(70);
	oya->melee->setPause(-1);
	oya->melee->setDestroy(false);
	oya->melee->setKeep(true);
	oya->melee->setWidth(50);
	oya->melee->setHeight(50);
	oya->set_creator_of_melee();
	oya->melee->setStaminaCost(120);
	oya->setHealth(160);
	oya->setMaxStamina(300);
	oya->melee->sprite.setTexture(Containers::texture_table["border"]);
	*/

	/*
	for (int i = 0; i < silverNum; i++) {
		silverSoldier[i]->setWidth(150);
		silverSoldier[i]->setHeight(150);
		silverSoldier[i]->sprite.setTexture(Containers::texture_table["silverSoldierTexture"]);
		silverSoldier[i]->sprite.setIdleTexture(Containers::texture_table["silverSoldierIdleTex"]);
		silverSoldier[i]->sprite.up = Containers::texture_table["ss_upRunTex"];
		silverSoldier[i]->sprite.down = Containers::texture_table["ss_downRunTex"];
		silverSoldier[i]->sprite.left = Containers::texture_table["ss_leftRunTex"];
		silverSoldier[i]->sprite.right = Containers::texture_table["ss_rightRunTex"];

		silverSoldier[i]->sprite.id_up = Containers::texture_table["ss_upIdleTex"];
		silverSoldier[i]->sprite.id_left = Containers::texture_table["ss_leftIdleTex"];
		silverSoldier[i]->sprite.id_right = Containers::texture_table["ss_rightIdleTex"];
		silverSoldier[i]->sprite.id_down = Containers::texture_table["ss_downIdleTex"];

		silverSoldier[i]->sprite.atk_up = Containers::texture_table["ss_upAtkTex"];
		silverSoldier[i]->sprite.atk_down = Containers::texture_table["ss_downAtkTex"];
		silverSoldier[i]->sprite.atk_left = Containers::texture_table["ss_leftAtkTex"];
		silverSoldier[i]->sprite.atk_right = Containers::texture_table["ss_rightAtkTex"];

		silverSoldier[i]->sprite.hurt_up = Containers::texture_table["ss_upHurtTex"];
		silverSoldier[i]->sprite.hurt_down = Containers::texture_table["ss_downHurtTex"];
		silverSoldier[i]->sprite.hurt_left = Containers::texture_table["ss_leftHurtTex"];
		silverSoldier[i]->sprite.hurt_right = Containers::texture_table["ss_rightHurtTex"];

		silverSoldier[i]->sprite.death_up = Containers::texture_table["ss_upDeathTex"];
		silverSoldier[i]->sprite.death_down = Containers::texture_table["ss_downDeathTex"];
		silverSoldier[i]->sprite.death_left = Containers::texture_table["ss_leftDeathTex"];
		silverSoldier[i]->sprite.death_right = Containers::texture_table["ss_rightDeathTex"];

		silverSoldier[i]->offsetBody(0, 60, 60, 75, 50);
		silverSoldier[i]->setInteractable(true);
		silverSoldier[i]->setName("silverSoldier");
		silverSoldier[i]->melee = Containers::Attack_table[silverSoldier[i]->getKey()];
		silverSoldier[i]->melee->setDmg(11);
		silverSoldier[i]->melee->setSpeed(5);
		silverSoldier[i]->melee->setBaseDir(4);
		silverSoldier[i]->melee->setCoolDown(60);
		silverSoldier[i]->melee->setPause(-1);
		silverSoldier[i]->melee->setDestroy(false);
		silverSoldier[i]->melee->setKeep(true);
		silverSoldier[i]->melee->setWidth(50);
		silverSoldier[i]->melee->setHeight(50);
		silverSoldier[i]->set_creator_of_melee();
		silverSoldier[i]->melee->setStaminaCost(90);
		silverSoldier[i]->setHealth(110);
		silverSoldier[i]->melee->setStaminaCost(120);
		silverSoldier[i]->setMaxStamina(300);
		//silverSoldier[i]->addAttackType(rockThrow);
		silverSoldier[i]->melee->sprite.setTexture(Containers::texture_table["border"]);
		silverSoldier[i]->setSpeed(7);
	}

	for (int i = 0; i < blueNum; i++) {
		blueSoldiers[i]->setWidth(150);
		blueSoldiers[i]->setHeight(150);
		blueSoldiers[i]->sprite.setTexture(Containers::texture_table["blueSoldierTexture"]);
		blueSoldiers[i]->sprite.setIdleTexture(Containers::texture_table["blueSoldierIdleTex"]);
		blueSoldiers[i]->sprite.up = Containers::texture_table["bs_upRunTex"];
		blueSoldiers[i]->sprite.down = Containers::texture_table["bs_downRunTex"];
		blueSoldiers[i]->sprite.left = Containers::texture_table["bs_leftRunTex"];
		blueSoldiers[i]->sprite.right = Containers::texture_table["bs_rightRunTex"];

		blueSoldiers[i]->sprite.id_up = Containers::texture_table["bs_upIdleTex"];
		blueSoldiers[i]->sprite.id_left = Containers::texture_table["bs_leftIdleTex"];
		blueSoldiers[i]->sprite.id_right = Containers::texture_table["bs_rightIdleTex"];
		blueSoldiers[i]->sprite.id_down = Containers::texture_table["bs_downIdleTex"];

		blueSoldiers[i]->sprite.atk_up = Containers::texture_table["bs_upAtkTex"];
		blueSoldiers[i]->sprite.atk_down = Containers::texture_table["bs_downAtkTex"];
		blueSoldiers[i]->sprite.atk_left = Containers::texture_table["bs_leftAtkTex"];
		blueSoldiers[i]->sprite.atk_right = Containers::texture_table["bs_rightAtkTex"];

		blueSoldiers[i]->sprite.hurt_up = Containers::texture_table["bs_upHurtTex"];
		blueSoldiers[i]->sprite.hurt_down = Containers::texture_table["bs_downHurtTex"];
		blueSoldiers[i]->sprite.hurt_left = Containers::texture_table["bs_leftHurtTex"];
		blueSoldiers[i]->sprite.hurt_right = Containers::texture_table["bs_rightHurtTex"];

		blueSoldiers[i]->sprite.death_up = Containers::texture_table["bs_upHurtTex"];
		blueSoldiers[i]->sprite.death_down = Containers::texture_table["bs_downHurtTex"];
		blueSoldiers[i]->sprite.death_left = Containers::texture_table["bs_leftHurtTex"];
		blueSoldiers[i]->sprite.death_right = Containers::texture_table["bs_rightHurtTex"];

		blueSoldiers[i]->offsetBody(0, 60, 60, 75, 50);
		blueSoldiers[i]->setInteractable(true);
		blueSoldiers[i]->setName("blueSoldier");
		blueSoldiers[i]->melee = Containers::Attack_table[blueSoldiers[i]->getKey()];
		blueSoldiers[i]->melee->setDmg(10);
		blueSoldiers[i]->melee->setSpeed(5);
		blueSoldiers[i]->melee->setBaseDir(4);
		blueSoldiers[i]->melee->setCoolDown(60);
		blueSoldiers[i]->melee->setPause(-1);
		blueSoldiers[i]->melee->setDestroy(false);
		blueSoldiers[i]->melee->setKeep(true);
		blueSoldiers[i]->melee->setWidth(50);
		blueSoldiers[i]->melee->setHeight(50);
		blueSoldiers[i]->set_creator_of_melee();
		blueSoldiers[i]->melee->setStaminaCost(90);
		blueSoldiers[i]->setHealth(90);
		blueSoldiers[i]->melee->setStaminaCost(120);
		blueSoldiers[i]->setMaxStamina(300);
		//blueSoldiers[i]->addAttackType(rockThrow);
		blueSoldiers[i]->melee->sprite.setTexture(Containers::texture_table["border"]);
		blueSoldiers[i]->setSpeed(8);
	}
	*/
	//VisibilityGraph graph;
	ai->graph.vertices = vertices;
	ai->graph.obstacles = edges;
	for (Vector2f vert : ai->graph.vertices) {
		
		std::cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		//////std::////cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	bool visible = true;
	for (Vector2f first : ai->graph.vertices) {
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
	}
/*

	yemoja->setName("Yemoja");
	yemoja->setInteractable(true);
	yemoja->setPersonality(30, 80, 80, 50, 50, 50, 80);// uncommented this
	oya->setPersonality(80, 50, 80, 50, 80, 80, 50);// uncommented this

	//staticRec->rel[OYA]->setAffinity(60);// uncommented this
	//staticRec->rel[OYA]->setNotoriety(40);// uncommented this
	//staticRec->rel[OYA]->setStrength(80);// uncommented this

	//staticRec->rel[SHANGO]->setAffinity(60);//added this
	//staticRec->rel[SHANGO]->setNotoriety(40);//added this
	//staticRec->rel[SHANGO]->setStrength(80);//added this

	//staticRec->rel[OYA]->setAffEstimate(60);// uncommented this
	//staticRec->rel[OYA]->setNotorEstimate(70);// uncommented this
	//staticRec->rel[OYA]->setStrEstimate(40);// uncommented this

	//staticRec->rel[SHANGO]->setAffEstimate(60);//added this
	//staticRec->rel[SHANGO]->setNotorEstimate(70);//added this
	//staticRec->rel[SHANGO]->setStrEstimate(40);//added this


	//*oya = *staticRec;
	//oya->setSpeed(5);
	oya->setName("Oya");
	oya->name = OYA;
	oya->offsetBody(0, 60, 60, 75, 50);
	yemoja->offsetBody(0, 60, 60, 75, 50);

	// SET UP RELATIONSHIP REFERENCE FOR YEMOJA 
	std::unordered_map<int, Relationship*> yemojaRelRef;
	yemojaRelRef[1] = new Relationship();
	yemojaRelRef[2] = new Relationship();
	yemojaRelRef[3] = new Relationship();

	std::unordered_map<int, Relationship*> OyaRelRef;
	OyaRelRef[1] = new Relationship();
	OyaRelRef[2] = new Relationship();
	OyaRelRef[3] = new Relationship();

	std::unordered_map<int, Relationship*> shangoRel;
	shangoRel[1] = new Relationship();
	shangoRel[2] = new Relationship();
	shangoRel[3] = new Relationship();

	Alex->rel = shangoRel;

	yemoja->rel = yemojaRelRef;
	oya->rel = OyaRelRef;

	ActionConfig::import_config(gameplay_functions, tBuffer, yemoja);
	ActionConfig::import_config(gameplay_functions, tBuffer, oya);

	Planner* YemojaPlanner = new Planner(yemoja);
	Planner* OyaPlanner = new Planner(oya);
	AIController::set_plan(YEMOJA, YemojaPlanner);
	AIController::set_plan(OYA, OyaPlanner);
	
	Action* test_ally = new Action(nullptr, nullptr, nullptr, 10, 1, "Create Alliance", "execute_train");
	Action* test_train = new Action(yemoja, oya, nullptr, 10, 1, "Conquer", "execute_conquer");

	RelPrecon* prec = new RelPrecon(Preconditions::AFF, 60);
	RelPost* post = new RelPost(Postcondition::STR, 10);
	RelPrecon* prec1 = new RelPrecon(Preconditions::AFF, 30);
	RelPost* post1 = new RelPost(Postcondition::STR, 15);
	RelPost* post2 = new RelPost(Postcondition::AFF, 15);
	
	
	test_ally->req_preconds.push_back(std::make_shared<RelPrecon>(*prec));
	test_ally->doer_succ_postconds.push_back(std::make_shared<RelPost>(*post));
	
	test_train->req_preconds.push_back(std::make_shared<RelPrecon>(*prec1));
	test_train->doer_succ_postconds.push_back(std::make_shared<RelPost>(*post1));
	test_train->doer_succ_postconds.push_back(std::make_shared<RelPost>(*post2));
*/
	
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	//////////////////                                                 ////////////////////////
	//////////////////             INIT CALLS FOR QUESTS               ////////////////////////
	//////////////////                                                 ////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	
	// THIS IS BEING RESET IN THE GAME LOOP. planner->get_current_action returns nullptr*/
	
	/*
	AIController::generate_end_state(YEMOJA, OYA);
	AIController::init_plans();
	*/


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

	ai->start = yemoja->getLoc();
	ai->goal = { 1100.00,1100.00 };

	ai->graph.insert(ai->start);
	//ai->graph.insert(ai->goal);

	yemoja->destination = { 4600.00,3600.00 };
	ai->graph.insert(yemoja->destination);
	ai->graph.insert(Vector2f(5000.00, 4100.00));
	ai->graph.insert(Vector2f(4600.00, 3600.00));
	ai->graph.insert(Vector2f(4500.00, 4000.00));
	ai->graph.insert(Vector2f(5650.00, 3700.00));
	for (Vector2f vert : ai->graph.vertices) {
		//////std::////cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		//////std::////cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	ai->graph._print();

	ai->astar_search(yemoja);
	// gameplay_functions->get_path(staticRec); //Generate the waypoints to the destination

	yemoja->setMode(WANDER);
	short M = GetKeyState('M') >> 15;
/*
	yemoja->setMode(WANDER);
	short M = GetKeyState('M') >> 15;
	Party::grave->set_perm(true);
	Party* party = new Party();
	//Party* party2 = new Party();
	Party* party3 = new Party();
	Party* party4 = new Party();
	party->addToParty(Alex, true);
	for (int i = 0; i < silverSoldier.size(); i++) {
		party4->addToParty(silverSoldier[i], false);
	}
	for (int i = 0; i < blueSoldiers.size(); i++) {
		party3->addToParty(blueSoldiers[i], false);
	}
	party3->addToParty(yemoja, true);
	party4->addToParty(oya, true);
	Village* v1 = new Village();
	//Village* v2 = new Village();
	Village* v3 = new Village();
	Village* v4 = new Village();
	v1->set_village_location(Alex->getLoc());
	//v2->set_village_location({ 6030, 4000 });
	v3->set_village_location(yemoja->getLoc());
	v4->set_village_location(oya->getLoc());
	v1->add_member(Alex);
	for (int i = 0; i < silverSoldier.size(); i++) {
		v4->add_member(silverSoldier[i]);
	}
	for (int i = 0; i < blueSoldiers.size(); i++) {
		v3->add_member(blueSoldiers[i]);
	}
	v3->add_member(yemoja);
	v4->add_member(oya);
	v1->leader = Alex;
	v3->leader = yemoja;
	v4->leader = oya;
	//v2->leader = oya;
	//v4->defenders->addToParty(oya, true);
	Alliance* a1 = new Alliance(v1);
	//Alliance* a2 = new Alliance(v2);
	Alliance* a3 = new Alliance(v3);
	Alliance* a4 = new Alliance(v4);
	v1->addToParties(party);
	//v2->addToParties(party2);
	v3->addToParties(party3);
	v4->addToParties(party4);
	//new War(v1,v2);
	//a1->add_alliance_to_alliance(v3->get_alliance());
	//if (blueSoldiers.size() > 0)party2->set_defend(blueSoldiers[0]->getLoc());
	//party2->setMode(Party::MODE_DEFEND);
	//party3->set_defend(staticRec->getLoc());
	//party3->setMode(Party::MODE_ATTACK);

	Alliance::update_enemies();
*/

	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	clock_t start_tick, current_ticks, delta_ticks;
	clock_t fps = 0;
	int fs = 120; //120
	int wait_time = fs * 3; //always wait 3 seconds	
	int count = 0;
	int state = 0;
	bool start = true;
	float shouldExit = -3000;
	int last_avg = 0;
	int total_fps = 0;

	vector<Soldier*> soldiers_list;
	soldiers_list.push_back(yemoja);
	soldiers_list.push_back(oya);
	for (auto itr : Containers::soldier_table) {
		soldiers_list.push_back(itr.second);
	}

	//for (int i = 0; i < silverSoldier.size(); i++) {
	//	soldiers_list.push_back(silverSoldier[i]);
	//}

	/*std::thread AI([=]() {
		while (GameWindow::isRunning()) {
			combatControl->updateSoliderStatus();
			combatControl->checkParties();
			for (int i = 0; i < soldiers_list.size(); i++) {
				combatControl->update_soldier(soldiers_list[i], state);
			}
		}
	});*/

/*
	t0.join();

*/
  Tutorial::launchStage(Tutorial::Stage::GAME_START, *iController, true);

	current_game_state = game_state::main_menu;

	//insert all of the immovable objects into the quad tree
	//_QuadTree->clear();
	//cout << "tree size is  " << _QuadTree->treeSize() << endl;
	for (int i = 0; i < recVec.size(); i++) {
		if (recVec[i]->getName() == "Oasis_Platform" || recVec[i]->getName() == "JungleVillage") largeStruct->push_back(recVec[i]);
		//_QuadTree->Insert(recVec[i]);	//insert all obj into tree
	}

	grid_worldobj->insert_worldobj_to_grid(recVec);
	grid_worldobj->insert_worldobj_to_grid(movVec);

	cout << "tree size is  " << _QuadTree->treeSize() << endl;
	cout << "size of recvec is " << recVec.size() << endl;
	cout << "size of largestruct is " << largeStruct->size() << endl;
	for (auto it : *largeStruct) cout << (it)->getName() << endl;

	if (PRELOAD_TEX) t0.join();

	while (GameWindow::isRunning()) {
		while (current_game_state == game_state::main_menu) {
			cout << "Current game state: main_menu" << endl;
			if (iController->current_game_state != game_state::main_menu) {
				iController->current_game_state = current_game_state;
			}

			if (shouldExit > 0) {
				_CrtDumpMemoryLeaks();
				return;
			}
			
			start_tick = clock();

			gameplay_functions->drawTut(Alex);

			iController->InputCheck();
			tBuffer->run();

			if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks)
				Sleep((1000 / fs) - (clock() - start_tick));
			}
			delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
			if (delta_ticks > 0) {
				fps = CLOCKS_PER_SEC / delta_ticks;
			}
			HUD::FPS = fps;
			//cout << "FPS: " << fps << endl;

			current_game_state = iController->current_game_state;
			//if(t0.joinable)t0.join();
		}
		while (current_game_state == game_state::in_game) {
      cout << "Current game state: in_game" << endl;
			if (iController->current_game_state != game_state::in_game) {
				iController->current_game_state = current_game_state;
			}

			if (shouldExit > 0) {
				_CrtDumpMemoryLeaks();
				return;
			}

			if (start) {
				gameplay_functions->change_song("Change", nullptr, RegionState::next_region.getRTheme(),RegionState::soundType::region_music);
				start = !start;
			}

      if(!Tutorial::isAnyStageActive()) {
        if(!Tutorial::isStageComplete(Tutorial::Stage::INTRO01))
          Tutorial::launchStage(Tutorial::Stage::INTRO01, *iController, true);
        else if(!Tutorial::isStageComplete(Tutorial::Stage::INTRO02))
          Tutorial::launchStage(Tutorial::Stage::INTRO02, *iController, true);
      }

			//Audio State code. might be moved into RegionState itself

			//commented out for demo
			/*if (Alex->getX() > 660 && Alex->getX() < 10847.5) { //Ogun Desert
			if (Alex->getY() < 3523.33) {
			if (RegionState::current_region == *Desert)
			RegionState::next_region = *Marsh;

			}
			else {
			if (RegionState::current_region == *Marsh) {
			RegionState::next_region = *Desert;
			}
			}
			}
			if (Alex->getX() > 10847.5 && Alex->getX() < 12395.5) {
			if (Alex->getY() < 14441) {
			if (RegionState::current_region == *Jungle)
			RegionState::next_region = *Mountain;
			}
			else {
			if (RegionState::current_region == *Mountain) {
			RegionState::next_region = *Jungle;
			}
			}
			}
			if (Alex->getX() > 660 && Alex->getX() < 25000) {
			if (Alex->getY() < 5132.23) {

			if (RegionState::current_region == *Mountain) {
			RegionState::next_region = *Marsh;
			}
			}
			else {
			if (RegionState::current_region == *Marsh)
			RegionState::next_region = *Mountain;
			}
			}
			if (Alex->getX() > 3479.67 && Alex->getX() < 10847.5) {
			if (Alex->getY() < 17000.7) {
			if (RegionState::current_region == *Jungle)
			RegionState::next_region = *Desert;
			}
			else {
			if (RegionState::current_region == *Desert) {
			RegionState::next_region = *Jungle;
			}
			}
			}*/

			//only 3 regions for demo
			if (Alex->getX() > 660 && Alex->getX() < 25000) { //Ogun Desert
				if (Alex->getY() < 3523.33) {
					if (RegionState::current_region == *RegionState::regions[RegionState::DESERT])
						RegionState::next_region = *RegionState::regions[RegionState::MARSH];

				}
				else {
					if (RegionState::current_region == *RegionState::regions[RegionState::MARSH]) {
						RegionState::next_region = *RegionState::regions[RegionState::DESERT];
					}
				}
			}
			if (Alex->getX() > 600 && Alex->getX() < 25000) {
				if (Alex->getY() < 20000.7) {
					if (RegionState::current_region == *RegionState::regions[RegionState::JUNGLE])
						RegionState::next_region = *RegionState::regions[RegionState::DESERT];
				}
				else {
					if (RegionState::current_region == *RegionState::regions[RegionState::DESERT]) {
						RegionState::next_region = *RegionState::regions[RegionState::JUNGLE];
					}
				}
			}
			if (!(RegionState::current_region == RegionState::next_region)) {
				RegionState::switch_music = true;
			}

			if (RegionState::switch_music) {
				if (RegionState::in_village) {

					gameplay_functions->change_song("Change", RegionState::current_region.getRTheme(), RegionState::current_region.getVTheme(), RegionState::soundType::theme_music);
					RegionState::switch_music = false;
				}
				else {
					gameplay_functions->change_song("Change", RegionState::current_region.getRTheme(), RegionState::next_region.getRTheme(), RegionState::soundType::region_music);
					//iController->current_region = current_region;
					RegionState::current_region = RegionState::next_region;

					//current_region->getRTheme(), next_region->getRTheme()
					RegionState::switch_music = false;
				}

			}
			start_tick = clock();
			if (!MAP_EDITOR) {
				//_QuadTree->clearMovable();
				//grid_worldobj->clear_and_reinsert(movVec);
				//vector<WorldObj*> temp = { Alex };
				//grid_worldobj->clear_and_reinsert(temp);
			}
			else {
				//_QuadTree->clear();
				grid_worldobj->clear_and_reinsert(movVec);
			}
			//grid->clear();
			//grid->insert_objs_to_grid(rivObj->getLines());
			Alex->updateCD();
			Alex->effect.sprite.animate();
			Alex->WorldObj::animateObj();

			if (MAP_EDITOR) {
				for (int i = 0; i < recVec.size(); i++) {
					if (recVec[i]->getType() != WorldObj::TYPE_WORLDOBJ) {
						recVec[i]->effect.sprite.animate();
						recVec[i]->WorldObj::animateObj();
					}
					// _QuadTree->Insert(recVec[i]);	//insert all obj into tree
				}

				for (int i = 0; i < movVec.size(); i++) {
					//cout << "movevec item type is " << movVec[i]->getType() << endl;
					if (movVec[i]->getType() != WorldObj::TYPE_WORLDOBJ) {
						movVec[i]->effect.sprite.animate();
						movVec[i]->WorldObj::animateObj();
					}
					//_QuadTree->Insert(movVec[i]);	//insert all obj into tree
				}
			}
			else {
				for (int i = 0; i < recVec.size(); i++) {
					if (recVec[i]->getType() != WorldObj::TYPE_WORLDOBJ) {
						recVec[i]->effect.sprite.animate();
						recVec[i]->WorldObj::animateObj();
					}
					//_QuadTree->Insert(recVec[i]);	//insert all obj into tree
				}
				for (int i = 0; i < movVec.size(); i++) {
					//cout << "movevec item type is " << movVec[i]->getType() << endl;
					if (movVec[i]->getType() != WorldObj::TYPE_WORLDOBJ) {
						movVec[i]->effect.sprite.animate();
						movVec[i]->WorldObj::animateObj();
					}
					//_QuadTree->Insert(movVec[i]);	//insert all obj into tree
				}
				//cout << "inserted into tree " << movVec.size() << " movable objs" << endl;
			}

			state = DialogueController::getState();

			
			/*combatControl->updateSoliderStatus();
			combatControl->checkParties();
			for (int i = 0; i < soldiers_list.size(); i++) {
				combatControl->update_soldier(soldiers_list[i], state);
			}*/

		//	std::thread AI([=]() {
				
		//	});
			//YemojaPlanner->set_current_action(test_train);
			combatControl->checkParties();

			for (int i = 0; i < soldiers_list.size(); i++) {
				combatControl->update_soldier(soldiers_list[i], state);
			}
			questM->update();


			//draw
			if (state == 0) {
				gameplay_functions->draw_frame(Alex);
			}
			//draw
			else if (state > 0) {
				for (auto itr : Containers::hero_table)
				{
					gameplay_functions->stop(itr.second);
				}
				gameplay_functions->drawDiaGui(Alex);
			}

			//run task buffer
			iController->InputCheck();

			//pool.push(test);
			
			cout << "size of buffer is " << tBuffer->queue_buffer.size() << " and physics buffer size is " << tBuffer->physics_buffer.size() << endl;

			//cout << "shango's position BEFORE is at " << Alex->getX() << ", " << Alex->getY() << endl;
			//iterate through physics_buffer

			//while(tBuffer->physics_buffer_isEmpty() == false) {
			//	Task* curr_task = tBuffer->pop_physics();
			//	cout << "num of idle threads is " << pool.n_idle() << endl;
			//	pool.push([&,tBuffer,curr_task](int id){ tBuffer->assignTask(0,curr_task); });
			//}
			//tBuffer->physics_buffer_empty();
			//pool.stop(true);
			//cout << "DONE WITH PHYSICS TASKS" << endl;
			//cout << "shango's position AFTER is at " << Alex->getX() << ", " << Alex->getY() << endl;
			tBuffer->run();

			/////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////
			for (auto iter : yemoja->rel) {
				Relationship* my_rel = iter.second;
				int with_hero = iter.first;

				if (my_rel->isChanged()) {
					//reevaluate goals for with_hero
					AIController::reevaluate_state(YEMOJA, with_hero);
					my_rel->setChanged(false);
				}
			}
			//getting here-------------------------------------------------------------------------***********
			//setting give as quest to false so that the excute runs
			//YemojaPlanner->give_as_quest = false;
//			cout << " first dest is " << staticRec->get_action_destination()->getXloc() << ", " << staticRec->get_action_destination()->getYloc() << endl;
			AIController::execute();
//			cout << "after execute dest is " << staticRec->get_action_destination()->getXloc() << ", " << staticRec->get_action_destination()->getYloc() << endl;
			//AI.join();
//			cout << "after thread join dest is " << staticRec->get_action_destination()->getXloc() << ", " << staticRec->get_action_destination()->getYloc() << endl;
			if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks)
				Sleep((1000 / fs) - (clock() - start_tick));
			}
			delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
			if (delta_ticks > 0) {
				fps = CLOCKS_PER_SEC / delta_ticks;
			}
			HUD::FPS = fps;
			//cout << "FPS: " << fps << endl;
			total_fps += fps;
			frame_count++;
			HUD::AVG = total_fps / frame_count;

			current_game_state = iController->current_game_state;
			//system("PAUSE");
			//Checks if game has reached final states
			//GameState::check_if_end_game(&current_game_state);
			

		}
		while (current_game_state == game_state::pause_menu) {
			for (int i = 0; i < 10; i++) {
				cout << "Press Q to return to game" << endl;

			}
			if (iController->current_game_state != game_state::pause_menu) {
				iController->current_game_state = current_game_state;
			}

			if (shouldExit > 0) {
				_CrtDumpMemoryLeaks();
				return;
			}
			start_tick = clock();

			//draw
			gameplay_functions->drawTut(Alex);

			//run task buffer
			iController->InputCheck();

			tBuffer->run();

			if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks) {www
				Sleep((1000 / fs) - (clock() - start_tick));
			}
			delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
			if (delta_ticks > 0) {
				fps = CLOCKS_PER_SEC / delta_ticks;
			}
			HUD::FPS = fps;
			//total_fps += fps;
			//cout << "FPS: " << fps << endl;

			//frame_count++;
			HUD::AVG = total_fps / frame_count;

			current_game_state = iController->current_game_state;
		}
		while (current_game_state == game_state::victory_menu) {

			if (iController->current_game_state != game_state::victory_menu) {
				iController->current_game_state = current_game_state;
			}

			if (shouldExit > 0) {
				_CrtDumpMemoryLeaks();
				return;
			}
			start_tick = clock();

			//draw
			gameplay_functions->drawTut(Alex);

			//run task buffer
			iController->InputCheck();

			tBuffer->run();

			if (game_ended) {
				break;
			}

			if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks) {www
				Sleep((1000 / fs) - (clock() - start_tick));
			}
			delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
			if (delta_ticks > 0) {
				fps = CLOCKS_PER_SEC / delta_ticks;
			}
			HUD::FPS = fps;
			//total_fps += fps;
			//cout << "FPS: " << fps << endl;

			//frame_count++;
			HUD::AVG = total_fps / frame_count;

			current_game_state = iController->current_game_state;

		}
		if (game_ended) {
			break;
		}
	}
	GameWindow::terminate();
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
